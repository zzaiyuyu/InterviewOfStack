#if 0
//栈应用面试题
#include "stack.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
//匹配返回1
int match_brackets(const char * string)
{
	if (NULL == string) {
		return 1;
	}
	Stack s;
	init(&s);
	//考虑左括号多，右括号多，和括号类型顺序不同三种情况
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
				//顺序不匹配
				return 0;
			}
		}
		else {
			string++;
		}
	}
	//只有当字符串扫描完了，并且栈中括号都匹配完了，才是正确匹配
	if (isEmpty(&s)) {
		return 1;
	}
	return 0;
}
//错误串返回-1,其他返回表达式值
int exp(const char* str)
{
	if(NULL == str){
		return 0;
	}
	char *low = str;
	char *fast = str;
	Stack s;
	init(&s);
	//排除掉串前多个空格
	while (*low && *low == ' ') {
		low++;
	}
	fast = low;
	//开始处理
	while (*fast) {
		if (isdigit(*low)) {
			//读取一个数字
			int sum = 0;
			while (*fast && isdigit(*fast)) {
				sum = sum * 10 + (*fast - '0');
				fast++;
			}
			pushBack(&s, sum);
		}
		else if(*low=='+' || *low == '-' || *low == '*' || *low == '/'){
			//是操作符
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
		//low和fast指向下一个字符开头
		
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