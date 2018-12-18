#pragma once
#include "Bullet.h"

struct bNode {
	Bullet *object;
	bNode *next;
};

class BulletList
{
	bNode *m_head;
	bNode *m_tail;
	int m_count;

public:
	BulletList();
	~BulletList();
	void insert(int pos, Bullet *obj);
	void remove(int pos);
	Bullet *getObject(int pos);
	void pushFront(Bullet *obj);
	void pushTail(Bullet *obj);
	bool isEmpty() { return m_head == nullptr; }
	int getCount() { return m_count; }
};

