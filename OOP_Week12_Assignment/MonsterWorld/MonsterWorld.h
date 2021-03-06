#pragma once
#include "Canvas.h"
#include "Monster.h"
#include "Matrix.h"
#include <windows.h>
#define DIM  40
#define MAXMONS 8

class MonsterWorld {
//	int map[DIM][DIM];      // MonsterWorld 객체 생성시 map[40][40] 메모리 할당
	Matrix world;
	int xMax, yMax, nMon, nMove, nItemCnt;
//	Monster mon[MAXMONS];    // MonsterWorld 객체 생성시 Monster객체 생성
	Monster* pMon[MAXMONS];
	Canvas	canvas;          

	int& Map(int x, int y) { return world.elem(x, y); }
	bool isDone(){
		if (countItems() == 0) {
			cout << " 아이템 = 0 --------> 게임 종료....\n\n";
			return true;
		}
		if (nMon == 0) {
			cout << " 몬스터 = 0 --------> 게임 종료....\n\n";
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
		for (int i = 0; i < nMon; i++) {
			delete pMon[i];
		}
	}
	void add(Monster* m);  
	void play(int maxwalk, int wait);  
	void checkEnergy();
};