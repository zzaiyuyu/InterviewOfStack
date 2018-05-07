#if 0
//ջӦ��������
#include "stack.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
//ƥ�䷵��1
int match_brackets(const char * string)
{
	if (NULL == string) {
		return 1;
	}
	Stack s;
	init(&s);
	//���������Ŷ࣬�����Ŷ࣬����������˳��ͬ�������
	while (*string) {
		if (*string == '(' || *string == '[' || *string == '{') {
			pushBack(&s, *string);
			string++;
			continue;
		}
		else if (*string == ')' || *string == '}' || *string == ']') {
			char tmp = top(&s);
			pop(&s);
			if ((*string == ')'&& tmp == '(') ||
				(*string == '}'&& tmp == '{') ||
				(*string == ']'&& tmp == '[') ) {
				string++;
				continue;
			}
			else {
				//˳��ƥ��
				return 0;
			}
		}
		else {
			string++;
		}
	}
	//ֻ�е��ַ���ɨ�����ˣ�����ջ�����Ŷ�ƥ�����ˣ�������ȷƥ��
	if (isEmpty(&s)) {
		return 1;
	}
	return 0;
}
//���󴮷���-1,�������ر��ʽֵ
int exp(const char* str)
{
	if(NULL == str){
		return 0;
	}
	char *low = str;
	char *fast = str;
	Stack s;
	init(&s);
	//�ų�����ǰ����ո�
	while (*low && *low == ' ') {
		low++;
	}
	fast = low;
	//��ʼ����
	while (*fast) {
		if (isdigit(*low)) {
			//��ȡһ������
			int sum = 0;
			while (*fast && isdigit(*fast)) {
				sum = sum * 10 + (*fast - '0');
				fast++;
			}
			pushBack(&s, sum);
		}
		else if(*low=='+' || *low == '-' || *low == '*' || *low == '/'){
			//�ǲ�����
			int tmp = 0;
			switch (*low) {
			case '+':
				tmp = top(&s); pop(&s); 
				tmp += top(&s); pop(&s);
				pushBack(&s, tmp);
				break;
			case '-':
				tmp = top(&s); pop(&s);
				tmp = top(&s) - tmp; pop(&s);
				pushBack(&s, tmp);
				break;
			case '*':
				tmp = top(&s); pop(&s);
				tmp *= top(&s); pop(&s);
				pushBack(&s, tmp);
				break;
			case '/':
				tmp = top(&s); pop(&s);
				tmp = top(&s) / tmp; pop(&s);
				pushBack(&s, tmp);
				break;
			default:break;
			}
			fast++;
		}
		else {
			return  -1;
		}
		//low��fastָ����һ���ַ���ͷ
		
		while (*fast && *fast == ' ') {
			fast++;
		}
		low = fast;
	}

	return top(&s);
}

int main()
{
	//const char *string = "(()()abc{[]})";
	//int ret = match_brackets(string);
	const char *str = "   12 3 4 + * 6 - 8 2 / +";
	int ans = exp(str);
	system("pause");
}

#endif