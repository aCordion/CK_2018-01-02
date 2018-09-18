#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>

using namespace std;

class Hangman
{
	string progress[64];
	string problem;
	string answer;
	string guessed;
	int nTries;
	const int maxTries = 7;

	void load(char* progName = "HangmanProgress.txt");
	void print();
	int countMatched(char ch);
	void guess();
public:
	Hangman();
	~Hangman();
	void play(string prob);
};