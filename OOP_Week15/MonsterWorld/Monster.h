#pragma once
#include "Canvas.h"
#include "Point.h"

#define DIM 40
#define INIT_ENERGY 100
#define ITEM_ENERGY 8

class Monster {
protected:
	string name, icon;	// ���� �̸��� ȭ�� ��¿� ������
	int nItem;		// ���� ��ġ�� ���� ������ ��
	int nEnergy;

	Point q, p;
	int nSleep;
	double dist;
	double total;

	void clip(int maxx, int maxy);  
//	void eat(int map[DIM][DIM]); 
	void eat(int** map);
	bool isSleep();

public:
	Monster(string n = "���̱���", string i = "��", int x = 0, int y = 0)
		: name(n), icon(i), p(x, y), q(x, y), nSleep(0), dist(0.0), total(0.0), nItem(0), nEnergy(INIT_ENERGY) {
		cout << "���� �̸� = " << n << endl;
		system("pause");
	}
	virtual ~Monster() { 
		cout << "\t" << icon << nItem << "�Ÿ�:" << total << endl;
//		system("pause");
	}

	void draw(Canvas &canvas);  
//	void move(int map[DIM][DIM], int maxx, int maxy);  
	//void move(int** map, int maxx, int maxy);
	virtual void move(int** map, int maxx, int maxy);
	void print();  
	string getName() { return name; }
	int getEnergy() { return nEnergy; }
};