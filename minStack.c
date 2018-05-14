//带最小值的栈
#include "stack.h"
#include <assert.h>
#include <stdlib.h>
typedef struct MINSTACK {
	Stack data;
	Stack min;
}MinStack, *pMinStack;

//初始化 
void MinStackInit(pMinStack s)
{
	assert(s);
	init(&s->min);
	init(&s->data);
}

//入栈
void MinStackPush(pMinStack s, DataType data)
{
	assert(s);
	if (isEmpty(&s->min) || data <= top(&s->min)) {
		pushBack(&s->min, data);
	}
	pushBack(&s->data, data);
}
//出栈
void MinStackPop(pMinStack s)
{
	assert(s);
	if (isEmpty(&s->data)) {
		exit(EXIT_FAILURE);
	}
	if (top(&s->min) == top(&s->data)) {
		pop(&s->min);
	}
	pop(&s->data);
}

//判空
int MinStackEmpty(pMinStack s)
{
	return isEmpty(&s->data);
}

//栈顶元素
DataType MinStackTop(pMinStack s)
{
	if (isEmpty(&s->data)) {
		exit(EXIT_FAILURE);
	}
	return top(&s->data);
}

//栈的长度
int MinStackSize(pMinStack s)
{
	assert(s);
	return stackSize(&s->data);
}

//最小元素
DataType MinStackMin(pMinStack s)
{
	if (isEmpty(&s->min)) {
		exit(EXIT_FAILURE);
	}
	return top(&s->min);
}

void testMinStack()
{
	MinStack minStack;
	MinStackInit(&minStack);
	MinStackPush(&minStack, 3);
	MinStackPush(&minStack, 2);
	MinStackPush(&minStack, 4);
	MinStackPush(&minStack, 6);
	MinStackPush(&minStack, 1);
	int size = MinStackSize(&minStack);
	int emp = MinStackEmpty(&minStack);
	MinStackPop(&minStack);
	int top = MinStackMin(&minStack);
	MinStackPop(&minStack);
	MinStackPop(&minStack);
	top = MinStackMin(&minStack);
}
