#pragma once
#include"global.h"

#define n 6
#define MaxNum 1000  /*定义一个最大整数*/

/*定义邻接矩阵类型*/
typedef int adjmatrix[n + 1][n + 1];   /*不使用第0个单元*/

typedef struct
{
	int beginVertex, endVertex;      			//生成树的起点和终点        
	int weight;							        //边的权重
}Edge, *EdgeNode;

int arcnum;     /*边的数量*/

/*建立图的邻接矩阵*/
void CreatMatrix(adjmatrix GA)
{
	int i, j, k, e;
	printf("图中有%d个顶点\n", n);//6
	for (i = 1; i <= n; i++)
	{
		for (j = 1; j <= n; j++)
		{
			if (i == j)
			{
				GA[i][j] = 0;         /*对角线的值置为0*/
			}
			else
			{
				GA[i][j] = MaxNum;    /*其他位置的值置初始化为一个最大整数*/
			}
		}
	}
	printf("请输入图中边的条数：");
	cin >> arcnum;
	printf("请输入边的信息，依照起点，终点，权值的形式输入：（例: 1,2,6）\n");
	for (k = 1; k <= arcnum; k++)
	{
		cout << "第" << k << "条边为：";
		scanf_s("%d,%d,%d", &i, &j, &e);  /*读入边的信息*/
		GA[i][j] = e;
		GA[j][i] = e;
	}
}

/*初始化图的边集数组，用于Kruskal算法*/
void InitEdge(EdgeNode GE, int m)
{
	int i;
	for (i = 1; i <= m; i++)
	{
		GE[i].weight = 0;
	}
}

/*依据图的邻接矩阵生成图的边集数组，用于Kruskal算法*/
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

//按升序排列图的边集数组，用于Kruskal算法
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

/*利用普里姆算法从初始点v出发求邻接矩阵表示的图的最小生成树*/
void Prim(adjmatrix GA, EdgeNode T)
{
	int i, j, k, min, u, m, w;
	Edge temp;
	/*给T赋初值。相应为v1依次到其余各顶点的边*/
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
	/*进行n-1次循环，每次求出最小生成树中的第k条边*/
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
		/*把最短边对调到k-1下标位置*/
		temp = T[k];
		T[k] = T[m];
		T[m] = temp;
		/*把新增加最小生成树T中的顶点序号赋给j*/
		j = T[k].endVertex;
		/*改动有关边，保留最小的边在T数组中，放弃大的边*/
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

/*输出边集数组的每条边*/
void OutEdge(EdgeNode GE, int e)
{
	int i;
	printf("依照起点，终点。权值的形式输出的最小生成树为：\n");
	for (i = 1; i <= e; i++)
	{
		printf("%d,%d,%d\n", GE[i].beginVertex, GE[i].endVertex, GE[i].weight);
	}
	printf("=============================\n");
}