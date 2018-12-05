#include "ArrayCircleQueue.h"

CArrayCircleQueue::~CArrayCircleQueue()
{
	delete[] m_Data;
}

CArrayCircleQueue::CArrayCircleQueue(int nData = 10)
{
	for (int i = 0; i < nData; i++) {
		m_Data = new int[nData];
	}
	for (int i = 0; i < nData; i++) {
		m_Data[i] = 0x00;
	}
	m_Front = 0;
	m_Rear = 0;
	m_count = 0;
	m_max = nData;
}

void CArrayCircleQueue::enqueue(int data)
{
	if (isFull()) {
		cout << "queue is FULL\n";
		return;
	}
	else if (m_Rear == m_max) {
		m_Data[m_Rear] = data;
		m_Rear = 0;
	}
	else {
		m_Data[m_Rear++] = data;
	}
	m_count++;
}

void CArrayCircleQueue::dequeue()
{
	if (isEmpty()) {
		cout << "queue is EMPTY\n";
		return;
	}

	else if (m_Front == m_max) {
		m_Front = 0;
	}
	else {
		m_Front++;
	}
	m_count--;

}
