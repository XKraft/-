#ifndef ZOMBIES
#define ZOMBIES
#include"Global.h"

class Zombies
{
public:
	Zombies();
	Zombies(const Zombies& z);
	//������game�����������н�ʬ����ֵ
	void SetZombie(string _name, int _hp, int _atk, int _speed, int _score);
	//�õ���ʬ������
	string GetZombieName();
	//�õ���ʬ��Ѫ��
	int GetZombieHP();
	//��ʬ����ѭ����ʬ�Ƿ��ܹ��ƶ�
	bool ZombieMove();
	//��ʬ����ѭ����ʬ�Ƿ��ܹ�����ֲ��
	bool ZombieEat();
	//�ڲ�����ʬʱ��ʼ����ʬ�ļ�ʱ��
	clock_t& GetMoveCounter();
	clock_t& GetEatCounter();
	//�õ���ʬ���ٶ�
	int GetZombieSpeed();
	//�õ���ʬ�Ĺ�����
	int GetZombeAtk();
	//�õ���ʬ���������ܵõ��ķ���
	int GetZombieScore();
	//�޸�ֲ���Ƿ�����ƶ���״̬
	bool& GetMove();
	//��ʬ�������Ĵ�����
	bool BeAttacked(int atk);
private:
	string name;//��ʬ����
	int hp;//��ʬѪ��
	int atk;//��ʬ������
	int speed;//��ʬ�ٶ�
	int score;//��ʬ����
	bool move;//��ʬ�Ƿ�����ƶ�
	clock_t move_counter;//��ʬ���ƶ���ʱ
	clock_t eat_counter;//��ʬ�Ĺ�����ʱ
};
#endif // !ZOMBIES