#ifndef ZOMBIES
#define ZOMBIES
#include"Global.h"

class Zombies
{
public:
	Zombies();
	Zombies(const Zombies& z);
	//用于在game类中设置所有僵尸的数值
	void SetZombie(string _name, int _hp, int _atk, int _speed, int _score);
	//得到僵尸的名字
	string GetZombieName();
	//得到僵尸的血量
	int GetZombieHP();
	//僵尸本次循环僵尸是否能够移动
	bool ZombieMove();
	//僵尸本次循环僵尸是否能够攻击植物
	bool ZombieEat();
	//在产生僵尸时初始化僵尸的计时器
	clock_t& GetMoveCounter();
	clock_t& GetEatCounter();
	//得到僵尸的速度
	int GetZombieSpeed();
	//得到僵尸的攻击力
	int GetZombeAtk();
	//得到僵尸被打死所能得到的分数
	int GetZombieScore();
	//修改植物是否可以移动的状态
	bool& GetMove();
	//僵尸被攻击的处理函数
	bool BeAttacked(int atk);
private:
	string name;//僵尸名字
	int hp;//僵尸血量
	int atk;//僵尸攻击力
	int speed;//僵尸速度
	int score;//僵尸分数
	bool move;//僵尸是否可以移动
	clock_t move_counter;//僵尸的移动计时
	clock_t eat_counter;//僵尸的攻击计时
};
#endif // !ZOMBIES