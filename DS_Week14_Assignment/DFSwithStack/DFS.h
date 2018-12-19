#pragma once
#include "LinkedListStack.h"
#include <iostream>
#include <iomanip>
#include <Windows.h>
using namespace std;
#define MAX_X 20

class DFS
{
	int m_maxX, m_maxY;
	int **m_copyMap;
	bool **m_visitMap;
	pos *m_route;
	int m_rIndex;
	pos m_curPos;
	pos m_fromPos;
	pos m_toPos;
	CLinkedListStack m_visitStack;

	
public:
	DFS(pos maxPos, pos from, pos to);
	~DFS();

	void mapCopy(int y, int x, int data);
	bool Find();

	bool checkVisited();
	void chooseNext();


	void TESTDRAW();
	void drawRoutePos();
	void drawRouteView();
};

