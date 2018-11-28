#pragma once
#include "ArrayStack.h"

class CMyCalc
{
	char *m_postFix;			//���� ǥ�� ����
	CArrayStack m_arrayStack;	//����
	int m_result;				//��� ���

	int m_curReadPos;			//���� ���Ŀ��� �о���̴� ��ġ

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

