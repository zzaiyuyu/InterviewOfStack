//��ջ����
#include "stack.h"
#include <assert.h>
#include <stdlib.h>

typedef struct QueueBySTACK {
	Stack stackA;
	Stack stackB;
}QueueByStack, *pQueueByStack;

//��ʼ������
void QueueBy2StackInit(pQueueByStack q)
{
	assert(q);
	init(&q->stackA);
	init(&q->stackB);
}

//���
void QueueBy2StackPush(pQueueByStack q, DataType data)
{
	//Aջ�룬Bջ��
	assert(q);
	pushBack(&q->stackA, data);
}

//����
void QueueBy2StackPop(pQueueByStack q)
{
	assert(q);
	if (isEmpty(&q->stackB)) {
		while (!isEmpty(&q->stackA)) {
			pushBack(&q->stackB, top(&q->stackA));
			pop(&q->stackA);
		}
	}
	if (isEmpty(&q->stackB)) {
		exit(EXIT_FAILURE);
	}
	pop(&q->stackB);
}

//�п�
int QueueBy2StackEmpty(pQueueByStack q)
{
	if (isEmpty(&q->stackA) && isEmpty(&q->stackB)) {
		return 1;
	}
	else
		return 0;
}
//�鿴��ͷԪ��
DataType QueueBy2StackFrontData(pQueueByStack q) {
	assert(q);
	if (isEmpty(&q->stackB)) {
		while (!isEmpty(&q->stackA)) {
			pushBack(&q->stackB, top(&q->stackA));
			pop(&q->stackA);
		}
	}
	if (isEmpty(&q->stackB)) {
		exit(EXIT_FAILURE);
	}
	return top(&q->stackB);
}

//�鿴��βԪ��
DataType QueueBy2StackTailData(pQueueByStack q) {
	assert(q);
	if (isEmpty(&q->stackA)) {
		exit(EXIT_FAILURE);
	}
	return top(&q->stackA);
}

//�鿴���г���
int QueueBy2StackSize(pQueueByStack q)
{
	return stackSize(&q->stackA) + stackSize(&q->stackB);
}

void testQueueByStack()
{
	QueueByStack q;
	QueueBy2StackInit(&q);
	QueueBy2StackPush(&q, 1);
	QueueBy2StackPush(&q, 2);
	QueueBy2StackPush(&q, 3);
	QueueBy2StackPop(&q);
	QueueBy2StackPush(&q, 4);
	QueueBy2StackPush(&q, 5);
	int head = QueueBy2StackFrontData(&q);
	int tail = QueueBy2StackTailData(&q);
	int size = QueueBy2StackSize(&q);

}