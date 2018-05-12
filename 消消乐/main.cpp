#include <graphics.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void gameBegin(); //初始化游戏界面
void gamePlay();
void drawCursor(int, int, COLORREF);
void drawTime(int);
void drawScore(int);

COLORREF color[6] = {RGB(0, 255, 255), RGB(255, 0, 0), RGB(0, 255, 0), 
						RGB(0, 0, 255), RGB(255, 255, 0), RGB(255, 0, 255)}; //定义颜色数组color

int main()
{
	gameBegin();

	gamePlay();

	_getch();
	closegraph();
	return 0;
}

void gameBegin()
{
	int tmp = 0;		//tmp为随机颜色数组下标

	initgraph(1000, 700);
	setlinestyle(PS_SOLID | PS_JOIN_BEVEL, 10);
	rectangle(255, 45, 745, 655); //绘制游戏边框
	setlinestyle(PS_SOLID | PS_JOIN_BEVEL, 1);

	srand((unsigned int)time(NULL)); 	//设置随机数种子

	for (int x = 280; x < 740; x += 40) //初始化小球
	{
		for (int y = 70; y < 650; y += 40)
		{
			tmp = rand() % 6;
			setlinecolor(color[tmp]);
			setfillcolor(color[tmp]);
			fillcircle(x, y, 18);
		}
	}

	//初始化光标
	drawCursor(480,390,RGB(255,255,255));

	//初始化时间
	settextstyle(30, 0, _T("宋体"));
	settextcolor(RGB(255, 0, 0));
	outtextxy(50,50,"Time: 30s");

	//初始化分数
	settextcolor(RGB(255, 255, 0));
	outtextxy(50,550,"score: 0");
}

void drawCursor(int x, int y, COLORREF c1)
{
	setlinecolor(c1);
	rectangle(x - 20, y - 20, x + 20, y + 20);
}

void drawTime(int time)
{
	//
}

void drawScore(int score)
{
	//
}

void gamePlay()
{
	//
}