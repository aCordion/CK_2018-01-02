#include "BulletList.h"



BulletList::BulletList() : m_head(nullptr), m_tail(nullptr), m_count(0)
{
}


BulletList::~BulletList()
{
	while (m_head) {
		remove(0);
	}
	if (m_head) {
		delete m_head;
	}
	if (m_tail) {
		delete m_tail;
	}
}

void BulletList::insert(int pos, Bullet * obj)
{
	if (pos < 0 || pos > m_count) {
		return;
	}
	bNode *curNode = m_head;
	bNode *inNode = new bNode;
	inNode->object = obj;

	if (pos == 0) {	// ù ��° ��ġ
		inNode->next = m_head;
		m_head = inNode;
		if (m_count == 0) {	// ù �Է� ������
			m_tail = inNode;
		}
	}
	else {	// pos-1��ġ���� ������ �̵�
		for (int i = 0; i < pos - 1; i++) {
			curNode = curNode->next;
		}
		inNode->next = curNode->next;
		curNode->next = inNode;
		if (m_count == pos) {
			m_tail = inNode;
		}
		//for (int i = 0; i < pos - 1; curNode = curNode->next, i++) {}
	}
	m_count++;
}

void BulletList::remove(int pos)
{
	if (isEmpty()) { return; }
	if (pos < 0 || pos > m_count - 1) { return; }

	bNode *curNode = m_head;
	bNode *delNode;
	if (pos == 0) {	// ù ��° object ������ ���
		delNode = m_head;
		m_head = m_head->next;
		if (delNode->next == nullptr) {
			m_tail = nullptr;
		}
		//delete delNode->object;
		delete delNode;
	}
	else {	//pos-1�� ��ġ���� ������ �̵�
		for (int i = 0; i < pos - 1; i++) {
			curNode = curNode->next;
		}
		delNode = curNode->next;
		if (delNode->next == nullptr) {
			m_tail = curNode;
		}
		curNode->next = delNode->next;
		//delete delNode->object;
		delete delNode;
	}
	m_count--;
}

Bullet * BulletList::getObject(int pos)
{
	bNode *retNode = m_head;

	if (isEmpty()) { return nullptr; }
	if (pos < 0 || pos > m_count - 1) { return nullptr; }

	for (int i = 0; i < pos; i++) {
		retNode = retNode->next;
	}
	return (retNode->object);
}

void BulletList::pushFront(Bullet * obj)
{
	insert(0, obj);
}

void BulletList::pushTail(Bullet * obj)
{
	bNode * inNode = new bNode;
	inNode->object = obj;
	inNode->next = nullptr;

	if (m_head == nullptr) {//if no object in the list
		m_tail = inNode;
		m_head = inNode;
	}
	else {
		m_tail->next = inNode;
		m_tail = inNode;
	}
	m_count++;
}
