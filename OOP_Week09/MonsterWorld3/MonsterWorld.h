#pragma once
#include "Canvas.h"
#include "Monster.h"
#include "Matrix.h"
#include <Windows.h>

#define DIM 40
#define MAXMONS 5

class CMonsterWorld
{
//	int map[DIM][DIM];
	CMatrix world;
	int xMax, yMax, nMon, nMove;
//	CMonster mon[MAXMONS];
	CMonster* pMon[MAXMONS];
	CCanvas canvas;
	int&Map(int x, int y) { return world.elem(x, y); }
	bool isDone() { return (countItems() == 0) || (nMon == 0); }
	int countItems();
	void print();

public:
	CMonsterWorld(int w, int h);
	~CMonsterWorld();
//	void add(CMonster& m) { if (nMon < MAXMONS) mon[nMon++] = m; }
	void add(CMonster* m) { if (nMon < MAXMONS) pMon[nMon++] = m; }
	void play(int maxwalk, int wait);
};

