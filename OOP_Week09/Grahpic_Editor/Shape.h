#pragma once
#include "Canvas.h"

class Point {
public:
	int x, y;
	Point(int xx = 0, int yy = 0) : x(xx), y(yy){}
	void move(int dx, int dy) { x += dx; y += dy; }
};

class Shape
{
protected:
	Point p;
public:
	Shape();
	Shape(int x = 0, int y = 0) : p(x, y) {}
	~Shape();
	void draw(CCanvas& canvas, string color = "¡Ú");
	void move(int dx, int dy) { p.move(dx, dy); }
};

inline int Abs(int x) { return x > 0 ? x : -x; }
inline int Max(int x, int y) { return x > y ? x : y; }
inline int Round(double x) { return (int)(x + 0.5); }

class Line : public Shape {
	Point q;

public:
	Line(int x1 = 0, int y1 = 0, int x2 = 0, int y2 = 0) :Shape(x1, y1), q(x2, y2) {}
	void draw(CCanvas& canvas, string color = "¼±");
	void move(int dx, int dy) { p.move(dx, dy); q.move(dx, dy); }
};

class HLine : public Line {
public:
	HLine(int x = 0, int y = 0, int len = 0) :Line(x, y, x + len, y) {}
};

class VLine : public Line {
public:
	VLine(int x = 0, int y = 0, int len = 0) :Line(x, y, x, y + len) {}
};


class Rect : public Shape {
	int w, h;
public:
	Rect(int x = 0, int y = 0, int ww = 0, int hh = 0) : Shape(x, y), w(ww), h(hh) {}
	void draw(CCanvas& canvas, string color = "¡á");
};

class Square : public Rect {
public :
	Square(int x = 0, int y = 0, int w = 0) : Rect(x, y, w, w) {}
};

class Circle : public Shape {
	int r;
public:
	Circle(int x = 0, int y = 0, int rr = 0) : Shape(x, y), r(rr) {}
	void draw(CCanvas& canvas, string color = "¡Ý");
};