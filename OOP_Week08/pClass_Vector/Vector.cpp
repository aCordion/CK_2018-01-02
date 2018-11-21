#include "Vector.h"


void CVector::setRand(int max)
{
	for (int i = 0; i < dim; i++) {
		arr[i] = rand() % (max * 10) / 10.0;
	}
}

void CVector::print(char * str)
{
	cout << str << "[" << dim << "] = < ";
	for (int i = 0; i < dim; i++) {
		cout << arr[i] << " ";
	}
	cout << ">\n";
}

void CVector::clone(CVector & a)
{
	if (dim > 0) {
		delete[] arr;
	}
	dim = a.dim;
	arr = new double[dim];
	for (int i = 0; i < dim; i++) {
		arr[i] = a.arr[i];
	}
}

//void CVector::add(CVector a, CVector b)	//복사 생성자 오류
void CVector::add(CVector& a, CVector& b)	//참조자를 이용하여 해결
{
	for (int i = 0; i < dim; i++) {
		arr[i] = a.arr[i] + b.arr[i];
	}
}

void CVector::add(CVector* a, CVector* b)	//포인터를 이용
{
	for (int i = 0; i < dim; i++) {
		arr[i] = a->arr[i] + b->arr[i];
	}
}
