#pragma once
#include "Monster.h"

class Zombie : public CMonster
{
public:
	Zombie(string n = "ÇãÁ¢Á»ºñ", string i = "¡×", int x = 0, int y = 0) : CMonster(n, i, x, y) {}
	~Zombie() { cout << " Zombie"; }
};

class Vampire : public CMonster {
public:
	Vampire(string n = "¹ìÆÄÀÌ¾î", string i = "¡Ú", int x = 0, int y = 0) : CMonster(n, i, x, y) {}
	~Vampire() { cout << " Vampire"; }
	void move(int **map, int maxx, int maxy);
};

class KGhost : public CMonster {
public:
	KGhost(string n = "Ã³³à±Í½Å", string i = "¢¾", int x = 0, int y = 0) : CMonster(n, i, x, y) {}
	~KGhost() { cout << " KGhost"; }
	void move(int **map, int maxx, int maxy);
};

class Jiangshi : public CMonster {
	bool bHori;
public:
	Jiangshi(string n = "´ë·ú°­½Ã", string i = "¡ê", int x = 0, int y = 0, bool bh = true) : CMonster(n, i, x, y), bHori(bh) {}
	~Jiangshi() { cout << " Jiangshi"; }
	void move(int **map, int maxx, int maxy);
};