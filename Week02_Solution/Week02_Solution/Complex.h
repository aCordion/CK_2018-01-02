#pragma once
#include <iostream>

struct Complex
{
	double real;
	double imag;
};


inline void setComplex(Complex &c, double r, double i) {
	c.real = r;
	c.imag = i;
}

extern Complex readComplex(char* msg = " 복소수 =");
extern void    printComplex(Complex c, char* msg = "복소수 = ");
extern Complex addComplex(Complex a, Complex b);