#pragma once
#include "global.h"

typedef struct {
	int *elem;
	int length;
	int listsize;
}SqList;

int InitList_Sq(SqList &L)//构造一个空的线性表
{
	L.elem = (int *)malloc(LIST_INIT_SIZE * sizeof(int));
	if (!L.elem)
		printf("分配空间失败!\n");
	else
	{
		L.length = 0;
		L.listsize = LIST_INIT_SIZE;
	}
	return 0;
}

int ListInsert(SqList &L, int i, int e)//线性表的插入
{
	if (i<1 || i>L.length + 1)
		printf("输入位置不合法!\n");
	else if (L.length >= L.listsize)
	{
		int *newbase = (int *)realloc(L.elem, (LIST_INIT_SIZE + LISTINCREMENT) * sizeof(int));
		if (!newbase)
			printf("存储空间分配失败!\n");
		else
		{
			L.elem = newbase;
			L.listsize += LISTINCREMENT;
		}
	}
	else
	{
		int *p = &(L.elem[L.length-1]);
		int *q = &(L.elem[i - 1]);
		for (p; p >= q; --p)
			*(p + 1) = *p;
		*q = e;
		L.length++;
	}
	return 0;
}

int ListDelete(SqList &L, int i, int e)//线性表的删除
{
	if (i<1 || i>L.length)
		printf("删除位置不合法!\n");
	else
	{
		int *p = &(L.elem[i - 1]);
		e = *p;
		int *q = L.elem + L.length - 1;
		for (++p; p <= q; ++p)
			*(p - 1) = *p;
		L.length--;
	}
	return 0;
}

int MergeList_Sq(SqList La, SqList Lb, SqList &Lc)//归并
{
	int *pa = La.elem;
	int *pb = Lb.elem;
	Lc.listsize = Lc.length = La.length + Lb.length;
	int *pc = Lc.elem = (int *)malloc(Lc.listsize * sizeof(int));
	if (!Lc.elem)
		printf("分配空间失败!\n");
	else
	{
		int *pa_last = La.elem + La.length - 1;
		int *pb_last = Lb.elem + Lb.length - 1;
		while (pa <= pa_last && pb <= pb_last) //归并
		{
			if (*pa <= *pb) *pc++ = *pa++;
			else  *pc++ = *pb++;
		}
		while (pa <= pa_last) *pc++ = *pa++;//插入La的剩余元素
		while (pb <= pb_last) *pc++ = *pb++;//插入Lb的剩余元素

		//输出合并后的结果
		printf("合并后的结果为:\n");
		for (int i = 1; i <= Lc.length; i++)
			printf("%d ", Lc.elem[i - 1]);
		printf("\n");
	}
	return 0;
}

void PrintSqList(SqList list){
	cout << "顺序表为：" ;
	for (int i = 0; i < list.length; i++)
	{
		cout << list.elem[i] << ",";
	}
	cout << endl;
}