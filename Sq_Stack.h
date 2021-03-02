#include"global.h"

#define STACK_INIT_SIZE 100
#define STACK_INCREMENT 10

#define ElemType char

typedef struct {	ElemType *base;	ElemType *top;	int size;}SqStack;Status InitStack(SqStack &S) {
	S.base = (ElemType *)malloc(sizeof(ElemType)*STACK_INIT_SIZE);
	if (!S.base) return ERROR;
	S.top = S.base;	S.size = STACK_INIT_SIZE;	return OK;}Status deleteStack(SqStack &S) {	S.top = S.base;	S.top = NULL;	S.base = NULL;	S.size = 0;	return OK;}Status Push(SqStack &S, ElemType e) {	if (S.top - S.base >= S.size) {		S.base = (ElemType *)realloc(S.base, (S.size + STACK_INCREMENT) * sizeof(ElemType));		if (!S.base) return ERROR;
		S.top = S.base + S.size;
		S.size += STACK_INCREMENT;	}	*S.top = e;	S.top++;	return OK;}Status Pop(SqStack &S, ElemType &e) {	if (S.top == S.base) return ERROR;	S.top--;	e = *S.top;	return OK;}ElemType GetTop(SqStack S) {	if (S.top <= S.base) 		return ERROR;	return *(S.top-1);}bool isEmpty(SqStack S) {	if (S.top == S.base)
	{
		return true;
	}	return false;}Status visit(SqStack S) {	ElemType *i;	for (i = S.top - 1; i >= S.base; --i)
	{
		cout << *i << ",";
	}	cout << endl;	return OK;}/*void conversion() {	SqStack S;	int num, hex, e;	InitStack(S);	cout << "请输入要转换的数字（10进制）：";	cin >> num;	cout << "请输入要转换的目标进制：";	cin >> hex;	while (num)
	{
		Push(S, num % hex);
		num = num / hex;
	}	while (!isEmpty(S))
	{
		Pop(S, e);
		cout << e;
	}}*/bool matching(char exp[]){	SqStack S;	InitStack(S);	int state = 1;	ElemType e;	int i = 0;	while (exp[i] != '\0')
	{
		switch (exp[i])
		{
		case '[':
		{
			Push(S, exp[i]);
			break;
		}
		case '(':
		{
			Push(S, exp[i]);
			break;
		}
		case ')':
		{
			if (!isEmpty(S) && GetTop(S)=='(')
			{
				Pop(S, exp[i]);
			}
			else
			{
				state = 0;
			}
			break;
		}
		case ']':
		{
			if (!isEmpty(S) && GetTop(S) == '[')
			{
				Pop(S, e);
			}
			else
			{
				state = 0;
			}
			break;
		}
		} 
		i++;
	}	if (state&&isEmpty(S))  
		return true;
	else
		return false;}bool In(char e)//判断读入字符是否为运算符 
{
	if (e == '+' || e == '-' || e == '*' || e == '/' || e == '(' || e == ')' || e == '#')
		return true;//是 
	else
		return false; //不是 
}
char Precede(char a, char b)//比较运算符的优先级 
{
	char f;
	if (a == '+' || a == '-')
	{
		if (b == '+' || b == '-' || b == ')' || b == '#')
			f = '>';
		else if (b == '*' || b == '/' || b == '(')
			f = '<';
	}
	else if (a == '*' || a == '/')
	{
		if (b == '+' || b == '-' || b == '*' || b == '/' || b == ')' || b == '#')
			f = '>';
		else if (b == '(')
			f = '<';
	}
	else if (a == '(')
	{
		if (b == '+' || b == '-' || b == '*' || b == '/' || b == '(')
			f = '<';
		else if (b == ')')
			f = '=';
	}
	else if (a == ')')
	{
		if (b == '+' || b == '-' || b == '*' || b == '/' || b == ')' || b == '#')
			f = '>';
	}
	else if (a == '#')
	{
		if (b == '+' || b == '-' || b == '*' || b == '/' || b == '(')
			f = '<';
		else if (b == '#')
			f = '=';
	}
	return f;
}
char Operate(char a, char theta, char b)//运算 
{
	char c;
	a = a - '0';//转整数
	b = b - '0';
	if (theta == '+')
		c = a + b + '0';
	else if (theta == '-')
		c = a - b + '0';
	else if (theta == '*')
		c = a * b + '0';
	else if (theta == '/')
		c = a / b + '0';
	return c;
}
int EvaluateExpression()
{
	SqStack OPND, OPTR;
	char ch, a, b, theta, x;
	InitStack(OPND);//寄存操作数和运算结果 
	InitStack(OPTR);//寄存运算符 
	Push(OPTR, '#');
	ch = getchar();
	while (ch != '#' || GetTop(OPTR) != '#')
	{
		if (!In(ch)) 
		{
			Push(OPND, ch);
			ch = getchar();
		}
		else
		{
			switch (Precede(GetTop(OPTR), ch))
			{
			case '<':
				Push(OPTR, ch);
				ch = getchar();
				break;
			case '>':
				Pop(OPTR, theta);
				Pop(OPND, b);
				Pop(OPND, a);
				Push(OPND, Operate(a, theta, b));
				break;
			case '=':
				Pop(OPTR, x);
				ch = getchar();
				break;
			}
		}
	}
	return GetTop(OPND) - '0';
}
/*void LineEdit() {	SqStack S;	InitStack(S);	char c;	char ch = getchar();	while (ch != EOF) { //EOF为全文结束符  		while (ch != '\n') {			switch (ch) {			case '#': Pop(S, c); break;			case '@': S.top = S.base; break;  // 重置S为空栈 			default : Push(S, ch);  break;			}			ch = getchar();  // 从终端接收下一个字符 		}		//SendData();     //将从栈底到栈顶的字符传送至调用过程的数据区；		S.top = S.base;      // 重置S为空栈 		if (ch != EOF)  			ch = getchar();	}	deleteStack(S);}*/