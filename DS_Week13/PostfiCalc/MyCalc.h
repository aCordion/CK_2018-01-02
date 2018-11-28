#pragma once
#include "ArrayStack.h"

class CMyCalc
{
	char *m_postFix;			//후위 표기 수식
	CArrayStack m_arrayStack;	//스택
	int m_result;				//계산 결과

	int m_curReadPos;			//현재 수식에서 읽어들이는 위치

public:
	~CMyCalc();
	CMyCalc(int Max) : m_result(-1), m_curReadPos(0) {
		m_postFix = new char[Max];
	}
	void setPostFix(char *strform);
	int getToken(char *token);
	void calc();
	int getResult() { return m_result; }
	void draw();
};

