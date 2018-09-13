#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void main() {
/*	string s1, s2 = "Game";
//	s1.size(), s2.size();
	cout << "s1.size = " << s1.size() << endl;
	cout << "s2.size = " << s2.size() << endl;

	cout << "s2.length = " << s2.length() << endl;

	s1 = s2 + ' ' + "Over";
	if (s1 == "Game Over")
		cout << s1 << "가 맞습니다\n";
	cout << s1.find("Over") << endl;
	cout << s1.find("e", 4) << endl;
	cout << s1[0] << endl;
	cout << s1.substr(5, 4) << endl;
	printf("s1 = %s\n", s1.c_str());
	getline(cin, s1);
	cout << s1 << endl;
	*/

	string s1("A");		//string s1 = "A";
	s1.append("+");		//s1 = s1 + "+";
	cout << "s1 = " << s1 << endl;

	s1.insert(2, "Grade");
	cout << "s1 = " << s1 << endl;

	string s2("I LOVE C++");
	char ch1 = s2.at(7);
	char ch2 = s2[7];	// 동일한 내용

	cout << "ch1 = " << ch1 << endl;
	cout << "ch2 = " << ch2 << endl;


}