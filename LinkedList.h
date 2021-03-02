#include "global.h"

typedef struct Node{
	ElemType data;
	struct Node *next;
}Node, *LinkList;


//�㷨2.8����������
Status createLinkList(LinkList &L, int n) {
	L = (LinkList)malloc(sizeof(Node));//ͷ�ڵ�
	L->next = NULL;
	//cin >> L->data;
	printf("�뵹�����������еĸ���Ԫ�أ�\n");
	for(int i = n; i > 0; i--)
	{
		LinkList p = (LinkList)malloc(sizeof(Node));
		cout<<"�������"<<i<<"��Ԫ��:";
		//scanf_s("%d",&p->data);
		cin >> p->data;
		p->next = L->next;
		L->next = p;
	}
	return OK;
}

//�㷨2.9��������Ĳ���
Status InsertLinkList(LinkList &L, int i, ElemType e) {
	LinkList p = L;
	int j = 0;
	while (p&&j<i-1) //Ѱ��Ŀ�Ľڵ��ǰһ���ڵ�
	{
		p = p->next;  //pָ�����
		j++;          //index����
	}
	if (!p||j>i-1) return ERROR;
	LinkList q = (LinkList)malloc(sizeof(Node));
	q->data = e;
	q->next = p->next;
	p->next = q;
	return OK;
}

//�㷨2.10���������ɾ��
Status deleteLinkList(LinkList &L, int i) {
	LinkList p = L;
	int j = 0;
	while(p->next && j < i - 1) //1
	{
		p = p->next; //pָ�����
		++j;
	}
	if (!(p->next) || j > i - 1) 
		return ERROR;
	LinkList q = p->next;
	p->next = q->next;
	free(q);
	return OK;
}


//�㷨2.11����ȡ�������еĵ�i��Ԫ��
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


void Print(LinkList L)//�������
{
	cout << "�����˴β����󣬵�����Ϊ��";
	LinkList p = L->next;
	while (p)
	{
		printf("%d ", p->data);
		p = p->next;
	}
	printf("\n");
}