#pragma once
#include"global.h"
#include<math.h>

#define INFINITY INF_MAX
#define MAX_VERTEX_NUM 20
#define VRType int
#define InfoType int

typedef char VertexType[5];

typedef enum { DG, DN, AG, AN } GraphKind;


/*--------------数组（邻接矩阵）存储-------------*/

typedef struct ArcCell {	VRType  adj;  // VRType是顶点关系类型。对无权图用1或0表示相邻否；                           				  // 对带权图，则为权值类型。    	InfoType   info; // 该弧的权值} ArcCell, AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];typedef struct {	VertexType   vexs[MAX_VERTEX_NUM]; // 顶点向量    	AdjMatrix     arcs; // 邻接矩阵    	int     vexnum, arcnum; // 图的当前顶点数和弧(边)数    	GraphKind   kind; // 图的种类标志 } MGraph;/*--------------邻接表（链式）存储-------------*/typedef struct ArcNode {  //表节点	int   adjvex; // 该弧所指向的顶点的位置     	struct ArcNode   *nextarc; // 指向下一条弧的指针     	InfoType   info; // 该弧相关信息（权值）}ArcNode;typedef struct VNode {	VertexType   data; // 顶点信息     	ArcNode       *firstarc; // 指向第一条依附该顶点的弧   }VNode, AdjList[MAX_VERTEX_NUM];typedef struct {	AdjList   vertices;	int   vexnum, arcnum; // 图的当前顶点数和弧数     	GraphKind   kind; // 图的种类标志 } ALGraph;/*---------------------图的基本操作算法-------------------*/int LocateVex(MGraph G, VertexType u)
{ /* 初始条件:图G存在,u和G中顶点有相同特征 */
  /* 操作结果:若G中存在顶点u,则返回该顶点在图中位置;否则返回-1 */
	int i;
	for (i = 0; i < G.vexnum; ++i)
		if (strcmp(u, G.vexs[i]) == 0)
			return i;
	return -1;
}