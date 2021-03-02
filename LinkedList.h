#include "global.h"

typedef struct Node{
	ElemType data;
	struct Node *next;
}Node, *LinkList;


//算法2.8，创建链表
Status createLinkList(LinkList &L, int n) {
	L = (LinkList)malloc(sizeof(Node));//头节点
	L->next = NULL;
	//cin >> L->data;
	printf("请倒序输入链表中的各个元素：\n");
	for(int i = n; i > 0; i--)
	{
		LinkList p = (LinkList)malloc(sizeof(Node));
		cout<<"请输入第"<<i<<"个元素:";
		//scanf_s("%d",&p->data);
		cin >> p->data;
		p->next = L->next;
		L->next = p;
	}
	return OK;
}

//算法2.9，单链表的插入
Status InsertLinkList(LinkList &L, int i, ElemType e) {
	LinkList p = L;
	int j = 0;
	while (p&&j<i-1) //寻找目的节点的前一个节点
	{
		p = p->next;  //p指针后移
		j++;          //index后移
	}
	if (!p||j>i-1) return ERROR;
	LinkList q = (LinkList)malloc(sizeof(Node));
	q->data = e;
	q->next = p->next;
	p->next = q;
	return OK;
}

//算法2.10，单链表的删除
Status deleteLinkList(LinkList &L, int i) {
	LinkList p = L;
	int j = 0;
	while(p->next && j < i - 1) //1
	{
		p = p->next; //p指针后移
		++j;
	}
	if (!(p->next) || j > i - 1) 
		return ERROR;
	LinkList q = p->next;
	p->next = q->next;
	free(q);
	return OK;
}


//算法2.11，获取单链表中的第i个元素
Status GetElem_L(LinkList L, int i, ElemType &e)
{
	LinkList p = L->next;
	int j = 1;
	while (p&&j < i)
	{
		p = p->next;
		++j;
	}
	if (!p || j > i)
		return ERROR;
	e = p->data;
	return OK;
}


void Print(LinkList L)//输出链表
{
	cout << "经过此次操作后，单链表为：";
	LinkList p = L->next;
	while (p)
	{
		printf("%d ", p->data);
		p = p->next;
	}
	printf("\n");
}