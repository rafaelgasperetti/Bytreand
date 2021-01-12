#pragma once

#include<Tools/StringUtils.h>

class Scope
{
	private:
		string Name;
		int Depth;
		Scope* ParentScope;
		
	public:
		Scope(string, int);
		void SetName(string);
		string GetName();
		void SetDepth(int);
		int GetDepth;
		void SetParentScope(Scope*);
		Scope* GetParentScope();
};