#include"Bullet.h"
Bullet::Bullet(int _x, int _y)
{
	x = _x;
	y = _y;
	dx = 0;
	atk = 25;
	speed = 2;
	c = clock();
}
void Bullet::DrawBullet()
{
	if (x + dx < STAGE_WIDTH - 1)//�������߽���ߵ�ǰ����λ����ֲ��ʱ���߽�ʬʱ����ʾ
	{
		CursorSetXY(x + dx, y);
		SetPrintColor(f_green);
		cout << "��";
		SetPrintColor(reset);
	}
}
bool Bullet::MoveBullet()
{
	if (SandGlass(c, speed))
	{
		if (x + dx >= STAGE_WIDTH - 1)//�ӵ����ͥԺ
			return true;
		dx += 2;
		return false;
	}
	return false;
}
int Bullet::GetBulletX()
{
	return x + dx;
}
int Bullet::GetBulletY()
{
	return y;
}
int Bullet::GetBulletAtk()
{
	return atk;
}