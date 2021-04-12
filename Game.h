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
};//标记游戏状态，分别是在购买中、在选择地块中、游戏结束
class Game
{
public:
	Game();
	~Game();
	//游戏的主循环
	void MainLoop();
	//绘制游戏的草坪的基本框架
	void DrawStage();
	//绘制游戏中的所有子弹
	void DrawBullets();
	//绘制游戏中的植物和僵尸信息等等
	void Draw();
	//实时活动用户输入并进行相应按键功能的实现
	void GetKey();
	//产生自然太阳光和向日葵产生太阳光
	void AddSunlight();
	//随着时间增加分数
	void AddScore();
	//移动网格光标
	void MoveGridCursor(int dx, int dy);
	//产生僵尸
	void AddZombie();
	//僵尸移动
	void MoveZombie();
	//游戏结束
	bool EndGame();
	//刷新每行是否存在僵尸的状态
	void RefreshExist();
	//所有的豌豆射手攻击
	void PeaShoot();
	//移动子弹
	void MoveBullets();
	//子弹攻击僵尸
	void AtkZombie();
	//僵尸攻击植物
	void AtkPlant();
private:
	State state;//标记游戏处于什么状态
	Store store;//生成一个商店对象
	Grid* grid;//一个grid类的指针，用于储存动态grid对象
	int cursor;//地块选择指针位于何处
	int sunlight;//游戏的当前阳光数
	int score;//游戏的当前分数
	Zombies _zombies[2];//游戏所有能产生的僵尸的数据模板
	vector<Bullet*> bullets[STAGE_LINES];//游戏每行草地子弹的容器
	bool exist_zombie[STAGE_LINES];//此行草地是否含有僵尸，用于确定是否发射子弹的条件之一
};
#endif // !GAME

