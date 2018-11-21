#pragma once
class CGameObject
{
	int m_x;
	int m_y;

public:
	CGameObject() {}
	~CGameObject() {}
	CGameObject(int x, int y) : m_x(x), m_y(y) {}

	int getX() { return m_x; }
	int getY() { return m_y; }

	void setXY(int x, int y) { m_x = x; m_y = y; }

	virtual void draw() = 0;
	virtual void update() = 0;
};

