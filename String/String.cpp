#include"String.h"

int main() {

	char s[] = "ababcabcacbab";
	char p[] = "cacbab";

	SString S, P;
	SString T;

	StrAssign(S, s);
	StrAssign(P, p);

	Concat(T, S, P);
	StrOutput(T);

	cout << "KMP�Ľ��Ϊ��" << KMP(S,P) << endl;



	int data;
	cin >> data;

	system("pause");


	return 0;

}