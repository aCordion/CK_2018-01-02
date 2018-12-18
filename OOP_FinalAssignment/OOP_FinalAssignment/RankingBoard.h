#include <iostream>
#include <fstream>
#include "FileException.h"

#define NUM_MVP 5

class PlayInfo {
	//char	name[200];
	//int	nMove;
	//double 	tElapsed;
	string name;
	int nItem;
	double itemPerMove;
	friend class RankingBoard;
public:
	PlayInfo(string na = "신인류", int ni = 0, double ipm = 0) : name(na), nItem(ni), itemPerMove(ipm) {}
};

class RankingBoard {
	PlayInfo MVP[NUM_MVP];
	int nMVP = NUM_MVP;		// VS2013:OK, VS2010:Error
	//void init() {  			// initRanking()과 동일
	//	PlayInfo noname = { "C++좋아요", 1000, 1000.0 };
	//	for (int i = 0; i<nMVP; i++)
	//		MVP[i] = noname;
	//}

public:
	//RankingBoard() : nMVP(NUM_MVP) {} 	// VS2010 이하인 경우 추가
	void load(string filename) { 		// loadRanking()과 동일
		ifstream is;
		is.open(filename);
		if (!is) {
			throw(FileException(filename, true));
		}
		else {
			for (int i = 0; i < nMVP; i++) {
				is >> MVP[i].name >> MVP[i].nItem >> MVP[i].itemPerMove;
			}
			is.close();
		}
	}
	void store(string filename) {  		// storeRanking()과 동일
		ofstream os;
		os.open(filename);
		if (!os) {
			throw(FileException(filename, false));
		}
		else {
			for (int i = 0; i < nMVP; i++) {
				os << MVP[i].name << '\t' << MVP[i].nItem << '\t' << MVP[i].itemPerMove << endl;
			}
			os.close();
		}
	}
	void print(string title = "게임 랭킹") {  			// printRanking()과 동일
		cout << endl << title << endl;
		for (int i = 0; i < nMVP; i++) {
			cout << "[ " << i + 1 << "위 ] " << MVP[i].name << "\t" << MVP[i].nItem << "\t" << MVP[i].itemPerMove << "\n";
		}
		cout << "엔터를 입력하시오......";
		getchar();
		cout << endl;
	}

	int add(int nItem, double ipm) { 	// addRanking()과 동일
		if (nItem <= MVP[nMVP - 1].nItem) {
			return 0;
		}
		int pos = nMVP - 1;
		for (; pos > 0; pos--) {
			if (nItem <= MVP[pos - 1].nItem) {
				break;
			}
			MVP[pos] = MVP[pos - 1];
		}
		MVP[pos].nItem = nItem;
		MVP[pos].itemPerMove = ipm;
		cout << "\n [ " << pos + 1 << "위 ] 이름을 입력하세요 : ";
		cin >> MVP[pos].name;
		return pos + 1;
	}
};