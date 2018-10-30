#pragma once


class CPlayer
{
	int m_x;	//플레이어 좌표
	int m_y;	//플레이어 좌표
	int m_width;	//화면 가로 크기
	int m_height;	//화면 세로 크기

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

