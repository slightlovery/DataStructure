#include"ArrayList.h"
//ע�⣬�������Ŀ�У��ж��cpp������ͬһ��ͷ�ļ�������ע�͵����������ã���Ȼ�ᱨLINK2005�ظ��������

void main() {
	
	SqList L;
	int i, n, e;
	InitList_Sq(L);
	printf("������Ԫ�ظ���:\n");
	scanf_s("%d", &n);
	printf("%d��Ԫ��Ϊ:\n", n);
	for (i = 1; i <= n; i++)
	{
		scanf_s("%d", &L.elem[i - 1]);
		L.length++;
	}
	printf("���Ա�Ϊ:\n");
	for (i = 1; i <= n; i++)
		printf("%d ", L.elem[i - 1]);
	printf("\n");

	printf("����������λ�úͲ����Ԫ��:\n");
	scanf_s("%d,%d", &i, &e);
	ListInsert(L, i, e);
	printf("����Ԫ��%d������Ա�Ϊ:\n", e);
	for (i = 1; i <= L.length; i++)
		printf("%d ", L.elem[i - 1]);
	printf("\n");

	printf("������ɾ����λ��:\n");
	scanf_s("%d", &i);
	ListDelete(L, i, e);
	printf("ɾ����%d��λ���ϵ�Ԫ��%d������Ա�Ϊ:\n", i, e);
	for (i = 1; i <= L.length; i++)
		printf("%d ", L.elem[i - 1]);
	printf("\n");


	//�鲢
	SqList La, Lb, Lc;
	int na, nb;
	InitList_Sq(La);
	printf("������La��Ԫ�صĸ���:\n");
	scanf_s("%d", &na);
	printf("La��%d��Ԫ��Ϊ:\n", na);
	for (i = 1; i <= na; i++)
	{
		scanf_s("%d", &La.elem[i - 1]);
		La.length++;
	}

	InitList_Sq(Lb);
	printf("������Lb��Ԫ�صĸ���:\n");
	scanf_s("%d", &nb);
	printf("Lb��%d��Ԫ��Ϊ:\n", nb);
	for (i = 1; i <= nb; i++)
	{
		scanf_s("%d", &Lb.elem[i - 1]);
		Lb.length++;
	}
	MergeList_Sq(La, Lb, Lc);

	system("pause");

}