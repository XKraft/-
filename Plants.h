#ifndef PLANTS
#define PLANTS
#include <string>
#include"Bullet.h"
class Plants
{
public:
	Plants();
	//用于从商店设置各种植物的参数
	void PlantSet(const char* _name, int _hp, int _cost, int _buycd, int _functioncd, bool _shoot, bool _addsunlight);
	//得到植物的名字
	const char* GetPlantName();
	//得到植物的购买冷却时间
	int GetPlantBuyCD();
	//得到植物购买所需的花费
	int GetPlantCost();
	//得到植物的血量
	int GetPlantHP();
	//实现对=的重载，分别植物的种植时从商店的模板赋值
	Plants& operator = (const Plants& p);
	//植物被僵尸吃，扣除hp，如果植物被吃掉放回true
	bool Ate(int atk);
	//如果植物具有发射豌豆功能，则调用发射豌豆
	Bullet* Shoot(int x, int y);
	//如果植物具有产生阳光功能，则调用产生阳光
	int AddSunlight();
private:
	const char* name;//植物名字
	int hp;//植物血量
	int cost;//植物所需的阳光
	int buycd;//植物的购买冷却时间
	int functioncd;//植物的功能函数执行的冷却时间
	clock_t c;//植物的计时器
	bool shoot;//植物是否具有发射功能
	bool addsunlight;//植物是否具有产生阳光的功能
};
#endif // !PLANTS

