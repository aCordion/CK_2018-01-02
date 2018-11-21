#pragma once
#include "Canvas.h"

#define DIM 40

class CMonster
{
	string name, icon;
	int x, y, nItem;

	void clip(int maxx, int maxy);
	void eat(int map[DIM][DIM]);

public:
	CMonster(string n = "³ª±«¹°", string i = "¡Ø", int px = 0, int py = 0) : name(n), icon(i), x(px), y(py), nItem(0) {}
	~CMonster(){ cout << "\t" << name << icon << "¹°·¯°©´Ï´Ù~~~\n"; }
	void draw(CCanvas &canvas) { canvas.draw(x, y, icon); }
	void move(int map[DIM][DIM], int maxx, int maxy);
	void print() { cout << "\t" << name << icon << ":" << nItem << endl; }
};

