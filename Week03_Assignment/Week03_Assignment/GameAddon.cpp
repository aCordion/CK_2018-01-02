#include "GameAddon.h"

enum EngOrKor { E = false, K = true };


CmyDic::CmyDic()
{
}


CmyDic::~CmyDic()
{
}

void CmyDic::add(string eng, string kor)
{	//�ϳ��� �ܾ� �߰�

	if (nWords >= MAXVALUE) { nWords = 0; }
	words[nWords].eng = eng;
	words[nWords].kor = kor;
	nWords++;
}

void CmyDic::load(string filename)
{
	string temp;
	{	//���Ͽ��� �ܾ� �б�
		ifstream Mydicload("MyDictionary.txt");
		if (Mydicload.is_open() == false) {
			cout << endl << "���� ���� ������(MyDictionary.txt)�� ���ų� �ҷ����⿡ �����Ͽ����ϴ�" << endl;
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
	//���Ͽ� ��� �ܾ� ����
	ofstream Mydicsave("MyDictionary.txt");
	Mydicsave << nWords << endl;
	if (Mydicsave.good() == false) { cout << endl << "���� ���忡 �����Ͽ����ϴ�" << endl; return; }

	for (int i = 0; i < MAXVALUE; i++) {
		Mydicsave << words[i].eng << endl << words[i].kor << endl;
	}
	Mydicsave.close();
	cout << endl << "���� ���� ������(MyDictionary.txt)�� ����Ǿ����ϴ�." << endl;
}

void CmyDic::print()
{	//��� �ܾ ȭ�鿡 ���
	for (int i = 0; i < MAXVALUE; i++) {
		cout << "[" << i << " ��]" << endl <<
			"���� �ܾ� : " << words[i].eng << endl <<
			"�ѱ� ���� : " << words[i].kor << endl << endl;
	}
}

//MAX���� �Է¹޾� 1 ~ MAX ���� �Է¹��� ������ ��ȯ���ִ� ���ȣ���Լ�
int CmyDic::getNums(const int MAX)
{
	int Num = 0;

	cout << "�Է� : ";
	cin >> Num;

	if (cin.fail()) {
		cout << "Ʋ�� ���Դϴ�. �ٽ� �Է��Ͽ� �ּ���." << endl;
		cin.clear();
		rewind(stdin);
		return getNums(MAX);
	}
	if (Num > MAX || Num <= 0) {
		cout << MAX << " ����, 1 �̻��� ���� �Է��� �ּ���." << endl;
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
			cout << endl << "���� �ܾ� �Է� : ";
			getline(cin, tempEng);
			cin.clear();
			rewind(stdin);
			cout << endl << "�Է��Ͻ� ���� �ܾ�� '" << tempEng << "' ��(��) �½��ϱ�?" << endl;
			cout << "[1] ��" << endl << "[2] �ƴϿ�" << endl;
			switch (getNums(2)) {
			case 1: return tempEng; break;
			case 2: continue; break;
			}
		case K:
			cout << endl << "�ѱ� ���� �Է� : ";
			getline(cin, tempKor);
			cin.clear();
			rewind(stdin);
			cout << endl << "�Է��Ͻ� �ѱ� ������ '" << tempKor << "' ��(��) �½��ϱ�?" << endl;
			cout << "[1] ��" << endl << "[2] �ƴϿ�" << endl;
			switch (getNums(2)) {
			case 1: return tempKor; break;
			case 2: continue; break;
			}
		}
	}
}