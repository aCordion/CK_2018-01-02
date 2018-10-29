#pragma once
#include <iostream>
#include <iomanip>
#include "Snake.h"

using namespace std;

class CMatrix
{
	int rows, cols;
	int** mat;
	bool food;

public:
	CMatrix(int r = 24, int c = 52) : rows(r), cols(c), mat(NULL) {
		mat = new int*[rows];
		for (int i = 0; i < rows; i++) {
			mat[i] = new int[cols];
		}
		food = false;
		init();
	}
	~CMatrix();
	void init();
	void setMat(int x, int y, int matType) { mat[y][x] = matType; }
	int& elem(int x, int y) { return mat[y][x]; }
	int Rows() { return rows; }
	int Cols() { return cols; }
	int** Data() { return mat; }
	void print();
//	void setFood(snakeParts &a);
	void setFood();
	void bSetFood(bool value) { food = value; }
	bool bGetFood() { return food; }
	bool wallCrash();
};

