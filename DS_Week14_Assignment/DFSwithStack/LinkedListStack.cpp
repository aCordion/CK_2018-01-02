#include "LinkedListStack.h"



CLinkedListStack::CLinkedListStack()
{
	m_top = nullptr;
	
}


CLinkedListStack::~CLinkedListStack()
{
	pos temp;
	while (!isEmpty()) {
		temp = pop();
	}
}

void CLinkedListStack::push(pos item)
{
	node * inTemp = new node;
	inTemp->item = item;
	inTemp->next = m_top;
	m_top = inTemp;
}

pos CLinkedListStack::pop()
{
	if (isEmpty()) {
		pos temp;
		temp.x = 0;
		temp.y = 0;
		return temp;
	}
	node *outTemp = m_top;
	pos item = outTemp->item;
	m_top = m_top->next;
	delete outTemp;

	return item;
}
