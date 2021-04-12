#include"Game.h"
Game::Game()
{
	state = BUYING;//初始化游戏状态
	sunlight = 0;//初始化阳光
	//初始网格及网格坐标
	grid = new Grid[STAGE_LINES * STAGE_WIDTH];
	if (!grid) exit(-1);
	for (int i = 0; i < STAGE_LINES; ++i)
		for (int j = 0; j < STAGE_COLS; ++j)
			grid[j + i * STAGE_COLS].SetGridXY(j * (GRID_WIDTH - 1), i * (GRID_HEIGHT - 1));
	
	cursor = 0;//初始化光标

	score = 0;//初始化游戏分数
	//游戏僵尸的数据模板
	_zombies[0].SetZombie("普通僵尸", 200, 25, 80, 25);
	_zombies[1].SetZombie("路障僵尸", 570, 25, 80, 40);
	//初始化每行是否有僵尸，全部为false
	exist_zombie[0] = false;
	exist_zombie[1] = false;
	exist_zombie[2] = false;
}
Game::~Game()
{
	delete[]grid;//归还内存
}
//游戏的主循环
void Game::MainLoop()
{
	HideCursor();//隐藏光标
	SetCMDSize(CMD_COLS, CMD_LINES);//设置命令行尺寸
	while (true)//主循环
	{
		Draw();//绘制界面
		if (EndGame())//判断游戏是否结束
			break;

		GetKey();//实时获得输入
		store.AddBuyCD();//刷新商店cd

		AddSunlight();//增加阳光
		AddScore();//增加分数

		AddZombie();//产生僵尸
		MoveZombie();//移动僵尸
		AtkPlant();//攻击植物

		RefreshExist();//刷新每行是否存在僵尸的状态
		PeaShoot();//发射豌豆
		MoveBullets();//移动豌豆
		AtkZombie();//攻击僵尸
	}
}
void Game::DrawStage()
{
	CursorSetXY(0, 0);
	for (int i = 0; i < STAGE_HEIGHT; ++i)
	{
		CursorSetXY(0, i);
		for (int j = 0; j < STAGE_WIDTH; ++j)
		{
			if (i % (GRID_HEIGHT - 1) == 0)
				cout << "#";
			else
			{
				if (j % (GRID_WIDTH - 1) == 0)
					cout << "#";
				else
					CursorSetXY(j + 1, i);
			}
		}
		cout << endl;
	}

	CursorSetXY(0, SUN_SCORE - 1);
	cout << "'w''s''a''d'控制光标移动，选择好植物后按'b'购买，再选择种植位置，回车确定种植，'x'取消种植" << endl;
	cout << "####################################################################" << endl;
	cout << "阳光：" << sunlight << "    " << "分数" << score << endl;
	cout << "####################################################################" << endl;
}
void Game::DrawBullets()
{
	for (int i = 0; i < STAGE_LINES; ++i)
		for (int j = 0; j < (int)bullets[i].size(); ++j)
			if(!grid[CoordCMDtoGRID(bullets[i][j]->GetBulletX(), bullets[i][j]->GetBulletY())].ExistZombieOrPlant())//当格子存在僵尸或者植物时不显示子弹
				bullets[i][j]->DrawBullet();
}
//绘制游戏画面
void Game::Draw()
{
	static clock_t c = clock();
	if (SandGlass(c, 2))
	{
		DrawStage();

		store.DrawStore();

		for (int i = 0; i < STAGE_LINES * STAGE_COLS; ++i)
			grid[i].DrawGrid();

		DrawBullets();
	}
}
//获得用户输入并做出反应
void Game::GetKey()
{
	char ch = ' ';
	if (_kbhit())
		ch = _getch();
	if (ch >= 'A' && ch <= 'Z')//预防用户使用大写输入，进行大小写转化处理
		ch = ch - ('A' - 'a');
	if(state == BUYING)
		switch (ch)
		{
		case 'w':
			store.MoveCursor(-1);break;
		case 's':
			store.MoveCursor(1);break;
		case 'b':
			if (sunlight >= store.GetCost() && store.CDIsOk())
			{
				state = SELECT;
				store.HideCursor();
				grid[cursor].ChangCursor();
			}break;
		}
	if(state == SELECT)
		switch (ch)
		{
		case 'w':
			MoveGridCursor(0, -1);break;
		case 's':
			MoveGridCursor(0, 1);break;
		case 'a':
			MoveGridCursor(-1, 0);break;
		case 'd':
			MoveGridCursor(1, 0);break;
		case 'x':
			state = BUYING;
			grid[cursor].ChangCursor();
			store.ResetCurset();break;
		case 13:
			if (grid[cursor].Is_Grow())
			{
				sunlight -= store.GetCost();
				state = BUYING;
				store.RefreshBuyCD();
				grid[cursor].GrowPlant(store.SellPlant());
				grid[cursor].ChangCursor();
				store.ResetCurset();
			}
		}
}
//实现阳光增加
void Game::AddSunlight()
{
	static clock_t c = clock();
	if (SandGlass(c, 60))
		sunlight += 25;
	for (int i = 0; i < STAGE_LINES; ++i)
		for (int j = 0; j < STAGE_COLS; ++j)
		{
			sunlight += grid[CoordTtoO(j, i)].plant.AddSunlight();
		}
}
//实现分数随游戏时间增加
void Game::AddScore()
{
	static clock_t c = clock();
	if (SandGlass(c, 10))
		score += 1;
}
//实现选择光标移动
void Game::MoveGridCursor(int dx, int dy)
{
	int x = cursor % STAGE_COLS;
	int y = cursor / STAGE_COLS;
	if (x + dx < 0 || x + dx >= STAGE_COLS)
		dx = 0;
	if (y + dy < 0 || y + dy >= STAGE_LINES)
		dy = 0;
	grid[cursor].ChangCursor();
	cursor = x + dx + (y + dy) * STAGE_COLS;
	grid[cursor].ChangCursor();
}
//实现更加游戏时间进行不同的投放僵尸方式
void Game::AddZombie()
{
	static clock_t c = clock();
	clock_t t = clock() / CLOCKS_PER_SEC;
	unsigned seed = (unsigned)clock() + (unsigned)time(0);
	srand(seed);
	if (t <= 18)//游戏开始18秒内不产生僵尸
		return;
	if (t > 18 && t <= 78)//18秒到78秒只产生普通僵尸
		if (SandGlass(c, 100))
		{
			//srand((unsigned)(0));
			int y = rand() % 3;
			Zombies* p = new Zombies(_zombies[0]);
			p->GetMoveCounter() = clock();
			grid[y * STAGE_COLS + STAGE_COLS - 1].zombies.push_back(p);
			++grid[y * STAGE_COLS + STAGE_COLS - 1].zombie_nums;
			return;
		}
	if (t > 78 && t <= 98)//78秒到98秒产生路障僵尸
		if (SandGlass(c, 90))
		{
			//srand((unsigned)time(0));
			int y = rand() % 3;
			Zombies* p = new Zombies(_zombies[1]);
			p->GetMoveCounter() = clock();
			grid[y * STAGE_COLS + STAGE_COLS - 1].zombies.push_back(p);
			++grid[y * STAGE_COLS + STAGE_COLS - 1].zombie_nums;
			return;
		}
	if (t > 98 && t <= 103)//98秒到103秒不产生僵尸，给玩家一个缓冲
		return;
	if (t > 103)//103秒后最大难度
		if (SandGlass(c, 25))
		{
			//srand((unsigned)time(0));
			int kind = rand() % 2;
			int y = rand() % 3;
			Zombies* p = new Zombies(_zombies[kind]);
			p->GetMoveCounter() = clock();
			grid[y * STAGE_COLS + STAGE_COLS - 1].zombies.push_back(p);
			++grid[y * STAGE_COLS + STAGE_COLS - 1].zombie_nums;
		}
}	
//实现移动僵尸
void Game::MoveZombie()
{
	for(int i = 0; i < STAGE_LINES; ++i)
		for (int j = 0; j < STAGE_COLS; ++j)
		{
			for(int m = 0; m < (int)grid[CoordTtoO(j, i)].zombies.size(); )
			{
				if (grid[CoordTtoO(j, i)].zombies[m]->ZombieMove())
				{
					if (j == 0)//僵尸到达了屋内
					{
						state = GAMEOVER;
						return;
					}
					Zombies* p = grid[CoordTtoO(j, i)].zombies[m];
					grid[CoordTtoO(j, i)].zombies.erase(grid[CoordTtoO(j, i)].zombies.begin() + m);
					grid[CoordTtoO(j - 1, i)].zombies.push_back(p);
					--grid[CoordTtoO(j, i)].zombie_nums;
					++grid[CoordTtoO(j - 1, i)].zombie_nums;
				}
				else
					++m;
			}
		}
}
//游戏结束
bool Game::EndGame()
{
	if (state == GAMEOVER)
	{
		system("cls");
		CursorSetXY(0, 0);
		SetPrintColor(f_red);
		cout << "僵尸吃掉了你的脑子！！！" << endl;
		cout << "分数：" << score;
		SetPrintColor(reset);
		return true;
	}
	return false;
}
//刷新每行的exist_zombies的状态
void Game::RefreshExist()
{
	for (int i = 0; i < STAGE_LINES; ++i)
	{
		int count = 0;
		for (int j = 0; j < STAGE_COLS; ++j)
			count += grid[i * STAGE_COLS + j].zombie_nums;
		if (count)
			exist_zombie[i] = true;
		else
			exist_zombie[i] = false;
	}
}
//实现豌豆射手发射子弹
void Game::PeaShoot()
{
	for (int i = 0; i < STAGE_LINES; ++i)
		for (int j = 0; j < STAGE_COLS; ++j)
		{
				if (exist_zombie[i])
				{
					Bullet* p = grid[CoordTtoO(j, i)].plant.Shoot(grid[CoordTtoO(j, i)].x + GRID_WIDTH - 1, grid[CoordTtoO(j, i)].y + 2);
					if(p)
						bullets[i].push_back(p);
				}
		}
}
//实现子弹移动
void Game::MoveBullets()
{
	for(int i = 0; i < STAGE_LINES; ++i)
		for (int j = 0; j < (int)bullets[i].size(); )
		{
			if (bullets[i][j]->MoveBullet())
			{
				Bullet* p = bullets[i][j];
				bullets[i].erase(bullets[i].begin() + j);
				delete p;
			}
			else
				++j;
		}
}
//实现豌豆击中僵尸
void Game::AtkZombie()
{
	for (int i = 0; i < STAGE_LINES; ++i)
		for (int j = 0; j < (int)bullets[i].size(); )
		{
			int x = bullets[i][j]->GetBulletX() / GRID_WIDTH;
			if (grid[CoordTtoO(x, i)].zombies.size())
			{
				if (grid[CoordTtoO(x, i)].zombies.front()->BeAttacked(bullets[i][j]->GetBulletAtk()))
				{
					Zombies* p = grid[CoordTtoO(x, i)].zombies.front();
					score += p->GetZombieScore();
					grid[CoordTtoO(x, i)].zombies.erase(grid[CoordTtoO(x, i)].zombies.begin());
					delete p;
					--grid[CoordTtoO(x, i)].zombie_nums;
				}
				Bullet* p = bullets[i][j];
				bullets[i].erase(bullets[i].begin() + j);
				delete p;
			}
			else
				++j;
		}
}
//实现僵尸吃植物
void Game::AtkPlant()
{
	for (int i = 0; i < STAGE_LINES; ++i)
		for (int j = 0; j < STAGE_COLS; ++j)
		{
			if (grid[CoordTtoO(j, i)].ExistZombieAndPlant())
			{
				for (int m = 0; m < grid[CoordTtoO(j, i)].zombie_nums; ++m)//让容器中的僵尸依次啃咬植物
				{
					grid[CoordTtoO(j, i)].zombies[m]->GetMove() = false;
					if(grid[CoordTtoO(j, i)].zombies[m]->ZombieEat())
						if (grid[CoordTtoO(j, i)].plant.Ate(grid[CoordTtoO(j, i)].zombies[m]->GetZombeAtk()))
						{//如果植物被吃掉，让所有僵尸回复能够继续前进的状态
							for (int n = 0; n < grid[CoordTtoO(j, i)].zombie_nums; ++n)
								grid[CoordTtoO(j, i)].zombies[n]->GetMove() = true;
							grid[CoordTtoO(j, i)].is_grow = true;//让格子便会可以种植植物的状态，也就是说明格子没有植物
							break;
						}
				}
			}
		}
}