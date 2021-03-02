#include"ArrayList.h"
//注意，如果在项目中，有多个cpp引用了同一个头文件，必须注释掉其他的引用，不然会报LINK2005重复定义错误

void main() {
	
	SqList L;
	int i, n, e;
	InitList_Sq(L);
	printf("请输入元素个数:\n");
	scanf_s("%d", &n);
	printf("%d个元素为:\n", n);
	for (i = 1; i <= n; i++)
	{
		scanf_s("%d", &L.elem[i - 1]);
		L.length++;
	}
	printf("线性表为:\n");
	for (i = 1; i <= n; i++)
		printf("%d ", L.elem[i - 1]);
	printf("\n");

	printf("请输入插入的位置和插入的元素:\n");
	scanf_s("%d,%d", &i, &e);
	ListInsert(L, i, e);
	printf("插入元素%d后的线性表为:\n", e);
	for (i = 1; i <= L.length; i++)
		printf("%d ", L.elem[i - 1]);
	printf("\n");

	printf("请输入删除的位置:\n");
	scanf_s("%d", &i);
	ListDelete(L, i, e);
	printf("删除第%d个位置上的元素%d后的线性表为:\n", i, e);
	for (i = 1; i <= L.length; i++)
		printf("%d ", L.elem[i - 1]);
	printf("\n");


	//归并
	SqList La, Lb, Lc;
	int na, nb;
	InitList_Sq(La);
	printf("请输入La中元素的个数:\n");
	scanf_s("%d", &na);
	printf("La中%d个元素为:\n", na);
	for (i = 1; i <= na; i++)
	{
		scanf_s("%d", &La.elem[i - 1]);
		La.length++;
	}

	InitList_Sq(Lb);
	printf("请输入Lb中元素的个数:\n");
	scanf_s("%d", &nb);
	printf("Lb中%d个元素为:\n", nb);
	for (i = 1; i <= nb; i++)
	{
		scanf_s("%d", &Lb.elem[i - 1]);
		Lb.length++;
	}
	MergeList_Sq(La, Lb, Lc);

	system("pause");

}