#pragma once
#include <string>
using namespace std;

class FileException
{
	string filename;
	bool bRead;
public:
	FileException(string name, bool b) : filename(name), bRead(b) {}
	~FileException();
};

