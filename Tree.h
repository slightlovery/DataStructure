#pragma once

#include"global.h"
#include<string.h>

typedef struct BiNode {
	char data;
	struct BiNode *lchild, *rchild;
}BiTNode, *BiTree;


void InitBiTree(BiTree T) {
	T = NULL;
}


void Create(BiTree &T)
{
	char ch;
	scanf_s("%c", &ch);
	if (ch == '*')
	{
		T = NULL;
	}
	else
	{
		T = (BiTNode *)malloc(sizeof(BiTNode));
		T->data = ch;
		Create(T->lchild);
		Create(T->rchild);
	}
}


void visit(char c) {
	printf("->%c", c);
}

void PreOrderTraverse(BiTree T) {
	if (T) {
		visit(T->data);
		PreOrderTraverse(T->lchild);
		PreOrderTraverse(T->rchild);
	}
}

void InOrderTraverse(BiTree T) {
	if (T) {
		InOrderTraverse(T->lchild);
		visit(T->data);
		InOrderTraverse(T->rchild);
	}
}


void PostOrderTraverse(BiTree T) {
	if (T) {
		PostOrderTraverse(T->lchild);
		PostOrderTraverse(T->rchild);
		visit(T->data);
	}
}

int depth(BiTree T) {
	int ldeep, rdeep;
	if (!T) return 0;
	else {
		ldeep = depth(T->lchild);
		rdeep = depth(T->rchild);
		return ldeep > rdeep ? ldeep + 1 : rdeep + 1;
	}
}
