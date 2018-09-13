#include <cstdio>
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

#define NUM_MVP 5


struct PlayInfo {
	char	name[200];	// 선수의 이름
	int	nMove;		// 퍼즐 조각을 움직인 횟수
	double	tElapsed;	// 경기 소요 시간
};

class RankingBoard {
private:
	PlayInfo MVP[NUM_MVP];	// 랭킹 배열
	int nMVP = NUM_MVP;	// 랭킹 배열의 길이
	void init();

public:
//	RankingBoard() : nMVP(NUM_MVP) {};
	void load(char* filename);
	void store(char* filename);
	void print();
	int add(int nMove, double tElap);
};