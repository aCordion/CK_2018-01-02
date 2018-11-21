#pragma once
#include "Monster.h"

class Zombie : public CMonster
{
public:
	Zombie(string n = "��������", string i = "��", int x = 0, int y = 0) : CMonster(n, i, x, y) {}
	~Zombie() { cout << " Zombie"; }
};

class Vampire : public CMonster {
public:
	Vampire(string n = "�����̾�", string i = "��", int x = 0, int y = 0) : CMonster(n, i, x, y) {}
	~Vampire() { cout << " Vampire"; }
	void move(int **map, int maxx, int maxy);
};

class KGhost : public CMonster {
public:
	KGhost(string n = "ó��ͽ�", string i = "��", int x = 0, int y = 0) : CMonster(n, i, x, y) {}
	~KGhost() { cout << " KGhost"; }
	void move(int **map, int maxx, int maxy);
};

class Jiangshi : public CMonster {
	bool bHori;
public:
	Jiangshi(string n = "�������", string i = "��", int x = 0, int y = 0, bool bh = true) : CMonster(n, i, x, y), bHori(bh) {}
	~Jiangshi() { cout << " Jiangshi"; }
	void move(int **map, int maxx, int maxy);
};