#include "Math.h"

void main()
{
	CMath M;
	int iValue1, iValue2, iValue3;

	cout << "�Ǻ���ġ ����, �ϳ��� ž ���α׷�" << endl <<
		"[1] �Ǻ���ġ ����" << endl <<
		"[2] �ϳ��� ž" << endl <<
		"[3] ����" << endl;

	switch (M.getNums(3))
	{
	case 1:
		system("cls");
		cout << "�Ǻ���ġ ������ 1�� �� ";
		iValue1 = M.getNums(100);
		cout << "�Ǻ���ġ ������ 2�� �� ";
		iValue2 = M.getNums(100);
		cout << "�Ǻ���ġ ���� ��� �ִ� Ƚ��  ";
		iValue3 = M.getNums(100);
		M.math_Fib(iValue1, iValue2, iValue3);
		break;
	case 2: 
		system("cls");
		cout << "�ϳ����� ž" << endl <<
			"����� ���� �� (1~64) ";
		iValue1 = M.getNums(64);
		M.math_Hanoi('A', 'B', 'C', iValue1);
		break;
	default:
		break;
	}
}