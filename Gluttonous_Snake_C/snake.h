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
int dx = 0; //横向坐标变化
int dy = 0; //纵向坐标变化
int lx = 0; //蛇身最后的横坐标
int ly = 0; //蛇身最后的纵坐标
void InitWall(); //初始化边界
void InitFood(); //初始化食物
void InitSnake(); //初始化蛇
void ShowUI();
void GameControl();

#endif // ! _SNAKE_H
