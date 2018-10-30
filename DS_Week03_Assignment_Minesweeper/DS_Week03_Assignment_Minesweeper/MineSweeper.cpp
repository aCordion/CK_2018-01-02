#include "MineSweeper.h"

enum TileType { eBomb = -1, eNone = 0 };
enum MaskingType { eHide = 0, eShow = 1, eFlag = 2};

CMineSweeper::CMineSweeper()
{
	rstMineMapMask();
	rstMineMapTile();
	nx = MAXSIZE;
	ny = MAXSIZE;
	nBomb = MAXSIZE;
}


CMineSweeper::~CMineSweeper()
{
}

void CMineSweeper::rstMineMapMask()
{
	MineMapMask = new int *[MAXSIZE];
	for (int i = 0; i < MAXSIZE; i++) {
		MineMapMask[i] = new int[MAXSIZE];
	}
}

void CMineSweeper::rstMineMapTile()
{
	MineMapTile = new int *[MAXSIZE];
	for (int i = 0; i < MAXSIZE; i++) {
		MineMapTile[i] = new int[MAXSIZE];
	}
}

void CMineSweeper::dig(int x, int y)
{

	if (isValid(x, y) && mask(x, y) != eShow) {
		mask(x, y) = eShow;
		if (label(x, y) == 0) {
			dig(x - 1, y - 1);
			dig(x - 1, y);
			dig(x - 1, y + 1);
			dig(x, y - 1);
			dig(x, y + 1);
			dig(x + 1, y - 1);
			dig(x + 1, y);
			dig(x + 1, y + 1);
		}
	}
}

void CMineSweeper::mark(int x, int y)
{
	if (isValid(x, y) && mask(x, y) == eHide) {
		mask(x, y) = eFlag;
	}
}

int CMineSweeper::getBombCount()
{
	int count = 0;
	for (int y = 0; y < ny; y++) {
		for (int x = 0; x < nx; x++) {
			if (mask(x, y) == eFlag) {
				count++;
			}
		}
	}
	return count;
}

void CMineSweeper::print()
{
	system("cls");
	printf("  발견 :%2d   전체 : %2d\n\n", getBombCount(), nBomb);
	printf("   ①②③④⑤⑥⑦⑧⑨\n");
	for (int y = 0; y < ny; y++) {
		printf("%2c ", 'A' + y);
		for (int x = 0; x < nx; x++) {
			if (mask(x, y) == eHide) {
				printf("□");
			}
			else if (mask(x, y) == eFlag) {
				printf("†");
			}
			else {
				if (isBomb(x, y)) {
					printf("※");
				}
				else if (isEmpty(x, y)) {
					printf("  ");
				}
				else {
					printf("%2d", label(x, y));
				}
			}
		}
		printf("\n");
	}
}

int CMineSweeper::countNbrBombs(int x, int y)
{
	int count = 0;
	for (int yy = y - 1; yy <= y + 1; yy++) {
		for (int xx = x - 1; xx <= x + 1; xx++) {
			if (isValid(xx, yy) && label(xx, yy) == eBomb) {
				count++;
			}
		}
	}
	return count;
}

void CMineSweeper::init(int total)
{
	srand((unsigned int)time(NULL));
	for (int y = 0; y < ny; y++) {
		for (int x = 0; x < nx; x++) {
			mask(x, y) = eHide;
			label(x, y) = 0;
		}
	}
	nBomb = total;
	for (int i = 0; i < nBomb; i++) {
		int x, y;
		do {
			x = rand() % nx;
			y = rand() % ny;
		} while (label(x, y) != eNone);
		label(x, y) = eBomb;
	}
	for (int y = 0; y < ny; y++) {
		for (int x = 0; x < nx; x++) {
			if (label(x, y) == eNone) {
				label(x, y) = countNbrBombs(x, y);
			}
		}
	}
}

bool CMineSweeper::getPos(int & x, int & y)
{
	char ch1, ch2, ch3;
	cout << "\n행(A-I)열(1-9)지뢰(P)\n 입력 --> ";
	bool isBomb = false;
	cin >> ch1 >> ch2 >> ch3;
	rewind(stdin);
	y = toupper(ch1) - 'A';
	x = ch2 - '1';
	if (toupper(ch3) == 'P') {
		isBomb = true;
	}
	return isBomb;
}

int CMineSweeper::checkDone()
{
	int count = 0;
	for (int y = 0; y < ny; y++) {
		for (int x = 0; x < nx; x++) {
			if (mask(x, y) != eShow) {
				count++;
			}
			else if (isBomb(x, y)) {
				return -1;
			}
		}
	}
	return (count == nBomb) ? 1 : 0;
}

void CMineSweeper::playMineSweeper(int total)
{
	int x, y, status;
	init(total);
	do {
		print();
		bool isBomb = getPos(x, y);
		if (isBomb) {
			mark(x, y);
		}
		else {
			dig(x, y);
		}
		status = checkDone();
	} while (status == 0);
	print();
	if (status < 0) {
		printf("\n실패: 지뢰 폭발!!!\n\n");
	}
	else {
		printf("\n성공: 탐색 성공!!!\n\n");
	}
}

bool CMineSweeper::isBomb(int x, int y)
{
	return isValid(x, y) && label(x, y) == eBomb;
}

bool CMineSweeper::isEmpty(int x, int y)
{
	return isValid(x, y) && label(x, y) == eNone;
}

int CMineSweeper::getNums(const int MAX)
{

	int Num = 0;
	bool isFail = false;

	do {
		cout << "입력 : ";
		cin >> Num;

		if (cin.fail()) {
			cout << "틀린 값입니다. 다시 입력하여 주세요." << endl;
			cin.clear();
			rewind(stdin);
			isFail = true;
		}
		if (Num > MAX || Num <= 0) {
			cout << MAX << " 이하, 1 이상의 값을 입력해 주세요." << endl;
			cin.clear();
			rewind(stdin);
			isFail = true;
		}
		if (!cin.fail()) {
			isFail = false;
		}
	} while (isFail == true);

	return Num;
}
