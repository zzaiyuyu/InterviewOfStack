//检测合法入栈序列
#include "stack.h"
#include <stdio.h>
#include <string.h>
int is_leagel(const char *in, const char *out)
{
	if (NULL == in || NULL == out) {
		return 0;
	}
	int lenOfIn = strlen(in);
	int lenOfOut = strlen(out);
	if (lenOfIn == lenOfOut) {
		Stack s;
		init(&s);
		while (*out != '\0') {
			if (isEmpty(&s) || *out != top(&s)) {
				if (*in == '\0') {
					return 0;
				}
				pushBack(&s, *in);
				in++;
			}
			else {
				//栈不空且out和栈顶元素相等
				pop(&s);
				out++;
			}
		}
		return 1;
	}
	return 0;
}
int main()
{
	const char *in = "12345";
	const char *out = "35421";
	int ret = is_leagel(in, out);
}