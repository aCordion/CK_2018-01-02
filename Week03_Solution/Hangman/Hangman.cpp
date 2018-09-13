#include "Hangman.h"


Hangman::Hangman()
{
}


Hangman::~Hangman()
{
}

void Hangman::play(string prob)
{
	load();
	problem = prob;
	answer = string(problem.length(), '-');
	guessed = string(24, '.');
	nTries = 0;
	while (nTries < maxTries && answer != problem) {
		print();
		guess();
	}
	print();
	cout << "\n\t" << ((nTries == maxTries) ? "실패" : "정답") << endl;
}

void Hangman::load(char* progName) {
	ifstream fs(progName);
	if (fs) {
		getline(fs, progress[0]);
		for (int i = 0; i < 64; i++) {
			getline(fs, progress[i]);
		}
	}
}

void Hangman::print()
{
	system("cls");
	cout << " <Hanhman Game>\n";
	for (int i = 0; i < 8; i++) {
		cout << '\t' << progress[nTries * 8 + i] << endl;
	}
	cout << "\n\t" << answer;
	cout << "\n\n" << guessed;
}

int Hangman::countMatched(char ch)
{
	int nMatched = 0;
	for (int pos = -1; ; ) {
		pos = problem.find(ch, pos + 1);
		if (pos < 0) break;
		answer[pos] = ch;
		nMatched++;
	}
	return nMatched;
}

void Hangman::guess()
{
	char ch = getch();
	if (ch >= 'a' && ch <= 'z') {
		int pos = guessed.find(ch);
		if (pos < 0) {
			guessed[ch - 'a'] = ch;
			if (countMatched(ch) == 0) nTries++;
		}
	}
}
