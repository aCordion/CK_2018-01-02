#pragma once
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>

#define MAXVALUE 50

using namespace std;

struct WordPair {	//�ϳ��� ���� ���� Ŭ����
	string eng;		//���� �ܾ�
	string kor;		//�ѱ� ����
};

class CMydic
{
	WordPair words[50];	//����� �ܾ� �迭
	int nWords;		//���� ��ϵ� �ܾ��� ��

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
		cout << endl << "���� �ܾ� �Է� : ";
		getline(cin, words[nWords].eng);
		cin.clear();
		rewind(stdin);
		return words[nWords].eng;
	}
	string setKor() {
		cout << endl << "�ѱ� ���� �Է� : ";
		getline(cin, words[nWords].kor);
		cin.clear();
		rewind(stdin);
		return words[nWords].kor;
	}

	void add(string eng, string kor) 
	{	//�ϳ��� �ܾ� �߰�
		nWords++;
		if (nWords > MAXVALUE) { nWords = 1; }

			words[nWords].eng = eng;
			words[nWords].kor = kor;

	}

	void load(string filename)
	{	//���Ͽ��� �ܾ� �б�
		ifstream Mydicload("MyDictionary.txt");
		if (Mydicload.is_open() == false) { cout << endl << "���� ���� ������(MyDictionary.txt)�� ���ų� �ҷ����⿡ �����Ͽ����ϴ�" << endl;
		cout << endl << "�� ������ �����մϴ�." << endl;
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
	{	//���Ͽ� ��� �ܾ� ����
		ofstream Mydicsave("MyDictionary.txt");

		if (Mydicsave.good() == false) { cout << endl << "���� ���忡 �����Ͽ����ϴ�" << endl; return; }
		for (int i = 0; i = MAXVALUE; i++) {
			Mydicsave << nWords << "\n" << words[i].eng << "\n" << words[i].kor << "\n\n\n";
		}
		cout << endl << "���� ���� ������(MyDictionary.txt)�� ����Ǿ����ϴ�." << endl;
		Mydicsave.close();
	}

	void print() 
	{	//��� �ܾ ȭ�鿡 ���
		for (int i = 0; i < nWords; i++) {
			cout << "[" << i << " ��]" << endl <<
				"���� �ܾ� : " << words[i].eng << endl <<
				"�ѱ� ���� : " << words[i].kor << endl << endl;
		}
	}
	string getEng(int id)
	{	//id��°�� ����ܾ� ��ȯ
		return words[id].eng;
	}
	string getKor(int id)
	{	//id��°�� �ѱ� ���� ��ȯ
		return words[id].kor;
	}

	/*
	string getEng(int id) 
	{	//id��°�� ����ܾ� ��ȯ
		string Eng;
		getline(cin,Eng);
		words[id].eng = Eng;
		return words[id].eng;
	}
	string getKor(int id)
	{	//id��°�� �ѱ� ���� ��ȯ
		string Kor;
		getline(cin, Kor);
		words[id].kor = Kor;
		return words[id].kor;
	}
	*/

};