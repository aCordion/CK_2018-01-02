#pragma once


class CMyCursor
{
	int m_x;	//Ŀ�� ��ǥ
	int m_y;	//Ŀ�� ��ǥ
	int m_width;	//ȭ�� ���� ũ��
	int m_height;	//ȭ�� ���� ũ��
	bool isHide;

public:
	CMyCursor();
	~CMyCursor();
	CMyCursor(int x, int y, int w, int h, bool hide = true) : m_x(x), m_y(y), m_width(w), m_height(h), isHide(hide){}
	int getX() { return m_x; }
	int getY() { return m_y; }
	void goUp() { m_y - 1 < 0 ? 0 : m_y--; }
	void goDown() { m_y + 1 > m_height - 1 ? 0 : m_y++; }
	void goLeft() { m_x - 1 < 0 ? 0 : m_x--; }
	void goRight() { m_x + 1 > m_width - 1 ? 0 : m_x++; }

	void setHide(bool hide) { isHide = hide; }

	void draw();

};

