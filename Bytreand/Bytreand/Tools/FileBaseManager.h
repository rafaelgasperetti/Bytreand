#pragma once

#include <fstream>
#include <Tools/StringUtils.h>

class FileBaseManager
{
private:
	string Path;
	string OpenType;

public:
	static const int READ_CONFIG_DO_NOTHING = 0;
	static const int READ_CONFIG_IGNORE_STARTING_WITH = 1;

	static const char* OPEN_TYPE_READ;
	static const char* OPEN_TYPE_WRITE;

	FileBaseManager(string);

	string GetPath();
	string GetPathSeparator();
	string GetFileName(bool);
	string GetParentPaths();
	string GetExtension();
	void SetPath(string);
	bool Exists();
	bool Delete();
};