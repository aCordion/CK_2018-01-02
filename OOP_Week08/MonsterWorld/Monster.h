#pragma once
#include "Canvas.h"

#define DIM 40
#define INIT_ENERGY 100
#define ITEM_ENERGY 8


class CMonster
{
	string name, icon;
	int x, y, nItem;
	int nEnergy;

	void clip(int maxx, int maxy);
//	void eat(int map[DIM][DIM]);
	void eat(int** map);

public:
	CMonster(string n = "������", string i = "��", int px = 0, int py = 0) : name(n), icon(i), x(px), y(py), nItem(0), nEnergy(INIT_ENERGY) {}
	~CMonster(){ cout << "\t" << name << icon << "�������ϴ�~~~\n"; }
	void draw(CCanvas &canvas) { canvas.draw(x, y, icon); }
//	void move(int map[DIM][DIM], int maxx, int maxy);
	void move(int** map, int maxx, int maxy);
	void print() { cout << "\t" << name << icon << ":" << nItem << " ������ : " << nEnergy << endl; }
};

