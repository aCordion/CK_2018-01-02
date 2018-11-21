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

//void CVector::add(CVector a, CVector b)	//���� ������ ����
void CVector::add(CVector& a, CVector& b)	//�����ڸ� �̿��Ͽ� �ذ�
{
	for (int i = 0; i < dim; i++) {
		arr[i] = a.arr[i] + b.arr[i];
	}
}

void CVector::add(CVector* a, CVector* b)	//�����͸� �̿�
{
	for (int i = 0; i < dim; i++) {
		arr[i] = a->arr[i] + b->arr[i];
	}
}
