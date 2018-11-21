#include "Matrix.h"


CMatrix::~CMatrix()
{
	if (mat != NULL) {
		for (int i = 0; i < rows; i++) {
			delete[] mat[i];
		}
		delete[] mat;
	}
}

void CMatrix::print(char * str)
{
	cout << str << " " << rows << "x" << cols << endl;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			cout << setw(4) << mat[i][j];
		}
		cout << endl;
	}
}

void CMatrix::setRand(int val)
{
	if (mat != NULL) {
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < cols; j++) {
				mat[i][j] = (rand() % val);
			}
		}
	}
}
