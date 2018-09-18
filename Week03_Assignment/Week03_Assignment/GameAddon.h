#pragma once
#include <stdio.h>
#include <conio.h>
#include <iostream>
#include <fstream>
#include <string>

#define MAXVALUE 7

using namespace std;

struct WordPair {	//�ϳ��� ���� ���� Ŭ����
	string eng;		//���� �ܾ�
	string kor;		//�ѱ� ����
};

class CmyDic
{
	WordPair words[MAXVALUE];	//����� �ܾ� �迭
	int nWords;		//���� ��ϵ� �ܾ��� ��
public:
	CmyDic();
	~CmyDic();
	void clswait() { cout << endl << "�ƹ� Ű�� ���� ����"; getch(); cin.clear(); rewind(stdin); system("cls"); }
	void resetwords() { memset(&words, 0x00, sizeof(words)); nWords = 0; }
	void add(string eng, string kor);
	void load(string filename);
	void store(string filename);
	void print();
	string getEng(int id) { return words[id].eng; }
	string getKor(int id) { return words[id].kor; }
	int getnWords() { return nWords; }
	int getNums(const int MAX);
	//�̸��� �Է¹޴� �Լ�
	string getString(bool bEoK);
};

