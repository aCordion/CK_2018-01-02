#include <iostream>

using namespace std;

void efunc(int a) throw(char*, int) {
	if (a == 0) {
		throw "�������� 0 �Դϴ�";
	}
	else {
		throw a;
	}
}

void main() {

	int a, b, c, d;

	cout << "�������� �ϱ� ���� �����͸� �Է��Ͻÿ�." << endl;
	cout << "������ ��(������)�� �Է��Ͻÿ� = ";
	cin >> a;
	
	cout << "������ ��(�Ǽ�)�� �Է��Ͻÿ� = ";
	cin >> b;
	try {
		if (b == 0) { throw b; }
		c = a / b;
		cout << "�� => " << c << endl;
		d = a % b;
		cout << "������ => " << d << endl;
	}
	catch(int ex){
		cout << ex << "�� �������� �õ��� �߻������Ƿ� ���ܷ� ó���մϴ�.\n";
	}
	cout << "���ܰ� �߻��ϴ��� ���������� �����մϴ�...\n";

	try {
		efunc(0);
	}
	catch (char *str) {
		cout << str << endl;
	}
	catch (int ex) {
		cout << "���� " << ex << " �� ���� ���ܹ߻�.......\n";
	}

	/*if (b == 0) {
		cout << "���� ��Ȳ�� �߻��߽��ϴ�......\n";
	}
	else {
		c = a / b;
		cout << "�� => " << c << endl;
		d = a % b;
		cout << "������ => " << d << endl;
	}*/


}