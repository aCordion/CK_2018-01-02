#include "Math.h"


CMath::CMath()
{
	count = 0;
	value = 0;
	Pillers[0] = 'A';
	Pillers[1] = 'B';
	Pillers[2] = 'C';
}


CMath::~CMath()
{
}

int CMath::math_Fib(int in1, int in2, const int MAX)
{
	if (count == 0) {
		cout << in1 << ", " << in2;
	}

	if (count <= 10) {
		value = in1 + in2;
		count++;
		cout << ", " << value;
		return math_Fib(in2, value, MAX);
	}
	else {
		count = 0;
		cout << endl;
		return 0;
	}
}

void CMath::math_Hanoi(char from, char by, char to, int num)
{
	if (num == 1) {
		//cout << Pill << " ��տ��� " << moveTo << " ������� �̵� " << endl;
//		math_HMove(from, to);
		printf("1�� ������ %c���� %c�� �̵�\n", from, to);
	}
	//math_Hanoi(Pill, Pillers[1] , num - 1);
	//cout << Pill << " ��տ��� " << moveTo << " ������� �̵� " << endl;
	//math_Hanoi(Pillers[1], moveTo, num - 1);
	else {
		math_Hanoi(from, to, by, num - 1);
//		math_HMove(from, to);
		printf("%d�� ������ %c���� %c�� �̵�\n", num, from, to);
		math_Hanoi(by, from, to, num - 1);
	}
}
/*
void CMath::math_Hanoi(char Pill, char moveTo, int num)
{
	if (num == 1) {
		//cout << Pill << " ��տ��� " << moveTo << " ������� �̵� " << endl;
		math_HMove(Pill, moveTo);
	}
	//math_Hanoi(Pill, Pillers[1] , num - 1);
	//cout << Pill << " ��տ��� " << moveTo << " ������� �̵� " << endl;
	//math_Hanoi(Pillers[1], moveTo, num - 1);
	else {
		math_Hanoi(Pillers[0], Pillers[1], num - 1);
		math_HMove(Pill, moveTo);
		math_Hanoi(Pillers[1], Pillers[2], num - 1);
	}
}
*/

void CMath::math_HMove(char from, char to)
{
	cout << from << " ���� " << to << " �� �̵�" << endl;
}

int CMath::getNums(const int MAX)
{
		int Num = 0;
		bool isFail = false;

		do {
			cout << "�Է� : ";
			cin >> Num;

			if (cin.fail()) {
				cout << "Ʋ�� ���Դϴ�. �ٽ� �Է��Ͽ� �ּ���." << endl;
				cin.clear();
				rewind(stdin);
				isFail = true;
			}
			if (Num > MAX || Num <= 0) {
				cout << MAX << " ����, 1 �̻��� ���� �Է��� �ּ���." << endl;
				cin.clear();
				rewind(stdin);
				isFail = true;
			}
			if (!cin.fail()) {
				isFail = false;
			}
		} while (isFail == true);

		return Num;
}
