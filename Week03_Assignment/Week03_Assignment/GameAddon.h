#pragma once
#include <stdio.h>
#include <conio.h>
#include <iostream>
#include <fstream>
#include <string>

#define MAXVALUE 7

using namespace std;

struct WordPair {	//하나의 쌍을 위한 클래스
	string eng;		//영어 단어
	string kor;		//한글 설명
};

class CmyDic
{
	WordPair words[MAXVALUE];	//저장된 단어 배열
	int nWords;		//현재 등록된 단어의 수
public:
	CmyDic();
	~CmyDic();
	void clswait() { cout << endl << "아무 키나 눌러 진행"; getch(); cin.clear(); rewind(stdin); system("cls"); }
	void resetwords() { memset(&words, 0x00, sizeof(words)); nWords = 0; }
	void add(string eng, string kor);
	void load(string filename);
	void store(string filename);
	void print();
	string getEng(int id) { return words[id].eng; }
	string getKor(int id) { return words[id].kor; }
	int getnWords() { return nWords; }
	int getNums(const int MAX);
	//이름을 입력받는 함수
	string getString(bool bEoK);
};

