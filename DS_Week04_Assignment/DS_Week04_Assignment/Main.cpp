#include "Math.h"

void main()
{
	CMath M;
	int iValue1, iValue2, iValue3;

	cout << "피보나치 수열, 하노이 탑 프로그램" << endl <<
		"[1] 피보나치 수열" << endl <<
		"[2] 하노이 탑" << endl <<
		"[3] 종료" << endl;

	switch (M.getNums(3))
	{
	case 1:
		system("cls");
		cout << "피보나치 수열의 1번 값 ";
		iValue1 = M.getNums(100);
		cout << "피보나치 수열의 2번 값 ";
		iValue2 = M.getNums(100);
		cout << "피보나치 수열 계산 최대 횟수  ";
		iValue3 = M.getNums(100);
		M.math_Fib(iValue1, iValue2, iValue3);
		break;
	case 2: 
		system("cls");
		cout << "하노이의 탑" << endl <<
			"사용할 판의 수 (1~64) ";
		iValue1 = M.getNums(64);
		M.math_Hanoi('A', 'B', 'C', iValue1);
		break;
	default:
		break;
	}
}