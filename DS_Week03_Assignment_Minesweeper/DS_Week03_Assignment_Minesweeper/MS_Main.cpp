#include "MineSweeper.h"

void main() {
	CMineSweeper MS;
	int total;
	cout << " <���� ã��>" << endl <<
		" �ż��� ����(50�� ����)�� ���� ";
	total = MS.getNums(50);
	MS.playMineSweeper(total);
}