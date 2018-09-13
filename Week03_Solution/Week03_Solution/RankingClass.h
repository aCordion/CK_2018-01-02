#include <cstdio>
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

#define NUM_MVP 5


struct PlayInfo {
	char	name[200];	// ������ �̸�
	int	nMove;		// ���� ������ ������ Ƚ��
	double	tElapsed;	// ��� �ҿ� �ð�
};

class RankingBoard {
private:
	PlayInfo MVP[NUM_MVP];	// ��ŷ �迭
	int nMVP = NUM_MVP;	// ��ŷ �迭�� ����
	void init();

public:
//	RankingBoard() : nMVP(NUM_MVP) {};
	void load(char* filename);
	void store(char* filename);
	void print();
	int add(int nMove, double tElap);
};