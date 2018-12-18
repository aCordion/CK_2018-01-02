#pragma once
#include "ObjectList.h"
#include "Character.h"

struct eNode {
	Enemy *object;
	eNode *next;
};

class EnemyList
{
	eNode *m_head;
	eNode *m_tail;
	int m_count;

public:
	EnemyList();
	~EnemyList();
	void insert(int pos, Enemy *obj);
	void remove(int pos);
	Enemy *getObject(int pos);
	void pushFront(Enemy *obj);
	void pushTail(Enemy *obj);
	bool isEmpty() { return m_head == nullptr; }
	int getCount() { return m_count; }
};

