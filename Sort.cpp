

#include"ArrayList.h"

#define ElemType int

void InsertSort(SqList &L) {  // �㷨10.1
  // ��˳���L��ֱ�Ӳ�������
	int i, j;
	for (i = 2; i < L.length; ++i)
		if (LT(L.elem[i], L.elem[i - 1])) {
			// "<"ʱ���轫L.elem[i]���������ӱ�
			L.elem[0] = L.elem[i];                 // ����Ϊ�ڱ�
			L.elem[i] = L.elem[i - 1];
			for (j = i - 2; LT(L.elem[0], L.elem[j]); --j)
				L.elem[j + 1] = L.elem[j];             // ��¼����
			L.elem[j + 1] = L.elem[0];               // ���뵽��ȷλ��
		}
}


void BiInsertionSort(SqList &L) {  //�۰��������
	int low, high, mid;
	for (int i = 2; i < L.length; ++i) {
		L.elem[0] = L.elem[i];      // �� L.elem[i] �ݴ浽 L.elem[0]
		low = 1, high = i - 1;
		while (low <= high) {
			mid = (low + high) / 2;           // �۰�
			if (L.elem[0] < L.elem[mid])
				high = mid - 1;   // ������ڵͰ���
			else  low = mid + 1; // ������ڸ߰���
		}
		for (int j = i - 1; j >= high + 1; --j)
			L.elem[j + 1] = L.elem[j];      // ��¼����
		L.elem[high + 1] = L.elem[0];  // ����
	}
}

void ShellInsert(SqList &L, int dk) {  // �㷨10.4
  // ��˳���L��һ��ϣ���������򡣱��㷨���㷨10.1���������޸ģ�
  //     1. ǰ���¼λ�õ�������dk��������1��
  //     2. elem[0]ֻ���ݴ浥Ԫ�������ڱ�����j<=0ʱ������λ�����ҵ���
	int i, j;
	for (i = dk + 1; i <= L.length; ++i)
		if (LT(L.elem[i], L.elem[i - dk])) { // �轫L.elem[i]�������������ӱ�
			L.elem[0] = L.elem[i];                   // �ݴ���L.elem[0]
			for (j = i - dk; j > 0 && LT(L.elem[0], L.elem[j]); j -= dk)
				L.elem[j + dk] = L.elem[j];              // ��¼���ƣ����Ҳ���λ��
			L.elem[j + dk] = L.elem[0];                // ����
		}
} // ShellInsert

void ShellSort(SqList &L, int dlta[], int t) {
	for (int i = 0; i < t; i++)
	{
		ShellInsert(L, dlta[i]);
	}
}//ShellSort

int Partition(SqList &L, int low, int high) {  // �㷨10.6(a)
   // ����˳���L��������L.elem[low..high]�ļ�¼��ʹ�����¼��λ��
   // ������������λ�ã���ʱ������֮ǰ���󣩵ļ�¼������С������
	ElemType pivotkey;
	ElemType temp;
	pivotkey = L.elem[low];     // ���ӱ�ĵ�һ����¼�������¼
	while (low < high) {           // �ӱ�����˽�������м�ɨ��
		while (low < high && L.elem[high] >= pivotkey) 
			--high;
		temp = L.elem[low];
		L.elem[low] = L.elem[high];
		L.elem[high] = temp;           // ���������¼С�ļ�¼�������Ͷ�
		
		while (low < high && L.elem[low] <= pivotkey) 
			++low;
		temp = L.elem[low];
		L.elem[low] = L.elem[high];
		L.elem[high] = temp;           // ���������¼��ļ�¼�������߶�
	}
	return low;                  // ������������λ��
} // Partition

void QSort(SqList &L, int low, int high) {  //�㷨10.7
  // ��˳���L�е�������L.elem[low..high]���п�������
	int pivotloc;
	if (low < high) {                      // ���ȴ���1
		pivotloc = Partition(L, low, high);  // ��L.elem[low..high]һ��Ϊ��
		QSort(L, low, pivotloc - 1); // �Ե��ӱ�ݹ�����pivotloc������λ��
		QSort(L, pivotloc + 1, high);          // �Ը��ӱ�ݹ�����
	}
} // QSort

void QuickSort(SqList &L) {  // �㷨10.8
   // ��˳���L���п�������
	QSort(L, 1, L.length);
} // QuickSort

/*
void SelectSort(SqList &L) {  // �㷨10.9
  // ��˳���L����ѡ������
	int i, j;
	for (i = 1; i < L.length; ++i) { // ѡ���iС�ļ�¼����������λ
		j = SelectMinKey(L, i);  // ��L.elem[i..L.length]��ѡ��key��С�ļ�¼
		if (i != j) {                // L.elem[i]����L.elem[j];   ���i����¼����
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
	cout << "sqlist�ĳ����ǣ�" << sqlist.length << endl;

	ListInsert(sqlist, 1, 0);
	ListInsert(sqlist, 2, 49);
	ListInsert(sqlist, 3, 38);
	ListInsert(sqlist, 4, 65);
	ListInsert(sqlist, 5, 97);
	ListInsert(sqlist, 6, 76);
	ListInsert(sqlist, 7, 13);
	ListInsert(sqlist, 8, 27);
	ListInsert(sqlist, 9, 49);

	cout << "sqlist�ĳ����ǣ�" << sqlist.length << endl;

	PrintSqList(sqlist);

	//��������
	/*
	InsertSort(sqlist);

	cout << "��������֮��Ľ��Ϊ��" << endl;

	PrintSqList(sqlist);
	
	*/
	
	BiInsertionSort(sqlist);

	cout << "�۰��������֮��Ľ��Ϊ��" << endl;

	PrintSqList(sqlist);
	

	//Shell����
	/*
	int dlta[] = { 3,2,1 };

	cout << "3��Shell����֮��Ľ��Ϊ��" << endl;

	ShellSort(sqlist, dlta, 3);

	PrintSqList(sqlist);

	*/

	//��������
	/*
	cout << "��������֮��Ľ��Ϊ��" << endl;

	QuickSort(sqlist);

	PrintSqList(sqlist);
	*/

	int data;
	cin >> data;
	system("pause");

	return 0;
}