#include "ArrayStack.h"



CArrayStack::CArrayStack(int ndata) : top(0)
{
	stack = new int[ndata];
	max = ndata;
}

CArrayStack::CArrayStack(const CArrayStack & S)
{
	top = S.top;
	for (int Index = 0; Index <= S.top; ++Index) {
		stack[Index] = S.stack[Index];
	}
}

void CArrayStack::push(int val)
{
	if (isFull()) {
		return;
	}
	stack[top] = val;
	top++;
}

int CArrayStack::pop()
{
	if (isEmpty()) {
		return 0;
	}
	int rVal;
	rVal = stack[top];
	top--;

	return rVal;
}

int CArrayStack::getTop()
{
	return top;
}

int CArrayStack::getTopItem()
{
	return stack[top - 1];
}

bool CArrayStack::isEmpty()
{
	return top == 0;
}

bool CArrayStack::isFull()
{
	return top >= MAX;
}
