#include "LinkedListQueue.h"



CLinkedListQueue::CLinkedListQueue()
{
	m_front = nullptr;
	m_tail = nullptr;
	m_count = 0;
}


CLinkedListQueue::~CLinkedListQueue()
{
	int temp;
	while (!isEmpty()) {
		temp = dequeue();
	}
}

void CLinkedListQueue::enqueue(int item)
{
	node * inTemp = new node;
	inTemp->item = item;
	inTemp->next = nullptr;

	//if(count == 0){
	if (!m_tail) {
		m_front = inTemp;
		m_tail = inTemp;
	}
	else {
		m_tail->next = inTemp;
		m_tail = inTemp;
	}
	m_count++;
}

int CLinkedListQueue::dequeue()
{
	//if ( (nullptr == m_front) || isEmpty()) {
	if (m_count == 0){
		return -1;
	}

	node *outTemp = m_front;
	int item = m_front->item;
	m_front = m_front->next;

	delete outTemp;
	m_count--;
	return item;
}
