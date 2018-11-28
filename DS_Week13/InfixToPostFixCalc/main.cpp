#include <iostream>
#include "LinkedListStack.h"

using namespace std;

void main() {

	CLinkedListStack lListStack;

	while (true) {
		if (!lListStack.isEmpty()) {
			cout << "���� ���ÿ� �ִ� ���� '" << lListStack.getTop() << "' �Դϴ�." << endl;
		}
		bool isEmpty = lListStack.isEmpty();
		int select = 0;
		int inStackVal = 0;
		cout << "1.���ÿ� �߰�" << endl <<
			"2.���ÿ��� ����" << endl <<
			"3.���� ������ top�� ���" << endl;
		cin >> select;
		switch (select) {
		case 1:
			cout << "���ÿ� �߰��� �� : ";
			cin >> inStackVal;
			lListStack.push(inStackVal);
			break;
		case 2:
			if (isEmpty) {
				cout << "������ ��� �ֽ��ϴ�." << endl;
			}
			else {
				cout << "���� ������ top���� '" << lListStack.getTop() << "' �Դϴ�." <<
					"�ش� ���� �����մϴ�." << endl;
				lListStack.pop();
			}
			break;
		case 3:
			if (isEmpty) {
				cout << "������ ��� �ֽ��ϴ�." << endl;
			}
			else {
				cout << "���� ������ top���� '" << lListStack.getTop() << "' �Դϴ�." << endl;
			}
			break;
		}
	}

}