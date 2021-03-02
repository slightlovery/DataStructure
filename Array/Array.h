#pragma once

#include"global.h"

#define MAXSIZE 100

typedef struct
{
	int i;//行 
	int j;//列 
	ElemType e;//值 
}Triple;

typedef struct
{
	Triple data[MAXSIZE + 1];
	int mu, nu, tu;//行、列、非零数
}TSMatrix;

//打印矩阵
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

//矩阵的初始化以课本上的 a.data 为原型 
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

//普通转置
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
}//行列转置 时间复杂度为 O(nu * tu);

void FastTransposeSMatrix(TSMatrix M, TSMatrix &T)
{
	int t, num[100], p, q, col, cpot[100];
	T.mu = M.nu;
	T.nu = M.mu;
	T.tu = M.tu;//改变三元组的值 
	if (T.tu) {
		for (col = 1; col <= M.nu; col++)
			num[col] = 0;
		for (t = 1; t <= M.tu; t++)
			num[M.data[t].j]++;//每一列中非零元素的个数 
		cpot[1] = 1;//chushiweizhi
		for (col = 2; col <= M.nu; col++)
			cpot[col] = cpot[col - 1] + num[col - 1];//下一行第一个 
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
}//快速转置，时间复杂度为 O(nu+tu)




//----------------------------十字链表-------------------------//
typedef struct OLNode
{
	int row, col; /*非零元素的行和列下标*/
	int value;
	struct OLNode *right; /*非零元素所在行表、列表的后继链域*/
	struct OLNode *down;
}OLNode, *OLink;

typedef struct
{
	OLink *row_head; /*行、列链表的头指针向量*/
	OLink *col_head;
	int m, n, len; /*稀疏矩阵的行数、列数、非零元素的个数*/
}CrossList;



/*建立稀疏矩阵的十字链表算法*/
void CreateCrossList(CrossList *M)
{
	int m, n, t, i, j, e;
	OLNode* p;
	OLNode* q;
	/*采用十字链表存储结构，创建稀疏矩阵M*/
	scanf_s("%d%d%d", &m, &n, &t); /*输入M的行数,列数和非零元素的个数*/
	M->m = m;
	M->n = n;
	M->len = t;
	if (!(M->row_head = (OLink *)malloc((m + 1) * sizeof(OLink))))
		exit(OVERFLOW);
	if (!(M->col_head = (OLink *)malloc((n + 1) * sizeof(OLink))))
		exit(OVERFLOW);
	/*初始化行、列头指针向量，各行、列链表为空的链表*/
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
			/*寻找行表中的插入位置*/
			for (q = M->row_head[i]; q->right&&q->right->col < j; q = q->right); /*空循环体*/
			p->right = q->right;
			q->right = p; /*完成插入*/
		}
		if (M->col_head[j] == NULL)
		{
			M->col_head[j] = p;
			p->down = NULL;
		}
		else
		{
			/*寻找列表中的插入位置*/
			for (q = M->col_head[j]; q->down&&q->down->row < i; q = q->down); /*空循环体*/
			p->down = q->down;
			q->down = p; /*完成插入*/
		}
	}
}
