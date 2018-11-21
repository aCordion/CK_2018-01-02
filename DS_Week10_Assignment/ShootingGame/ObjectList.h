#pragma once
#include "GameObject.h"

struct node {
	CGameObject object;
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
	void insert(int pos, CGameObject obj);
	void remove(int pos);
	CGameObject *getObject(int pos);
	void pushFront(CGameObject obj);
	void pushTail(CGameObject obj);
	bool isEmpty() { return m_head == nullptr; }
	int getCount() { return m_count; }
};

