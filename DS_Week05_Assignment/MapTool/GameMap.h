#pragma once



class CGameMap
{
	int m_width;
	int m_height;
	int **m_map;

public:
	CGameMap();
	~CGameMap();
	CGameMap(int w, int h) : m_width(w), m_height(h) {
		m_map = new int *[h];
		for (int i = 0; i < h; i++) {
			m_map[i] = new int[w];
		}
		initMap();
	}
	void initMap();
	int getTileNum(int x, int y) { return m_map[y][x]; }
	void setTile(int x, int y, int tile) { m_map[y][x] = tile; }
	void draw();
	void actDraw(int x, int y, int KEY);

	void curStatDraw(int x, int y);
};

