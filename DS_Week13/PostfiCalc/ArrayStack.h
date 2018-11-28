#pragma once

#define MAX 100

class CArrayStack
{
	int top;
	int *stack;

	int max;

public:
	CArrayStack();
	CArrayStack(int ndata);
	~CArrayStack() { delete[] stack; }
	CArrayStack(const CArrayStack& S);

	void push(int item);
	int pop();
	int getTop();
	int getTopItem();
	int maxLengthIs() { return max; }
	bool isEmpty();
	bool isFull();
};

