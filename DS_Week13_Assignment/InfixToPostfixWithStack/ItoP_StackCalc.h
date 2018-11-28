#pragma once
#include <iostream>
#include "LinkedListStack.h"

using namespace std;

class ItoP_StackCalc
{
	CLinkedListStack calcList;
	CLinkedListStack operatorList;

	//char *sInVal;
	char sInVal[127];
	int InValPos;
	int OutVal[127];
	int tokens[127];
	int OutValCnt;
	int result;

public:
	~ItoP_StackCalc();
	ItoP_StackCalc();

	void inputVal();
	void tokenization();
	int calculation();
	void testDrawAll();
};

