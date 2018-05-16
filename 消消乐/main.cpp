#include <graphics.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//定义一个点的结构体
typedef struct Postype
{
	int x;
	int y;
} pos;

void gameBegin(); //初始化游戏界面
void gamePlay();
void drawCursor(pos, COLORREF);
void drawTime(int);
void drawScore(int);
void getSameColorBall(pos, COLORREF);
int isValid(pos);
void orderArr();
void ballsfall();

pos cur;		  //定义光标的坐标点
pos arrBall[180]; //建立一个数组统计小球坐标
int index = 0;	//建立相同小球个数

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
	int tmp = 0; //tmp为随机颜色数组下标

	initgraph(1000, 700);
	setlinestyle(PS_SOLID | PS_JOIN_BEVEL, 10);
	rectangle(255, 45, 745, 655); //绘制游戏边框
	setlinestyle(PS_SOLID | PS_JOIN_BEVEL, 1);

	srand((unsigned int)time(NULL)); //设置随机数种子

	for (int x = 280; x < 740; x += 40) //初始化小球
	{
		for (int y = 70; y < 650; y += 40)
		{
			tmp = rand() % 6; //随机数
			setlinecolor(color[tmp]);
			setfillcolor(color[tmp]);
			fillcircle(x, y, 18);
		}
	}

	//初始化光标
	cur.x = 480;
	cur.y = 390;
	drawCursor(cur, RGB(255, 255, 255));

	//初始化时间
	drawTime(30);

	//初始化分数
	drawScore(0);
}

/*==================== gameBegin中的函数 ====================*/

void drawCursor(pos cur, COLORREF c1)
{
	setlinecolor(c1);
	rectangle(cur.x - 20, cur.y - 20, cur.x + 20, cur.y + 20);
}

void drawTime(int t)
{
	char str[30];
	settextstyle(30, 0, _T("宋体"));
	settextcolor(RGB(255, 0, 0));
	sprintf_s(str, "Time: %.2d s", t);
	outtextxy(50, 50, str);
}

void drawScore(int s)
{
	char str[30];

	settextstyle(30, 0, _T("宋体"));
	settextcolor(RGB(255, 255, 0));
	sprintf_s(str, "Score: %d", s);
	outtextxy(50, 550, str);
}
/* ====================================================== */

void gamePlay()
{
	MOUSEMSG m;  //定义鼠标信息
	COLORREF cl; //定义颜色信息
	int sum = 0; //定义计分变量

	while (1)
	{
		m = GetMouseMsg(); //获取鼠标信息

		switch (m.uMsg)
		{
		case WM_LBUTTONDOWN:
			if ((260 < m.x && m.x < 740) && (50 < m.y && m.y < 650))
			{
				//移动光标
				drawCursor(cur, RGB(0, 0, 0));
				cur.x = ((m.x - 260) / 40 + 1) * 40 + 260 - 20;
				cur.y = ((m.y - 50) / 40 + 1) * 40 + 50 - 20;
				drawCursor(cur, RGB(255, 255, 255));

				//统计小球个数
				cl = getpixel(cur.x, cur.y);
				getSameColorBall(cur, cl);

				//消除小球
				if (index > 1)
				{
					orderArr(); //将数组中的值排序。防止最下面一层的小球无法消去的bug出现
					ballsfall();
				}

				//计分
				sum += index;
				drawScore(sum);

				index = 0; //重新计数
			}
			break;

		default:
			break;
		}
	}
}

void getSameColorBall(pos cur, COLORREF cl)
{
	arrBall[index].x = cur.x;
	arrBall[index].y = cur.y;
	index++;

	//上
	if (cl == getpixel(cur.x, cur.y - 40))
	{
		cur.y = cur.y - 40;
		if (isValid(cur))
		{
			getSameColorBall(cur, cl);
		}
		cur.y = cur.y + 40;
	}

	//下
	if (cl == getpixel(cur.x, cur.y + 40))
	{
		cur.y = cur.y + 40;
		if (isValid(cur))
			getSameColorBall(cur, cl);
		cur.y = cur.y - 40;
	}

	//左
	if (cl == getpixel(cur.x - 40, cur.y))
	{
		cur.x = cur.x - 40;
		if (isValid(cur))
			getSameColorBall(cur, cl);
		cur.x = cur.x + 40;
	}

	//右
	if (cl == getpixel(cur.x + 40, cur.y))
	{
		cur.x = cur.x + 40;
		if (isValid(cur))
			getSameColorBall(cur, cl);
		cur.x = cur.x - 40;
	}
}

#if 0
/********* getSameColorBall的另一种写法 **********/

void getSameColorBall(pos cur, COLORREF cl)
{
	int i = 0;
	pos tmpPos;

	arrBall[index].x = cur.x;
	arrBall[index].y = cur.y;
	index++;

	for (i = 0; i < 4; i++)
	{
		switch (i)
		{
		case 0:
		{
			tmpPos.x = cur.x - 40;
			tmpPos.y = cur.y;
			if (cl == getpixel(tmpPos.x, tmpPos.y) && isValid(tmpPos))
				getSameColorBall(tmpPos, cl);
			break;
		}
		case 1:
		{
			tmpPos.x = cur.x + 40;
			tmpPos.y = cur.y;
			if (cl == getpixel(tmpPos.x, tmpPos.y) && isValid(tmpPos))
				getSameColorBall(tmpPos, cl);
			break;
		}
		case 2:
		{
			tmpPos.x = cur.x;
			tmpPos.y = cur.y - 40;
			if (cl == getpixel(tmpPos.x, tmpPos.y) && isValid(tmpPos))
				getSameColorBall(tmpPos, cl);
			break;
		}
		case 3:
		{
			tmpPos.x = cur.x;
			tmpPos.y = cur.y + 40;
			if (cl == getpixel(tmpPos.x, tmpPos.y) && isValid(tmpPos))
				getSameColorBall(tmpPos, cl);
			break;
		}
		default:
			break;
		}
	}
}
#endif

int isValid(pos cur)
{
	for (int k = 0; k < index; k++)
	{
		if (cur.x == arrBall[k].x && cur.y == arrBall[k].y)
			return 0;
	}
	return 1;
}

void orderArr()
{
	int temp = 0;
	int i, j;
	for (j = 0; j < index; j++)
		for (i = 0; i < index - j - 1; i++)
		{
			if (arrBall[i].y > arrBall[i + 1].y)
			{
				temp = arrBall[i].y;
				arrBall[i].y = arrBall[i + 1].y;
				arrBall[i + 1].y = temp;
				temp = arrBall[i].x;
				arrBall[i].x = arrBall[i + 1].x;
				arrBall[i + 1].x = temp;
			}
		}
}
void ballsfall()
{
	for (int i = 0; i < index; i++)
	{
		for (int k = arrBall[i].y; k > 70; k -= 40)
		{
			COLORREF cl = getpixel(arrBall[i].x, k - 40);
			setlinecolor(cl);
			setfillcolor(cl);
			fillcircle(arrBall[i].x, k, 18);
		}
		COLORREF cl = color[rand() % 6];
		setlinecolor(cl);
		setfillcolor(cl);
		fillcircle(arrBall[i].x, 50 + 20, 18);
	}
}