#include <iostream>
#include "ArrayStack.h"

using namespace std;


void main() {
	int sLength = 0;
	cout << "������ �ִ� ���� : ";
	cin >> sLength;
	CArrayStack aStack(sLength);

	//cout << "������ �ִ� ���̴� '" << aStack.maxLengthIs() << "' �Դϴ�." << endl;

	while (true) {
		cout << "������ �ִ� ���̴� '" << aStack.maxLengthIs() << "' �Դϴ�." << endl <<
			"���� ���ÿ� �ִ� ���� ���� '" << aStack.getTop() << "' �Դϴ�." << endl;
		bool isEmpty = aStack.isEmpty();
		bool isFull = aStack.isFull();	
		int select = 0;
		int inStackVal = 0;
		cout << "1.���ÿ� �߰�" << endl <<
			"2.���ÿ��� ����" << endl <<
			"3.���� ������ top�� ���" << endl;
		cin >> select;
		switch (select) {
		case 1:
			if (isFull) {
				cout << "������ ���� á���ϴ�." << endl;
			}
			else {
				cout << "���ÿ� �߰��� �� : ";
				cin >> inStackVal;
				aStack.push(inStackVal);
			}
			break;
		case 2:
			if (isEmpty) {
				cout << "������ ��� �ֽ��ϴ�." << endl;
			}
			else {
				cout << "���� ������ top���� '" << aStack.getTopItem() << "' �Դϴ�." <<
					"�ش� ���� �����մϴ�." << endl;
				aStack.pop();
			}
			break;
		case 3:
			if (isEmpty) {
				cout << "������ ��� �ֽ��ϴ�." << endl;
			}
			else {
				cout << "���� ������ top���� '" << aStack.getTop() << "' �Դϴ�." << endl;
			}
			break;
		}
	}
}

/*		if (isEmpty) {
			cout << "����Ʈ�� ��� �ֽ��ϴ�" << endl;
		}
		else if (isFull) {
			cout << "����Ʈ�� ���� á���ϴ�" << endl;
		}
		*/