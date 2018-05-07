#include "stack.h"
#include "maze.h"
#include <assert.h>
#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
void init(Stack *s)
{
	assert(s);
	s->capacity = 10;
	s->array = (DataType*)malloc(sizeof(DataType)*(s->capacity));
	if (NULL == s->array) {
		printf("����ʧ��");
	}
	s->top = 0;
}

void pushBack(Stack *s, DataType data)
{
	assert(s);
	if (checkCapacity(s)) {
		s->array[s->top] = data;
		s->top++;
	}
}
int checkCapacity(Stack *s)
{
	assert(s);
	//��Ҫ������
	if (s->top == s->capacity) {
		DataType * new = NULL;
		new = (DataType*)realloc(s->array, sizeof(DataType) * 2 * (s->capacity)); //��������
		if (NULL == new) {
			return 0;
		}
		s->array = new;
		s->capacity *= 2;
	}
	return 1;
}

void pop(Stack *s)
{
	assert(s);
	if (0 == s->top) {
		return;
	}
	s->top--;
}

DataType top(Stack *s)
{
	assert(s);
	if (0 == s->top) {
		printf("û��Ԫ�ؿ�ȡ��");
		exit(EXIT_FAILURE);
	}
	return s->array[(s->top) - 1];
}

void destory(Stack* s)
{
	free(s->array);
	s->array = NULL;
	s->capacity = 0;
	s->top = 0;
}
//�п�
int isEmpty(Stack* s)
{
	assert(s);
	return s->top ? 0 : 1;
}
//��ȡջԪ�ظ���
int stackSize(Stack * s)
{
	assert(s);
	return s->top;
}

