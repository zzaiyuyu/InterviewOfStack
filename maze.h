#if 0
#pragma once
#define ROW 6
#define COL 6
extern struct stack;
typedef struct stack Stack;
//��������з�װ
typedef struct position {
	int x;
	int y;
}Position;

int map[ROW][COL];//�Թ�
void initMap(int maze[ROW][COL]); //��ʼ��map
int isValidEntry(int maze[ROW][COL], Position entry);//���Ϸ����
int isValidPath(int maze[ROW][COL], Position next);//����Ƿ������
int isExit(int maze[ROW][COL], Position next, Position entry);//����ǲ��ǳ���
int passMaze(int maze[ROW][COL], Position entry, Stack* path);//ջʵ�����Թ�
int isValidPathC(int maze[ROW][COL], Position cur, Position next);//����Ƿ������
void printMap(); 
int passMazeR(int maze[ROW][COL], Position cur, Position entry, Stack* path);//�ݹ����Թ�
void passMazeC(int maze[ROW][COL], Position cur, Position entry, Stack* path, Stack * min);//����ڿ��ܴ����Թ�

#endif