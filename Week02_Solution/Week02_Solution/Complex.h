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

extern Complex readComplex(char* msg = " ���Ҽ� =");
extern void    printComplex(Complex c, char* msg = "���Ҽ� = ");
extern Complex addComplex(Complex a, Complex b);