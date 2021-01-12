#pragma once

#include<iostream>
#include<fstream>
#include<stdexcept>

#include <Tools/FileBaseManager.h>

class FileReader : public FileBaseManager
{
public:
	//Constructors
	FileReader(string);

	//Actions
	string ReadFileLine(ifstream&, int);
	string ReadFileLine(ifstream&);
	string ReadFile(const int, string pattern, bool);
	string ReadFile();
};