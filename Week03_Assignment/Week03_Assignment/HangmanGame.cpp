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
		cout << "[행맨 게임]" << endl <<
			"[1] 게임 시작" << endl << 
			"[2] 사전 쓰기" << endl <<
			"[3] 사전 저장" << endl <<
			"[4] 사전 내용 표시" << endl <<
			"[5] 사전 내용 초기화" << endl <<
			"[6] 종료" << endl;

		switch (mydic.getNums(6))
		{
		case 1: 
			game.play(mydic.getEng(rvalue));
			cout << endl << "정답은 [" << mydic.getEng(rvalue) << "] 였습니다" << endl << "단어의 의미는 [" << mydic.getKor(rvalue) << "] 입니다." << endl; break;
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