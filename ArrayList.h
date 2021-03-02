#pragma once
#include "global.h"

typedef struct {
	int *elem;
	int length;
	int listsize;
}SqList;

int InitList_Sq(SqList &L)//����һ���յ����Ա�
{
	L.elem = (int *)malloc(LIST_INIT_SIZE * sizeof(int));
	if (!L.elem)
		printf("����ռ�ʧ��!\n");
	else
	{
		L.length = 0;
		L.listsize = LIST_INIT_SIZE;
	}
	return 0;
}

int ListInsert(SqList &L, int i, int e)//���Ա�Ĳ���
{
	if (i<1 || i>L.length + 1)
		printf("����λ�ò��Ϸ�!\n");
	else if (L.length >= L.listsize)
	{
		int *newbase = (int *)realloc(L.elem, (LIST_INIT_SIZE + LISTINCREMENT) * sizeof(int));
		if (!newbase)
			printf("�洢�ռ����ʧ��!\n");
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

int ListDelete(SqList &L, int i, int e)//���Ա��ɾ��
{
	if (i<1 || i>L.length)
		printf("ɾ��λ�ò��Ϸ�!\n");
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

int MergeList_Sq(SqList La, SqList Lb, SqList &Lc)//�鲢
{
	int *pa = La.elem;
	int *pb = Lb.elem;
	Lc.listsize = Lc.length = La.length + Lb.length;
	int *pc = Lc.elem = (int *)malloc(Lc.listsize * sizeof(int));
	if (!Lc.elem)
		printf("����ռ�ʧ��!\n");
	else
	{
		int *pa_last = La.elem + La.length - 1;
		int *pb_last = Lb.elem + Lb.length - 1;
		while (pa <= pa_last && pb <= pb_last) //�鲢
		{
			if (*pa <= *pb) *pc++ = *pa++;
			else  *pc++ = *pb++;
		}
		while (pa <= pa_last) *pc++ = *pa++;//����La��ʣ��Ԫ��
		while (pb <= pb_last) *pc++ = *pb++;//����Lb��ʣ��Ԫ��

		//����ϲ���Ľ��
		printf("�ϲ���Ľ��Ϊ:\n");
		for (int i = 1; i <= Lc.length; i++)
			printf("%d ", Lc.elem[i - 1]);
		printf("\n");
	}
	return 0;
}

void PrintSqList(SqList list){
	cout << "˳���Ϊ��" ;
	for (int i = 0; i < list.length; i++)
	{
		cout << list.elem[i] << ",";
	}
	cout << endl;
}