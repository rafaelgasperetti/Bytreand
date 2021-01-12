#include <time.h>
#include <iostream>

#include <Tools/Comparable.h>

Comparable::Comparable()
{
	Hash = CalculateHash();
}

unsigned int Comparable::GetHash()
{
	return Hash;
}

bool Comparable::Equals(Comparable* comparable)
{
	return comparable != NULL && comparable->GetHash() == GetHash();
}

int Comparable::RecursiveOperation(int number, int operationsLeft)
{
	if (operationsLeft == 0)
	{
		return 1;
	}
	else
	{
		return (number * RecursiveOperation(number, operationsLeft - 1));
	}
}

unsigned int Comparable::CalculateHash()
{
	string str;

	for (int i = 0; i < 100; i++)
	{
		str = str + StringUtils::ToString(32 + (rand() % 95));//32 a 126 (126 - 32)
	}

	unsigned int hash = 0;
	for (unsigned int i = 0; i < str.size(); i++)
	{
		int x = ((str.size() - 1) - i);
		hash += static_cast<int>(str[i]) * RecursiveOperation(32, x);
	}
	return hash;
}