#pragma once

#include <Tools/StringUtils.h>

class Comparable
{
	private:
		unsigned int Hash;
		unsigned int CalculateHash();
		int RecursiveOperation(int, int);

	public:
		Comparable();
		unsigned int GetHash();
		bool Equals(Comparable*);
};