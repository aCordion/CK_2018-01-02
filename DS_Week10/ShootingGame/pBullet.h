#pragma once

struct Bullet {
	int b_x;
	int b_y;
};

struct node {
	Bullet data;
	node *next;
};

class CpBullet
{
	node*	m_head;
	node*	m_tail;
	int		m_count;	//리스트에 저장된 데이터의 갯수

	int		m_width;	//화면 가로 크기
	int		m_height;	//화면 세로 크기

public:
	CpBullet(int w, int h);
	~CpBullet();
	void insert(int pos, int data_x, int data_y);
	Bullet retrieve(int pos);
	void remove(int pos);
	void append(int data_x, int data_y);
	bool isEmpty() { return m_head == nullptr; }
	int getLength() { return m_count; }

	void draw();

	void bulletGoUp();
	void tailFind();

};
