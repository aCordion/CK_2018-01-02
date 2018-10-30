#pragma once
class CTile
{
private:
	int m_x;
	int m_y;
	int m_num;

public:
	CTile();
	~CTile();
	CTile(int x, int y, int n) : m_x(x), m_y(y), m_num(n){}
	void setTile(int x, int y, int n) { m_x = x; m_y = y; m_num = n; }
	int getX() { return m_x; }
	int getY() { return m_y; }
	int getNum() { return m_num; }
	void draw();
};

