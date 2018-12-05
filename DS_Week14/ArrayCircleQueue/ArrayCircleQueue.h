#pragma once
#include <iostream>

using namespace std;

class CArrayCircleQueue
{
	int *m_Data;
	int m_Front;
	int m_Rear;
	int m_count;
	int m_max;

public:
	~CArrayCircleQueue();
	CArrayCircleQueue(int nData);

	void enqueue(int data);
	void dequeue();
	int getFront() { return m_Data[m_Front]; }
	bool isEmpty() { return (m_count == 0); }
	bool isFull() { return (m_count >= m_max); }
	int getSize() { return m_count; }
};

