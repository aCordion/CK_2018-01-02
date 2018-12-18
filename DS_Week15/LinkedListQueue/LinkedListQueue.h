#pragma once

struct node
{
	int item;
	node* next;
};

class CLinkedListQueue
{
	node *m_front;
	node *m_tail;
	int m_count;

public:
	CLinkedListQueue();
	~CLinkedListQueue();
	void enqueue(int item);
	int dequeue();
	int getFront() { return m_front->item; }
	bool isEmpty() { return (nullptr == m_front); }
};

