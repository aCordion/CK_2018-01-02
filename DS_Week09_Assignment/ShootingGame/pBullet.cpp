#include "pBullet.h"
#include "util.h"
#include <iostream>

using namespace std;



CpBullet::CpBullet(int w, int h) : m_head(nullptr), m_tail(nullptr), m_count(0), m_width(w), m_height(h)
{
}


CpBullet::~CpBullet()
{
}

void CpBullet::insert(int pos, int data_x, int data_y)
{
	node *inData = new node;
	inData->data.b_x = data_x;
	inData->data.b_y = data_y;

	if (pos == 0) {		//첫 번째 위치에 데이터 추가하는 경우
		inData->next = m_head;
		m_head = inData;
		if (m_count == 0) {
			m_tail = m_head;
		}
		m_count++;
		tailFind();
		return;
	}
	node *temp = m_head;
	for (int i = 0; i < (pos - 1) && (i < m_count - 1); i++) {	//pos-1 위치까지 포인터 이동
		temp = temp->next;
	}
	inData->next = temp->next;
	temp->next = inData;
	m_count++;
	tailFind();
	/*
	m_tail = m_head;
	for (int i = 0; i < m_count - 1; i++) {
		m_tail = m_tail->next;
	}
	*/
}


Bullet CpBullet::retrieve(int pos)
{
	node * temp = m_head;
	for (int i = 0; i < pos; i++) {
		temp = temp->next;
	}
	return temp->data;
}


void CpBullet::remove(int pos)
{
	node * delNode;
	if (isEmpty()) {
		return;
	}
	if (pos == 0) {		//첫 번째 데이터를 삭제할 경우
	
		delNode = m_head;
		m_head = m_head->next;
		delete delNode;

		m_count--;
		tailFind();//
		return;
	}
	
	if (pos > m_count) {	// out of range
		return;
	}
	node *temp = m_head;
	for (int i = 0; i < pos - 1; i++) {		//삭제할 데이터 전 위치까지 포인터 이동
		temp = temp->next;
	}
	delNode = temp->next;
	temp->next = delNode->next;
	delete delNode;
	m_count--;
	tailFind();//
}

void CpBullet::append(int data_x, int data_y)
{

	if (m_head == nullptr) {
		insert(0, data_x, data_y);		
	}

	else {
		node *apendData = new node;
		apendData->data.b_x = data_x;
		apendData->data.b_y = data_y;
		apendData->next = m_tail->next;
		m_tail->next = apendData;
		m_count++;
		tailFind();
	}
}

void CpBullet::draw()
{
	node *temp = m_head;
	while (temp != nullptr){
		char *bulletImg = "Δ";
		ScreenPrint(temp->data.b_x * 2, temp->data.b_y, bulletImg);
		temp = temp->next;
	}
	cout << endl;

}

void CpBullet::bulletGoUp()
{
//	bool wTrigger = true;
	node *temp = m_head;
	int cTemp = m_count;
	int pos = 0;

	while (temp != nullptr) {
		temp->data.b_y -= 1;
		temp = temp->next;
	}

	temp = m_head;
	for (pos; pos < cTemp; pos++) {
		if (temp->next != nullptr) {
			temp = temp->next;
			//if (temp->data.b_y < 1) {
		}
		if (m_head->data.b_y < 1) {
			remove(0);
			//				cTemp = m_count;
		}
		else { 
			return;
		}
		/*
		if (temp != nullptr) {
			if (temp->data.b_y < 1) {
				remove(0);
				cTemp = m_count;
			}
		}*/
		//temp = temp->next;

	}


	/*
	while (temp != nullptr) {
		if ((temp->data.b_y - 1) < 1) {
			remove(pos);
		}
		temp->data.b_y -= 1;
		temp = temp->next;
		if (pos + 1 > m_count) {
			break;
		}
		else {
			pos++;
		}
	}
	*/
	/*
	while (temp != nullptr) {
		temp->data.b_y -= 1;
		temp = temp->next;
	}
	*/
}

void CpBullet::tailFind()
{
	m_tail = m_head;
	for (int i = 0; i < m_count - 1; i++) {
		m_tail = m_tail->next;
	}
}
