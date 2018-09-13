#include "RankingClass.h"
#include <stdlib.h>
#include <time.h>
void main()
{
	srand((unsigned int)time(NULL));
	RankingBoard board;
	board.load("ranking.txt");
	board.print();

	for (int i = 0; i < 5; i++)
		board.add(rand() % 500, rand() % 1000 * 0.1);
	board.store("ranking.txt");
}