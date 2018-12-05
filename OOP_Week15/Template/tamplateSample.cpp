#include <iostream>

using namespace std;

//int myabs(int num) {
//	if (num < 0) {
//		num = -num;
//	}
//	return num;
//}
//double myabs(double num) {
//	if (num < 0) {
//		num = -num;
//	}
//	return num;
//}
//long myabs(long num) {
//	if (num < 0) {
//		num = -num;
//	}
//	return num;
//}

template <typename T>

T myabs(T num) {
	if (num < 0) {
		num = -num;
	}
	return num;
}

void main() {
	int a = -10;
	cout << a << "의 절대값 = " << myabs(a) << endl;

	double b = -3.4;
	cout << b << "의 절대값 = " << myabs(b) << endl;

	long c = -20l;
	cout << c << "의 절대값 = " << myabs(c) << endl;
}