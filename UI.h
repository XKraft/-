#ifndef UI
#define UI
#include"Global.h"
//�������
const int GRID_WIDTH = 14;//���ӿ��
const int GRID_HEIGHT = 6;//���Ӹ߶�
const int STAGE_COLS = 7;//��ƺ����
const int STAGE_LINES = 3;//��ƺ����
const int STAGE_WIDTH = (GRID_WIDTH - 1) * 7 + 1;//��ƺ���
const int STAGE_HEIGHT = (GRID_HEIGHT - 1) * 3 + 1;//��ƺ�߶�
const int CMD_COLS = STAGE_WIDTH + 1;//�����п��
const int CMD_LINES = STAGE_HEIGHT + 7;//�����и߶�
const int SUN_SCORE = STAGE_HEIGHT + 1;//����ͷ�����ʾλ��
const int STORE_LINES = STAGE_HEIGHT + 4;//�̵���ʾλ��
//����������������ɫ
const int b_red = BACKGROUND_INTENSITY | BACKGROUND_RED;
const int f_red = FOREGROUND_INTENSITY | FOREGROUND_RED;
const int reset = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED;
const int f_green = FOREGROUND_INTENSITY | FOREGROUND_GREEN;
//ʱ�����
const int TIME = 100;

//���ܺ���
//������ʾ��ɫ
void SetPrintColor(int color_id);
//�ƶ���굽ָ��λ��
void CursorSetXY(int x, int y);
//���������д��ڴ�С
void SetCMDSize(int cols, int lines);
//���ع��
void HideCursor();
//�������еĶ�ά����ת��Ϊһά
int CoordTtoO(int x, int y);
//���������еĶ�λ����ת��Ϊ�����е�һά
int CoordCMDtoGRID(int x, int y);
//ɳ©���������ڼ�ʱ
bool SandGlass(clock_t& c, int s);
#endif // !UI
