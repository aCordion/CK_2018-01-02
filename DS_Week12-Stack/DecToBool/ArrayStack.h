#pragma once

#define MAX 100

class CArrayStack
{
	int top;
	int stack[MAX];

public:
	CArrayStack(int ndata);
	~CArrayStack() {}
	CArrayStack(const CArrayStack& S);

	void push(int item);
	int pop();
	int getTop();
	bool isEmpty();
	bool isFull();
};

