#include "MonsterWorld.h"
#include <time.h>

void main() {
	srand((unsigned int)time(NULL));
	int w = 16, h = 8;

	CMonsterWorld game(w, h);
	{
		//	CMonster m("����", "��", rand() % w, rand() % h);
		//	game.add(m);
			/*
			game.add(CMonster("����", "��", rand() % w, rand() % h));
			game.add(CMonster("������", "��", rand() % w, rand() % h));
			game.add(CMonster("���״�", "��", rand() % w, rand() % h));
			game.add(CMonster("��Ʈ", "��", rand() % w, rand() % h));
			*/
	}
	{
		game.add(new CMonster("����", "��", rand() % w, rand() % h));
		game.add(new CMonster("������", "��", rand() % w, rand() % h));
		game.add(new CMonster("���״�", "��", rand() % w, rand() % h));
		game.add(new CMonster("��Ʈ", "��", rand() % w, rand() % h));
	}
	game.play(500, 10);
	printf("------���� ����-------------------\n");
}