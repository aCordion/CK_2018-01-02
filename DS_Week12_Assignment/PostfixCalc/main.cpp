#include <iostream>
#include <stdio.h>
#include <string>
#include "ArrayStack.h"

using namespace std;

int Calc(int lVal, int rVal, char oper);

void main() {

	CArrayStack arrStack(2);

	char *sInVal = new char[sizeof(char) * 50];
	/*char *sTempVal = new char[sizeof(char) * 50];
	char *pos = new char[sizeof(char) * 50];*/
	char *sTempVal;
	char *pos;
	//char *integer = "0123456789";
	int leftVal, rightVal, result;
	int iPosTemp;
	//int resultTemp;
	char cPosTemp;

	while (true) {
		sTempVal = nullptr;
		pos = nullptr;
		leftVal = 0;
		rightVal = 0;
		result = 0;
		iPosTemp = 0;
		cPosTemp = ' ';
		char oper = '+';

		cout << "<후위표현(Postfix)식 계산기>" << endl <<
			"계산할 내용을 각 연산자나 피연산자의 사이를 공백(space)로 구분하여" << endl <<
			"후위표현식으로 입력하세요" << endl <<
			"ex) 3 4 + 5 * 2 -		== ((3+4) * 5) - 2 = 33" << endl;
		{
			//fgets(InTemp, sizeof(InTemp), stdin);
			////scanf("%s",sInVal);
			//cin.getline(sInVal,sizeof(InTemp));

			////strcpy(InTemp, sInVal);
			//InTemp = sInVal;

			//pos = strtok_s(InTemp, " ", &sTempVal);
			//while (pos != nullptr) {
			//	cout << pos << endl;
			//	pos = strtok_s(NULL, " ", &sTempVal);
			//}
		}
		cin.getline(sInVal, sizeof(char) * 50);

		pos = strtok_s(sInVal, " ", &sTempVal);
		iPosTemp = *pos;

		int cCounter = 1;
		int temp;
		while (true) {
			{
				//			//if (pos >= "0" && pos <= "9")
				//			if (cCounter >= 1 && pos == "^1~9") {
				//				iPosTemp = stoi(pos);
				//				arrStack.push(iPosTemp);
				//				cCounter = 0;
				//			} 
				//			else if (pos != integer) {
				//				rightVal = arrStack.pop();
				//				leftVal = arrStack.pop();
				//				//char tPos = *pos;
				//				resultTemp = Calc(leftVal, rightVal, *pos);
				//				arrStack.push(resultTemp);
				//			}
				////			else if(pos == "*" || pos == "+" || pos == "-" || pos == "/") 
				//			else if (pos == nullptr) {
				//				cCounter = 0;
				//				break;
				//			}
			}
			if (pos == nullptr) {
				break;
			}
			else{ iPosTemp = *pos; }
			if (iPosTemp >= 48 && iPosTemp <= 57) {
				//arrStack.push(stoi(pos));
				temp = stoi(pos);
				//temp = (iPosTemp - 48);
				arrStack.push(temp);
			}
			else if (iPosTemp == 42 || iPosTemp == 43 || iPosTemp == 45 || iPosTemp == 47) {
				cPosTemp = *pos;
				rightVal = arrStack.pop();
				leftVal = arrStack.pop();
				result = Calc(leftVal, rightVal, cPosTemp);
				arrStack.push(result);
			}
			pos = strtok_s(sTempVal, " ", &sTempVal);
			cCounter++;
		}
		cout << "계산 결과 = " << result << endl;
		system("pause");
		system("cls");
	}
	delete[] sInVal;
}

int Calc(int lVal, int rVal, char oper) {
	{
		/*if (oper == "+") {
			return (lVal + rVal);
		}
		else if (oper == "-") {
			return (lVal - rVal);
		}
		else if (oper == "*") {
			return (lVal * rVal);
		}
		else if (oper == "/") {
			return (lVal / rVal);
		}
		else { return 0; }*/
	}
	switch (oper) {
	case '+':
		return (lVal + rVal);
		break;
	case '-':
		return (lVal - rVal);
		break;
	case '*':
		return (lVal * rVal);
		break;
	case '/':
		return (lVal / rVal);
		break;
	}
}