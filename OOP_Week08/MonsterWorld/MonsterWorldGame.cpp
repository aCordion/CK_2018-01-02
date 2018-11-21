#include "MonsterWorld.h"
#include <time.h>

void main() {
	srand((unsigned int)time(NULL));
	int w = 16, h = 8;

	CMonsterWorld game(w, h);
	{
		//	CMonster m("몬스터", "※", rand() % w, rand() % h);
		//	game.add(m);
			/*
			game.add(CMonster("몬스터", "※", rand() % w, rand() % h));
			game.add(CMonster("도깨비", "§", rand() % w, rand() % h));
			game.add(CMonster("별그대", "★", rand() % w, rand() % h));
			game.add(CMonster("고스트", "♥", rand() % w, rand() % h));
			*/
	}
	{
		game.add(new CMonster("몬스터", "※", rand() % w, rand() % h));
		game.add(new CMonster("도깨비", "§", rand() % w, rand() % h));
		game.add(new CMonster("별그대", "★", rand() % w, rand() % h));
		game.add(new CMonster("고스트", "♥", rand() % w, rand() % h));
	}
	game.play(500, 10);
	printf("------게임 종료-------------------\n");
}