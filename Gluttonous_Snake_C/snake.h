#pragma once
#ifndef __SNAKE_H__
#define __SNAKE_H__

#define HIGH 20
#define WIDE 60

struct BODY
{
	int x;
	int y;
};
struct snake
{
	int size;
	struct BODY body[HIGH*WIDE];
	//int score;
	//int level;
}Snake;
int food[2] = { 0 };
int dx = 0; //��������仯
int dy = 0; //��������仯
int lx = 0; //�������ĺ�����
int ly = 0; //��������������
void InitWall(); //��ʼ���߽�
void InitFood(); //��ʼ��ʳ��
void InitSnake(); //��ʼ����
void ShowUI();
void GameControl();

#endif // ! _SNAKE_H
