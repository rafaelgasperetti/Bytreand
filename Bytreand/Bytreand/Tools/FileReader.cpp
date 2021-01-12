#include <Tools/FileReader.h>

FileReader::FileReader(string path) : FileBaseManager::FileBaseManager(path)
{
	
}

string FileReader::ReadFileLine(ifstream& file, int lineNumber)
{
	string line = "";

	if (file.is_open())
	{
		if (getline(file, line))
		{
			return line;
		}
		else
		{
			return "";
		}
	}
	else
	{
		throw invalid_argument("The file \"" + GetPath() + "\" is not opened.");
	}
}

string FileReader::ReadFileLine(ifstream& file)
{
	return ReadFileLine(file, -1);
}

string FileReader::ReadFile(const int readConfig, string pattern, bool ignoreEmptyLines)
{
	int lineNumber = 0;
	string ret = "", line;

	ifstream file;
	file.open(GetPath().c_str());

	while (!file.eof())
	{
		line = ReadFileLine(file);

		if (!file.eof() && (!ignoreEmptyLines || !line.empty()))
		{
			switch (readConfig)
			{
			case READ_CONFIG_IGNORE_STARTING_WITH:
				if (!StringUtils::StartsWith(line, pattern))
				{
					ret = StringUtils::AppendLine(ret, line, lineNumber != 0, false, true);
					lineNumber++;
				}
				break;
			default:
				ret = StringUtils::AppendLine(ret, line, lineNumber != 0, false, true);
				lineNumber++;
				break;
			}
		}

		line = "";

	}

	if (file.is_open())
	{
		file.close();
	}

	return ret;
}

string FileReader::ReadFile()
{
	return ReadFile(READ_CONFIG_DO_NOTHING, "", false);
}
