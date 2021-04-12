#include"Plants.h"
Plants::Plants()
{
	name = NULL;
	hp = 0;
	cost = 0;
	buycd = 0;
	functioncd = 0;
	shoot = false;
	addsunlight = false;
	c = clock();
}
void Plants::PlantSet(const char* _name, int _hp, int _cost, int _buycd, int _functioncd, bool _shoot, bool _addsunlight)
{
	name = _name;
	hp = _hp;
	cost = _cost;
	buycd = _buycd;
	functioncd = _functioncd;
	shoot = _shoot;
	addsunlight = _addsunlight;
}
const char* Plants::GetPlantName()
{
	return name;
}
int Plants::GetPlantBuyCD()
{
	return buycd;
}
int Plants::GetPlantCost()
{
	return cost;
}
int Plants::GetPlantHP()
{
	return hp;
}
Plants& Plants::operator = (const Plants& p)
{
	name = p.name;
	hp = p.hp;
	cost = p.cost;
	buycd = p.buycd;
	functioncd = p.functioncd;
	c = p.c;
	shoot = p.shoot;
	addsunlight = p.addsunlight;
	return *this;
}
bool Plants::Ate(int atk)
{
	hp -= atk;
	if (hp <= 0)
	{
		name = nullptr;
		hp = 0;
		cost = 0;
		buycd = 0;
		functioncd = 0;
		shoot = false;
		addsunlight = false;
		c = clock();
		return true;
	}
	return false;
}
Bullet* Plants::Shoot(int x, int y)
{
	if (shoot && SandGlass(c, functioncd))
	{
		Bullet* p = new Bullet(x, y);
		if (!p) exit(-1);
		return p;
	}
	return NULL;
}
int Plants::AddSunlight()
{
	if (addsunlight && SandGlass(c, functioncd))
	{
		return 25;
	}
	return 0;
}