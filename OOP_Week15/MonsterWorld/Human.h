#pragma once
#include "Monster.h"
#include <conio.h>

#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80
#define KEY_W 87
#define KEY_w 119
#define KEY_A 65
#define KEY_a 97
#define KEY_S 83
#define KEY_s 115
#define KEY_D 68
#define KEY_d 100

class Human : public Monster {
public:
	Human(string n = "미래인류", string i = "♣", int x = 0, int y = 0) : Monster(n, i, x, y) {}
	~Human() { cout << " [Human]"; }

	void move(int** map, int maxx, int maxy);
	int getDirKey() { return _getwche() == 224 ? _getwche() : 0; }
};

class Tuman : public Human {
	//bool isLeft;
public:
	Tuman(string n = "미래종파", string i = "파", int x = 0, int y = 0) : Human(n, i, x, y) {}
	~Tuman() { cout << " Tuman"; }
	void move(int** map, int maxx, int maxy, char ch) { moveHuman(map, maxx, maxy, ch); }
	void moveHuman(int** map, int maxx, int maxy, char ch);
};