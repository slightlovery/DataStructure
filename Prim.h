#pragma once
#include"global.h"

#define n 6
#define MaxNum 1000  /*����һ���������*/

/*�����ڽӾ�������*/
typedef int adjmatrix[n + 1][n + 1];   /*��ʹ�õ�0����Ԫ*/

typedef struct
{
	int beginVertex, endVertex;      			//�������������յ�        
	int weight;							        //�ߵ�Ȩ��
}Edge, *EdgeNode;

int arcnum;     /*�ߵ�����*/

/*����ͼ���ڽӾ���*/
void CreatMatrix(adjmatrix GA)
{
	int i, j, k, e;
	printf("ͼ����%d������\n", n);//6
	for (i = 1; i <= n; i++)
	{
		for (j = 1; j <= n; j++)
		{
			if (i == j)
			{
				GA[i][j] = 0;         /*�Խ��ߵ�ֵ��Ϊ0*/
			}
			else
			{
				GA[i][j] = MaxNum;    /*����λ�õ�ֵ�ó�ʼ��Ϊһ���������*/
			}
		}
	}
	printf("������ͼ�бߵ�������");
	cin >> arcnum;
	printf("������ߵ���Ϣ��������㣬�յ㣬Ȩֵ����ʽ���룺����: 1,2,6��\n");
	for (k = 1; k <= arcnum; k++)
	{
		cout << "��" << k << "����Ϊ��";
		scanf_s("%d,%d,%d", &i, &j, &e);  /*����ߵ���Ϣ*/
		GA[i][j] = e;
		GA[j][i] = e;
	}
}

/*��ʼ��ͼ�ı߼����飬����Kruskal�㷨*/
void InitEdge(EdgeNode GE, int m)
{
	int i;
	for (i = 1; i <= m; i++)
	{
		GE[i].weight = 0;
	}
}

/*����ͼ���ڽӾ�������ͼ�ı߼����飬����Kruskal�㷨*/
void GetEdgeSet(adjmatrix GA, EdgeNode GE)
{
	int i, j, k = 1;
	for (i = 1; i <= n; i++)
	{
		for (j = i + 1; j <= n; j++)
		{
			if (GA[i][j] != 0 && GA[i][j] != MaxNum)
			{
				GE[k].beginVertex = i;
				GE[k].endVertex = j;
				GE[k].weight = GA[i][j];
				k++;
			}
		}
	}
}

//����������ͼ�ı߼����飬����Kruskal�㷨
/*
void SortEdge(EdgeNode GE, int m)
{
	int i, j, k;
	Edge temp;
	for (i = 1; i < m; i++)
	{
		k = i;
		for (j = i + 1; j <= m; j++)
		{
			if (GE[k].weight > GE[j].weight)
			{
				k = j;
			}
		}
		if (k != i)
		{
			temp = GE[i];
			GE[i] = GE[k];
			GE[k] = temp;
		}
	}
}
*/

/*��������ķ�㷨�ӳ�ʼ��v�������ڽӾ����ʾ��ͼ����С������*/
void Prim(adjmatrix GA, EdgeNode T)
{
	int i, j, k, min, u, m, w;
	Edge temp;
	/*��T����ֵ����ӦΪv1���ε����������ı�*/
	k = 1;
	for (i = 1; i <= n; i++)
	{
		if (i != 1)
		{
			T[k].beginVertex = 1;
			T[k].endVertex = i;
			T[k].weight = GA[1][i];
			k++;
		}
	}
	/*����n-1��ѭ����ÿ�������С�������еĵ�k����*/
	for (k = 1; k < n; k++)
	{
		min = MaxNum;
		m = k;
		for (j = k; j < n; j++)
		{
			if (T[j].weight < min)
			{
				min = T[j].weight; 
				m = j;
			}
		}
		/*����̱߶Ե���k-1�±�λ��*/
		temp = T[k];
		T[k] = T[m];
		T[m] = temp;
		/*����������С������T�еĶ�����Ÿ���j*/
		j = T[k].endVertex;
		/*�Ķ��йرߣ�������С�ı���T�����У�������ı�*/
		for (i = k + 1; i < n; i++)
		{
			u = T[i].endVertex;
			w = GA[j][u];
			if (w < T[i].weight)
			{
				T[i].weight = w; 
				T[i].beginVertex = j;
			}
		}
	}
}

/*����߼������ÿ����*/
void OutEdge(EdgeNode GE, int e)
{
	int i;
	printf("������㣬�յ㡣Ȩֵ����ʽ�������С������Ϊ��\n");
	for (i = 1; i <= e; i++)
	{
		printf("%d,%d,%d\n", GE[i].beginVertex, GE[i].endVertex, GE[i].weight);
	}
	printf("=============================\n");
}