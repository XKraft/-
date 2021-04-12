#include"Zombies.h"
Zombies::Zombies()
{
	hp = 0;
	atk = 0;
	speed = 0;
	move = true;
	score = 0;
	move_counter = clock();
	eat_counter = clock();
}
Zombies::Zombies(const Zombies& z)
{
	name = z.name;
	hp = z.hp;
	atk = z.atk;
	speed = z.speed;
	score = z.score;
	move = true;
	move_counter = z.move_counter;
	eat_counter = z.eat_counter;
}
void Zombies::SetZombie(string _name, int _hp, int _atk, int _speed, int _score)
{
	name = _name;
	hp = _hp;
	atk = _atk;
	speed = _speed;
	score = _score;
}
string Zombies::GetZombieName()
{
	return name;
}
int Zombies::GetZombieHP()
{
	return hp;
}
bool Zombies::ZombieMove()
{
	if (SandGlass(move_counter, speed) && move)
		return true;
	else
		return false;
}
bool Zombies::ZombieEat()
{
	if (SandGlass(eat_counter, 20))//一秒一口
		return true;
	else
		return false;
}
clock_t& Zombies::GetMoveCounter()
{
	return move_counter;
}
clock_t& Zombies::GetEatCounter()
{
	return eat_counter;
}
int Zombies::GetZombieSpeed()
{
	return speed;
}
int Zombies::GetZombeAtk()
{
	return atk;
}
int Zombies::GetZombieScore()
{
	return score;
}
bool& Zombies::GetMove()
{
	return move;
}
bool Zombies::BeAttacked(int atk)
{
	hp -= atk;
	if (hp <= 0)//如果僵尸被打死则放回true，接下来进行消亡处理
		return true;
	else
		return false;
}