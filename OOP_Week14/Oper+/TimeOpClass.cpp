#include "TimeOpClass.h"


void main() {
	CTimeOpClass t1(10000), t2, t3(11, 22, 33), t4, t5, t6;
	cout << " t2 총 시간을 입력하시오 = ";
	cin >> t2;
	cout << t1 << endl;
	cout << t2 << endl;

	cout << "t1 + t2 = " << t1 + t2 << endl;
	cout << "t1 - t2 = " << t1 - t2 << endl;
	cout << " t1 = " << t1 << endl;

	cout << "++t1 = " << ++t1 << endl;
	cout << " t1 = " << t1 << endl;

	cout << "--t1 = " << --t1 << endl;
	cout << " t1 = " << t1 << endl;
	
	cout << "t1++ = " << t1++ << endl;
	cout << " t1 = " << t1 << endl;
	
	cout << "t1-- = " << t1-- << endl;
	cout << " t1 = " << t1 << endl;
	
	cout << "t1[0~2] = " << t1[0] << " " << t1[1] << " " << t1[2] << " " << t1[3] << endl;
	
	cout << "t2[sec] = " << (int)t2 << endl;
	cout << "t2[double] = " << (double)t2 << endl;
	
	cout << "2 * t2 = " << 2 * t2 << endl;

}
