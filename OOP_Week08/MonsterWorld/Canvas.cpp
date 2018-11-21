#include "Canvas.h"



CCanvas::CCanvas()
{
}
CCanvas::CCanvas(int nx = 10, int ny = 10): xMax(nx), yMax(ny) {
	for (int y = 0; y < yMax; y++) {
		line[y] = string(xMax * 2, ' ');
	}
}

CCanvas::~CCanvas()
{
}

void CCanvas::draw(int x, int y, string val)
{
	if (x >= 0 && y >= 0 && x < xMax && y < yMax) {
		line[y].replace(x * 2, 2, val);
	}
}

void CCanvas::clear(string val)
{
	for (int y = 0; y < yMax; y++) {
		for (int x = 0; x < xMax; x++) {
			draw(x, y, val);
		}
	}
}

void CCanvas::print(char * title)
{
	system("cls");
	cout << title << endl;
	for (int y = 0; y < yMax; y++) {
		cout << line[y] << endl;
	}
	cout << endl;
}
