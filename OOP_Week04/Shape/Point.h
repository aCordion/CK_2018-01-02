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
		cout << "�� ( " << x << " , " << y << " ) ������ \n";
	}
	~Point(){
		cout << "�� ( " << x << " , " << y << " ) �Ҹ��� \n";
	}

	void print() { cout << "\t (" << x << " , " << y << " ) \n"; }
};

