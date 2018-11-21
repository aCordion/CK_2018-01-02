#pragma once
#include <iostream>
#include <string>

using namespace std;

class Rational {
	int top;
	int bottom;

public:
	Rational(int t = 0, int b = 1) : top(t), bottom(b) {}

	int& operator[] (int id) {
		if (id == 0) { return top; }
		else if (id == 1) { return bottom; }
		else { exit(0); }
	}

	int& operator() (int id) {
		return (*this)[id];
	}

	friend ostream& operator << (ostream& os, const Rational& f) {
		os << f.top << " / " << f.bottom;
		return os;
	}

	friend istream& operator >> (istream& is, Rational& f) {
		is >> f.top >> f.bottom;
		return is;
	}

	operator double() {		//a.operator(double)
		return (double)top / bottom;
	}

	operator float() {		//a.operator(float)
		return (float)top / bottom;
	}

	Rational& operator ++ () {
		++top;
		return *this;
	}

	Rational operator ++ (int) {	//a.operator++(NULL);
		++top;
		return Rational(top - 1, bottom);
	}

};