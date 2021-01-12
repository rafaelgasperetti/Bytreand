#pragma once

#include<iostream>
#include<fstream>
#include<stdexcept>

#include <Tools/FileBaseManager.h>

class FileWriter : public FileBaseManager
{
public:
	//Constructors
	FileWriter(string);

	//Actions
	void WriteFile(string);
};