#pragma once
#include "Canvas.h"
#include "Monster.h"
#include "Matrix.h"
#include <windows.h>
#include "MyVector.h"
//#define DIM  40
//#define MAXMONS 8

class MonsterWorld {
//	int map[DIM][DIM];      // MonsterWorld ��ü ������ map[40][40] �޸� �Ҵ�
	//Matrix world;
	Vector<Vector<int>> world;

	int xMax, yMax,/* nMon,*/ nMove, nItemCnt;
//	Monster mon[MAXMONS];    // MonsterWorld ��ü ������ Monster��ü ����
	//Monster* pMon[MAXMONS];
	Vector<Monster*> pMon;
	Canvas	canvas;          

	int& Map(int x, int y) { return world[y][x]; }
	bool isDone(){
		if (countItems() == 0) {
			cout << " ������ = 0 --------> ���� ����....\n\n";
			return true;
		}
		if (pMon.size() == 0) {
			cout << " ���� = 0 --------> ���� ����....\n\n";
			return true;
		}
		return false;
	}
	int countItems();  
	void print(); 
public:
//	MonsterWorld(int w, int h);
	MonsterWorld(int w, int h, int n);
	~MonsterWorld() { 
		for (int i = 0; i < pMon.size(); i++) {
			delete pMon[i];
		}
	}
	void add(Monster* m);  
	void play(int maxwalk, int wait);  
	void checkEnergy();
};