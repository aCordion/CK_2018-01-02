#pragma once
#include "util.h"

enum TileType {BLANK, WALL};

class CGameMap
{
	int **m_gameMap;
	int m_width;
	int m_heigth;

public:
	~CGameMap(){}
	CGameMap(int w, int h) : m_width(w), m_heigth(h) {
		m_gameMap = new int *[h];
		for (int i = 0; i < h; i++) {
			m_gameMap[i] = new int[w];
		}
		initMap();
	}

	int getWidth() { return m_width; }
	int getHeigth() { return m_heigth; }
	int getMapdata(int x, int y) { return m_gameMap[y][x]; }

	void initMap() {
		TileType tile;
		for (int y = 0; y < m_heigth; y++) {
			for (int x = 0; x < m_width; x++) {
				tile = (x == 0 || x == m_width - 1 || y == 0 || y == m_heigth - 1) ? WALL : BLANK;
					m_gameMap[y][x] = tile;
			}
		}
	}

	void draw() {
		char *tileImg[] = { "  ", "¢Æ" };
		for (int y = 0; y < m_heigth; y++) {
			for (int x = 0; x < m_width; x++) {
				ScreenPrint(x * 2, y, tileImg[m_gameMap[y][x]]);
			}
		}
	}
};