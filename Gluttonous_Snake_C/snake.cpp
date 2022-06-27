#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
#include <conio.h>
#include <math.h>
#include <time.h>
#include "snake.h"

int main(void)
{
	srand((size_t)time(NULL)); //随机数种子

	/*优化界面，不显示光标*/
	CONSOLE_CURSOR_INFO cci;
	cci.dwSize = sizeof(cci);
	cci.bVisible = FALSE;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cci);

	InitWall();
	InitSnake();
	InitFood();
	GameControl();

	return 0;
}

void InitWall()  //初始化墙壁
{
	int i = 0;
	int j = 0;
	for (i = 0; i <= HIGH; i++)
	{
		for (j = 0; j <= WIDE; j++)
		{
			if (i == HIGH)
				putchar('=');
			else if (j == WIDE)
				putchar('=');
			else
				putchar(' ');
		}
		putchar('\n');
	}
}

void InitFood()  //初始化食物
{
	food[0] = rand() % WIDE - 1;
	food[1] = rand() % HIGH - 1;
}

void InitSnake()  //初始化蛇
{
	Snake.size = 3;
	Snake.body[0].x = WIDE / 2 - 2;
	Snake.body[0].y = HIGH / 2 - 1;
	
	Snake.body[1].x = WIDE / 2 - 3;
	Snake.body[1].y = HIGH / 2 - 1;

	Snake.body[2].x = WIDE / 2 - 4;
	Snake.body[2].y = HIGH / 2 - 1;

}

void ShowUI()  //显示蛇和食物
{
	COORD coord;
	int j = 0;

	/*向前递补空格，更新蛇身体，避免出现蛇身体越来越长的虚空身体*/
	coord.X = lx;
	coord.Y = ly;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	putchar(' ');

	for (j = 0; j < Snake.size; j++)
	{
		coord.X = Snake.body[j].x;
		coord.Y = Snake.body[j].y;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
		if(j == 0)
			putchar('@');
		else
			putchar('&');
	}

	coord.X = food[0];
	coord.Y = food[1];
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	putchar('#');

}

void GameControl()  //游戏控制
{
	char key = 'D'; //初始方向向右
	int i = 0;

	/*当蛇没有碰撞边界时可以持续游戏*/
	while ( (Snake.body[0].x >= 0) && (Snake.body[0].x < WIDE ) 
		 && (Snake.body[0].y >= 0) && (Snake.body[0].y < HIGH ) )
	{

		ShowUI();
		while (_kbhit())  //判断是否有键盘输入，若有返回值非0
		{
			key = _getch();  //接收键盘输入
		}
		switch (key)
		{
		case 'D':case 'd':dx = 1; dy = 0; break;
		case 'W':case 'w':dx = 0; dy = -1; break;
		case 'A':case 'a':dx = -1; dy = 0; break;
		case 'S':case 's':dx = 0; dy = 1; break;
		}

		lx = Snake.body[Snake.size - 1].x;
		ly = Snake.body[Snake.size - 1].y; //记录蛇身最后的坐标
		for (i = Snake.size - 1; i > 0; i--) //向前递补更新蛇身坐标
		{

			Snake.body[i].x = Snake.body[i - 1].x;
			Snake.body[i].y = Snake.body[i - 1].y;
		}
		Snake.body[0].x += dx; 
		Snake.body[0].y += dy; //更新蛇头坐标

		for (i = 1; i < Snake.size; i++) //游戏规则，蛇不能和自己身体碰撞
		{
			if ((Snake.body[0].x == Snake.body[i].x) && (Snake.body[0].y == Snake.body[i].y))
				break;
		}

		if ((Snake.body[0].x == food[0]) && (Snake.body[0].y == food[1])) //游戏规则，吃到食物则更新食物位置并蛇身尺寸加一
		{
			InitFood();
			Snake.size++;
		}

		Sleep(150); //一定的延时，避免闪退
		//
	}
	system("cls");  //清屏
	printf("Game Over\n");
}
