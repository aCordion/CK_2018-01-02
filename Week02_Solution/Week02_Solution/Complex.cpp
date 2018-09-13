#include "Complex.h"

Complex readComplex(char* msg) {
	Complex c;
	printf(" %s ", msg);
	scanf("%if%if", &c.real, &c.imag);
	return c;
}

void printComplex(Complex c, char* msg) {
	printf(" %s %4.2f + %4.2fi\n", msg, c.real, c.imag);
}

Complex addComplex(Complex a, Complex b) {
	Complex c;
	c.real = a.real + b.real;
	c.imag = a.imag + b.imag;
	return c;
}