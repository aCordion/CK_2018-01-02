#pragma once
#include <iostream>

using namespace std;

class Point
{
public:
//	Point();
//	~Point();
	int x, y;
	Point(int xx = 0, int yy = 0) : x(xx), y(yy) {
		cout << "점 ( " << x << " , " << y << " ) 생성자 \n";
	}
	~Point(){
		cout << "점 ( " << x << " , " << y << " ) 소멸자 \n";
	}

	void print() { cout << "\t (" << x << " , " << y << " ) \n"; }
};

