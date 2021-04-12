#ifndef STORE
#define STORE
#include"Global.h"
#include"Grid.h"
const int PLANT_KINDS = 2;//植物的种类数
class Store
{
public:
	Store();
	//绘制商店
	void DrawStore();
	//移动光标
	void MoveCursor(int dy);
	//当进入选择种植地点时进入隐藏商店光标状态
	void HideCursor();
	//重置光标
	void ResetCurset();
	//让cd归零，开始计时
	void RefreshBuyCD();
	//增加cd的计时
	void AddBuyCD();
	//检测冷却时间是否结束
	bool CDIsOk();
	//得到光标所指向的植物的所应花费发阳光数
	int GetCost();
	//售卖植物
	Plants& SellPlant();
private:
	Plants plant_card[PLANT_KINDS];//植物的模板
	bool is_cursor[PLANT_KINDS];//光标是否在这
	int buy_cd[PLANT_KINDS];//每种植物的cd
	int cursor;//光标位置
};
#endif // !STORE

