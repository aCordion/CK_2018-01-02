#pragma once
#include <iostream>

using namespace std;

class CMath
{
	int count;
	int value;
	char Pillers[3];

public:
	CMath();
	~CMath();
	int math_Fib(int in1, int in2, const int MAX);
	void math_Hanoi(char from, char to, char by, int num);
	void math_HMove(char from, char to);
	int getNums(const int MAX);
	char getPillers(int num) { return Pillers[num]; }
};

