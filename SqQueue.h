#pragma once
#include"global.h"

#define MAXSIZE 100
#define QElemType int

typedef struct {
	QElemType *base;
	QElemType front;
	QElemType rear;
}SqQueue;

Status InitQueue(SqQueue &Q) {
	Q.base = (QElemType *)malloc(MAXSIZE * sizeof(QElemType));
	if (!Q.base)
	{
		exit(OVERFLOW);
	}
	Q.front = Q.rear = 0;
	return OK;
}

int QueueLength(SqQueue Q){
	return (Q.rear - Q.front + MAXSIZE) % MAXSIZE;
}

Status EnQueue(SqQueue &Q, ElemType e)
{
	if ((Q.rear + 1) % MAXSIZE == Q.front) return ERROR;
	Q.base[Q.rear] = e;
	Q.rear = (Q.rear + 1) % MAXSIZE;
	return OK;
}

Status DeQueue(SqQueue &Q, QElemType &e){
	if (Q.rear == Q.front)
	{
		return ERROR;
	}
	e = Q.base[Q.front];
	Q.front = (Q.front + 1) % MAXSIZE;
	return OK;
}