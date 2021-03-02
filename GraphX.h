#pragma once
#include"global.h"
#include<queue>


#define MaxVerNum 100 //顶点最大数目值
#define VexType char //顶点数据类型
#define EdgeType int //边数据类型,无向图时邻接矩阵对称，有权值时表示权值，没有时1连0不连


typedef struct Graph
{
	VexType Vex[MaxVerNum];//顶点表
	EdgeType Edge[MaxVerNum][MaxVerNum];//边表
	int vexnum, arcnum;//顶点数、边数
}Graph;

//*********************************************基本操作函数*****************************************//
//初始化函数 参数：图G 作用：初始化图的顶点表，邻接矩阵等
void InitGraph(Graph &G)
{
	memset(G.Vex, '#', sizeof(G.Vex));//初始化顶点表
	memset(G.Edge, 0, sizeof(G.Edge));//初始化边表
	G.arcnum = G.vexnum = 0;          //初始化顶点数、边数
}


//插入顶点函数 参数：图G,顶点v 作用：在图G中插入顶点v,即改变顶点表
bool InsertNode(Graph &G, VexType v)
{
	if (G.vexnum < MaxVerNum)
	{
		G.Vex[G.vexnum++] = v;
		return true;
	}
	return false;
}

//插入边函数 参数：图G,某边两端点v和w 作用：在图G两点v,w之间加入边，即改变邻接矩阵
bool InsertEdge(Graph &G, VexType v, VexType w)// a b 
{
	int p1, p2;//v,w两点下标
	p1 = p2 = -1;//初始化
	for (int i = 0; i < G.vexnum; i++)//寻找顶点下标
	{
		if (G.Vex[i] == v) p1 = i;
		if (G.Vex[i] == w) p2 = i;
	}
	if (p1 != -1 && p2 != -1)//两点均可在图中找到
	{
		G.Edge[p1][p2] = G.Edge[p2][p1] = 1;//无向图邻接矩阵对称
		G.arcnum++;
		return true;
	}
	return false;
}


//判断是否存在边(v,w)函数 参数：图G，某边两端点v和w 作用：判断是否存在边(v,w) 
bool Adjancent(Graph G, VexType v, VexType w)
{
	int p1, p2;//v,w两点下标
	p1 = p2 = -1;//初始化
	for (int i = 0; i < G.vexnum; i++)//寻找顶点下标
	{
		if (G.Vex[i] == v) p1 = i;
		if (G.Vex[i] == w) p2 = i;
	}
	if (p1 != -1 && p2 != -1)//两点均可在图中找到
	{
		if (G.Edge[p1][p2] == 1)//存在边
		{
			return true;
		}
		return false;
	}
	return false;
}

//**********************************************功能实现函数*****************************************//
//打印图的顶点表
void PrintVex(Graph G)
{
	cout << "图的顶点表为：" << endl;
	for (int i = 0; i < G.vexnum; i++)
	{
		cout << G.Vex[i] << " ";
	}
	cout << endl;
	cout << endl;
}
//打印图的边矩阵
void PrintEdge(Graph G)
{
	cout << "其邻接矩阵表示为：" << endl;
	for (int i = 0; i < G.vexnum; i++)
	{
		for (int j = 0; j < G.vexnum; j++)
		{
			cout << G.Edge[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}


//创建图功能实现函数 参数：图G  InsertNode 作用：创建图
void CreateGraph(Graph &G)
{
	VexType v, w;
	int vn, an;//顶点数，边数
	cout << "请输入顶点数目:";
	cin >> vn;
	cout << "请输入边数目:";
	cin >> an;
	cout << "*****请输入所有顶点的值*****"<<endl;
	for (int i = 0; i < vn; i++)
	{
		cout << "请输入第" << i + 1 << "个顶点：";
		cin >> v;
		if (InsertNode(G, v)) continue;//插入点
		else {
			cout << "输入错误！" << endl; break;
		}
	}
	cout << "**********请输入所有边**********" << endl;
	for (int j = 0; j < an; j++)
	{
		cout << "请输入第" << j + 1 << "条边的两个相邻顶点（空格分开）：";
		cin >> v >> w;
		if (InsertEdge(G, v, w)) continue;//插入边
		else {
			cout << "输入错误！" << endl; break;
		}
	}
	cout << "图创建成功!" << endl;
	PrintVex(G);
	PrintEdge(G);
}


bool visited[MaxVerNum];//访问标记数组，用于遍历时的标记


//广度遍历函数 参数：图G,开始结点下标start 作用：宽度遍历
void BFS(Graph G, int start)
{
	queue<int> Q;//辅助队列
	cout << G.Vex[start];//访问结点
	visited[start] = true;
	Q.push(start);//入队
	while (!Q.empty())//队列非空
	{
		int v = Q.front();//得到队头元素
		Q.pop();//出队
		for (int j = 0; j < G.vexnum; j++)//邻接点
		{
			if (G.Edge[v][j] == 1 && !visited[j])//是邻接点且未访问
			{
				cout << "->";
				cout << G.Vex[j];//访问结点
				visited[j] = true;
				Q.push(j);//入队
			}
		}
	}//while
	cout << endl;
}

//深度遍历函数（递归形式）参数：图G,开始结点下标start 作用：深度遍历
void DFS(Graph G, int start)
{
	cout << G.Vex[start];//访问
	visited[start] = true;
	for (int j = 0; j < G.vexnum; j++)
	{
		if (G.Edge[start][j] == 1 && !visited[j])//是邻接点且未访问
		{
			cout << "->";
			DFS(G, j);//递归深度遍历
		}
	}
}


//广度遍历功能实现函数 参数：图G 作用：宽度遍历
void BFSTraverse(Graph G)
{
	for (int i = 0; i < MaxVerNum; i++)//初始化访问标记数组
	{
		visited[i] = false;
	}
	for (int i = 0; i < G.vexnum; i++)//对每个连通分量进行遍历
	{
		if (!visited[i])
			BFS(G, i);
	}
}

//深度遍历功能实现函数 参数：图G 作用：深度遍历
void DFSTraverse(Graph G)
{
	for (int i = 0; i < MaxVerNum; i++)//初始化访问标记数组
	{
		visited[i] = false;
	}
	for (int i = 0; i < G.vexnum; i++)//对每个连通分量进行遍历
	{
		if (!visited[i])
		{
			DFS(G, i); 
			cout << endl;
		}
	}
}
//菜单
void menu()
{
	cout << "************************" << endl;
	cout << "        1.创 建 图      " << endl;
	cout << "        2.广度遍历      " << endl;
	cout << "        3.深度遍历      " << endl;
	cout << "        4.退    出      " << endl;
	cout << "************************" << endl;
	
}

