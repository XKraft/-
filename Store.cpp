#include"Store.h"
Store::Store()
{
	//建立植物模板
	plant_card[0].PlantSet("豌豆射手", 100, 100, 50, 15, true, false);
	plant_card[1].PlantSet("向日葵", 100, 50, 50, 60, false, true);
	//初始化光标状态
	is_cursor[0] = true;
	is_cursor[1] = false;
	//初始化植物cd
	buy_cd[0] = plant_card[0].GetPlantBuyCD();
	buy_cd[1] = plant_card[1].GetPlantBuyCD();
	//初始化光标位置
	cursor = 0;
}
void Store::DrawStore()
{
	CursorSetXY(0, STORE_LINES);
	for (int i = 0; i < PLANT_KINDS; ++i)
	{
		if (is_cursor[i])
		{
			SetPrintColor(b_red);
			cout << plant_card[i].GetPlantName() << " " << plant_card[i].GetPlantCost() << " ";
			SetPrintColor(reset);
		}
		else
			cout << plant_card[i].GetPlantName() << " " << plant_card[i].GetPlantCost() << " ";
		if (buy_cd[i] != plant_card[i].GetPlantBuyCD())//如果cd没好则输出已加载量
			cout << (int)((buy_cd[i] / (double)plant_card[i].GetPlantBuyCD()) * 100.0) << "%";
		cout << "          ";//覆盖上次cd的显示
		cout << endl;
	}
}
bool Store::CDIsOk()
{
	if (buy_cd[cursor] == plant_card[cursor].GetPlantBuyCD())
		return true;
	else
		return false;
}
void Store::MoveCursor(int dy)
{
	if (cursor + dy < 0 || cursor + dy >= PLANT_KINDS)
		dy = 0;
	is_cursor[cursor] = false;
	cursor += dy;
	is_cursor[cursor] = true;
}
void Store::HideCursor()
{
	is_cursor[cursor] = false;
}
void Store::ResetCurset()
{
	is_cursor[cursor] = false;
	cursor = 0;
	is_cursor[cursor] = true;
}
void Store::AddBuyCD()
{
	static clock_t c = clock();
	if (SandGlass(c, 1))//每100mscd增加1，也就是总的冷却时间为 cd/10 s
	{
		for (int i = 0; i < PLANT_KINDS; ++i)
			if (buy_cd[i] < plant_card[i].GetPlantBuyCD())
				++buy_cd[i];
	}
}
void Store::RefreshBuyCD()
{
	buy_cd[cursor] = 0;
}
int Store::GetCost()
{
	return plant_card[cursor].GetPlantCost();
}
//提供植物的模板数据用于初始化植物对象
Plants& Store::SellPlant()
{
	return plant_card[cursor];
}