#pragma once


class CMyCursor
{
	int m_x;	//커서 좌표
	int m_y;	//커서 좌표
	int m_width;	//화면 가로 크기
	int m_height;	//화면 세로 크기
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

	void setPos(int x, int y) { m_x = x, m_y = y; }
	void setHide(bool hide) { isHide = hide; }

	void draw();

};

