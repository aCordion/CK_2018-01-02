#pragma once
#include "Objects.h"

struct node {
	Objects *object;
	node *next;
};

class CObjectList
{
	node *m_head;
	node *m_tail;
	int m_count;

public:
	CObjectList();
	~CObjectList();
	void insert(int pos, Objects *obj);
	void remove(int pos);
	Objects *getObject(int pos);
	void pushFront(Objects *obj);
	void pushTail(Objects *obj);
	bool isEmpty() { return m_head == nullptr; }
	int getCount() { return m_count; }
};
