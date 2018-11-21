#pragma once
#include <iostream>

using namespace std;

class CVector
{
	int dim;
	double* arr;

public:
	CVector(int d = 0) : dim(d) { arr = new double[dim]; };
	~CVector() { delete[] arr; };
	void setRand(int max = 100);
	void print(char *str = "Vector");
	void clone(CVector& a);
//	void add(CVector a, CVector b);
	void add(CVector& a, CVector& b);
	void add(CVector* a, CVector* b);
	void operator = (CVector & a) { clone(a); }
};

