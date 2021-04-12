#include"UI.h"
//设置命令行输出字体颜色
void SetPrintColor(int color_id)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color_id);
}
//设置命令行光标位置
void CursorSetXY(int x, int y)
{
	COORD cursor;
	cursor.X = x;
	cursor.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursor);
}
//设置命令行窗口大小
void SetCMDSize(int cols, int lines)
{
	char str[40];
	sprintf(str, "mode con cols=%d lines=%d", cols, lines);
	system(str);
}
//隐藏命令行光标
void HideCursor()
{
	HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cci;
	cci.bVisible = 0;
	cci.dwSize = 1;
	SetConsoleCursorInfo(hOutput, &cci);
}
//将二维坐标转化成一维
int CoordTtoO(int x, int y)
{
	return x + y * STAGE_COLS;
}
//将命令行中的二位坐标转换为网格中的一维
int CoordCMDtoGRID(int x, int y)
{
	int i = x / GRID_WIDTH;
	int j = y / GRID_HEIGHT;
	return i + j * STAGE_COLS;
}
//沙漏函数，用于计时，一次周期为s*100ms
bool SandGlass(clock_t& c, int s)
{
	if (clock() - c >= s * TIME)
	{
		c = clock();
		return true;
	}
	else
		return false;
}