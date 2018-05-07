#if 0
//π≤œÌ’ª
#include <malloc.h>
#include <stdlib.h>
#include <assert.h>
#define DataType int
#define Capacity 100
typedef struct SHARE {
	DataType *arr;
	int top1;
	int top2;
}ShareStack, *pShareStack;

void InitSStack(pShareStack s)
{
	s->arr = (DataType*)malloc(sizeof(DataType)*Capacity);
	if (NULL == s->arr) {
		exit(EXIT_FAILURE);
	}
	s->top1 = 0;
	s->top2 = 1;
}
void PushSStack(pShareStack s, int k, DataType data)
{
	assert(s);
	if (1 == k) {
		s->arr[s->top1] = data;
		s->top1 += 2;
	}
	else if (2 == k) {
		s->arr[s->top2] = data;
		s->top2 += 2;
	}
}

void PopSStack(pShareStack s, int k)
{
	if (s->top1 > 0 && s->top2 > 1) {
		if (1 == k) {
			s->top1 -= 2;
		}
		else if (2 == k) {
			s->top2 -= 2;
		}
	}
}

DataType TopSStack(pShareStack s, int k)
{
	if (s->top1 > 0 && s->top2 > 1) {
		if (1 == k) {
			return s->arr[s->top1 - 2];
		}
		else if (2 == k) {
			return s->arr[s->top2 - 2];
		}
	}
	exit(EXIT_FAILURE);
}

int main()
{
	ShareStack s;
	InitSStack(&s);
	PushSStack(&s, 1, 1);
	PushSStack(&s, 2, 2);
	PushSStack(&s, 1, 3);
	int ret = TopSStack(&s, 1);
	PopSStack(&s, 1);
	PopSStack(&s, 2);

}
#endif