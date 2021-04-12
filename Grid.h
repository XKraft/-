#ifndef GRID
#define GRID
#include"Global.h"
#include"Plants.h"
#include"Zombies.h"
class Grid
{
public:
	Grid();
	void DrawGrid();//绘制格子中的内容
	void ChangCursor();//改变格子中的光标状态
	void GrowPlant(Plants& p);//在格子中种植植物
	bool Is_Grow();//得到该格子是否可以种植植物的信息
	void SetGridXY(int _x, int _y);//设置格子的坐标
	vector<Zombies*> GetVector();//返回存储僵尸的容器
	bool ExistZombieOrPlant();//返回当前格子是否有僵尸或者植物
	bool ExistZombieAndPlant();//返回当前格子是否有僵尸和者植物
	friend class Game;
private:
	Plants plant;//当前格子的植物
	vector<Zombies*> zombies;//一个储存僵尸对象指针的容器
	int x;//（x，y）代表格子的左上角在命令行中的坐标
	int y;
	int zombie_nums;//当前格子的僵尸书
	bool is_cursor;//是否光标在这
	bool is_grow;//是否可以种植，同时作为是否有植物存在的标志
};
#endif // !GRID

