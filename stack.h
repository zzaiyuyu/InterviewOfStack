#pragma once
//extern struct position;
//typedef struct position Position;
//#define DataType Position
#define DataType char
//��̬ջ
typedef struct stack {
	DataType *array;
	int top;
	int capacity;
}Stack;

void init(Stack *s);//��ʼ��
void pushBack(Stack *s, DataType data);//��ջ
void pop(Stack *s);//��ջ
DataType top(Stack *s);//��ȡջ��Ԫ��
int  checkCapacity(Stack *s);//�������������
void destory(Stack* s);//����ջ   
int isEmpty(Stack* s);//�п�
int stackSize(Stack * s);//��ȡջԪ�ظ���
void printStack(Stack * min);//�ӵ׵�����ӡջ

