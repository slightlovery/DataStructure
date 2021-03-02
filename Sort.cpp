

#include"ArrayList.h"

#define ElemType int

void InsertSort(SqList &L) {  // 算法10.1
  // 对顺序表L作直接插入排序。
	int i, j;
	for (i = 2; i < L.length; ++i)
		if (LT(L.elem[i], L.elem[i - 1])) {
			// "<"时，需将L.elem[i]插入有序子表
			L.elem[0] = L.elem[i];                 // 复制为哨兵
			L.elem[i] = L.elem[i - 1];
			for (j = i - 2; LT(L.elem[0], L.elem[j]); --j)
				L.elem[j + 1] = L.elem[j];             // 记录后移
			L.elem[j + 1] = L.elem[0];               // 插入到正确位置
		}
}


void BiInsertionSort(SqList &L) {  //折半插入排序
	int low, high, mid;
	for (int i = 2; i < L.length; ++i) {
		L.elem[0] = L.elem[i];      // 将 L.elem[i] 暂存到 L.elem[0]
		low = 1, high = i - 1;
		while (low <= high) {
			mid = (low + high) / 2;           // 折半
			if (L.elem[0] < L.elem[mid])
				high = mid - 1;   // 插入点在低半区
			else  low = mid + 1; // 插入点在高半区
		}
		for (int j = i - 1; j >= high + 1; --j)
			L.elem[j + 1] = L.elem[j];      // 记录后移
		L.elem[high + 1] = L.elem[0];  // 插入
	}
}

void ShellInsert(SqList &L, int dk) {  // 算法10.4
  // 对顺序表L作一趟希尔插入排序。本算法对算法10.1作了以下修改：
  //     1. 前后记录位置的增量是dk，而不是1；
  //     2. elem[0]只是暂存单元，不是哨兵。当j<=0时，插入位置已找到。
	int i, j;
	for (i = dk + 1; i <= L.length; ++i)
		if (LT(L.elem[i], L.elem[i - dk])) { // 需将L.elem[i]插入有序增量子表
			L.elem[0] = L.elem[i];                   // 暂存在L.elem[0]
			for (j = i - dk; j > 0 && LT(L.elem[0], L.elem[j]); j -= dk)
				L.elem[j + dk] = L.elem[j];              // 记录后移，查找插入位置
			L.elem[j + dk] = L.elem[0];                // 插入
		}
} // ShellInsert

void ShellSort(SqList &L, int dlta[], int t) {
	for (int i = 0; i < t; i++)
	{
		ShellInsert(L, dlta[i]);
	}
}//ShellSort

int Partition(SqList &L, int low, int high) {  // 算法10.6(a)
   // 交换顺序表L中子序列L.elem[low..high]的记录，使枢轴记录到位，
   // 并返回其所在位置，此时，在它之前（后）的记录均不大（小）于它
	ElemType pivotkey;
	ElemType temp;
	pivotkey = L.elem[low];     // 用子表的第一个记录作枢轴记录
	while (low < high) {           // 从表的两端交替地向中间扫描
		while (low < high && L.elem[high] >= pivotkey) 
			--high;
		temp = L.elem[low];
		L.elem[low] = L.elem[high];
		L.elem[high] = temp;           // 将比枢轴记录小的记录交换到低端
		
		while (low < high && L.elem[low] <= pivotkey) 
			++low;
		temp = L.elem[low];
		L.elem[low] = L.elem[high];
		L.elem[high] = temp;           // 将比枢轴记录大的记录交换到高端
	}
	return low;                  // 返回枢轴所在位置
} // Partition

void QSort(SqList &L, int low, int high) {  //算法10.7
  // 对顺序表L中的子序列L.elem[low..high]进行快速排序
	int pivotloc;
	if (low < high) {                      // 长度大于1
		pivotloc = Partition(L, low, high);  // 将L.elem[low..high]一分为二
		QSort(L, low, pivotloc - 1); // 对低子表递归排序，pivotloc是枢轴位置
		QSort(L, pivotloc + 1, high);          // 对高子表递归排序
	}
} // QSort

void QuickSort(SqList &L) {  // 算法10.8
   // 对顺序表L进行快速排序
	QSort(L, 1, L.length);
} // QuickSort

/*
void SelectSort(SqList &L) {  // 算法10.9
  // 对顺序表L作简单选择排序。
	int i, j;
	for (i = 1; i < L.length; ++i) { // 选择第i小的记录，并交换到位
		j = SelectMinKey(L, i);  // 在L.elem[i..L.length]中选择key最小的记录
		if (i != j) {                // L.elem[i]←→L.elem[j];   与第i个记录交换
			ElemType temp;
			temp = L.elem[i];
			L.elem[i] = L.elem[j];
			L.elem[j] = temp;
		}
	}
} // SelectSort

*/

int main() {

	SqList sqlist;
	InitList_Sq(sqlist);
	cout << "sqlist的长度是：" << sqlist.length << endl;

	ListInsert(sqlist, 1, 0);
	ListInsert(sqlist, 2, 49);
	ListInsert(sqlist, 3, 38);
	ListInsert(sqlist, 4, 65);
	ListInsert(sqlist, 5, 97);
	ListInsert(sqlist, 6, 76);
	ListInsert(sqlist, 7, 13);
	ListInsert(sqlist, 8, 27);
	ListInsert(sqlist, 9, 49);

	cout << "sqlist的长度是：" << sqlist.length << endl;

	PrintSqList(sqlist);

	//插入排序
	/*
	InsertSort(sqlist);

	cout << "插入排序之后的结果为：" << endl;

	PrintSqList(sqlist);
	
	*/
	
	BiInsertionSort(sqlist);

	cout << "折半插入排序之后的结果为：" << endl;

	PrintSqList(sqlist);
	

	//Shell排序
	/*
	int dlta[] = { 3,2,1 };

	cout << "3趟Shell排序之后的结果为：" << endl;

	ShellSort(sqlist, dlta, 3);

	PrintSqList(sqlist);

	*/

	//快速排序
	/*
	cout << "快速排序之后的结果为：" << endl;

	QuickSort(sqlist);

	PrintSqList(sqlist);
	*/

	int data;
	cin >> data;
	system("pause");

	return 0;
}