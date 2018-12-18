#pragma once
#include "Monster.h"

class Zombie : public Monster {
public:
	Zombie(string n = "��������", string i = "��", int x = 0, int y = 0)
		: Monster(n, i, x, y) {}
	~Zombie() { cout << " Zombie"; }
};

class Vampire : public Monster {
public:
	Vampire(string n = "�����̾�", string i = "��", int x = 0, int y = 0)
		: Monster(n, i, x, y) {}
	~Vampire() { cout << " Vampire"; }

	void move(Vector<Vector<int>>& map, int maxx, int maxy);
};

class KGhost : public Monster {
public:
	KGhost(string n = "ó��ͽ�", string i = "��", int x = 0, int y = 0)
		: Monster(n, i, x, y) {}
	~KGhost() { cout << " KGhost"; }

	void move(Vector<Vector<int>>& map, int maxx, int maxy);
};

class Jiangshi : public Monster {
	bool	bHori;
public:
	Jiangshi(string n = "�������", string i = "��", int x = 0, int y = 0, bool bH = true)
		: Monster(n, i, x, y), bHori(bH) {}
	~Jiangshi() { cout << " Jiangshi"; }

	void move(Vector<Vector<int>>& map, int maxx, int maxy);
};

class Smombi : public Monster {
public:
	Smombi(string n = "�渷����", string i = "��", int x = 0, int y = 0)
		: Monster(n, i, x, y) {}
	~Smombi() { cout << " Smombi"; }

	void move(Vector<Vector<int>>& map, int maxx, int maxy);
};

class SuperSmombi : public Smombi {
public:
	SuperSmombi(string n = "���۱渷����", string i = "��", int x = 0, int y = 0)
		: Smombi(n, i, x, y) {}
	~SuperSmombi() { cout << " SuperSmombi"; }

	void move(Vector<Vector<int>>& map, int maxx, int maxy);
};