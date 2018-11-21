#include <iostream>
#include <cstdio>
#include <iomanip>
#include "rational.h"

using namespace std;

class Complex {
	double real;
	double imag;

public:
	Complex(double r = 0.0, double i = 0.0) : real(r), imag(i){}
	void print(char* msg = "복소수 = ") {
		cout << msg << real << " + " << imag << "i" << endl;
	}

	// c.add(a, b);
	void add(Complex a, Complex b) {
		real = a.real + b.real;
		imag = a.imag + b.imag;
	}

	// c = add(a,b);
	friend Complex add(Complex a, Complex b) {
		return Complex(a.real + b.real, a.imag + b.imag);
	}

	// c = a.add(b);
	Complex add(Complex b) {
		return Complex(real + b.real, imag + b.imag);
	}

	// c3 = c1 + c2;
	Complex operator + (Complex b) {
		return Complex(real + b.real, imag + b.imag);
	}

	// c3 = -c1;
	Complex operator-() {
		return Complex(-real, -imag);
	}

	// c3 = ~c1;
	Complex operator~() {
		return Complex(real, -imag);
	}

	Complex operator * (double s) {
		return Complex(real*s, imag*s);
	}

	friend Complex operator * (double s, Complex c) {
		return Complex(c.real * s, c.imag * s);
	}

	Complex& operator = (Complex a) {
		return Complex(real = a.real, imag = a.imag);
	}

	Complex& operator += (Complex a) {
		return Complex(real += a.real, imag += a.imag);
	}

	Complex& operator -= (Complex a) {
		return Complex(real -= a.real, imag -= a.imag);
	}

	bool operator == (Complex a) {
		return (real == a.real) && (imag == a.imag);
	}

	bool operator != (Complex a) {
		return (real != a.real) || (imag != a.imag);
	}

};

void main() {
	Complex c1(1, 2), c2(3, 4), s1, s2, s3, s4, c3, c4, c5, c6,c7, c8;

	s1.add(c1, c2);		// case #1
	s2 = add(c1, c2);	// case #2
	s3 = c1.add(c2);	// case #3
	s4 = c1 + c2;		// case #4	//c1.operator+(c2);

	c1.print("c1(1, 2) = ");
	c2.print("c1(3, 4) = ");
	s1.print("s1.add(c1, c2) = ");
	s1.print("s2 = add(c1, c2) =");
	s1.print("s3 = c1.add(c2) =");
	s1.print("s4 = c1 + c2 =");

	c3 = -c1;	//-a -bi
	c3.print("c3 = -c1 : ");
	c4 = ~c1;	//a -bi
	c4.print("c4 = ~c1 : ");

	c5 = c1 * 2.0;
	c5.print("c5 = c1 * 2.0 : ");
	c6 = 3.0 * c1;
	c6.print("c6 = 3.0 * c1 : ");

	c7 = c8 = c1;
	c7.print("c7 = c8 = c1 : ");

	c7 += c1;	//c7.operator += (c1);
	c7.print("c7 += c1 : ");

	c8 -= c1;
	c8.print("c8 -= c1 : ");

	bool f = c1 == c2;
	cout << "f = c1 == c2 : " << f << endl;

	f = c1 != c2;
	cout << "f = c1 != c2 : " << f << endl;

	Rational a(4), b(8, 6), c, d;

	c[0] = 3;
	cout << "c[0] = 3 : " << c[0] << endl;
	c[1] = 4;
	cout << "c[1] = 4 : " << c[1] << endl;

	cout << "a = " << a << endl;

	cout << " d 입력 = (top, bottom) : ";
	cin >> d;
	cout << "d = " << d << endl;

	cout << "(double) a : " << (double)a << endl;
	cout << "(float) b : " << setprecision(3) << (float)b << endl;

	cout << "a : " << a << endl;
	cout << "a++ : " << a++ << endl;
	cout << "a : " << a << endl;

	cout << "b : " << b << endl;
	cout << "++b : " << ++b << endl;

}