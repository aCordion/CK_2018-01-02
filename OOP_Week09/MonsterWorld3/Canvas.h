#pragma once
#include <iostream>
#include <string>

#define MAXLINES 100
using namespace std;

class CCanvas
{
	string line[MAXLINES];
	int xMax, yMax;
public:
	CCanvas();
	~CCanvas();
	CCanvas(int nx, int ny);
	void draw(int x, int y, string val);
	void clear(string val = "  ");
	void print(char *title);
};

