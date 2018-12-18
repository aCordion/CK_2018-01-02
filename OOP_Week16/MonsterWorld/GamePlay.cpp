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
		cout << "������ ��й�ȣ�� �Է��Ͻÿ� = ";
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
			cout << "��й�ȣ�� ��ġ���� �ʽ��ϴ�... ���� ����\n\n";
			exit(0);
		}
	}

	rank.print("[ ���� ��ŷ : ���� ]");

	srand((unsigned int)time(NULL));
	int w = 16, h = 8, n;
	cout << "�� ũ�⸦ �Է��Ͻÿ�(width, height) = ";
	cin >> w >> h;
	getchar();

	n = (w*h) / 2;
//	cout << "MAIN STARTING........\n";
	MonsterWorld game(w, h, n);
//	cout << "���� �߰�..........\n";
	/*
	Monster m("����", "��", rand() % w, rand() % h);
	game.add(m);
	game.add(Monster("������", "��", rand() % w, rand() % h));
	game.add(Monster("���״�", "��", rand() % w, rand() % h));
	game.add(Monster("��Ʈ", "��", rand() % w, rand() % h));
	

	game.add(new Monster("����", "��", rand() % w, rand() % h));
	game.add(new Monster("������", "��", rand() % w, rand() % h));
	game.add(new Monster("���״�", "��", rand() % w, rand() % h));
	game.add(new Monster("��Ʈ", "��", rand() % w, rand() % h));
	*/
	game.add(new Zombie("����������", "��", rand() % w, rand() % h));
	game.add(new Vampire("�����̾�¯", "��", rand() % w, rand() % h));
	game.add(new KGhost("��¼�ٱͽ�", "��", rand() % w, rand() % h));
	game.add(new Smombi("�������ͽ�", "��", rand() % w, rand() % h));
	game.add(new SuperSmombi("���۸�����", "��", rand() % w, rand() % h));
	if ((rand() % 2) == 0) {
		game.add(new Jiangshi("���Ծ��", "��", rand() % w, rand() % h, true));
	}
	else {
		game.add(new Jiangshi("���Ծ��", "��", rand() % w, rand() % h, false));
	}
	//game.add(new Human("�����ΰ�", "��", rand() % w, rand() % h));
	//game.add(new Tuman("�ΰ���Ű", "��", rand() % w, rand() % h));
	Tuman* human;
	game.add(human = new Tuman("�̷��ΰ���", "��", rand() % w, rand() % h));

	game.play(500, 100);

	rank.add(human->getItem(), human->getItem() / human->getTotal());
	rank.print("[ ���� ��ŷ : ���� ]");
	rank.store("MonsterWorld.rnk");

	printf("------���� ����-------------------\n");
	
	 
}