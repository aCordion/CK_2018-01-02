#pragma once
#include "Point.h"

class Circle
{
	Point center;
	int radius;

public:
	Circle(int cx = 0, int cy = 0, int r = 0) : center(cx, cy), radius(r) {
		cout << "���� ������ = " << radius << " ������ " << endl;
	}
	~Circle() {
		cout << "���� ������ = " << radius << " �Ҹ��� " << endl;
	}
};

