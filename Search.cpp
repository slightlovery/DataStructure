/*
#include"ArrayList.h"
#include"Tree.h"



typedef struct {
	int location;
	int count;
}Set;

//顺序查找
int Search_SqList(SqList list, ElemType key) {
	list.elem[0] = key;
	int i = list.length;
	for (i ; !EQ(list.elem[i], key); i--);
	return i;
}

//折半查找
Set Search_Bin(SqList list, ElemType key){
	Set set = {0,0};
	int low = 1, high = list.length-1, mid = 0 ,count = 0;
	while (low<=high)
	{
		count++;
		mid = (high + low) / 2;
		if (EQ(key, list.elem[mid]))
		{
			set = {mid,count};
			return set;
		}
		else if(LT(key, list.elem[mid])){
			high = mid - 1;
		}
		else {
			low = mid + 1;
		}
	}
	set = { 0,0 };
	return set;   //0表示没有找到key
}


//二叉排序树的查找算法
BiTree Search_BiTree(BiTree tree, char key) {
	if ((!tree) || EQ(key, tree->data)) return tree;
	else if (LT(key, tree->data)) return Search_BiTree(tree->lchild, key);
	else return Search_BiTree(tree->rchild, key);
}

//二叉排序树的查找算法（插入）
Status Search_BiTree(BiTree tree, char key, BiTree f, BiTree &p) {
	if (!tree) { p = f; return FALSE; }
	else if EQ(key, tree->data) { p = tree; return TRUE; }
	else if LT(key, tree->data) return Search_BiTree(tree->lchild,key,tree,p);
	else return Search_BiTree(tree->rchild, key, tree, p);
}



int main() {
	// -------------- 顺序查找 --------------- 
	int i;
	SqList sqlist;
	InitList_Sq(sqlist);
	cout << "sqlist的长度是：" << sqlist.length << endl;
	for (i = 1; i <= 12; i++)
	{
		ListInsert(sqlist,i,i-1);
	}
	cout << "sqlist的长度是：" << sqlist.length << endl;
	for (i = 1; i < sqlist.length; i++)
	{
		//cout << sqlist.elem[i] << endl;
		cout << i << "所在的位置是：" << Search_SqList(sqlist, i) << endl;
	}

	//-------------- 折半查找 --------------
	Set result;
	for (i = 1; i < sqlist.length; i++)
	{
		result = Search_Bin(sqlist, i);
		cout << "用折半查找" << i << "所在的位置是：" << result.location;
		cout << ",所用的次数是：" << result.count << endl;
	}

	//-------------- 二叉排序树 --------------
	BiTree tree = NULL;
	BiTree f = NULL;
	BiTree p = NULL;
	InitBiTree(tree);
	Create(tree);
	cout << Search_BiTree(tree,'a')->data << endl;
	cout << Search_BiTree(tree, 'f', f, p) << endl;


	int data;
	cin >> data;
	system("pause");

	return 0;

}

*/


/*
typedef struct {
	int location;
	int count;
}Set;

//顺序查找
int Search_SqList(SqList list, ElemType key) {
	list.elem[0] = key;
	int i = list.length;
	for (i; !EQ(list.elem[i], key); i--);
	return i;
}

//折半查找
Set Search_Bin(SqList list, ElemType key) {
	Set set = { 0,0 };
	int low = 1, high = list.length - 1, mid = 0, count = 0;
	while (low <= high)
	{
		count++;
		mid = (high + low) / 2;
		if (EQ(key, list.elem[mid]))
		{
			set = { mid,count };
			return set;
		}
		else if (LT(key, list.elem[mid])) {
			high = mid - 1;
		}
		else {
			low = mid + 1;
		}
	}
	set = { 0,0 };
	return set;   //0表示没有找到key
}


//二叉排序树的查找算法
BiTree Search_BiTree(BiTree tree, char key) {
	if ((!tree) || EQ(key, tree->data)) return tree;
	else if (LT(key, tree->data)) return Search_BiTree(tree->lchild, key);
	else return Search_BiTree(tree->rchild, key);
}

//二叉排序树的查找算法（插入）
Status Insert(BiTree& tree, ElemType key) {
	BiTree p = NULL;
	BiTree s = NULL;
	if (!Search_BiTree_INSERT(tree, key, NULL, p))
	{
		s = (BiTree)malloc(sizeof(BiTNode));
		s->data = key; s->lchild = s->rchild = NULL;
	}
	if (!p)
	{
		tree = s;
	}
	else if (LT(key, p->data))
	{
		p->lchild = s;
		return TRUE;
	}
	else return FALSE;
}


Status Search_BiTree_INSERT(BiTree tree, char key, BiTree f, BiTree& p) {
	if (!tree) { p = f; return FALSE; }
	else if EQ(key, tree->data) { p = tree; return TRUE; }
	else if LT(key, tree->data) return Search_BiTree_INSERT(tree->lchild, key, tree, p);
	else return Search_BiTree_INSERT(tree->rchild, key, tree, p);
}

//二叉排序树的查找算法（删除）
Status Delete(BiTree& p) {
	BiTree q = NULL;
	BiTree s = NULL;
	if (!p->rchild)
	{
		q = p; p = p->lchild; free(q);
	}
	else if (!p->lchild)
	{
		q = p; p = p->rchild; free(q);
	}
	else {
		q = p; s = p->lchild;
		while (s->rchild) {
			q = s; s = s->rchild;
		}
		p->data = s->data;
		if (q != p)
		{
			q->rchild = s->lchild;
		}
		else {
			q->lchild = s->lchild;
			delete s;
		}
		return TRUE;
	}
}


Status Search_BiTree_DELETE(BiTree& tree, char key) {
	if (!tree) {
		return FALSE;
	}
	else
	{
		if (EQ(key, tree->data))
		{
			return Delete(tree);
		}
		else if (LT(key, tree->data))
		{
			return Search_BiTree_DELETE(tree->lchild, key);
		}
		else
		{
			return Search_BiTree_DELETE(tree->rchild, key);
		}
	}
}

int main() {
	// -------------- 顺序查找 ---------------
	int i;
	SqList sqlist;
	InitList_Sq(sqlist);
	cout << "sqlist的长度是：" << sqlist.length << endl;
	for (i = 1; i <= 12; i++)
	{
		ListInsert(sqlist, i, i - 1);
	}
	cout << "sqlist的长度是：" << sqlist.length << endl;
	for (i = 1; i < sqlist.length; i++)
	{
		//cout << sqlist.elem[i] << endl;
		cout << i << "所在的位置是：" << Search_SqList(sqlist, i) << endl;
	}

	//-------------- 折半查找 --------------
	Set result;
	for (i = 1; i < sqlist.length; i++)
	{
		result = Search_Bin(sqlist, i);
		cout << "用折半查找" << i << "所在的位置是：" << result.location;
		cout << ",所用的次数是：" << result.count << endl;
	}

	//-------------- 二叉排序树 --------------
	BiTree tree = NULL;
	BiTree f = NULL;
	BiTree p = NULL;

	InitBiTree(tree);
	Create(tree);
	cout << "查找结果为：" << endl;
	cout << Search_BiTree(tree, 'f')->data << endl;
	cout << "插入" << endl;
	cout << Search_BiTree_INSERT(tree, 'a', f, p) << endl;
	cout << "删除" << endl;
	cout << Delete(p) << endl;
	cout << Search_BiTree_DELETE(tree, 'b') << endl;

	int data;
	cin >> data;
	system("pause");

	return 0;

}

*/