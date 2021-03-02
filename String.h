#pragma once
#include"global.h"
#include<string>

#define MAXSTRLEN 80

typedef struct
{
	unsigned char data[MAXSTRLEN + 1];
	int length;
}SString;

typedef struct {
	char *ch;
	int length;
}HString;

typedef struct Chunk
{
	char ch[MAXSTRLEN];
	struct Chunk *next;
};

typedef struct {
	Chunk *head, *tail;
	int curlen;
}LString;


//通过一个字符数组cstr来构建一个SString串
Status StrAssign(SString &s, char cstr[])
{
	int i;
	for (i = 1; cstr[i - 1] != '\0'; i++) {
		if (i > MAXSTRLEN) return ERROR;
		s.data[i] = cstr[i - 1];
	}
	s.length = i - 1;
	cout << s.length << endl;
	return OK;
}

//字符串的输出
Status StrOutput(SString S)
{
	int i;
	cout << "串的元素为:";
	for (i = 1; i <= S.length; i++)
		cout << S.data[i] << ",";
	cout << endl;
	return OK;
}


//  符串的拼接
Status Concat(SString &T, SString S1, SString S2)
{
	int i;
	bool uncut;
	if (S1.length + S2.length <= MAXSTRLEN)
	{
		for (i = 1; i <= S1.length; i++)
			T.data[i] = S1.data[i];
		for (i = S1.length + 1; i <= S1.length + S2.length; i++)
			T.data[i] = S2.data[i - S1.length];
		T.length = S1.length + S2.length;
		uncut = TRUE;
	}
	else if (S1.length < MAXSTRLEN)
	{
		for (i = 1; i <= S1.length; i++)
			T.data[i] = S1.data[i];
		for (i = S1.length + 1; i <= MAXSTRLEN; i++)
			T.data[i] = S2.data[i - S1.length];
		T.length = MAXSTRLEN;
		uncut = FALSE;
	}
	else
	{
		for (i = 0; i <= MAXSTRLEN; i++)
			T.data[i] = S1.data[i];
		uncut = FALSE;
	}
	return uncut;
}

//  返回需要的子字符串
Status SubString(SString &Sub, SString S, int pos, int len)
{
	int i;
	if (pos<1 || pos>S.length || len<0 || len>S.length - pos + 1)
		return ERROR;
	for (i = 1; i <= len; i++)
		Sub.data[i] = S.data[pos + i - 1];
	Sub.length = len;
	return OK;
}

//  串的长度
Status GetStrLength(SString S)
{
	return S.length;
}


//  清除串
Status ClearStr(SString &S)
{
	int i;
	for (i = 1; i <= S.length; i++)
		S.data[i] = '\0';
	S.length = 0;
	return OK;
}


//  判断串是否为空
Status StrIsEmpty(SString S)
{
	if (S.length = 0)
		return OK;
	else
		return ERROR;
}


//  将串S复制给T
Status StrCopy(SString &T, SString S)
{
	int i;
	for (i = 0; i <= S.length; i++)
	{
		T.data[i] = S.data[i];
	}
	return OK;
}


//  查询子串，BF算法
Status StrIndex(SString S, SString T, int pos)
{
	int i = pos + 1, j = 1;
	while (i <= S.length&&j <= T.length)
	{
		if (S.data[i] == T.data[j])
		{
			++i; ++j;
		}
		else
		{
			i = i - j + 2; j = 1;  //i退回到原本位置的后一个位置
		}
	}
	if (j > T.length)return i - T.length;
	else return FALSE;
}


//判断串是否相等
bool StrCompare(SString S, SString T)
{
	if (T.length != S.length)
		return FALSE;
	else
	{
		int i;
		for (i = 1; i <= T.length; i++)
		{
			if (T.data[i] != S.data[i])
			{
				return FALSE;
			}
		}
	}
	return TRUE;
}


//串的插入
Status StrInsert(SString &S, int pos, SString T)
{
	int i;
	if (S.length + T.length > MAXSTRLEN || pos <= 0 || pos > S.length)
		return ERROR;
	for (i = T.length + S.length; i >= S.length; i--)
		S.data[i] = S.data[i - T.length];
	for (i = 1; i <= T.length; i++)
		S.data[pos + i - 1] = T.data[i];
	S.length += T.length;
	return OK;
}



//串的删除
Status StrDelete(SString &S, int pos, int len)
{
	int i;
	if (pos<1 || pos>S.length || len<0 || len>S.length - pos + 1)
		return ERROR;
	for (i = pos; i <= pos + len; i++)
		S.data[i] = S.data[i + 1];
	S.length = S.length - len;
	return OK;
}

//销毁串
Status DestroyStr(SString &S)
{
	int i;
	for (i = MAXSTRLEN; i >= 0; i--)
		free(S.data + i);
	return OK;
}


//kmp的next数组
void get_next(SString S, int *next)
{
	int i = 1, j = 0;
	next[1] = 0;
	while (i < S.length)
	{
		if (j == 0 || S.data[i] == S.data[j])
		{
			++i;
			++j;
			next[i] = j;
		}
		else {
			j = next[j];
		}
	}
	for (i = 1; i <= S.length; i++)
		cout << next[i];
	cout << endl;
}

//kmp算法
int KMP(SString S, SString T)
{
	int i = 1;
	int j = 1;
	int next[MAXSTRLEN];
	get_next(T, next);
	while (i <= S.length && j <= T.length) {
		if (j == 0 || S.data[i] == T.data[j]) {
			++i;
			++j;
		}
		else {
			j = next[j];
		}
	}
	if (j > T.length)
		return i - T.length;
	else return 0;
}
