#include "MonsterWorld.h"
#include "VariousMonsters.h"
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
		/*
		game.add(new CMonster("몬스터", "※", rand() % w, rand() % h));
		game.add(new CMonster("도깨비", "§", rand() % w, rand() % h));
		game.add(new CMonster("별그대", "★", rand() % w, rand() % h));
		game.add(new CMonster("고스트", "♥", rand() % w, rand() % h));
		*/
	}
	{
		game.add(new Zombie("허접한좀비", "§", rand() % w, rand() % h));
		game.add(new Vampire("뱀파이어짱", "★", rand() % w, rand() % h));
		game.add(new KGhost("어쩌다귀신", "♥", rand() % w, rand() % h));
		game.add(new Jiangshi("못먹어도고", "↔", rand() % w, rand() % h, true));
		game.add(new Jiangshi("못먹어세로", "↕", rand() % w, rand() % h, false));
	}
	game.play(500, 500);
	printf("------게임 종료-------------------\n");
}