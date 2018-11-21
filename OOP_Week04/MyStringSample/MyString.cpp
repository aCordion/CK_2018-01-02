#include <iostream>
#include <string>

using namespace std;

class MyString {

private:
	int m_nLen;
	char *m_pStr;

public:
	MyString();
	MyString(const char * const str);
	MyString(const MyString & str);
	~MyString();
	friend ostream & operator << (ostream & os, MyString & temp);
};

//¾èÀº º¹»ç
MyString::MyString(const char * const str) {
	m_nLen = strlen(str) + 1;
	m_pStr = new char[m_nLen];
	strcpy(m_pStr, str);
}

//±íÀº º¹»ç
MyString::MyString(const MyString & str) {
	m_nLen = str.m_nLen;
	m_pStr = new char[m_nLen];
	strcpy(m_pStr, str.m_pStr);
}

MyString::MyString() {
	m_nLen = 1;
	m_pStr = new char[m_nLen];
	strcpy(m_pStr, "");
}

MyString::~MyString() {
	delete[]m_pStr;
	m_nLen = 0;
	m_pStr = NULL;
}

ostream & operator << (ostream & os, MyString & temp) {
	cout << temp.m_pStr;
	return os;
}

void main() {
	MyString strA("Apple");
	MyString strB;

	cout << "strA = " << strA << endl;
	cout << "strB = " << strB << endl;

	MyString strC(strA);
	cout << "strC = " << strC << endl;
}