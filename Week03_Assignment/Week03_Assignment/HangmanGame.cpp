#include "Hangman.h"
#include "GameAddon.h"
#include <Windows.h>
#include <ctime>

enum EngOrKor { E = false, K = true };

void main() {

	srand((unsigned)time(NULL));

	Hangman game;
	CmyDic mydic;
	mydic.resetwords();
	string tempwords, tempE, tempK;
	int rvalue;

	mydic.load("MyDictionary.txt");
	rvalue = rand() % mydic.getnWords();

	while (true) {
		cout << "[��� ����]" << endl <<
			"[1] ���� ����" << endl << 
			"[2] ���� ����" << endl <<
			"[3] ���� ����" << endl <<
			"[4] ���� ���� ǥ��" << endl <<
			"[5] ���� ���� �ʱ�ȭ" << endl <<
			"[6] ����" << endl;

		switch (mydic.getNums(6))
		{
		case 1: 
			game.play(mydic.getEng(rvalue));
			cout << endl << "������ [" << mydic.getEng(rvalue) << "] �����ϴ�" << endl << "�ܾ��� �ǹ̴� [" << mydic.getKor(rvalue) << "] �Դϴ�." << endl; break;
		case 2:
			tempE = mydic.getString(E);
			tempK = mydic.getString(K);
			mydic.add(tempE, tempK);
			//			mydic.add(mydic.getString(E), mydic.getString(K));
			break;
		case 3: mydic.store("MyDictionary.txt"); break;
		case 4: mydic.print(); break;
		case 5: mydic.resetwords(); break;
		default:
			exit(0);
			break;
		}
		mydic.clswait();
	}

}