#pragma once
#include <string>
using namespace std;

struct pos {
	int x, y;

	bool operator != (pos a) {
		return (x != a.x) || (y != a.y);
	}
	friend ostream& operator << (ostream& os, const pos& f) {
		os << "(y" << f.y << ", x" << f.x <<")";
		return os;
	}
};

struct node
{
	pos item;
	node* next;
};

class CLinkedListStack
{
	node *m_top;

public:
	CLinkedListStack();
	~CLinkedListStack();
	void push(pos item);
	pos pop();
	pos getTop() { return m_top->item; }
	bool isEmpty() { return (m_top == nullptr); }


};



