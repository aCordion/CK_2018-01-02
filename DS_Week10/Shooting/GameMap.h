#pragma once

class CGameMap
{
	int m_width;
	int m_heigth;

public:
	~CGameMap(){}
	CGameMap(int w, int h) : m_width(w), m_heigth(h) {}

	int getWidth() { return m_width; }
	int getHeigth() { return m_heigth; }
};
