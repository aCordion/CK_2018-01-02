#pragma once
#include <iostream>

using namespace std;

class CVector
{
	int dim;
	double *arr;

public:
	CVector(int d = 0) : dim(d) { arr = new double[dim]; }
	~CVector() { delete[] arr; }

	double& operator[] (int id) { return arr[id]; }	// a[i];
	friend ostream& operator<< (ostream& os, CVector& v) {
		os << " < ";
		for (int i = 0; i < v.dim; i++) {
			os << v.arr[i] << " ";
		}
		os << " >";
		return os;
	}
	CVector operator+ (CVector& v) {
		CVector sum(v.dim);
		for (int i = 0; i < dim; i++) {
			sum[i] = arr[i] + v[i];
		}
		return sum;
	}

	void setRand(int max = 100) {
		for (int i = 0; i < dim; i++) {
			arr[i] = rand() % (max * 10) / 10.0;
		}
	}

	void print(char* str = "Vector") {
		cout << str << "[ " << dim << " ] = <";
		for (int i = 0; i < dim; i++) {
			cout << arr[i] << " ";
		}
		cout << "\n";
	}

	void add(CVector& a, CVector& b) {
		for (int i = 0; i < dim; i++) {
			arr[i] = a[i] + b[i];
		}
	}

	void clone(CVector& a) {
		if (dim > 0) {
			delete[] arr;
		}
		dim = a.dim;
		arr = new double[dim];
		for (int i = 0; i < dim; i++) {
			arr[i] = a.arr[i];
		}
	}
	CVector& operator= (CVector& a) {
		clone(a);
		return *this;
	}

	CVector(CVector& a) : arr(NULL) { clone(a); }
};