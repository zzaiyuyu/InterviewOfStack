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
//栈实现走迷宫
int passMaze(int maze[ROW][COL], Position entry, Stack* path)
{	
	//检测合法入口
	if (!isValidEntry(maze, entry)) {
		return 0;
	}
	maze[entry.x][entry.y] = 2;     //标记已走的为2
	pushBack(path, entry);			//走一步入口节点
	Position cur;                   //记录当前走的位置
	//上右下左走
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

		//四个方向均无法走，回退一步
		maze[cur.x][cur.y] = 3;  //标记为3可以看出哪些点是回退的
		pop(path);

	}
	return 0;
}
//递归走迷宫
int passMazeR(int maze[ROW][COL], Position cur, Position entry, Stack* path)
{
	if (!isValidEntry(maze, entry)) {
		return 0;
	}
	//先标记入口点
	maze[entry.x][entry.y] = 2;
	//求解子迷宫问题
	return _passMazeR(maze, entry, entry, path);
}

int _passMazeR(int maze[ROW][COL], Position cur, Position entry, Stack* path)
{
	//入栈当前点
	pushBack(path, cur);
	if (isExit(maze, cur, entry)) {
		return 1;
	}
	//上右下左走
	Position tmp = cur; //下一个要试探的位置
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
	//四个方向均尝试，出栈
	pop(path);
	return 0;
}


int isValidEntry(int maze[ROW][COL], Position entry)//检测合法入口
{
	if (entry.x < 0 || entry.y < 0 || entry.x >= ROW || entry.y >= COL) {
		return 0;
	}
	return maze[entry.x][entry.y];
}
int isValidPath(int maze[ROW][COL], Position next)//检查是否可以走
{
	if (next.x < 0 || next.y < 0 || next.x >= ROW || next.y >= COL) {
		return 0;
	}
	else if (1 == maze[next.x][next.y]) {
		return 1;
	}
	return 0;
}
int isExit(int maze[ROW][COL], Position next, Position entry)//检查是不是出口
{
	//不能是入口
	if (next.x == entry.x && (next.y == entry.y)) {
		return 0;
	}
	//因为进来的都是有效点，所以只用判断是不是边界
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
/*****************************复杂迷宫找最短路*************************************/
//多出口可能带环迷宫
void update(Stack *dest, Stack *src);
void _passMazeC(int maze[ROW][COL], Position cur, Position entry, Stack* path, Stack * min);
void passMazeC(int maze[ROW][COL], Position cur, Position entry, Stack* path, Stack * min)
{
	if (!isValidEntry(maze, entry)) {
		return 0;
	}
	//标记入口点
	maze[entry.x][entry.y] = 2;
	//求解子迷宫问题
	_passMazeC(maze, cur, entry, path, min);
}

void _passMazeC(int maze[ROW][COL], Position cur, Position entry, Stack* path, Stack * min)
{
	pushBack(path, cur);
	if (isExit(maze, cur, entry)) {
		//第一次找到路径，或者更新最短路径
		if ( isEmpty(path) || (min->top > path->top)) {
			update(min, path);
		}
		pop(path);
		return;
	}
	//上右下左走
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
	//四个方向都走完了
	pop(path);
	return ;
}
int isValidPathC(int maze[ROW][COL], Position cur, Position next)//检查是否可以走
{
	if (next.x < 0 || next.y < 0 || next.x >= ROW || next.y >= COL) {
		return 0;
	}
	else if (maze[next.x][next.y] == 1 || ( maze[cur.x][cur.y]+1 < maze[next.x][next.y])) {
		return 1;
	}
	return 0;
}
//更新最小路径——复制栈
void update(Stack *dest, Stack *src)
{
	//销毁原栈，按src的大小给dest开辟空间
	destory(dest);
	Stack* tmp = NULL;
	tmp= (Stack*)malloc(src->capacity * sizeof(Datatype));
	if (NULL != tmp) {
		dest->array = tmp;
	}
	dest->capacity = src->capacity;
	dest->top = src->top;
	//复制内容
	int i = 0;
	for (i = 0; i < src->top; i++) {
		dest->array[i] = src->array[i];
	}
}

void printStack(Stack * min)//从底到顶打印栈
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
	printf("************************栈思路*********************\n");
	passMaze(map, entry, &path);
	printMap();
	printf("走出路径：");
	printStack(&path);
	//printf("************************递归思路*********************\n");
	//init(&path);
	//initMap(tmp);
	//int ret = passMazeR(map, entry, entry, &path);
	//printMap();
	//printf("走出路径："); 
	//printStack(&path);

	//Stack min;
	//init(&min);
	//passMazeC(map, entry, entry, &path, &min);
	//printMap();
	//printf("最短路径：");
	//printStack(&min);
}
#endif