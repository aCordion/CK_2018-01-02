#pragma once

struct node
{
	int item;
	node* next;
};

class CLinkedListStack
{
	node *m_top;

public:
	CLinkedListStack();
	~CLinkedListStack();
	void push(int item);
	int pop();
	int getTop() { return m_top->item; }
	bool isEmpty() { return (m_top == nullptr); }
};

