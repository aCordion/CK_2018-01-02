#include "ObjectList.h"


CObjectList::CObjectList() : m_head(nullptr), m_tail(nullptr), m_count(0)
{
}

CObjectList::~CObjectList()
{
	if (m_head) {
		delete m_head;
	}
	if (m_tail) {
		delete m_tail;
	}
}

void CObjectList::insert(int pos, CGameObject *obj)
{
	if (pos < 0 || pos > m_count) {
		return;
	}
	node *curNode = m_head;
	node *inNode = new node;
	inNode->object = obj;

	if (pos == 0) {	// 첫 번째 위치
		inNode->next = m_head;
		m_head = inNode;
		if (m_count == 0) {	// 첫 입력 데이터
			m_tail = inNode;
		}
	}
	else {	// pos-1위치까지 포인터 이동
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

void CObjectList::remove(int pos)
{
	if (isEmpty()) { return; }
	if (pos < 0 || pos > m_count - 1) { return; }

	node *curNode = m_head;
	node *delNode;
	if (pos == 0) {	// 첫 번째 object 제거일 경우
		delNode = m_head;
		m_head = m_head->next;
		if (delNode->next == nullptr) {
			m_tail = nullptr;
		}
		delete delNode->object;
		delete delNode;
	}
	else {	//pos-1의 위치까지 포인터 이동
		for (int i = 0; i < pos - 1; i++) {
			curNode = curNode->next;
		}
		delNode = curNode->next;
		if (delNode->next == nullptr) {
			m_tail = curNode;
		}
		curNode->next = delNode->next;
		delete delNode->object;
		delete delNode;
	}
	m_count--;
}

CGameObject * CObjectList::getObject(int pos)
{
	node *retNode = m_head;
	
	if (isEmpty()) { return nullptr; }
	if (pos < 0 || pos > m_count - 1) { return nullptr; }

	for (int i = 0; i < pos; i++) {
		retNode = retNode->next;
	}
	return (retNode->object);
}

void CObjectList::pushFront(CGameObject *obj)
{
	insert(0, obj);
	/*
	node *inNode = new node;
	inNode->object = obj;
	inNode->next = m_head;
	m_head = inNode;
	if (m_head->next == nullptr) {
		m_tail = inNode;
	}
	m_count++;
	*/
}

void CObjectList::pushTail(CGameObject *obj)
{
	node * inNode = new node;
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
