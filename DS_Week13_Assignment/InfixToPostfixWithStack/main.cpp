#include "ItoP_StackCalc.h"

void main() {

	system("Title Infix to Postfix Convert and Calculate Program");

	while (true) {
		ItoP_StackCalc ITPSC;
		ITPSC.inputVal();
		ITPSC.tokenization();
		ITPSC.testDrawAll();
		system("pause");
		ITPSC.~ItoP_StackCalc();
		system("cls");
	}

}