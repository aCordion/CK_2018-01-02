#pragma once
#include "Tile.h"
#include <iostream>

using namespace std;


class CGameMap
{
	int m_width;
	int m_height;
	int m_mineNum;
	int checkStatus;
	int nLeftTiles;
	int nOpenTiles;
	CTile ** m_map;

public:
	~CGameMap();
	CGameMap(int w, int h, int n);
	void initMap();
	void setMines();
	void setMap(int w, int h, int n);
	void updateTile(int x, int y);
	CTile ** getMap() { return m_map; }
	void setTile(int x, int y, bool bOpen);
	void draw();
	void rcTileOpenner(int x, int y);
	void allTileOpen();
	bool isBomb(int x, int y) { return m_map[y][x].getNum() == 9; }
	bool isEmpty(int x, int y) { return m_map[y][x].getNum() == 0; }
	int getCheckStatus() { return checkStatus; }
	void setCheckStatus(int status) { checkStatus = status; }
	int getLeftTiles() { return nLeftTiles; }
	int getOpenTiles() { return nOpenTiles; }
	void rstMap(int w, int h, int n);

//	void setOpen(bool open) { (*m_map)->setOpen(open); }
};

