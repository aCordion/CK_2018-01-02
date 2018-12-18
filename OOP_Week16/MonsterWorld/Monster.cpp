#include "Monster.h"

void Monster::clip(int maxx, int maxy) {
	//if (x < 0) x = 0;
	//if (x >= maxx) x = maxx - 1;
	//if (y < 0) y = 0;
	//if (y >= maxy) y = maxy - 1;
	p(maxx, maxy);
}

//void Monster::eat(int** map) {
//	if (map[p.y][p.x] == 1) {
//		map[p.y][p.x] = 0;
//		nItem++;
//		nEnergy += ITEM_ENERGY;
//	}
//	dist += (double)(p - q);
//	total += (double)(p - q);
//	q = p;
//	if (dist > 20) {
//		dist = 0;
//		nSleep = 10;
//	}
//	//else {
//	//	if(nEnergy > 0) nEnergy--;
//	//}
//}

void Monster::eat(Vector<Vector<int>>& map)
{
	if (map[p.y][p.x] == 1) {
		map[p.y][p.x] = 0;
		nItem++;
		nEnergy += ITEM_ENERGY;
	}
	dist += (double)(p - q);
	total += (double)(p - q);
	q = p;
	if (dist > 20) {
		dist = 0;
		nSleep = 10;
	}
}

bool Monster::isSleep()
{
	if (nSleep > 0) {
		nSleep--;
		return true;
	}
	else return false;
}
 
void Monster::draw(Canvas &canvas) { canvas.draw(p, icon); }
//void Monster::move(int** map, int maxx, int maxy) {
//	if (!isSleep()) {
//		int num = rand() % 9 + 1;
//		p += Point(num % 3 - 1, num / 3 - 1);
//		clip(maxx, maxy);
//		eat(map);
//		}
//		
//}

void Monster::move(Vector<Vector<int>>& map, int maxx, int maxy) {
	if (!isSleep()) {
		int num = rand() % 9 + 1;
		p += Point(num % 3 - 1, num / 3 - 1);
		clip(maxx, maxy);
		eat(map);
	}
}

void Monster::print() { 
	cout << "\t" << name << icon << ":" << nItem << " ¿¡³ÊÁö : " << nEnergy << " SleepCnt:" << nSleep << endl; }