#pragma once
#include "Tile.h"
#include <iostream>

using namespace std;


class CGameMap
{
	int m_width;
	int m_height;
	CTile ** m_map;

public:
	~CGameMap();
	CGameMap(int w, int h);
	void initMap();
	void setMap(int w, int h);
	CTile ** getMap() { return m_map; }
	void draw();
};

