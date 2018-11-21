#include "constructor.h"



Complex::Complex()
{
	real = 5;
	image = 20;
}


/*
Complex::Complex(int r, int i)
{
	real = r;
	image = i;
}
*/

Complex::Complex(int r, int i) : real(r), image(i) {};
/*
{
	real = r;
	image = i;
}
*/


Complex::~Complex()
{
	cout << "Complex Detructor Call......\n";
}

void Complex::ShowComplex() const
{
	cout << "( " << real << " + " << image << "i )" << endl;
}

void main() {
	Complex a;
	a.ShowComplex();

	Complex b(10, 30);
	b.ShowComplex();
}