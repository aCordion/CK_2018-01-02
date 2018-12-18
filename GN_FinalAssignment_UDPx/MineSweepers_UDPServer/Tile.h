#pragma once
class CTile
{
private:
	int m_x;
	int m_y;
	int m_num;
	bool m_bOpen;
public:
	CTile();
	~CTile();
	CTile(int x, int y, int n) : m_x(x), m_y(y), m_num(n), m_bOpen(false){}
	void setTile(int x, int y, int n) { m_x = x; m_y = y; m_num = n; }
	int getX() { return m_x; }
	int getY() { return m_y; }
	int getNum() { return m_num; }
	char getCNum();
	bool isOpen() { return m_bOpen; }
	void setOpen(bool open) { m_bOpen = open; }
	void draw();
};

