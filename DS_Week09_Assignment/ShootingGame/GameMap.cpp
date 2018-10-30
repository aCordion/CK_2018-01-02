#include "GameMap.h"
#include <Windows.h>

enum eTileType { BLANK = 0, WALL = 1};

CGameMap::~CGameMap()
{
}

CGameMap::CGameMap(int w, int h)
{
	m_map = nullptr;
	setMap(w, h);
}

void CGameMap::initMap()
{
	for (int y = 0; y < m_height; y++) {
		for (int x = 0; x < m_width; x++) {
			m_map[y][x].setTile(x, y, BLANK);
			if (y == 0 || y == m_height - 1 || x == 0 || x == m_width - 1) {
				m_map[y][x].setTile(x, y, WALL);
			}
		}
	}
}

void CGameMap::setMap(int w, int h)
{

	if (m_map) {
		for (int i = 0; i < m_height; i++) {
			delete[] m_map[i];
		}
		delete[] m_map;
		m_map = nullptr;
	}

	m_width = w;
	m_height = h;

	m_map = new CTile *[m_height];
	for (int i = 0; i < m_height; i++)
		m_map[i] = new CTile[m_width];
	initMap();
}


void CGameMap::draw()
{
	for (int y = 0; y < m_height; y++) {
		for (int x = 0; x < m_width; x++) {
			m_map[y][x].draw();
		}
	}
}
