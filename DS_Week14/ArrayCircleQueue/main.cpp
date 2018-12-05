#include "ArrayCircleQueue.h"

void main() {
	CArrayCircleQueue ACQ(6);
	int choice, input;
	while (true) {
		choice = 0;
		input = 0;
		//system("cls");
		cout << "CircleQueue" << endl <<
			"1. enqueue" << endl <<
			"2. dequeue" << endl <<
			"3. getFront" << endl <<
			"4. getSize" << endl <<
			"choice : ";
		cin >> choice;
		cin.clear();
		cout << endl;

		switch (choice) {
		case 1:
			cout << "inData : ";
			cin >> input;
			ACQ.enqueue(input);
			break;
		case 2:
			if (!ACQ.isEmpty()) {
				cout << "front data : '" << ACQ.getFront();
			}
			ACQ.dequeue();
			if (!ACQ.isEmpty()) {
				cout << "' is dequeued" << endl;
			}
			break;
		case 3:
			if (!ACQ.isEmpty()) {
				cout << "front data : " << ACQ.getFront() << endl;
			}
			else {
				cout << "queue is EMPTY\n";
			}
			break;
		case 4:
			cout << "queueSize : " << ACQ.getSize() << endl;
			break;
		}
		cout << endl;
	}
}