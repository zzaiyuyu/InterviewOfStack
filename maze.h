#if 0
#pragma once
#define ROW 6
#define COL 6
extern struct stack;
typedef struct stack Stack;
//对坐标进行封装
typedef struct position {
	int x;
	int y;
}Position;

int map[ROW][COL];//迷宫
void initMap(int maze[ROW][COL]); //初始化map
int isValidEntry(int maze[ROW][COL], Position entry);//检测合法入口
int isValidPath(int maze[ROW][COL], Position next);//检查是否可以走
int isExit(int maze[ROW][COL], Position next, Position entry);//检查是不是出口
int passMaze(int maze[ROW][COL], Position entry, Stack* path);//栈实现走迷宫
int isValidPathC(int maze[ROW][COL], Position cur, Position next);//检查是否可以走
void printMap(); 
int passMazeR(int maze[ROW][COL], Position cur, Position entry, Stack* path);//递归走迷宫
void passMazeC(int maze[ROW][COL], Position cur, Position entry, Stack* path, Stack * min);//多出口可能带环迷宫

#endif