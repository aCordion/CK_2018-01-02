#include <string>
#include "ItoP_StackCalc.h"



ItoP_StackCalc::ItoP_StackCalc() : result(0), OutValCnt(0), InValPos(0)
{
	//sInVal = new char[sizeof(char) * 127];
	for (int i = 0; i <= 127; i++) {
		sInVal[i] = '\0';
		OutVal[i] = 0;
		tokens[i] = 0;
	}

}

void ItoP_StackCalc::inputVal()
{
	cout << "<중위표현(Infix)식 입력>" << endl <<
		"계산할 내용을 피연산자의 사이를 연산자나 공백(space)으로 구분하여" << endl <<
		"중위표현식으로 입력하세요" << endl <<
		"ex) ( 30 + 20 ) * 2 - 90" << endl;
	cin.getline(sInVal, sizeof(char) * 127);

	cout << "입력받은 값은" << endl << sInVal << endl << "입니다." << endl << endl;
}

enum tokenType { PLUS, MINUS, MULTI, DIVIDE, LPAREN, RPAREN, NUMBER, BLANK, OPERATOR, END };

void ItoP_StackCalc::tokenization()
{
	int num = 0;
	int iPosTemp = 0;
	char cPosTemp = '\0';
	int closeCnt = 0;


	while (true) {

		if (sInVal[InValPos] == '=' || sInVal[InValPos] == '\0') {
			while (!operatorList.isEmpty()) {
				tokens[OutValCnt] = OPERATOR;
				OutVal[OutValCnt++] = operatorList.pop();
			}
			OutVal[OutValCnt] = '\0';
			return;
		}
		else if (sInVal[InValPos] == ' ') {
			InValPos++;
		}
		else { iPosTemp = sInVal[InValPos]; cPosTemp = sInVal[InValPos]; }
		//0~9
		if (sInVal[InValPos] >= '0' && sInVal[InValPos] <= '9') {
			int num = 0;
			for (; sInVal[InValPos] >= '0' && sInVal[InValPos] <= '9'; InValPos++) {
				num = 10 * num + sInVal[InValPos] - '0';
			}
			tokens[OutValCnt] = NUMBER;
			OutVal[OutValCnt++] = num;
		}
		//else if (cPosTemp == '+' || cPosTemp == '-') {

		//else if (cPosTemp == '(') {
		else if (sInVal[InValPos] == '(') {
			operatorList.push(sInVal[InValPos++]);
		}

		else if (sInVal[InValPos] == '+' || sInVal[InValPos] == '-') {
			if (operatorList.isEmpty()) {
				operatorList.push(sInVal[InValPos++]);
			}
			else {
				while (!operatorList.isEmpty()) {
					if (operatorList.getTop() == '(') {
						break;
					}
					tokens[OutValCnt] = OPERATOR;
					OutVal[OutValCnt++] = operatorList.pop();
				}
				operatorList.push(sInVal[InValPos++]);
			}
		}

		else if (sInVal[InValPos] == '*' || sInVal[InValPos] == '/') {
			if (!operatorList.isEmpty()) {
				if (operatorList.getTop() == '*' || operatorList.getTop() == '/') {
					tokens[OutValCnt] = OPERATOR;
					OutVal[OutValCnt++] = operatorList.pop();
				}
			}
			operatorList.push(sInVal[InValPos++]);
		}

		//else if (cPosTemp == ')') {
		else if (sInVal[InValPos] == ')') {
			InValPos++;
			while (!operatorList.isEmpty() && operatorList.getTop() != '(') {
				tokens[OutValCnt] = OPERATOR;
				OutVal[OutValCnt++] = operatorList.pop();
			}
			operatorList.pop();
		}
		//else if (cPosTemp == '=' || cPosTemp == '\0') {
		else if (sInVal[InValPos] == '=' || sInVal[InValPos] == '\0') {
			OutVal[OutValCnt++] = operatorList.pop();
			OutVal[OutValCnt] = '\0';
			return;
		}
		else {
			closeCnt++;
			if (closeCnt >= 3) {
				OutVal[OutValCnt] = operatorList.pop();
				return;
			}
		}
		//
	}
}


int ItoP_StackCalc::calculation()
{
	int lVal, rVal, result;
	char oper;

	/*for (int i = 0; i < OutValCnt; i++) {*/
	for (int i = 0; OutVal[i] != '\0'; i++) {
		if (tokens[i] == NUMBER) {
			calcList.push(OutVal[i]);
		}
		else if (tokens[i] == OPERATOR) {
			oper = (char)OutVal[i];
			rVal = calcList.pop();
			lVal = calcList.pop();
			switch (oper) {
			case '+': result = (lVal + rVal); break;
			case '-': result = (lVal - rVal); break;
			case '*': result = (lVal * rVal); break;
			case '/': if (rVal == 0) { cout << "에러. 0으로 나눌 수 없습니다."; return -1; }
					  else { result = (lVal / rVal); }
					  break;
			}
			calcList.push(result);
		}
	}
	cout << "결과 값 : " << result << endl;
	return result;
}

void ItoP_StackCalc::testDrawAll()
{
	cout << "<Infix to Postfix>" << endl;
	for (int i = 0; i < OutValCnt; i++) {
		if (tokens[i] == OPERATOR) {
			cout << (char)OutVal[i] << " ";
		}
		else if (tokens[i] == NUMBER) {
			cout << OutVal[i] << " ";
		}
	}
	cout << endl << "--------------------" << endl;
	calculation();
}


ItoP_StackCalc::~ItoP_StackCalc()
{
	//delete[] sInVal;
}
