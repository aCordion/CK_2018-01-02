#pragma once
#include "Point.h"

class Line
{
	Point p1, p2;

public:
	Line(int x1, int y1, int x2, int y2) : p1(x1, y1), p2(x2, y2) {
		cout << "Line = (" << x1 << ", " << y1 << "), (" << x2 << ", " << y2 << ") 持失切 \n";
	}
	~Line() {
		cout << "Line  社瑚切 \n";
	}
	void print() {
		cout << "Line : \n";
		p1.print();
		p2.print();
	}
};

