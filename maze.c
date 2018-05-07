#if 0
#include "maze.h"
#include "stack.h"
#include <malloc.h>
void initMap(int maze[ROW][COL])
{
	int i, j;
	for (i = 0; i < ROW; i++) {
		for (j = 0; j < COL; j++) {
			map[i][j] = maze[i][j];
		}
	}
}
//ջʵ�����Թ�
int passMaze(int maze[ROW][COL], Position entry, Stack* path)
{	
	//���Ϸ����
	if (!isValidEntry(maze, entry)) {
		return 0;
	}
	maze[entry.x][entry.y] = 2;     //������ߵ�Ϊ2
	pushBack(path, entry);			//��һ����ڽڵ�
	Position cur;                   //��¼��ǰ�ߵ�λ��
	//����������
	while (!isEmpty(path)) {
		cur = top(path);
		if (isExit(maze, cur, entry)) {
			maze[cur.x][cur.y] = 2;
			return 1;
		}
		Position next;
		next = cur;
		next.x -= 1;
		if (isValidPath(maze, next)) {
			maze[next.x][next.y] = 2;
			pushBack(path, next);
			continue;
		}

		next = cur;
		next.y += 1;
		if (isValidPath(maze, next)) {
			maze[next.x][next.y] = 2;
			pushBack(path, next);
			continue;
		}

		next = cur;
		next.x += 1;
		if (isValidPath(maze, next)) {
			maze[next.x][next.y] = 2;
			pushBack(path, next);
			continue;
		}

		next = cur;
		next.y -= 1;
		if (isValidPath(maze, next)) {
			maze[next.x][next.y] = 2;
			pushBack(path, next);
			continue;
		}

		//�ĸ�������޷��ߣ�����һ��
		maze[cur.x][cur.y] = 3;  //���Ϊ3���Կ�����Щ���ǻ��˵�
		pop(path);

	}
	return 0;
}
//�ݹ����Թ�
int passMazeR(int maze[ROW][COL], Position cur, Position entry, Stack* path)
{
	if (!isValidEntry(maze, entry)) {
		return 0;
	}
	//�ȱ����ڵ�
	maze[entry.x][entry.y] = 2;
	//������Թ�����
	return _passMazeR(maze, entry, entry, path);
}

int _passMazeR(int maze[ROW][COL], Position cur, Position entry, Stack* path)
{
	//��ջ��ǰ��
	pushBack(path, cur);
	if (isExit(maze, cur, entry)) {
		return 1;
	}
	//����������
	Position tmp = cur; //��һ��Ҫ��̽��λ��
	tmp.x -= 1;
	if (isValidPath(maze, tmp)) {
		maze[tmp.x][tmp.y] = 2;
		if (_passMazeR(maze, tmp, entry, path))
			return 1;
	}

	tmp = cur;
	tmp.y += 1;
	if (isValidPath(maze, tmp)) {
		maze[tmp.x][tmp.y] = 2;
		if (_passMazeR(maze, tmp, entry, path))
			return 1;
	}

	tmp = cur;
	tmp.x += 1;
	if (isValidPath(maze, tmp)) {
		maze[tmp.x][tmp.y] = 2;
		if (_passMazeR(maze, tmp, entry, path))
			return 1;
	}

	tmp = cur;
	tmp.y -= 1;
	if (isValidPath(maze, tmp)) {
		maze[tmp.x][tmp.y] = 2;
		if (_passMazeR(maze, tmp, entry, path))
			return 1;
	}
	//�ĸ���������ԣ���ջ
	pop(path);
	return 0;
}


int isValidEntry(int maze[ROW][COL], Position entry)//���Ϸ����
{
	if (entry.x < 0 || entry.y < 0 || entry.x >= ROW || entry.y >= COL) {
		return 0;
	}
	return maze[entry.x][entry.y];
}
int isValidPath(int maze[ROW][COL], Position next)//����Ƿ������
{
	if (next.x < 0 || next.y < 0 || next.x >= ROW || next.y >= COL) {
		return 0;
	}
	else if (1 == maze[next.x][next.y]) {
		return 1;
	}
	return 0;
}
int isExit(int maze[ROW][COL], Position next, Position entry)//����ǲ��ǳ���
{
	//���������
	if (next.x == entry.x && (next.y == entry.y)) {
		return 0;
	}
	//��Ϊ�����Ķ�����Ч�㣬����ֻ���ж��ǲ��Ǳ߽�
	else if ((0 == next.x || 0 == next.y || (ROW - 1) == next.x || (COL - 1) == next.y)) {
		
		return 1;
	}
	return 0;
}
void printMap()
{
	int i, j;
	for (i = 0; i < ROW; i++) {
		for (j = 0; j < COL; j++) {
			printf("%d ", map[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}
/*****************************�����Թ������·*************************************/
//����ڿ��ܴ����Թ�
void update(Stack *dest, Stack *src);
void _passMazeC(int maze[ROW][COL], Position cur, Position entry, Stack* path, Stack * min);
void passMazeC(int maze[ROW][COL], Position cur, Position entry, Stack* path, Stack * min)
{
	if (!isValidEntry(maze, entry)) {
		return 0;
	}
	//�����ڵ�
	maze[entry.x][entry.y] = 2;
	//������Թ�����
	_passMazeC(maze, cur, entry, path, min);
}

void _passMazeC(int maze[ROW][COL], Position cur, Position entry, Stack* path, Stack * min)
{
	pushBack(path, cur);
	if (isExit(maze, cur, entry)) {
		//��һ���ҵ�·�������߸������·��
		if ( isEmpty(path) || (min->top > path->top)) {
			update(min, path);
		}
		pop(path);
		return;
	}
	//����������
	Position tmp = cur;
	tmp.x -= 1;
	if (isValidPathC(maze, cur, tmp)) {
		maze[tmp.x][tmp.y] = maze[cur.x][cur.y] + 1;
		_passMazeC(maze, tmp, entry, path, min);
	}

	tmp = cur;
	tmp.y += 1;
	if (isValidPathC(maze, cur, tmp)) {
		maze[tmp.x][tmp.y] = maze[cur.x][cur.y] + 1;
		_passMazeC(maze, tmp, entry, path, min);
	}

	tmp = cur;
	tmp.x += 1;
	if (isValidPathC(maze, cur, tmp)) {
		maze[tmp.x][tmp.y] = maze[cur.x][cur.y] + 1;
		_passMazeC(maze, tmp, entry, path, min);
	}

	tmp = cur;
	tmp.y -= 1;
	if (isValidPathC(maze, cur, tmp)) {
		maze[tmp.x][tmp.y] = maze[cur.x][cur.y] + 1;
		_passMazeC(maze, tmp, entry, path, min);
	}
	//�ĸ�����������
	pop(path);
	return ;
}
int isValidPathC(int maze[ROW][COL], Position cur, Position next)//����Ƿ������
{
	if (next.x < 0 || next.y < 0 || next.x >= ROW || next.y >= COL) {
		return 0;
	}
	else if (maze[next.x][next.y] == 1 || ( maze[cur.x][cur.y]+1 < maze[next.x][next.y])) {
		return 1;
	}
	return 0;
}
//������С·����������ջ
void update(Stack *dest, Stack *src)
{
	//����ԭջ����src�Ĵ�С��dest���ٿռ�
	destory(dest);
	Stack* tmp = NULL;
	tmp= (Stack*)malloc(src->capacity * sizeof(Datatype));
	if (NULL != tmp) {
		dest->array = tmp;
	}
	dest->capacity = src->capacity;
	dest->top = src->top;
	//��������
	int i = 0;
	for (i = 0; i < src->top; i++) {
		dest->array[i] = src->array[i];
	}
}

void printStack(Stack * min)//�ӵ׵�����ӡջ
{
	assert(min);
	int i = 0;
	for (i = 0; i < min->top; i++) {
		printf("(%d, %d ) ", min->array[i].x, min->array[i].y);
	}
	printf("\n");
}

void test_maze()
{
	Stack path;
	init(&path);
	int tmp[ROW][COL] = {
		{ 0,0,0,0,0,0 },
	{ 0,1,0,1,1,0 },
	{ 0,1,1,1,1,0 },
	{ 0,1,0,0,1,0 },
	{ 0,1,1,1,1,0 },
	{ 0,1,0,0,1,1 },
	};
	initMap(tmp);
	printMap();
	Position entry = { 5,1 };
	printf("************************ջ˼·*********************\n");
	passMaze(map, entry, &path);
	printMap();
	printf("�߳�·����");
	printStack(&path);
	//printf("************************�ݹ�˼·*********************\n");
	//init(&path);
	//initMap(tmp);
	//int ret = passMazeR(map, entry, entry, &path);
	//printMap();
	//printf("�߳�·����"); 
	//printStack(&path);

	//Stack min;
	//init(&min);
	//passMazeC(map, entry, entry, &path, &min);
	//printMap();
	//printf("���·����");
	//printStack(&min);
}
#endif