#pragma once
#include <iostream>
#include <iomanip>

using namespace std;

class CMatrix
{
	int rows, cols;
	int** mat;

public:
	CMatrix(int r = 0, int c = 0) : rows(r), cols(c), mat(NULL) {
		mat = new int*[rows];
		for (int i = 0; i < rows; i++) {
			mat[i] = new int[cols];
		}
	}
	~CMatrix();
	int& elem(int x, int y) { return mat[y][x]; }
	int Rows() { return rows; }
	int Cols() { return cols; }
	int** Data() { return mat; }	//**mat
	void print(char *str = "Mat");
	void setRand(int val = 100);
};

