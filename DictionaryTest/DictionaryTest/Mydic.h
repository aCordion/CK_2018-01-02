#pragma once
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>

#define MAXVALUE 50

using namespace std;

struct WordPair {	//하나의 쌍을 위한 클래스
	string eng;		//영어 단어
	string kor;		//한글 설명
};

class CMydic
{
	WordPair words[50];	//저장된 단어 배열
	int nWords;		//현재 등록된 단어의 수

public:

	CMydic()
	{
	}

	~CMydic()
	{
	}

	CMydic(int nWords) : nWords(0) {}

	void resetwords() { memset(&words, 0, sizeof(struct WordPair)); }

	string setEng() {
		cout << endl << "영어 단어 입력 : ";
		getline(cin, words[nWords].eng);
		cin.clear();
		rewind(stdin);
		return words[nWords].eng;
	}
	string setKor() {
		cout << endl << "한글 설명 입력 : ";
		getline(cin, words[nWords].kor);
		cin.clear();
		rewind(stdin);
		return words[nWords].kor;
	}

	void add(string eng, string kor) 
	{	//하나의 단어 추가
		nWords++;
		if (nWords > MAXVALUE) { nWords = 1; }

			words[nWords].eng = eng;
			words[nWords].kor = kor;

	}

	void load(string filename)
	{	//파일에서 단어 읽기
		ifstream Mydicload("MyDictionary.txt");
		if (Mydicload.is_open() == false) { cout << endl << "개인 사전 데이터(MyDictionary.txt)가 없거나 불러오기에 실패하였습니다" << endl;
		cout << endl << "새 파일을 생성합니다." << endl;
		store("MyDictionary.txt");
		return;
		}
		Mydicload >> nWords;
		for (int i = 0; i < nWords; i++) {
			Mydicload >> words[i].eng >> words[i].kor;
		}
		Mydicload.close();
	}

	void store(string filename)
	{	//파일에 모든 단어 저장
		ofstream Mydicsave("MyDictionary.txt");

		if (Mydicsave.good() == false) { cout << endl << "파일 저장에 실패하였습니다" << endl; return; }
		for (int i = 0; i = MAXVALUE; i++) {
			Mydicsave << nWords << "\n" << words[i].eng << "\n" << words[i].kor << "\n\n\n";
		}
		cout << endl << "개인 사전 데이터(MyDictionary.txt)가 저장되었습니다." << endl;
		Mydicsave.close();
	}

	void print() 
	{	//모든 단어를 화면에 출력
		for (int i = 0; i < nWords; i++) {
			cout << "[" << i << " 번]" << endl <<
				"영어 단어 : " << words[i].eng << endl <<
				"한글 설명 : " << words[i].kor << endl << endl;
		}
	}
	string getEng(int id)
	{	//id번째의 영어단어 반환
		return words[id].eng;
	}
	string getKor(int id)
	{	//id번째의 한글 설명 반환
		return words[id].kor;
	}

	/*
	string getEng(int id) 
	{	//id번째의 영어단어 반환
		string Eng;
		getline(cin,Eng);
		words[id].eng = Eng;
		return words[id].eng;
	}
	string getKor(int id)
	{	//id번째의 한글 설명 반환
		string Kor;
		getline(cin, Kor);
		words[id].kor = Kor;
		return words[id].kor;
	}
	*/

};