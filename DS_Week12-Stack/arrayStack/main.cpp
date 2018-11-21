#include <iostream>
#include "ArrayStack.h"

using namespace std;


void main() {
	int sLength = 0;
	cout << "스택의 최대 길이 : ";
	cin >> sLength;
	CArrayStack aStack(sLength);

	//cout << "스택의 최대 길이는 '" << aStack.maxLengthIs() << "' 입니다." << endl;

	while (true) {
		cout << "스택의 최대 길이는 '" << aStack.maxLengthIs() << "' 입니다." << endl <<
			"현재 스택에 있는 값의 수는 '" << aStack.getTop() << "' 입니다." << endl;
		bool isEmpty = aStack.isEmpty();
		bool isFull = aStack.isFull();	
		int select = 0;
		int inStackVal = 0;
		cout << "1.스택에 추가" << endl <<
			"2.스택에서 제거" << endl <<
			"3.현재 스택의 top값 출력" << endl;
		cin >> select;
		switch (select) {
		case 1:
			if (isFull) {
				cout << "스택이 가득 찼습니다." << endl;
			}
			else {
				cout << "스택에 추가할 값 : ";
				cin >> inStackVal;
				aStack.push(inStackVal);
			}
			break;
		case 2:
			if (isEmpty) {
				cout << "스택이 비어 있습니다." << endl;
			}
			else {
				cout << "현재 스택의 top값은 '" << aStack.getTopItem() << "' 입니다." <<
					"해당 값을 삭제합니다." << endl;
				aStack.pop();
			}
			break;
		case 3:
			if (isEmpty) {
				cout << "스택이 비어 있습니다." << endl;
			}
			else {
				cout << "현재 스택의 top값은 '" << aStack.getTop() << "' 입니다." << endl;
			}
			break;
		}
	}
}

/*		if (isEmpty) {
			cout << "리스트가 비어 있습니다" << endl;
		}
		else if (isFull) {
			cout << "리스트가 가득 찼습니다" << endl;
		}
		*/