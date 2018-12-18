#pragma once
#include "Monster.h"

class Zombie : public Monster {
public:
	Zombie(string n = "허접좀비", string i = "§", int x = 0, int y = 0)
		: Monster(n, i, x, y) {}
	~Zombie() { cout << " Zombie"; }
};

class Vampire : public Monster {
public:
	Vampire(string n = "뱀파이어", string i = "★", int x = 0, int y = 0)
		: Monster(n, i, x, y) {}
	~Vampire() { cout << " Vampire"; }

	void move(Vector<Vector<int>>& map, int maxx, int maxy);
};

class KGhost : public Monster {
public:
	KGhost(string n = "처녀귀신", string i = "♥", int x = 0, int y = 0)
		: Monster(n, i, x, y) {}
	~KGhost() { cout << " KGhost"; }

	void move(Vector<Vector<int>>& map, int maxx, int maxy);
};

class Jiangshi : public Monster {
	bool	bHori;
public:
	Jiangshi(string n = "대륙강시", string i = "↔", int x = 0, int y = 0, bool bH = true)
		: Monster(n, i, x, y), bHori(bH) {}
	~Jiangshi() { cout << " Jiangshi"; }

	void move(Vector<Vector<int>>& map, int maxx, int maxy);
};

class Smombi : public Monster {
public:
	Smombi(string n = "길막지마", string i = "◑", int x = 0, int y = 0)
		: Monster(n, i, x, y) {}
	~Smombi() { cout << " Smombi"; }

	void move(Vector<Vector<int>>& map, int maxx, int maxy);
};

class SuperSmombi : public Smombi {
public:
	SuperSmombi(string n = "슈퍼길막지마", string i = "♨", int x = 0, int y = 0)
		: Smombi(n, i, x, y) {}
	~SuperSmombi() { cout << " SuperSmombi"; }

	void move(Vector<Vector<int>>& map, int maxx, int maxy);
};