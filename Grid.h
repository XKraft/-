#ifndef GRID
#define GRID
#include"Global.h"
#include"Plants.h"
#include"Zombies.h"
class Grid
{
public:
	Grid();
	void DrawGrid();//���Ƹ����е�����
	void ChangCursor();//�ı�����еĹ��״̬
	void GrowPlant(Plants& p);//�ڸ�������ֲֲ��
	bool Is_Grow();//�õ��ø����Ƿ������ֲֲ�����Ϣ
	void SetGridXY(int _x, int _y);//���ø��ӵ�����
	vector<Zombies*> GetVector();//���ش洢��ʬ������
	bool ExistZombieOrPlant();//���ص�ǰ�����Ƿ��н�ʬ����ֲ��
	bool ExistZombieAndPlant();//���ص�ǰ�����Ƿ��н�ʬ����ֲ��
	friend class Game;
private:
	Plants plant;//��ǰ���ӵ�ֲ��
	vector<Zombies*> zombies;//һ�����潩ʬ����ָ�������
	int x;//��x��y��������ӵ����Ͻ����������е�����
	int y;
	int zombie_nums;//��ǰ���ӵĽ�ʬ��
	bool is_cursor;//�Ƿ�������
	bool is_grow;//�Ƿ������ֲ��ͬʱ��Ϊ�Ƿ���ֲ����ڵı�־
};
#endif // !GRID

