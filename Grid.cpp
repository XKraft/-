#include"Grid.h"
Grid::Grid()
{
	x = 0;
	y = 0;
	zombie_nums = 0;
	is_cursor = false;
	is_grow = true;
}
//���Ƹ����е����ݣ���Ϊֻ��ֲ�ֻ��һֻ��ʬ����ֻ��ʬ��ֲ��ӽ�ʬ�͹���Ƿ�����
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
			cout << "��ʬ ��" << zombie_nums;
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
			cout << "��ʬ ��" << zombie_nums;
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
//�ı���ֵĹ��״̬
void Grid::ChangCursor()
{
	if (is_cursor)
		is_cursor = false;
	else
		is_cursor = true;
}
//��ֲֲ��
void Grid::GrowPlant(Plants& p)
{
	plant = p;
	is_grow = false;
}
//�õ��Ƿ������ֲ
bool Grid::Is_Grow()
{
	return is_grow;
}
//�趨����������
void Grid::SetGridXY(int _x, int _y)
{
	x = _x;
	y = _y;
}
//�Żظ��ӵĴ��潩ʬ������
vector<Zombies*> Grid::GetVector()
{
	return zombies;
}
//���ص�ǰ�����Ƿ��н�ʬ����ֲ��
bool Grid::ExistZombieOrPlant()
{
	if (zombie_nums || !is_grow)
		return true;
	else
		return false;
}
//���ص�ǰ�����Ƿ��н�ʬ��ֲ��
bool Grid::ExistZombieAndPlant()
{
	if (zombie_nums && !is_grow)
		return true;
	else
		return false;
}