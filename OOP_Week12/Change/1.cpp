#include <iostream>

using namespace std;

void main() {
	int i = 5;
	double d = 10.6;

	cout << "i = " << i << endl;
	cout << "d = " << d << endl;

	d = i;
	cout << "����ȯ �� d = " << d << endl;

	d = 3.14;
	i = (int)d;
	cout << "����ȯ �� i = " << i << endl;

	int x = 10;
	int *pi = &x;
	float *pf = (float*)pi;
	cout << "�ʱ� x = " << x << endl;

	*pf = 3.14f;
	cout << "������ ����ȯ *pf = " << *pf << endl;
	cout << "��ȯ x = " << x << endl;
}