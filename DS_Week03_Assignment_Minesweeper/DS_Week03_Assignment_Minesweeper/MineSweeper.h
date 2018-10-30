#pragma once
#include <iostream>
#include <cstdlib>
#include <string>
#include <conio.h>
#include <memory>
#include <ctime>
#include <ctype.h>

#define MAXSIZE 9

using namespace std;

class CMineSweeper
{
	int **MineMapMask;
	int **MineMapTile;
	int nx, ny, nBomb;
public:
	CMineSweeper();
	~CMineSweeper();

	void rstMineMapMask();
	void rstMineMapTile();

	void dig(int x, int y);
	void mark(int x, int y);
	int getBombCount();
	void print();
	int countNbrBombs(int x, int y);
	void init(int total = 9);
	bool getPos(int& x, int& y);
	int checkDone();
	void playMineSweeper(int total);

	int& mask(int x, int y) { return MineMapMask[y][x]; }
	int& label(int x, int y) { return MineMapTile[y][x]; }
	bool isValid(int x, int y) { return (x >= 0 && x < nx && y >= 0 && y < ny); }
	bool isBomb(int x, int y);
	bool isEmpty(int x, int y);
	int getNums(const int MAX);
};

