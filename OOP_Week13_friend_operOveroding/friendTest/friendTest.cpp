#include <iostream>
#include <cstdio>
#include <iomanip>

using namespace std;

class Point {
	int x, y;
	friend class Shape;

public:
	Point(int xx = 0, int yy = 0) : x(xx), y(yy) {}
	void print(char *s = "점") { cout << "s = " << s << ", x = " << x << ", y = " << y << endl; }
	friend Point addPoint(Point& p, Point& q);
};

class Shape {

protected:
	Point p;

public:
	Shape(int x = 0, int y = 0) : p(x, y) {}
	void draw() { cout << "[ 형태 ] 위치 = " << p.x << ", " << p.y << endl; }
};

Point addPoint(Point& p, Point& q) {
	Point r;
	r.x = p.x + q.x;
	r.y = p.y + q.y;
	return r;
}

void main() {
	Shape sh(10, 20);
	sh.draw();

	Point arr[3] = { Point(1,2), Point(2,3) };
	arr[2] = addPoint(arr[0], arr[1]);
	arr[2].print();
}