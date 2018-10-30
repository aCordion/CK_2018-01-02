#include "MineSweeper.h"

void main() {
	CMineSweeper MS;
	int total;
	cout << " <지뢰 찾기>" << endl <<
		" 매설할 지뢰(50개 이하)의 개수 ";
	total = MS.getNums(50);
	MS.playMineSweeper(total);
}