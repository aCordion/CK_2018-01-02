#pragma once
//#include "ScreenManager.h"
#include "util.h"
#include "Character.h"
#include "Objects.h"

#define MAX_HEIGHT 20
#define MAX_WIDTH 40

class CGameMap
{
	int m_map[MAX_HEIGHT][MAX_WIDTH];
	int m_width;
	int m_height;
	//CScreenManager scrManager;

public:
	CGameMap(int w = MAX_WIDTH, int h = MAX_HEIGHT);
	~CGameMap();

	int& Map(int x, int y) { return m_map[y][x]; }

	void init();
	void draw();
	void print();
};