#include "LinkedListStack.h"



CLinkedListStack::CLinkedListStack()
{
	m_top = nullptr;
}


CLinkedListStack::~CLinkedListStack()
{
	int temp;
	while (!isEmpty()) {
		temp = pop();
	}
}

void CLinkedListStack::push(int item)
{
	node * inTemp = new node;
	inTemp->item = item;
	inTemp->next = m_top;
	m_top = inTemp;
}

int CLinkedListStack::pop()
{
	if (isEmpty()) {
		return -1;
	}
	node *outTemp = m_top;
	int item = outTemp->item;
	m_top = m_top->next;
	delete outTemp;
	return item;
}
