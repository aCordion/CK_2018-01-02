#include <iostream>
#include <cassert>

using namespace std;

void onExit() { cout << "......... ���α׷� ���� �Լ� .........\n"; }
void divide(int a, int b) {
	int c, d;

	cout << "********* Divide �Լ� *********\n";

	if (b == 0) throw b; //����

	c = a / b;
	cout << "�� => " << c << endl;
	d = a % b;
	cout << "������ => " << d << endl;
}
void efunc(int a) throw(char *, int) {
	if (a == 0) throw "������ ���� 0��";
	else {
		throw a;
	}
}

class UserError {
public:
	void func();
};

void UserError::func() {
	cout << "����� ���� ����......\n";
}
void main() {

	atexit(onExit);

	//int a, b, c, d;
	//cout << " �������� �ϱ� ���� �����͸� �Է��Ͻÿ�......\n";
	//cout << "������ ��(������)�� �Է��Ͻÿ� = ";
	//cin >> a;
	//cout << "������ ��(����)�� �Է��Ͻÿ� = ";
	//cin >> b;

	///*if (b == 0) {
	//	cout << " ���� ��Ȳ�� �߻��߽��ϴ�......\n";
	//	exit(0);
	//}

	//c = a / b;

	//cout << "�� => " << c << endl;

	//d = a % d;

	//cout << "������ => " << d << endl;*/
	//try {
	//	if (b == 0) throw b;
	//	c = a / b;
	//	cout << "�� => " << c << endl;
	//	d = a % b;
	//	cout << "������ => " << d << endl;
	//}
	//catch (int ex) {
	//	cout << ex << " �� �������� �õ��� Ȯ�εǾ� ���ܷ� ó���մϴ�...\n";
	//}
	//cout << "���ܰ� �߻��ϴ��� �׻� ����...\n";

	//try {
	//	divide(10, 2);
	//	divide(10, 0);
	//	divide(10, 4);
	//}
	//catch (int ex) {
	//	cout << ex << " �� �������� �õ��� Ȯ�εǾ� ���ܷ� ó���մϴ�...\n";
	//}
	/*int a;
	cout << "���� �Է��Ͻÿ� = ";
	cin >> a;

	try {
		efunc(a);
	}
	catch (char *str) {
		cout << str << endl;
	}
	catch (int ex) {
		cout << ex << " ���ڷ� ���� ���ܹ߻�......\n";
	}
*/
	try {

		throw UserError();

	}
	catch (UserError &ex) {
		cout << "����� ���� ���� �߻� ó��......\n";
		ex.func();
	}
}