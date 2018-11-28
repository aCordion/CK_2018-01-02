#include <iostream>
#include "LinkedListStack.h"

using namespace std;

void main() {

	CLinkedListStack lListStack;

	while (true) {
		if (!lListStack.isEmpty()) {
			cout << "현재 스택에 있는 값은 '" << lListStack.getTop() << "' 입니다." << endl;
		}
		bool isEmpty = lListStack.isEmpty();
		int select = 0;
		int inStackVal = 0;
		cout << "1.스택에 추가" << endl <<
			"2.스택에서 제거" << endl <<
			"3.현재 스택의 top값 출력" << endl;
		cin >> select;
		switch (select) {
		case 1:
			cout << "스택에 추가할 값 : ";
			cin >> inStackVal;
			lListStack.push(inStackVal);
			break;
		case 2:
			if (isEmpty) {
				cout << "스택이 비어 있습니다." << endl;
			}
			else {
				cout << "현재 스택의 top값은 '" << lListStack.getTop() << "' 입니다." <<
					"해당 값을 삭제합니다." << endl;
				lListStack.pop();
			}
			break;
		case 3:
			if (isEmpty) {
				cout << "스택이 비어 있습니다." << endl;
			}
			else {
				cout << "현재 스택의 top값은 '" << lListStack.getTop() << "' 입니다." << endl;
			}
			break;
		}
	}

}