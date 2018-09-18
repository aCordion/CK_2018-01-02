#include "GameAddon.h"

enum EngOrKor { E = false, K = true };


CmyDic::CmyDic()
{
}


CmyDic::~CmyDic()
{
}

void CmyDic::add(string eng, string kor)
{	//하나의 단어 추가

	if (nWords >= MAXVALUE) { nWords = 0; }
	words[nWords].eng = eng;
	words[nWords].kor = kor;
	nWords++;
}

void CmyDic::load(string filename)
{
	string temp;
	{	//파일에서 단어 읽기
		ifstream Mydicload("MyDictionary.txt");
		if (Mydicload.is_open() == false) {
			cout << endl << "개인 사전 데이터(MyDictionary.txt)가 없거나 불러오기에 실패하였습니다" << endl;
			store("MyDictionary.txt");
			return;
		}
		Mydicload >> nWords;
		getline(Mydicload, temp);
		for (int i = 0; i < MAXVALUE; i++) {
			//			Mydicload >> words[i].eng >> words[i].kor;
			//			getline(Mydicload, nWords);
			getline(Mydicload, words[i].eng);
			getline(Mydicload, words[i].kor);
		}
		Mydicload.close();
	}
}

void CmyDic::store(string filename)
{
	//파일에 모든 단어 저장
	ofstream Mydicsave("MyDictionary.txt");
	Mydicsave << nWords << endl;
	if (Mydicsave.good() == false) { cout << endl << "파일 저장에 실패하였습니다" << endl; return; }

	for (int i = 0; i < MAXVALUE; i++) {
		Mydicsave << words[i].eng << endl << words[i].kor << endl;
	}
	Mydicsave.close();
	cout << endl << "개인 사전 데이터(MyDictionary.txt)가 저장되었습니다." << endl;
}

void CmyDic::print()
{	//모든 단어를 화면에 출력
	for (int i = 0; i < MAXVALUE; i++) {
		cout << "[" << i << " 번]" << endl <<
			"영어 단어 : " << words[i].eng << endl <<
			"한글 설명 : " << words[i].kor << endl << endl;
	}
}

//MAX값을 입력받아 1 ~ MAX 중의 입력받은 정수를 반환해주는 재귀호출함수
int CmyDic::getNums(const int MAX)
{
	int Num = 0;

	cout << "입력 : ";
	cin >> Num;

	if (cin.fail()) {
		cout << "틀린 값입니다. 다시 입력하여 주세요." << endl;
		cin.clear();
		rewind(stdin);
		return getNums(MAX);
	}
	if (Num > MAX || Num <= 0) {
		cout << MAX << " 이하, 1 이상의 값을 입력해 주세요." << endl;
		cin.clear();
		rewind(stdin);
		return getNums(MAX);
	}

	return Num;
}

string CmyDic::getString(bool bEorK)
{
	string tempEng, tempKor;

	while (true)
	{
		cin.clear();
		rewind(stdin);
		switch (bEorK) {
		case E:
			cout << endl << "영어 단어 입력 : ";
			getline(cin, tempEng);
			cin.clear();
			rewind(stdin);
			cout << endl << "입력하신 영어 단어는 '" << tempEng << "' 가(이) 맞습니까?" << endl;
			cout << "[1] 예" << endl << "[2] 아니오" << endl;
			switch (getNums(2)) {
			case 1: return tempEng; break;
			case 2: continue; break;
			}
		case K:
			cout << endl << "한글 설명 입력 : ";
			getline(cin, tempKor);
			cin.clear();
			rewind(stdin);
			cout << endl << "입력하신 한글 설명은 '" << tempKor << "' 가(이) 맞습니까?" << endl;
			cout << "[1] 예" << endl << "[2] 아니오" << endl;
			switch (getNums(2)) {
			case 1: return tempKor; break;
			case 2: continue; break;
			}
		}
	}
}