#include <iostream>
#include "LinkedListQueue.h"

using namespace std;

void main() {

	CLinkedListQueue lListQueue;

	while (true) {
		if (!lListQueue.isEmpty()) {
			cout << "현재 큐에 있는 front값은 '" << lListQueue.getFront() << "' 입니다." << endl;
		}
		bool isEmpty = lListQueue.isEmpty();
		int select = 0;
		int inQueueVal = 0;
		cout << "1.큐에 추가" << endl <<
			"2.큐에서 제거" << endl <<
			"3.현재 큐의 front값 출력" << endl;
		cin >> select;
		switch (select) {
		case 1:
			cout << "큐에 추가할 값 : ";
			cin >> inQueueVal;
			lListQueue.enqueue(inQueueVal);
			break;
		case 2:
			if (isEmpty) {
				cout << "큐가 비어 있습니다." << endl;
			}
			else {
				cout << "현재 큐의 front값은 '" << lListQueue.getFront() << "' 입니다." <<
					"해당 값을 삭제합니다." << endl;
				lListQueue.dequeue();
			}
			break;
		case 3:
			if (isEmpty) {
				cout << "큐가 비어 있습니다." << endl;
			}
			else {
				cout << "현재 큐의 front값은 '" << lListQueue.getFront() << "' 입니다." << endl;
			}
			break;
		}
	}

}