#pragma once
class CGameObject
{
	int m_x;
	int m_y;
	char *m_img;

public:
	CGameObject();
	~CGameObject();
	CGameObject(int x, int y, char * img) : m_x(x), m_y(y), m_img(img) {}

	int getX() { return m_x; }
	int getY() { return m_y; }

	void setXY(int x, int y) { m_x = x; m_y = y; }

	void draw();
	virtual void update() {};
};

