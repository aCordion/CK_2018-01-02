#include "MyCalc.h"
#include <iostream>

using namespace std;


CMyCalc::~CMyCalc()
{
	if (m_postFix) {
		delete[] m_postFix;
	}
}

void CMyCalc::setPostFix(char * strform)
{
	int i = 0;
	/*for (i = 0; strform[i] != 0; m_postFix[i] = strform[i++]);
	m_postFix[i] = '\0';*/
	do {
		m_postFix[i] = strform[i];
		i++;
	} while (strform[i-1] != '\0');
}

enum tokenType { PLUS, MINUS, MULTI, DIVIDE, LPAREN, RPAREN, NUMBER, BLANK, END };
int CMyCalc::getToken(char * token)
{
	int tokenPos = 0;
	switch (m_postFix[m_curReadPos]) {
	case '+':
		token[tokenPos++] = m_postFix[m_curReadPos++];
		token[tokenPos] = '\0';
		return PLUS;
	case '-':
		token[tokenPos++] = m_postFix[m_curReadPos++];
		token[tokenPos] = '\0';
		return MINUS;
	case '*':
		token[tokenPos++] = m_postFix[m_curReadPos++];
		token[tokenPos] = '\0';
		return MULTI;
	case '/':
		token[tokenPos++] = m_postFix[m_curReadPos++];
		token[tokenPos] = '\0';
		return DIVIDE;
	/*case '(':
	case ')':*/
	case ' ':
		m_curReadPos++;
		return BLANK;
	case '\0':
	case '=':
		return END;
	default:		//숫자 처리 부분
		while (m_postFix[m_curReadPos] >= '0' && m_postFix[m_curReadPos] <= '9') {
			token[tokenPos++] = m_postFix[m_curReadPos++];
		}
		token[tokenPos]	= '\0';
		return NUMBER;
	}
	return -1;
}

void CMyCalc::calc()
{
	int popVal1, popVal2;	//stack pop data;
	int num;				//문자 숫자 ==> 정수로 변환 변수
	char token[20];			//수식에서 토큰을 넘겨받을 배열

	m_curReadPos = 0;
	int curTokenType;
	while (curTokenType = getToken(token) != END) {
		switch (curTokenType) {
		case PLUS:
			popVal2 = m_arrayStack.pop();
			popVal1 = m_arrayStack.pop();
			m_arrayStack.push(popVal1 + popVal2);
			break;
		case MINUS:
			popVal2 = m_arrayStack.pop();
			popVal1 = m_arrayStack.pop();
			m_arrayStack.push(popVal1 - popVal2);
			break;
		case MULTI:
			popVal2 = m_arrayStack.pop();
			popVal1 = m_arrayStack.pop();
			m_arrayStack.push(popVal1 * popVal2);
			break;
		case DIVIDE:	//0으로 나눌때의 예외처리 필요
			popVal2 = m_arrayStack.pop();
			popVal1 = m_arrayStack.pop();
			if (popVal2 == 0) {
				exit(1);
			}
			m_arrayStack.push(popVal1 / popVal2);
			break;
		case BLANK:
			break;
		case NUMBER:
			num = 0;
			for (int i = 0; token[i] != '\0'; i++) {
				num = 10 * num + token[i] - '0';
			}
			m_arrayStack.push(num);
			break;
		default:
			break;
		}
	}	//EoWhile
	m_result = m_arrayStack.pop();
}

void CMyCalc::draw()
{
	cout << "PostFix : " << m_postFix << " = " << m_result << endl;
}
