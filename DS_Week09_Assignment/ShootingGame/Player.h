#pragma once


class CPlayer
{
	int m_x;	//�÷��̾� ��ǥ
	int m_y;	//�÷��̾� ��ǥ
	int m_width;	//ȭ�� ���� ũ��
	int m_height;	//ȭ�� ���� ũ��

public:
	CPlayer();
	~CPlayer();
	CPlayer(int x, int y, int w, int h) : m_x(x), m_y(y),m_width(w),m_height(h){}
	int getX() { return m_x; }
	int getY() { return m_y; }
	void goLeft() { m_x - 2 < 0 ? 0 : m_x--; }
	void goRight() { m_x + 1 > m_width - 2 ? 0 : m_x++; }

	void draw();

};

