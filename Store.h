#ifndef STORE
#define STORE
#include"Global.h"
#include"Grid.h"
const int PLANT_KINDS = 2;//ֲ���������
class Store
{
public:
	Store();
	//�����̵�
	void DrawStore();
	//�ƶ����
	void MoveCursor(int dy);
	//������ѡ����ֲ�ص�ʱ���������̵���״̬
	void HideCursor();
	//���ù��
	void ResetCurset();
	//��cd���㣬��ʼ��ʱ
	void RefreshBuyCD();
	//����cd�ļ�ʱ
	void AddBuyCD();
	//�����ȴʱ���Ƿ����
	bool CDIsOk();
	//�õ������ָ���ֲ�����Ӧ���ѷ�������
	int GetCost();
	//����ֲ��
	Plants& SellPlant();
private:
	Plants plant_card[PLANT_KINDS];//ֲ���ģ��
	bool is_cursor[PLANT_KINDS];//����Ƿ�����
	int buy_cd[PLANT_KINDS];//ÿ��ֲ���cd
	int cursor;//���λ��
};
#endif // !STORE

