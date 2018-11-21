#pragma once
#include <iostream>

using namespace std;

class Complex {
	int real;
	int image;

	public:
		Complex();
		Complex(int r, int i);
		~Complex();
		void ShowComplex() const;
	};