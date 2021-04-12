#ifndef PLANTS
#define PLANTS
#include <string>
#include"Bullet.h"
class Plants
{
public:
	Plants();
	//���ڴ��̵����ø���ֲ��Ĳ���
	void PlantSet(const char* _name, int _hp, int _cost, int _buycd, int _functioncd, bool _shoot, bool _addsunlight);
	//�õ�ֲ�������
	const char* GetPlantName();
	//�õ�ֲ��Ĺ�����ȴʱ��
	int GetPlantBuyCD();
	//�õ�ֲ�ﹺ������Ļ���
	int GetPlantCost();
	//�õ�ֲ���Ѫ��
	int GetPlantHP();
	//ʵ�ֶ�=�����أ��ֱ�ֲ�����ֲʱ���̵��ģ�帳ֵ
	Plants& operator = (const Plants& p);
	//ֲ�ﱻ��ʬ�ԣ��۳�hp�����ֲ�ﱻ�Ե��Ż�true
	bool Ate(int atk);
	//���ֲ����з����㶹���ܣ�����÷����㶹
	Bullet* Shoot(int x, int y);
	//���ֲ����в������⹦�ܣ�����ò�������
	int AddSunlight();
private:
	const char* name;//ֲ������
	int hp;//ֲ��Ѫ��
	int cost;//ֲ�����������
	int buycd;//ֲ��Ĺ�����ȴʱ��
	int functioncd;//ֲ��Ĺ��ܺ���ִ�е���ȴʱ��
	clock_t c;//ֲ��ļ�ʱ��
	bool shoot;//ֲ���Ƿ���з��书��
	bool addsunlight;//ֲ���Ƿ���в�������Ĺ���
};
#endif // !PLANTS

