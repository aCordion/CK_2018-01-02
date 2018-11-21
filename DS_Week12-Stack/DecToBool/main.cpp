#include <iostream>
#include "ArrayStack.h"

using namespace std;


void main() {
	CArrayStack aStack(100);

	while (true) {
		int DtoB = 0;
		cout << "Dec->Bool (input DecValue): ";
		cin >> DtoB;
		
		while (true) {
			if (DtoB == 0) {
				aStack.push(0);
				break;
			}
			else if (DtoB == 1) {
				aStack.push(1);
//				aStack.push(0);
				break;
			}
			else {
				int temp = DtoB % 2;
				DtoB /= 2;
				aStack.push(temp);
			}
		}
		while (!aStack.isEmpty()) {
			cout << aStack.pop() << " ";
		}
		cout << endl;
	}
}

/*		if (isEmpty) {
			cout << "리스트가 비어 있습니다" << endl;
		}
		else if (isFull) {
			cout << "리스트가 가득 찼습니다" << endl;
		}
		*/