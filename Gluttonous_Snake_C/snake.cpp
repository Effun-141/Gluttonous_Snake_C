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
	srand((size_t)time(NULL)); //���������

	/*�Ż����棬����ʾ���*/
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

void InitWall()  //��ʼ��ǽ��
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

void InitFood()  //��ʼ��ʳ��
{
	food[0] = rand() % WIDE - 1;
	food[1] = rand() % HIGH - 1;
}

void InitSnake()  //��ʼ����
{
	Snake.size = 3;
	Snake.body[0].x = WIDE / 2 - 2;
	Snake.body[0].y = HIGH / 2 - 1;
	
	Snake.body[1].x = WIDE / 2 - 3;
	Snake.body[1].y = HIGH / 2 - 1;

	Snake.body[2].x = WIDE / 2 - 4;
	Snake.body[2].y = HIGH / 2 - 1;

}

void ShowUI()  //��ʾ�ߺ�ʳ��
{
	COORD coord;
	int j = 0;

	/*��ǰ�ݲ��ո񣬸��������壬�������������Խ��Խ�����������*/
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

void GameControl()  //��Ϸ����
{
	char key = 'D'; //��ʼ��������
	int i = 0;

	/*����û����ײ�߽�ʱ���Գ�����Ϸ*/
	while ( (Snake.body[0].x >= 0) && (Snake.body[0].x < WIDE ) 
		 && (Snake.body[0].y >= 0) && (Snake.body[0].y < HIGH ) )
	{

		ShowUI();
		while (_kbhit())  //�ж��Ƿ��м������룬���з���ֵ��0
		{
			key = _getch();  //���ռ�������
		}
		switch (key)
		{
		case 'D':case 'd':dx = 1; dy = 0; break;
		case 'W':case 'w':dx = 0; dy = -1; break;
		case 'A':case 'a':dx = -1; dy = 0; break;
		case 'S':case 's':dx = 0; dy = 1; break;
		}

		lx = Snake.body[Snake.size - 1].x;
		ly = Snake.body[Snake.size - 1].y; //��¼������������
		for (i = Snake.size - 1; i > 0; i--) //��ǰ�ݲ�������������
		{

			Snake.body[i].x = Snake.body[i - 1].x;
			Snake.body[i].y = Snake.body[i - 1].y;
		}
		Snake.body[0].x += dx; 
		Snake.body[0].y += dy; //������ͷ����

		for (i = 1; i < Snake.size; i++) //��Ϸ�����߲��ܺ��Լ�������ײ
		{
			if ((Snake.body[0].x == Snake.body[i].x) && (Snake.body[0].y == Snake.body[i].y))
				break;
		}

		if ((Snake.body[0].x == food[0]) && (Snake.body[0].y == food[1])) //��Ϸ���򣬳Ե�ʳ�������ʳ��λ�ò�����ߴ��һ
		{
			InitFood();
			Snake.size++;
		}

		Sleep(150); //һ������ʱ����������
		//
	}
	system("cls");  //����
	printf("Game Over\n");
}
