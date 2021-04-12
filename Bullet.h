#pragma once
#include"Global.h"
class Bullet
{
public:
	Bullet(int x, int y);
	void DrawBullet();//绘制子弹
	bool MoveBullet();//移动子弹
	int GetBulletX();//得到子弹所在x坐标
	int GetBulletY();//得到子弹所在y坐标
	int GetBulletAtk();//得到子弹的攻击力
private:
	int x;//子弹坐标初始位置
	int y;//子弹所在y轴
	int dx;//子弹x轴偏移量
	int atk;//子弹攻击力，单位：点/每颗
	int speed;//子弹移动速度，单位：100ms/每格
	clock_t c;//用于移动计时
};