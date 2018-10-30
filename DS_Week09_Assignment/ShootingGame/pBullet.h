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
	int		m_count;	//����Ʈ�� ����� �������� ����

	int		m_width;	//ȭ�� ���� ũ��
	int		m_height;	//ȭ�� ���� ũ��

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
