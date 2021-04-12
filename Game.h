#ifndef GAME
#define GAME
#include"Global.h"
#include"Store.h"
class Grid;
class Store;
enum State
{
	BUYING,
	SELECT,
	GAMEOVER,
};//�����Ϸ״̬���ֱ����ڹ����С���ѡ��ؿ��С���Ϸ����
class Game
{
public:
	Game();
	~Game();
	//��Ϸ����ѭ��
	void MainLoop();
	//������Ϸ�Ĳ�ƺ�Ļ������
	void DrawStage();
	//������Ϸ�е������ӵ�
	void DrawBullets();
	//������Ϸ�е�ֲ��ͽ�ʬ��Ϣ�ȵ�
	void Draw();
	//ʵʱ��û����벢������Ӧ�������ܵ�ʵ��
	void GetKey();
	//������Ȼ̫��������տ�����̫����
	void AddSunlight();
	//����ʱ�����ӷ���
	void AddScore();
	//�ƶ�������
	void MoveGridCursor(int dx, int dy);
	//������ʬ
	void AddZombie();
	//��ʬ�ƶ�
	void MoveZombie();
	//��Ϸ����
	bool EndGame();
	//ˢ��ÿ���Ƿ���ڽ�ʬ��״̬
	void RefreshExist();
	//���е��㶹���ֹ���
	void PeaShoot();
	//�ƶ��ӵ�
	void MoveBullets();
	//�ӵ�������ʬ
	void AtkZombie();
	//��ʬ����ֲ��
	void AtkPlant();
private:
	State state;//�����Ϸ����ʲô״̬
	Store store;//����һ���̵����
	Grid* grid;//һ��grid���ָ�룬���ڴ��涯̬grid����
	int cursor;//�ؿ�ѡ��ָ��λ�ںδ�
	int sunlight;//��Ϸ�ĵ�ǰ������
	int score;//��Ϸ�ĵ�ǰ����
	Zombies _zombies[2];//��Ϸ�����ܲ����Ľ�ʬ������ģ��
	vector<Bullet*> bullets[STAGE_LINES];//��Ϸÿ�вݵ��ӵ�������
	bool exist_zombie[STAGE_LINES];//���вݵ��Ƿ��н�ʬ������ȷ���Ƿ����ӵ�������֮һ
};
#endif // !GAME

