#pragma once
#include"global.h"
#include<queue>


#define MaxVerNum 100 //���������Ŀֵ
#define VexType char //������������
#define EdgeType int //����������,����ͼʱ�ڽӾ���Գƣ���Ȩֵʱ��ʾȨֵ��û��ʱ1��0����


typedef struct Graph
{
	VexType Vex[MaxVerNum];//�����
	EdgeType Edge[MaxVerNum][MaxVerNum];//�߱�
	int vexnum, arcnum;//������������
}Graph;

//*********************************************������������*****************************************//
//��ʼ������ ������ͼG ���ã���ʼ��ͼ�Ķ�����ڽӾ����
void InitGraph(Graph &G)
{
	memset(G.Vex, '#', sizeof(G.Vex));//��ʼ�������
	memset(G.Edge, 0, sizeof(G.Edge));//��ʼ���߱�
	G.arcnum = G.vexnum = 0;          //��ʼ��������������
}


//���붥�㺯�� ������ͼG,����v ���ã���ͼG�в��붥��v,���ı䶥���
bool InsertNode(Graph &G, VexType v)
{
	if (G.vexnum < MaxVerNum)
	{
		G.Vex[G.vexnum++] = v;
		return true;
	}
	return false;
}

//����ߺ��� ������ͼG,ĳ�����˵�v��w ���ã���ͼG����v,w֮�����ߣ����ı��ڽӾ���
bool InsertEdge(Graph &G, VexType v, VexType w)// a b 
{
	int p1, p2;//v,w�����±�
	p1 = p2 = -1;//��ʼ��
	for (int i = 0; i < G.vexnum; i++)//Ѱ�Ҷ����±�
	{
		if (G.Vex[i] == v) p1 = i;
		if (G.Vex[i] == w) p2 = i;
	}
	if (p1 != -1 && p2 != -1)//���������ͼ���ҵ�
	{
		G.Edge[p1][p2] = G.Edge[p2][p1] = 1;//����ͼ�ڽӾ���Գ�
		G.arcnum++;
		return true;
	}
	return false;
}


//�ж��Ƿ���ڱ�(v,w)���� ������ͼG��ĳ�����˵�v��w ���ã��ж��Ƿ���ڱ�(v,w) 
bool Adjancent(Graph G, VexType v, VexType w)
{
	int p1, p2;//v,w�����±�
	p1 = p2 = -1;//��ʼ��
	for (int i = 0; i < G.vexnum; i++)//Ѱ�Ҷ����±�
	{
		if (G.Vex[i] == v) p1 = i;
		if (G.Vex[i] == w) p2 = i;
	}
	if (p1 != -1 && p2 != -1)//���������ͼ���ҵ�
	{
		if (G.Edge[p1][p2] == 1)//���ڱ�
		{
			return true;
		}
		return false;
	}
	return false;
}

//**********************************************����ʵ�ֺ���*****************************************//
//��ӡͼ�Ķ����
void PrintVex(Graph G)
{
	cout << "ͼ�Ķ����Ϊ��" << endl;
	for (int i = 0; i < G.vexnum; i++)
	{
		cout << G.Vex[i] << " ";
	}
	cout << endl;
	cout << endl;
}
//��ӡͼ�ı߾���
void PrintEdge(Graph G)
{
	cout << "���ڽӾ����ʾΪ��" << endl;
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


//����ͼ����ʵ�ֺ��� ������ͼG  InsertNode ���ã�����ͼ
void CreateGraph(Graph &G)
{
	VexType v, w;
	int vn, an;//������������
	cout << "�����붥����Ŀ:";
	cin >> vn;
	cout << "���������Ŀ:";
	cin >> an;
	cout << "*****���������ж����ֵ*****"<<endl;
	for (int i = 0; i < vn; i++)
	{
		cout << "�������" << i + 1 << "�����㣺";
		cin >> v;
		if (InsertNode(G, v)) continue;//�����
		else {
			cout << "�������" << endl; break;
		}
	}
	cout << "**********���������б�**********" << endl;
	for (int j = 0; j < an; j++)
	{
		cout << "�������" << j + 1 << "���ߵ��������ڶ��㣨�ո�ֿ�����";
		cin >> v >> w;
		if (InsertEdge(G, v, w)) continue;//�����
		else {
			cout << "�������" << endl; break;
		}
	}
	cout << "ͼ�����ɹ�!" << endl;
	PrintVex(G);
	PrintEdge(G);
}


bool visited[MaxVerNum];//���ʱ�����飬���ڱ���ʱ�ı��


//��ȱ������� ������ͼG,��ʼ����±�start ���ã���ȱ���
void BFS(Graph G, int start)
{
	queue<int> Q;//��������
	cout << G.Vex[start];//���ʽ��
	visited[start] = true;
	Q.push(start);//���
	while (!Q.empty())//���зǿ�
	{
		int v = Q.front();//�õ���ͷԪ��
		Q.pop();//����
		for (int j = 0; j < G.vexnum; j++)//�ڽӵ�
		{
			if (G.Edge[v][j] == 1 && !visited[j])//���ڽӵ���δ����
			{
				cout << "->";
				cout << G.Vex[j];//���ʽ��
				visited[j] = true;
				Q.push(j);//���
			}
		}
	}//while
	cout << endl;
}

//��ȱ����������ݹ���ʽ��������ͼG,��ʼ����±�start ���ã���ȱ���
void DFS(Graph G, int start)
{
	cout << G.Vex[start];//����
	visited[start] = true;
	for (int j = 0; j < G.vexnum; j++)
	{
		if (G.Edge[start][j] == 1 && !visited[j])//���ڽӵ���δ����
		{
			cout << "->";
			DFS(G, j);//�ݹ���ȱ���
		}
	}
}


//��ȱ�������ʵ�ֺ��� ������ͼG ���ã���ȱ���
void BFSTraverse(Graph G)
{
	for (int i = 0; i < MaxVerNum; i++)//��ʼ�����ʱ������
	{
		visited[i] = false;
	}
	for (int i = 0; i < G.vexnum; i++)//��ÿ����ͨ�������б���
	{
		if (!visited[i])
			BFS(G, i);
	}
}

//��ȱ�������ʵ�ֺ��� ������ͼG ���ã���ȱ���
void DFSTraverse(Graph G)
{
	for (int i = 0; i < MaxVerNum; i++)//��ʼ�����ʱ������
	{
		visited[i] = false;
	}
	for (int i = 0; i < G.vexnum; i++)//��ÿ����ͨ�������б���
	{
		if (!visited[i])
		{
			DFS(G, i); 
			cout << endl;
		}
	}
}
//�˵�
void menu()
{
	cout << "************************" << endl;
	cout << "        1.�� �� ͼ      " << endl;
	cout << "        2.��ȱ���      " << endl;
	cout << "        3.��ȱ���      " << endl;
	cout << "        4.��    ��      " << endl;
	cout << "************************" << endl;
	
}

