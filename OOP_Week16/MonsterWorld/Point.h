#pragma once
#include <iostream>
#include <cmath>

using namespace std;


class Point
{
	int x, y;
	friend class Monster;
	friend class Canvas;

public:
	Point(int xx = 0, int yy = 0) : x(xx), y(yy) {}
	~Point();
	int& operator[] (int id);
	operator double();
	void operator()(int maxx, int maxy);
	Point operator- ();
	bool operator== (Point &p);
	bool operator!= (Point &p);
	Point operator- (Point &p);
	Point operator+ (Point &p);
	void operator+= (Point &p);
	void operator-= (Point &p);
};

