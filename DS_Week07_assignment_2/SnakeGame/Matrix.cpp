#pragma once
#include "Matrix.h"

enum eTileType { BLANK = 0, WALL = 1, FOOD = 2, SNAKE = 3 };
char *arrTileImg[] = { " ", "¡á", "¡Ý", "¢Ã" };

CMatrix::~CMatrix()
{
	if (mat != NULL) {
		for (int i = 0; i < rows; i++) {
			delete[] mat[i];
		}
		delete[] mat;
	}
	delete[] arrTileImg;
}

void CMatrix::init()
{
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			mat[i][j] = BLANK;
			if (i == 0 || i == rows-1 || j == 0 || j == cols-1) {
				mat[i][j] = WALL;
			}
		}
	}
}

void CMatrix::print()
{
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			cout << setw(2) << arrTileImg[mat[i][j]];
		}
		cout << endl;
	}
}

void CMatrix::setFood()
{
	int x, y;

	bool isContinue = true;

	if (!food) {
		while (isContinue) {
			x = (rand() % rows);
			y = (rand() % cols);
			x++; y++;
			if ( (y > 0 && y < rows - 1 && x > 0 && x < cols - 1) && mat[y][x] == BLANK){
				mat[y][x] = FOOD;
				food = true;
				isContinue = false;
			}
		} 
		//while (elem(x,y) != BLANK || ((y <= 0) || (y >= (tempRows-1)) || (x <= 0) || (x >= (tempCols-1))));
	}
}
bool CMatrix::wallCrash()
{
//	if (i == 0 || i == rows - 1 || j == 0 || j == cols - 1)
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			if (i == 0 || i == rows - 1 || j == 0 || j == cols - 1) {
				if (mat[i][j] != WALL) {
					return true;
				}
			}
		}
	}
	return false;
}
/*
void CMatrix::setFood(snakeParts &a)
{
	if (!food) {
		int x, y;
		do {
			x = rand() % (rows);
			y = rand() % (cols);
		} while ((a.x == (x)) && (a.y == (y)) || ((y == 0) || (y == rows-1) || (x == 0) || (x == cols-1)));
		mat[y][x] = FOOD;
		food = true;
	}
}
*/
