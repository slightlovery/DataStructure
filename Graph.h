#pragma once
#include"global.h"
#include<math.h>

#define INFINITY INF_MAX
#define MAX_VERTEX_NUM 20
#define VRType int
#define InfoType int

typedef char VertexType[5];

typedef enum { DG, DN, AG, AN } GraphKind;


/*--------------���飨�ڽӾ��󣩴洢-------------*/

typedef struct ArcCell {	VRType  adj;  // VRType�Ƕ����ϵ���͡�����Ȩͼ��1��0��ʾ���ڷ�                           				  // �Դ�Ȩͼ����ΪȨֵ���͡�    	InfoType   info; // �û���Ȩֵ} ArcCell, AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];typedef struct {	VertexType   vexs[MAX_VERTEX_NUM]; // ��������    	AdjMatrix     arcs; // �ڽӾ���    	int     vexnum, arcnum; // ͼ�ĵ�ǰ�������ͻ�(��)��    	GraphKind   kind; // ͼ�������־ } MGraph;/*--------------�ڽӱ���ʽ���洢-------------*/typedef struct ArcNode {  //��ڵ�	int   adjvex; // �û���ָ��Ķ����λ��     	struct ArcNode   *nextarc; // ָ����һ������ָ��     	InfoType   info; // �û������Ϣ��Ȩֵ��}ArcNode;typedef struct VNode {	VertexType   data; // ������Ϣ     	ArcNode       *firstarc; // ָ���һ�������ö���Ļ�   }VNode, AdjList[MAX_VERTEX_NUM];typedef struct {	AdjList   vertices;	int   vexnum, arcnum; // ͼ�ĵ�ǰ�������ͻ���     	GraphKind   kind; // ͼ�������־ } ALGraph;/*---------------------ͼ�Ļ��������㷨-------------------*/int LocateVex(MGraph G, VertexType u)
{ /* ��ʼ����:ͼG����,u��G�ж�������ͬ���� */
  /* �������:��G�д��ڶ���u,�򷵻ظö�����ͼ��λ��;���򷵻�-1 */
	int i;
	for (i = 0; i < G.vexnum; ++i)
		if (strcmp(u, G.vexs[i]) == 0)
			return i;
	return -1;
}