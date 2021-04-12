#include"Grid.h"
Grid::Grid()
{
	x = 0;
	y = 0;
	zombie_nums = 0;
	is_cursor = false;
	is_grow = true;
}
//绘制格子中的内容，分为只有植物、只有一只僵尸、多只僵尸、植物加僵尸和光标是否在这
void Grid::DrawGrid()
{
	for (int i = 1; i <= 4; ++i)
	{
		CursorSetXY(x + 1, y + i);
		cout << "            ";
	}
	if (is_cursor)
	{
		SetPrintColor(f_red);
		for (int i = 0; i < GRID_HEIGHT; ++i)
		{
			CursorSetXY(x, y + i);
			for (int j = 0; j < GRID_WIDTH; ++j)
				if (i % (GRID_HEIGHT - 1) == 0)
					cout << "#";
				else
					if (j % (GRID_WIDTH - 1) == 0)
						cout << "#";
					else
						cout << " ";
			
		}
		SetPrintColor(reset);
	}
	if (is_grow)
	{
		
		if (zombie_nums == 1)
		{
			CursorSetXY(x + 1, y + 2);
			cout << zombies.front()->GetZombieName();
			CursorSetXY(x + 1, y + 3);
			cout << "HP:" << zombies.front()->GetZombieHP();
		}
		if (zombie_nums > 1 && zombie_nums <= 3)
		{
			for (int i = 0; i < zombie_nums; ++i)
			{
				CursorSetXY(x + 1, y + i + 1);
				cout << zombies[i]->GetZombieName();
			}
		}
		if (zombie_nums > 3)
		{
			for (int i = 0; i < 3; ++i)
			{
				CursorSetXY(x + 1, y + i + 1);
				cout << zombies[i]->GetZombieName();
			}
			CursorSetXY(x + 1, y + 4);
			cout << "僵尸 ×" << zombie_nums;
		}
	}
	else
	{
		if (zombie_nums)
		{
			CursorSetXY(x + 1, y + 1);
			cout << "HP:" << plant.GetPlantHP();
			CursorSetXY(x + 1, y + 2);
			cout << plant.GetPlantName();
			CursorSetXY(x + 1, y + 3);
			cout << zombies.front()->GetZombieName();
			CursorSetXY(x + 1, y + 4);
			cout << "僵尸 ×" << zombie_nums;
		}
		else
		{
			CursorSetXY(x + 1, y + 2);
			cout << plant.GetPlantName();
			CursorSetXY(x + 1, y + 3);
			cout << "HP:" << plant.GetPlantHP();
		}
	}
}
//改变各种的光标状态
void Grid::ChangCursor()
{
	if (is_cursor)
		is_cursor = false;
	else
		is_cursor = true;
}
//种植植物
void Grid::GrowPlant(Plants& p)
{
	plant = p;
	is_grow = false;
}
//得到是否可以种植
bool Grid::Is_Grow()
{
	return is_grow;
}
//设定网格子坐标
void Grid::SetGridXY(int _x, int _y)
{
	x = _x;
	y = _y;
}
//放回格子的储存僵尸的容器
vector<Zombies*> Grid::GetVector()
{
	return zombies;
}
//返回当前格子是否有僵尸或者植物
bool Grid::ExistZombieOrPlant()
{
	if (zombie_nums || !is_grow)
		return true;
	else
		return false;
}
//返回当前格子是否有僵尸和植物
bool Grid::ExistZombieAndPlant()
{
	if (zombie_nums && !is_grow)
		return true;
	else
		return false;
}