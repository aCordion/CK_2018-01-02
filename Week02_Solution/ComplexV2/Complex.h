#pragma once
#include <iostream>

class Complex
{
	double real;
	double imag;

public:
	void set(double r, double i);
	void read(char* msg = " ���Ҽ� =");
	void print(char* msg = "���Ҽ� = ");
	void add(Complex a, Complex b);
};