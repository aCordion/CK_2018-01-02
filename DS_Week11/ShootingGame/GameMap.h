#pragma once
#include "util.h"

class CGameMap
{
	int **m_map;
	int m_width;
	int m_heigth;

public:
	~CGameMap(){}
	CGameMap(int w, int h) : m_width(w), m_heigth(h) {
		m_map = new int *[h];
		for (int i = 0; i < h; i++) {
			m_map[i] = new int[w];
		}
		initMap();
	}

	int getWidth() { return m_width; }
	int getHeigth() { return m_heigth; }
	void initMap() {
		for (int y = 0; y < m_heigth; y++) {
			for (int x = 0; x < m_width; x++) {
				if (x == 0 || x == m_width - 1 || y == 0 || y == m_heigth - 1) {
					m_map[y][x] = 1;
				}
				else {
					m_map[y][x] = 0;
				}
			}
		}
	}

	void draw() {
		char *img[] = { "  ", "¢Æ" };
		for (int y = 0; y < m_heigth; y++) {
			for (int x = 0; x < m_width; x++) {
				ScreenPrint(x * 2, y, img[m_map[y][x]]);
			}
		}
	}
};