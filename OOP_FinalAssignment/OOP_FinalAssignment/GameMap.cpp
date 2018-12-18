#include "GameMap.h"

enum TileStatus {BLANK, WALL, DOOR, VEIL, BOSS};
char *TileImgs[] = { "  ", "¡á", "¢Ì", "¢É", "¢Æ"};

CGameMap::CGameMap(int w, int h) : m_width(w), m_height(h)
{
	for (int i = 0; i < m_height; i++) {
		memset(m_map[i], BLANK, sizeof(int)*m_width);
	}
}

CGameMap::~CGameMap()
{

}

void CGameMap::init()
{
	ScreenInit();
	for (int y = 0; y < m_height; y++) {
		for (int x = 0; x < m_width; x++) {
			if (x == 0 || y == 0 || x == m_width - 1 || y == m_height - 1) {
				m_map[y][x] = WALL;
			}
		}
	}
	//Map create
	{   //WALL
		{
			for (int i = 1; i < 6; i++)
				Map(i, 8) = WALL;
			for (int i = 2; i < 7; i++)
				Map(5, i) = WALL;
			for (int i = 1; i < 6; i++)
				Map(i, 15) = WALL;
			for (int i = 17; i < 19; i++)
				Map(5, i) = WALL;
			for (int i = 5; i < 10; i++)
				Map(9, i) = WALL;
			for (int i = 13; i < 19; i++)
				Map(9, i) = WALL;
			for (int i = 1; i < 15; i++)
				Map(14, i) = WALL;
			for (int i = 11; i < 19; i++)
				Map(18, i) = WALL;
			for (int i = 1; i < 10; i++)
				Map(21, i) = WALL;
			for (int i = 3; i < 7; i++)
				Map(25, i) = WALL;
			for (int i = 10; i < 15; i++)
				Map(25, i) = WALL;
			for (int i = 10; i < 17; i++)
				Map(29, i) = WALL;
			for (int i = 29; i < 39; i++)
				Map(i, 10) = WALL;
			for (int i = 17; i < 19; i++)
				Map(29, i) = DOOR;
		}
		//secret
		{//30,11 to 38,18
			for (int x = 30; x < 39; x++) {
				for (int y = 11; y < 19; y++) {
					Map(x, y) = VEIL;
				}
			}
		}
	}
}

void CGameMap::draw()
{
	for (int y = 0; y < m_height; y++) {
		for (int x = 0; x < m_width; x++) {
			ScreenPrint(x * 2, y, TileImgs[m_map[y][x]]);
		}
	}
}

void CGameMap::print()
{
	ScreenFlipping();
}
