#pragma once
#include <iostream>
#include <cstdlib>
#include <ctime>

class SpeedGuguDan {
private:
	int NumGames = 0;
	int NumWins = 0;
	double Score = 0;

public:
	double tElapsed = 0;
	bool playGuguOnce();
	double play(int nPlay);
};