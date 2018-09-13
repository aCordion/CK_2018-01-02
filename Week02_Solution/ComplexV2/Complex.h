#pragma once
#include <iostream>

class Complex
{
	double real;
	double imag;

public:
	void set(double r, double i);
	void read(char* msg = " 복소수 =");
	void print(char* msg = "복소수 = ");
	void add(Complex a, Complex b);
};