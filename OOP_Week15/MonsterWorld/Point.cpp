#include "Point.h"


Point::~Point()
{
}

int & Point::operator[](int id)
{
	if (id == 0) return x;
	else if (id == 1) return y;
	else exit(0);
}

Point::operator double()
{
	return sqrt((double)x*x + y*y);
}

void Point::operator()(int maxx, int maxy)
{
	if (x < 0) x = 0;
	if (x >= maxx) x = maxx - 1;
	if (y < 0) y = 0;
	if (y >= maxy) y = maxy - 1;
}

Point Point::operator-()
{
	return Point(-x,-y);
}

bool Point::operator==(Point & p)
{
	return x == p.x && y == p.y;
}

bool Point::operator!=(Point & p)
{
	return x != p.x || y != p.y;
}

Point Point::operator-(Point & p)
{
	return Point(x - p.x, y - p.y);
}

Point Point::operator+(Point & p)
{
	return Point(x + p.x, y + p.y);
}

void Point::operator+=(Point & p)
{
	x += p.x, y += p.y;
}

void Point::operator-=(Point & p)
{
	x -= p.x, y -= p.y;
}
