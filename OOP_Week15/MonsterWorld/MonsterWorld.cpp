#include "MonsterWorld.h"
#include "VariousMonster.h"
#include "Human.h"
#include <conio.h>

int MonsterWorld::countItems() {
	int nItems = 0;
	for (int y = 0; y < yMax; y++)
		for (int x = 0; x < xMax; x++)
			if (Map(x, y) > 0) nItems++;
	return nItems;
}
void MonsterWorld::print() {
	canvas.clear();
	Point q;
	for (int y = 0; y < yMax; y++) {
		q[1] = y;
		for (int x = 0; x < xMax; x++) {
			q[0] = x;
			if (Map(x, y) > 0) canvas.draw(q, "■");
		}
	}
	for (int i = 0; i < nMon; i++)
	//	mon[i].draw(canvas);
		pMon[i]->draw(canvas);
	canvas.print("[ Monster World (몬스터들의 세상) ]");

	cerr << " 전체 이동 횟수 = " << nMove << endl;
	cerr << " 남은 아이템 수 = " << countItems() << endl;
	for (int i = 0; i < nMon; i++)
	//	mon[i].print();
		pMon[i]->print();
}
 /*
MonsterWorld::MonsterWorld(int w, int h) : world(h, w), canvas(w, h), xMax(w), yMax(h) {
	nMon = 0;
	nMove = 0;
	for (int y = 0; y < yMax; y++)
		for (int x = 0; x < xMax; x++) Map(x, y) = 1;
}
*/

MonsterWorld::MonsterWorld(int w, int h, int n) : world(h, w), canvas(w, h), xMax(w), yMax(h), nItemCnt(n) {
	nMon = 0;
	nMove = 0;
	for (int y = 0; y < yMax; y++)
	for (int x = 0; x < xMax; x++) Map(x, y) = 0;
	int x, y, cnt;

	cnt = nItemCnt;

	while (cnt) {
		x = (rand() % xMax);
		y = (rand() % yMax);

		if (Map(x, y) == 0) {
			Map(x, y) = 1;
			cnt--;
		}
	}
}

//void MonsterWorld::add(Monster& m) {
void MonsterWorld::add(Monster* m) {
//	cout << "몬스터 이름 = " << m->getName() << endl;
	//	if (nMon < MAXMONS) mon[nMon++] = m;
	if (nMon < MAXMONS) pMon[nMon++] = m;
}

void MonsterWorld::play(int maxwalk, int wait) {
	string monName = "";
		print();
		cerr << " 엔터를 누르세요...";
		getchar();
		for (int i = 0; i < maxwalk; i++) {
			for (int k = 0; k < nMon - 1; k++) {
				//			mon[k].move(map, xMax, yMax);
				pMon[k]->move(world.Data(), xMax, yMax);	//virtual 함수 사용
			}
			if (_kbhit()) {
				unsigned char ch = _getch();
				if (ch == 224) {
					ch = _getch();
					((Tuman*)(pMon[nMon - 1]))->moveHuman(world.Data(), xMax, yMax, ch);
				}
				/*else {
					((Tuman*)(pMon[nMon - 2]))->moveHuman(world.Data(), xMax, yMax, ch);
				}*/
			}
			nMove++;
			print();
			checkEnergy();
			if (isDone()) break;
			Sleep(wait);
		}
}

void MonsterWorld::checkEnergy()
{
	for (int i = 0; i < nMon; i++) {
		if (pMon[i]->getEnergy() == 0) {
			string str = pMon[i]->getName();
			cout << "\t" << str << " Monster가 굶어 죽었습니다." << endl;
			delete pMon[i];
			if (i != (nMon - 2)) {
				pMon[i] = pMon[nMon - 2];
			}
			//pMon[nMon - 3] = pMon[nMon - 2];
			pMon[nMon - 2] = pMon[nMon - 1];
			nMon--;
			system("pause");
		}
	}
}
