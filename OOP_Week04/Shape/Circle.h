#pragma once
#include "Point.h"

class Circle
{
	Point center;
	int radius;

public:
	Circle(int cx = 0, int cy = 0, int r = 0) : center(cx, cy), radius(r) {
		cout << "원의 반지름 = " << radius << " 생성자 " << endl;
	}
	~Circle() {
		cout << "원의 반지름 = " << radius << " 소멸자 " << endl;
	}
};

