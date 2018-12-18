#include <iostream>
#include "LinkedListQueue.h"

using namespace std;

void main() {

	CLinkedListQueue lListQueue;

	while (true) {
		if (!lListQueue.isEmpty()) {
			cout << "���� ť�� �ִ� front���� '" << lListQueue.getFront() << "' �Դϴ�." << endl;
		}
		bool isEmpty = lListQueue.isEmpty();
		int select = 0;
		int inQueueVal = 0;
		cout << "1.ť�� �߰�" << endl <<
			"2.ť���� ����" << endl <<
			"3.���� ť�� front�� ���" << endl;
		cin >> select;
		switch (select) {
		case 1:
			cout << "ť�� �߰��� �� : ";
			cin >> inQueueVal;
			lListQueue.enqueue(inQueueVal);
			break;
		case 2:
			if (isEmpty) {
				cout << "ť�� ��� �ֽ��ϴ�." << endl;
			}
			else {
				cout << "���� ť�� front���� '" << lListQueue.getFront() << "' �Դϴ�." <<
					"�ش� ���� �����մϴ�." << endl;
				lListQueue.dequeue();
			}
			break;
		case 3:
			if (isEmpty) {
				cout << "ť�� ��� �ֽ��ϴ�." << endl;
			}
			else {
				cout << "���� ť�� front���� '" << lListQueue.getFront() << "' �Դϴ�." << endl;
			}
			break;
		}
	}

}