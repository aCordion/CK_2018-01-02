#include <iostream>

using namespace std;

void main() {
	int i = 5;
	double d = 10.6;

	cout << "i = " << i << endl;
	cout << "d = " << d << endl;

	d = i;
	cout << "형변환 값 d = " << d << endl;

	d = 3.14;
	i = (int)d;
	cout << "형변환 값 i = " << i << endl;

	int x = 10;
	int *pi = &x;
	float *pf = (float*)pi;
	cout << "초기 x = " << x << endl;

	*pf = 3.14f;
	cout << "포인터 형변환 *pf = " << *pf << endl;
	cout << "변환 x = " << x << endl;
}