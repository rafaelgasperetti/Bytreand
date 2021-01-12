#include <Tools/FileWriter.h>

using namespace std;

FileWriter::FileWriter(string path) : FileBaseManager::FileBaseManager(path)
{

}

void FileWriter::WriteFile(string text)
{
	ofstream file(GetPath());
	file << text;
	file.close();
}