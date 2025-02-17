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
	//在HT[1..n]中选择parent为0且weight最小的两个结点，
	// 其序号分别为s1和s2。
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
	// 并求出n个字符的哈夫曼编码HC
	int i, m, s1, s2, start;
	char *cd;
	unsigned int c, f;
	if (n <= 1) return;
	m = 2 * n - 1;
	HT = (HuffmanTree)malloc((m + 1) * sizeof(HTNode));  // 0号单元未用
	for (i = 1; i <= n; i++) { //初始化
		HT[i].weight = w[i - 1];
		HT[i].parent = 0;
		HT[i].lchild = 0;
		HT[i].rchild = 0;
	}
	for (i = n + 1; i <= m; i++) { //初始化
		HT[i].weight = 0;
		HT[i].parent = 0;
		HT[i].lchild = 0;
		HT[i].rchild = 0;
	}
	for (i = n + 1; i <= m; i++) {  // 建哈夫曼树
	  // 在HT[1..i-1]中选择parent为0且weight最小的两个结点，
	  // 其序号分别为s1和s2。
		Select(HT, i - 1, s1, s2);
		HT[s1].parent = i;  HT[s2].parent = i;
		HT[i].lchild = s1;  HT[i].rchild = s2;
		HT[i].weight = HT[s1].weight + HT[s2].weight;
	}
	//--- 从叶子到根逆向求每个字符的哈夫曼编码 ---
	cd = (char *)malloc(n * sizeof(char));    // 分配求编码的工作空间
	cd[n - 1] = '\0';                         // 编码结束符。
	for (i = 1; i <= n; ++i) {                  // 逐个字符求哈夫曼编码
		start = n - 1;                          // 编码结束符位置
		for (c = i, f = HT[i].parent; f != 0; c = f, f = HT[f].parent)
			// 从叶子到根逆向求编码
			if (HT[f].lchild == c) cd[--start] = '0';
			else cd[--start] = '1';
		HC[i] = (char *)malloc((n - start) * sizeof(char));
		// 为第i个字符编码分配空间
		strcpy(HC[i], &cd[start]);    // 从cd复制编码(串)到HC    

	}
	free(cd);   //释放工作空间
} //HuffmanCoding

void mainview_user()            //界面函数
{
	BiTree T;
	int c;
	while (1)
	{
		system("CLS");  //清除屏幕函数
		printf("     ------------------------------------\n");
		printf("      |**********二叉树的应用*********|\n");
		printf("      |********1   哈夫曼编码*********|\n");
		printf("      |********2   输入二叉树*********|\n");
		printf("      |********3   前序遍历***********|\n");
		printf("      |********4   中序遍历***********|\n");
		printf("      |********5   后序遍历***********|\n");
		printf("      |********0   退出系统***********|\n");
		printf("     ------------------------------------\n");
		printf("\n");

		printf("请选择：");
		scanf("%d", &c);
		switch (c)
		{
		case 1: {
			int i, n;
			int *w;
			HuffmanTree HT;
			HuffmanCode HC;
			printf("请输入要输入权值的数量:");
			scanf("%d", &n);  //权值个数
			w = (int *)malloc(n * sizeof(int));
			printf("Input weights:");
			for (i = 0; i < n; i++)  //录入权值
				scanf("%d", &w[i]);

			HC = (char **)malloc((n + 1) * sizeof(char*)); //0空间未用
			HT = (HuffmanTree)malloc((2 * n + 1 + 1) * sizeof(HTNode));//0空间未用
			HuffmanCoding(HT, HC, w, n);
			printf("\n");
			for (i = 1; i < n + 1; i++) {
				printf("权值%d的哈夫曼编码为：", w[i - 1]);
				printf("%s\n", HC[i]);  //输出哈夫曼编码
				free(HC[i]);  //释放空间
			}
			free(HC);
			free(HT);
			break;
		}
		case 2: {
			printf("按先序读入字符串:");
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
		default:printf("输入错误，请重新输入!\n"); fflush(stdin);
		}
		printf("\n\n");

		system("PAUSE");
	}
}
