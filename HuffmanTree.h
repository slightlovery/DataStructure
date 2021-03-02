#pragma once

#include"global.h"

typedef char TElemType;
typedef int Status;
typedef struct {
	unsigned int weight;
	unsigned int parent, lchild, rchild;
}HTNode, *HuffmanTree;
typedef char **HuffmanCode;

typedef struct BiTNode {
	TElemType data;
	struct BiTNode *lchild, *rchild;
}BiTNode, *BiTree;

Status CreateBiTree(BiTree &T) {
	char ch;
	scanf("%c", &ch);
	if ('#' == ch)
		T = NULL;
	else {
		T = new BiTNode;
		T->data = ch;
		CreateBiTree(T->lchild);
		CreateBiTree(T->rchild);
	}
}

Status Visit(TElemType e) {
	printf("%c ", e);
	return OK;
}

void PreOrderTraverse(BiTree T) {
	if (T)
	{
		printf("%c ", T->data);
		PreOrderTraverse(T->lchild);
		PreOrderTraverse(T->rchild);
	}

}

void InOrderTraverse(BiTree T) {
	if (T)
	{
		InOrderTraverse(T->lchild);
		printf("%c ", T->data);
		InOrderTraverse(T->rchild);
	}
}

void PostOrderTraverse(BiTree T) {
	if (T)
	{
		PostOrderTraverse(T->lchild);
		PostOrderTraverse(T->rchild);
		printf("%c ", T->data);
	}
}


void Select(HuffmanTree &HT, int n, int &s1, int &s2)
{
	//��HT[1..n]��ѡ��parentΪ0��weight��С��������㣬
	// ����ŷֱ�Ϊs1��s2��
	int i;
	s1 = -1; s2 = -1;
	for (i = 1; i <= n; i++)
		if (HT[i].parent == 0)
		{
			if (s1 == -1)
				s1 = i;
			else if (HT[i].weight < HT[s1].weight)
			{
				s2 = s1;
				s1 = i;
			}
			else if (s2 == -1 || HT[i].weight < HT[s2].weight)
				s2 = i;
		}
}
void HuffmanCoding(HuffmanTree &HT, HuffmanCode &HC, int *w, int n)
{
	// �����n���ַ��Ĺ���������HC
	int i, m, s1, s2, start;
	char *cd;
	unsigned int c, f;
	if (n <= 1) return;
	m = 2 * n - 1;
	HT = (HuffmanTree)malloc((m + 1) * sizeof(HTNode));  // 0�ŵ�Ԫδ��
	for (i = 1; i <= n; i++) { //��ʼ��
		HT[i].weight = w[i - 1];
		HT[i].parent = 0;
		HT[i].lchild = 0;
		HT[i].rchild = 0;
	}
	for (i = n + 1; i <= m; i++) { //��ʼ��
		HT[i].weight = 0;
		HT[i].parent = 0;
		HT[i].lchild = 0;
		HT[i].rchild = 0;
	}
	for (i = n + 1; i <= m; i++) {  // ����������
	  // ��HT[1..i-1]��ѡ��parentΪ0��weight��С��������㣬
	  // ����ŷֱ�Ϊs1��s2��
		Select(HT, i - 1, s1, s2);
		HT[s1].parent = i;  HT[s2].parent = i;
		HT[i].lchild = s1;  HT[i].rchild = s2;
		HT[i].weight = HT[s1].weight + HT[s2].weight;
	}
	//--- ��Ҷ�ӵ���������ÿ���ַ��Ĺ��������� ---
	cd = (char *)malloc(n * sizeof(char));    // ���������Ĺ����ռ�
	cd[n - 1] = '\0';                         // �����������
	for (i = 1; i <= n; ++i) {                  // ����ַ������������
		start = n - 1;                          // ���������λ��
		for (c = i, f = HT[i].parent; f != 0; c = f, f = HT[f].parent)
			// ��Ҷ�ӵ������������
			if (HT[f].lchild == c) cd[--start] = '0';
			else cd[--start] = '1';
		HC[i] = (char *)malloc((n - start) * sizeof(char));
		// Ϊ��i���ַ��������ռ�
		strcpy(HC[i], &cd[start]);    // ��cd���Ʊ���(��)��HC    

	}
	free(cd);   //�ͷŹ����ռ�
} //HuffmanCoding

void mainview_user()            //���溯��
{
	BiTree T;
	int c;
	while (1)
	{
		system("CLS");  //�����Ļ����
		printf("     ------------------------------------\n");
		printf("      |**********��������Ӧ��*********|\n");
		printf("      |********1   ����������*********|\n");
		printf("      |********2   ���������*********|\n");
		printf("      |********3   ǰ�����***********|\n");
		printf("      |********4   �������***********|\n");
		printf("      |********5   �������***********|\n");
		printf("      |********0   �˳�ϵͳ***********|\n");
		printf("     ------------------------------------\n");
		printf("\n");

		printf("��ѡ��");
		scanf("%d", &c);
		switch (c)
		{
		case 1: {
			int i, n;
			int *w;
			HuffmanTree HT;
			HuffmanCode HC;
			printf("������Ҫ����Ȩֵ������:");
			scanf("%d", &n);  //Ȩֵ����
			w = (int *)malloc(n * sizeof(int));
			printf("Input weights:");
			for (i = 0; i < n; i++)  //¼��Ȩֵ
				scanf("%d", &w[i]);

			HC = (char **)malloc((n + 1) * sizeof(char*)); //0�ռ�δ��
			HT = (HuffmanTree)malloc((2 * n + 1 + 1) * sizeof(HTNode));//0�ռ�δ��
			HuffmanCoding(HT, HC, w, n);
			printf("\n");
			for (i = 1; i < n + 1; i++) {
				printf("Ȩֵ%d�Ĺ���������Ϊ��", w[i - 1]);
				printf("%s\n", HC[i]);  //�������������
				free(HC[i]);  //�ͷſռ�
			}
			free(HC);
			free(HT);
			break;
		}
		case 2: {
			printf("����������ַ���:");
			getchar();
			CreateBiTree(T);
			break;
		}
		case 3: {
			PreOrderTraverse(T);
			break;
		}
		case 4: {
			InOrderTraverse(T);
			break;
		}
		case 5: {
			PostOrderTraverse(T);
			break;
		}
		case 0: {
			return;
		}
		default:printf("�����������������!\n"); fflush(stdin);
		}
		printf("\n\n");

		system("PAUSE");
	}
}
