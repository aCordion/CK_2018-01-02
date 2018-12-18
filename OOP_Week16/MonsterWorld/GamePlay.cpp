#include "MonsterWorld.h"
#include "VariousMonster.h"
#include "Human.h"
#include <time.h>
#include "ObjTest.h"
#include "RankingBoard.h"

void main()
{
	RankingBoard rank;
	try {
		rank.load("MonsterWorld.rnk");
	}
	catch (FileException e) {
		char str[80];
		string password, correct = "123456";
		cout << "관리자 비밀번호를 입력하시오 = ";
		for (int i = 0; ; i++) {
			str[i] = getch();
			putchar('*');

			if (str[i] == '\r') {
				str[i] = '\0';
				password = str;
				cout << endl;
				break;
			}
		}
		if (password != correct) {
			cout << "비밀번호가 일치하지 않습니다... 게임 종료\n\n";
			exit(0);
		}
	}

	rank.print("[ 게임 랭킹 : 시작 ]");

	srand((unsigned int)time(NULL));
	int w = 16, h = 8, n;
	cout << "맵 크기를 입력하시오(width, height) = ";
	cin >> w >> h;
	getchar();

	n = (w*h) / 2;
//	cout << "MAIN STARTING........\n";
	MonsterWorld game(w, h, n);
//	cout << "몬스터 추가..........\n";
	/*
	Monster m("몬스터", "◈", rand() % w, rand() % h);
	game.add(m);
	game.add(Monster("도깨비", "◎", rand() % w, rand() % h));
	game.add(Monster("별그대", "★", rand() % w, rand() % h));
	game.add(Monster("고스트", "♥", rand() % w, rand() % h));
	

	game.add(new Monster("몬스터", "◈", rand() % w, rand() % h));
	game.add(new Monster("도깨비", "◎", rand() % w, rand() % h));
	game.add(new Monster("별그대", "★", rand() % w, rand() % h));
	game.add(new Monster("고스트", "♥", rand() % w, rand() % h));
	*/
	game.add(new Zombie("허접한좀비", "◎", rand() % w, rand() % h));
	game.add(new Vampire("뱀파이어짱", "★", rand() % w, rand() % h));
	game.add(new KGhost("어쩌다귀신", "♥", rand() % w, rand() % h));
	game.add(new Smombi("막지마귀신", "※", rand() % w, rand() % h));
	game.add(new SuperSmombi("슈퍼막지마", "♨", rand() % w, rand() % h));
	if ((rand() % 2) == 0) {
		game.add(new Jiangshi("못먹어도고", "↔", rand() % w, rand() % h, true));
	}
	else {
		game.add(new Jiangshi("못먹어세로", "↕", rand() % w, rand() % h, false));
	}
	//game.add(new Human("슈퍼인간", "♣", rand() % w, rand() % h));
	//game.add(new Tuman("인간좌키", "좌", rand() % w, rand() % h));
	Tuman* human;
	game.add(human = new Tuman("미래인간임", "♣", rand() % w, rand() % h));

	game.play(500, 100);

	rank.add(human->getItem(), human->getItem() / human->getTotal());
	rank.print("[ 게임 랭킹 : 종료 ]");
	rank.store("MonsterWorld.rnk");

	printf("------게임 종료-------------------\n");
	
	 
}