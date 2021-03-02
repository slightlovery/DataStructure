#pragma once

#include"global.h"

#define MAXSIZE 100

typedef struct
{
	int i;//�� 
	int j;//�� 
	ElemType e;//ֵ 
}Triple;

typedef struct
{
	Triple data[MAXSIZE + 1];
	int mu, nu, tu;//�С��С�������
}TSMatrix;

//��ӡ����
void print(TSMatrix M) {
	int p, q, m = 1;
	for (p = 1; p <= M.mu; p++)
		for (q = 1; q <= M.nu; q++) {
			if (M.data[m].i == p && M.data[m].j == q) {
				//cout <<  M.data[m].e << ",";
				printf("%2d ", M.data[m].e);
				m++;
			}
			else
				cout  << " 0 ";
			if (q == M.nu)
				cout << endl;
		}
	cout << endl;
}

void addTriple(TSMatrix &M, Triple T) {
	M.tu++;
	M.data[M.tu].i = T.i;
	M.data[M.tu].j = T.j;
	M.data[M.tu].e = T.e;
}

//����ĳ�ʼ���Կα��ϵ� a.data Ϊԭ�� 
void CreateSMatrix(TSMatrix &M) {
	M.mu = 6;
	M.nu = 7;
	M.tu = 0;
	addTriple(M, { 1,2,12 });
	addTriple(M, { 1,3,9 });
	addTriple(M, { 3,1,-3 });
	addTriple(M, { 3,6,14 });
	addTriple(M, { 4,3,24 });
	addTriple(M, { 5,2,18 });
	addTriple(M, { 6,1,15 });
	addTriple(M, { 6,4,-7 });
}

//��ͨת��
void TransposeSMatrix(TSMatrix M, TSMatrix &T)
{
	int p, q, col;
	T.mu = M.nu;
	T.nu = M.mu;
	T.tu = M.tu;
	if (T.tu) {
		q = 1;
		for (col = 1; col <= M.nu; col++)
			for (p = 1; p <= M.tu; p++)
				if (M.data[p].j == col) {
					T.data[q].i = M.data[p].j;
					T.data[q].j = M.data[p].i;
					T.data[q].e = M.data[p].e;
					q++;
				}
	}
	cout << endl;
}//����ת�� ʱ�临�Ӷ�Ϊ O(nu * tu);

void FastTransposeSMatrix(TSMatrix M, TSMatrix &T)
{
	int t, num[100], p, q, col, cpot[100];
	T.mu = M.nu;
	T.nu = M.mu;
	T.tu = M.tu;//�ı���Ԫ���ֵ 
	if (T.tu) {
		for (col = 1; col <= M.nu; col++)
			num[col] = 0;
		for (t = 1; t <= M.tu; t++)
			num[M.data[t].j]++;//ÿһ���з���Ԫ�صĸ��� 
		cpot[1] = 1;//chushiweizhi
		for (col = 2; col <= M.nu; col++)
			cpot[col] = cpot[col - 1] + num[col - 1];//��һ�е�һ�� 
		for (p = 1; p <= M.tu; p++) {
			col = M.data[p].j;
			q = cpot[col];
			T.data[q].i = M.data[p].j;
			T.data[q].j = M.data[p].i;
			T.data[q].e = M.data[p].e;
			cpot[col]++;
		}
	}
	cout << endl;
}//����ת�ã�ʱ�临�Ӷ�Ϊ O(nu+tu)




//----------------------------ʮ������-------------------------//
typedef struct OLNode
{
	int row, col; /*����Ԫ�ص��к����±�*/
	int value;
	struct OLNode *right; /*����Ԫ�������б��б�ĺ������*/
	struct OLNode *down;
}OLNode, *OLink;

typedef struct
{
	OLink *row_head; /*�С��������ͷָ������*/
	OLink *col_head;
	int m, n, len; /*ϡ����������������������Ԫ�صĸ���*/
}CrossList;



/*����ϡ������ʮ�������㷨*/
void CreateCrossList(CrossList *M)
{
	int m, n, t, i, j, e;
	OLNode* p;
	OLNode* q;
	/*����ʮ������洢�ṹ������ϡ�����M*/
	scanf_s("%d%d%d", &m, &n, &t); /*����M������,�����ͷ���Ԫ�صĸ���*/
	M->m = m;
	M->n = n;
	M->len = t;
	if (!(M->row_head = (OLink *)malloc((m + 1) * sizeof(OLink))))
		exit(OVERFLOW);
	if (!(M->col_head = (OLink *)malloc((n + 1) * sizeof(OLink))))
		exit(OVERFLOW);
	/*��ʼ���С���ͷָ�����������С�������Ϊ�յ�����*/
	for (int h = 0; h < m + 1; h++)
	{
		M->row_head[h] = NULL;
	}
	for (int t = 0; t < n + 1; t++)
	{
		M->col_head[t] = NULL;
	}
	for (scanf_s("%d%d%d", &i, &j, &e); i != 0; scanf_s("%d%d%d", &i, &j, &e))
	{
		if (!(p = (OLNode *)malloc(sizeof(OLNode))))
			exit(OVERFLOW);
		p->row = i;
		p->col = j;
		p->value = e;
		if((M->row_head[i] == NULL) || M->row_head[i] == p)
		   p->right = NULL;
		else
		{
			/*Ѱ���б��еĲ���λ��*/
			for (q = M->row_head[i]; q->right&&q->right->col < j; q = q->right); /*��ѭ����*/
			p->right = q->right;
			q->right = p; /*��ɲ���*/
		}
		if (M->col_head[j] == NULL)
		{
			M->col_head[j] = p;
			p->down = NULL;
		}
		else
		{
			/*Ѱ���б��еĲ���λ��*/
			for (q = M->col_head[j]; q->down&&q->down->row < i; q = q->down); /*��ѭ����*/
			p->down = q->down;
			q->down = p; /*��ɲ���*/
		}
	}
}
