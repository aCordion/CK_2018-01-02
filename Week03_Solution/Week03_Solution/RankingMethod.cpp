#include "RankingClass.h"

void RankingBoard::init() {
	PlayInfo noname = { "C++좋아요", 1000, 1000.0 };
	for (int i = 0; i<nMVP; i++)
		MVP[i] = noname;
}
void RankingBoard::load(char* fname) {
//	FILE* fp = fopen(fname, "r");
	ifstream fin;
	fin.open(fname);
//	if (fp == NULL)
	if (fin.good() == false)
		init();
	else {
		for (int i = 0; i < nMVP; i++)
			//			fscanf(fp, "%d%s%lf", &MVP[i].nMove,
			//				MVP[i].name, &MVP[i].tElapsed);
			fin >> MVP[i].nMove >> MVP[i].name >> MVP[i].tElapsed;
//		fclose(fp);
		fin.close();
	}
}
void RankingBoard::store(char* fname) {
//	FILE* fp = fopen(fname, "w");
	ofstream fout;
	fout.open(fname);

//	if (fp == NULL) return;
	if (fout.good() == false) return;

	for (int i = 0; i < nMVP; i++)
		//		fprintf(fp, "  %4d  %-16s %-5.1f\n", MVP[i].nMove,
		//			MVP[i].name, MVP[i].tElapsed);

		fout << "   " << left << setw(4) << MVP[i].nMove << "   " << setw(16) << MVP[i].name << setw(5) << MVP[i].tElapsed << endl;

	//	fclose(fp);
	fout.close();
}
void RankingBoard::print() {
	for (int i = 0; i<nMVP; i++)
		printf("  [%2d위]  %4d  %-16s %5.1f\n", i + 1, MVP[i].nMove,
			MVP[i].name, MVP[i].tElapsed);
}
int RankingBoard::add(int nMove, double tElap) {
	if (nMove < MVP[nMVP - 1].nMove) {
		int pos = nMVP - 1;
		for (; pos>0; pos--) {
			if (nMove >= MVP[pos - 1].nMove) break;
			MVP[pos] = MVP[pos - 1];
		}
		MVP[pos].nMove = nMove;
		MVP[pos].tElapsed = tElap;
		printf(" %d위입니다. 이름을 입력하세요: ", pos + 1);
		scanf("%s", MVP[pos].name);
		return pos + 1;
	}
	return 0;
}