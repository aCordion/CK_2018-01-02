#pragma once
#include <iostream>

using namespace std;

class CMyCursor
{
	int m_x;	//Ŀ�� ��ǥ
	int m_y;	//Ŀ�� ��ǥ
	int m_width;	//ȭ�� ���� ũ��
	int m_height;	//ȭ�� ���� ũ��

public:
	CMyCursor();
	~CMyCursor();
	CMyCursor(int x, int y, int w, int h) : m_x(x), m_y(y),m_width(w),m_height(h){}
	int getX() { return m_x; }
	int getY() { return m_y; }
	void goUp() { m_y - 1 < 0 ? 0 : m_y--; }
	void goDown() { m_y + 1 > m_height - 1 ? 0 : m_y++; }
	void goLeft() { m_x - 1 < 0 ? 0 : m_x--; }
	void goRight() { m_x + 1 > m_width - 1 ? 0 : m_x++; }

	void draw();
};

