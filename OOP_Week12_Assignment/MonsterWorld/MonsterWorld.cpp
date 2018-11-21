#include <conio.h>
#include "MonsterWorld.h"
#include "VariousMonster.h"
#include "Human.h"

int MonsterWorld::countItems() {
	int nItems = 0;
	for (int y = 0; y < yMax; y++)
		for (int x = 0; x < xMax; x++)
			if (Map(x, y) > 0) nItems++;
	return nItems;
}
void MonsterWorld::print() {
	canvas.clear();
	for (int y = 0; y < yMax; y++)
		for (int x = 0; x < xMax; x++)
			if (Map(x, y) > 0) canvas.draw(x, y, "��");
	for (int i = 0; i < nMon; i++)
	//	mon[i].draw(canvas);
		pMon[i]->draw(canvas);
	canvas.print("[ Monster World (���͵��� ����) ]");

	cerr << " ��ü �̵� Ƚ�� = " << nMove << endl;
	cerr << " ���� ������ �� = " << countItems() << endl;
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
//	cout << "���� �̸� = " << m->getName() << endl;
	//	if (nMon < MAXMONS) mon[nMon++] = m;
	if (nMon < MAXMONS) pMon[nMon++] = m;
}

void MonsterWorld::play(int maxwalk, int wait) {
	string monName = "";
		print();
		cerr << " ���͸� ��������...";
		getchar();
		for (int i = 0; i < maxwalk; i++) {
			for (int k = 0; k < nMon-2; k++) {
				//			mon[k].move(map, xMax, yMax);
				pMon[k]->move(world.Data(), xMax, yMax);	//virtual �Լ� ���
				{
					/*
					((Zombie*)pMon[0])->move(world.Data(), xMax, yMax);   // ����ȯ�� �ʿ���
					((Vampire*)pMon[1])->move(world.Data(), xMax, yMax);
					((KGhost*)pMon[2])->move(world.Data(), xMax, yMax);
					((Jiangshi*)pMon[3])->move(world.Data(), xMax, yMax);
					((Jiangshi*)pMon[4])->move(world.Data(), xMax, yMax);
					*/
					/*
		monName = pMon[k]->getName();
		if (monName == "����������") {
			((Zombie*)pMon[k])->move(world.Data(), xMax, yMax);
		}
		else if(monName == "�����̾�¯") {
			((Vampire*)pMon[k])->move(world.Data(), xMax, yMax);
		}
		else if (monName == "��¼�ٱͽ�") {
			((KGhost*)pMon[k])->move(world.Data(), xMax, yMax);
		}
		else if (monName == "�������ͽ�") {
			((Smombi*)pMon[k])->move(world.Data(), xMax, yMax);
		}
		else if (monName == "���۸�����") {
			((SuperSmombi*)pMon[k])->move(world.Data(), xMax, yMax);
		}
		else if (monName == "���Ծ��" || monName == "���Ծ��") {
			((Jiangshi*)pMon[k])->move(world.Data(), xMax, yMax);
		}
		else {
			cout << "�������� �ʴ� �ͽ�......" << endl;
			system("pause");
		}
		*/
				}
			}
			if (_kbhit()) {
				unsigned char ch = _getche();
				if (ch == 224) {
					ch = _getche();
					((Tuman*)(pMon[nMon - 1]))->move(world.Data(), xMax, yMax, ch);
				}
				else {((Tuman*)(pMon[nMon - 2]))->move(world.Data(), xMax, yMax, ch); }
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
			cout << "\t" << str << " Monster�� ���� �׾����ϴ�." << endl;
			delete pMon[i];
			if (i != (nMon - 1)) {
				pMon[i] = pMon[nMon - 1];
			}
			nMon--;
			system("pause");
		}
	}
}
