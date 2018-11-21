#pragma once
#include "Canvas.h"
#define DIM 40
#define INIT_ENERGY 100
#define ITEM_ENERGY 8

class Monster {
protected:
	string name, icon;	// 몬스터 이름과 화면 출력용 아이콘
	int x, y, nItem;		// 현재 위치와 먹은 아이템 수
	int nEnergy;

	void clip(int maxx, int maxy);  
//	void eat(int map[DIM][DIM]); 
	void eat(int** map);
public:
	Monster(string n = "더미괴물", string i = "※", int px = 0, int py = 0)
		: name(n), icon(i), x(px), y(py), nItem(0), nEnergy(INIT_ENERGY) {
		cout << "몬스터 이름 = " << n << endl;
		system("pause");
	}
	~Monster() { 
		cout << "\t" << name << icon << " 물러갑니다~~~\n";
//		system("pause");
	}

	void draw(Canvas &canvas);  
//	void move(int map[DIM][DIM], int maxx, int maxy);  
	void move(int** map, int maxx, int maxy);
	void print();  
	string getName() { return name; }
	int getEnergy() { return nEnergy; }
};