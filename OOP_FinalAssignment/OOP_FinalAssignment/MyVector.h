#pragma once
#include <iostream>
#include <string>
using namespace std;

template <typename T>
class Vector {
	T*	arr;
	int	dim;
	int	maxCapacity;
public:
	Vector(int d = 0) : dim(0), maxCapacity(0), arr(NULL) {
		resize((d>4) ? d : 4);
		dim = d;
	}
	Vector(Vector<T>& v) :arr(NULL) { clone(v); }
	~Vector() { delete[] arr; }

	void resize(int size) {
		if (size > maxCapacity) {
			T*	old = arr;
			maxCapacity = size;
			arr = new T[maxCapacity];
			for (int i = 0; i < dim; i++)
				arr[i] = old[i];
			delete[] old;
		}
	}
	Vector& clone(Vector<T>& v) {
		delete[] arr;
		dim = v.dim;
		maxCapacity = v.capacity();
		arr = new T[maxCapacity];
		for (int i = 0; i < dim; i++)
			arr[i] = v[i];
		return *this;
	}
	Vector<T>& operator=(Vector<T>& v) { return clone(v); }

	int size() { return dim; }
	int capacity() { return maxCapacity; }
	bool empty() { return dim == 0; }
	void clear() { dim = 0; }

	T front() { return arr[0]; }
	T back() { return arr[dim - 1]; }
	T&	at(int id) { return arr[id]; }
	T& operator[] (int id) { return arr[id]; }

	void pop_back() { dim--; }
	void push_back(T val) {
		if (dim == maxCapacity)
			resize(maxCapacity * 2);
		arr[dim++] = val;
	}
	friend ostream& operator << (ostream& os, Vector<T>& v) {
		os << "< ";
		for (int i = 0; i < v.dim; i++)
			os << v[i] << " ";
		os << ">";
		return os;
	}
};