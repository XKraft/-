#include"Game.h"
Game::Game()
{
	state = BUYING;//��ʼ����Ϸ״̬
	sunlight = 0;//��ʼ������
	//��ʼ������������
	grid = new Grid[STAGE_LINES * STAGE_WIDTH];
	if (!grid) exit(-1);
	for (int i = 0; i < STAGE_LINES; ++i)
		for (int j = 0; j < STAGE_COLS; ++j)
			grid[j + i * STAGE_COLS].SetGridXY(j * (GRID_WIDTH - 1), i * (GRID_HEIGHT - 1));
	
	cursor = 0;//��ʼ�����

	score = 0;//��ʼ����Ϸ����
	//��Ϸ��ʬ������ģ��
	_zombies[0].SetZombie("��ͨ��ʬ", 200, 25, 80, 25);
	_zombies[1].SetZombie("·�Ͻ�ʬ", 570, 25, 80, 40);
	//��ʼ��ÿ���Ƿ��н�ʬ��ȫ��Ϊfalse
	exist_zombie[0] = false;
	exist_zombie[1] = false;
	exist_zombie[2] = false;
}
Game::~Game()
{
	delete[]grid;//�黹�ڴ�
}
//��Ϸ����ѭ��
void Game::MainLoop()
{
	HideCursor();//���ع��
	SetCMDSize(CMD_COLS, CMD_LINES);//���������гߴ�
	while (true)//��ѭ��
	{
		Draw();//���ƽ���
		if (EndGame())//�ж���Ϸ�Ƿ����
			break;

		GetKey();//ʵʱ�������
		store.AddBuyCD();//ˢ���̵�cd

		AddSunlight();//��������
		AddScore();//���ӷ���

		AddZombie();//������ʬ
		MoveZombie();//�ƶ���ʬ
		AtkPlant();//����ֲ��

		RefreshExist();//ˢ��ÿ���Ƿ���ڽ�ʬ��״̬
		PeaShoot();//�����㶹
		MoveBullets();//�ƶ��㶹
		AtkZombie();//������ʬ
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
	cout << "'w''s''a''d'���ƹ���ƶ���ѡ���ֲ���'b'������ѡ����ֲλ�ã��س�ȷ����ֲ��'x'ȡ����ֲ" << endl;
	cout << "####################################################################" << endl;
	cout << "���⣺" << sunlight << "    " << "����" << score << endl;
	cout << "####################################################################" << endl;
}
void Game::DrawBullets()
{
	for (int i = 0; i < STAGE_LINES; ++i)
		for (int j = 0; j < (int)bullets[i].size(); ++j)
			if(!grid[CoordCMDtoGRID(bullets[i][j]->GetBulletX(), bullets[i][j]->GetBulletY())].ExistZombieOrPlant())//�����Ӵ��ڽ�ʬ����ֲ��ʱ����ʾ�ӵ�
				bullets[i][j]->DrawBullet();
}
//������Ϸ����
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
//����û����벢������Ӧ
void Game::GetKey()
{
	char ch = ' ';
	if (_kbhit())
		ch = _getch();
	if (ch >= 'A' && ch <= 'Z')//Ԥ���û�ʹ�ô�д���룬���д�Сдת������
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
//ʵ����������
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
//ʵ�ַ�������Ϸʱ������
void Game::AddScore()
{
	static clock_t c = clock();
	if (SandGlass(c, 10))
		score += 1;
}
//ʵ��ѡ�����ƶ�
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
//ʵ�ָ�����Ϸʱ����в�ͬ��Ͷ�Ž�ʬ��ʽ
void Game::AddZombie()
{
	static clock_t c = clock();
	clock_t t = clock() / CLOCKS_PER_SEC;
	unsigned seed = (unsigned)clock() + (unsigned)time(0);
	srand(seed);
	if (t <= 18)//��Ϸ��ʼ18���ڲ�������ʬ
		return;
	if (t > 18 && t <= 78)//18�뵽78��ֻ������ͨ��ʬ
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
	if (t > 78 && t <= 98)//78�뵽98�����·�Ͻ�ʬ
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
	if (t > 98 && t <= 103)//98�뵽103�벻������ʬ�������һ������
		return;
	if (t > 103)//103�������Ѷ�
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
//ʵ���ƶ���ʬ
void Game::MoveZombie()
{
	for(int i = 0; i < STAGE_LINES; ++i)
		for (int j = 0; j < STAGE_COLS; ++j)
		{
			for(int m = 0; m < (int)grid[CoordTtoO(j, i)].zombies.size(); )
			{
				if (grid[CoordTtoO(j, i)].zombies[m]->ZombieMove())
				{
					if (j == 0)//��ʬ����������
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
//��Ϸ����
bool Game::EndGame()
{
	if (state == GAMEOVER)
	{
		system("cls");
		CursorSetXY(0, 0);
		SetPrintColor(f_red);
		cout << "��ʬ�Ե���������ӣ�����" << endl;
		cout << "������" << score;
		SetPrintColor(reset);
		return true;
	}
	return false;
}
//ˢ��ÿ�е�exist_zombies��״̬
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
//ʵ���㶹���ַ����ӵ�
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
//ʵ���ӵ��ƶ�
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
//ʵ���㶹���н�ʬ
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
//ʵ�ֽ�ʬ��ֲ��
void Game::AtkPlant()
{
	for (int i = 0; i < STAGE_LINES; ++i)
		for (int j = 0; j < STAGE_COLS; ++j)
		{
			if (grid[CoordTtoO(j, i)].ExistZombieAndPlant())
			{
				for (int m = 0; m < grid[CoordTtoO(j, i)].zombie_nums; ++m)//�������еĽ�ʬ���ο�ҧֲ��
				{
					grid[CoordTtoO(j, i)].zombies[m]->GetMove() = false;
					if(grid[CoordTtoO(j, i)].zombies[m]->ZombieEat())
						if (grid[CoordTtoO(j, i)].plant.Ate(grid[CoordTtoO(j, i)].zombies[m]->GetZombeAtk()))
						{//���ֲ�ﱻ�Ե��������н�ʬ�ظ��ܹ�����ǰ����״̬
							for (int n = 0; n < grid[CoordTtoO(j, i)].zombie_nums; ++n)
								grid[CoordTtoO(j, i)].zombies[n]->GetMove() = true;
							grid[CoordTtoO(j, i)].is_grow = true;//�ø��ӱ�������ֲֲ���״̬��Ҳ����˵������û��ֲ��
							break;
						}
				}
			}
		}
}