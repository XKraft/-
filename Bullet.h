#pragma once
#include"Global.h"
class Bullet
{
public:
	Bullet(int x, int y);
	void DrawBullet();//�����ӵ�
	bool MoveBullet();//�ƶ��ӵ�
	int GetBulletX();//�õ��ӵ�����x����
	int GetBulletY();//�õ��ӵ�����y����
	int GetBulletAtk();//�õ��ӵ��Ĺ�����
private:
	int x;//�ӵ������ʼλ��
	int y;//�ӵ�����y��
	int dx;//�ӵ�x��ƫ����
	int atk;//�ӵ�����������λ����/ÿ��
	int speed;//�ӵ��ƶ��ٶȣ���λ��100ms/ÿ��
	clock_t c;//�����ƶ���ʱ
};