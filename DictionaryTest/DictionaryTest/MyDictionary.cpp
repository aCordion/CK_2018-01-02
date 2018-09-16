#include "Mydic.h"

void main() {
	
	CMydic mydic;

	cout << "개인 사전" << endl;

	mydic.resetwords();
	mydic.load("MyDictionary.txt");
	mydic.print();
	string ENG, KOR;
	ENG = mydic.setEng();
	KOR = mydic.setKor();
	mydic.add(ENG, KOR);
}