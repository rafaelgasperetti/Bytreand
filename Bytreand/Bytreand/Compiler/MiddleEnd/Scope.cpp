#include <Compiler/MiddleEnd/Scope.h>

Scope::Scope(string name, int depth)
{
	SetName(name);
	SetDepth(depth);
}

void Scope::SetName(string name)
{
	Name = name;
}

string Scope::GetName()
{
	return Name;
}

void Scope::SetDepth(int depth)
{
	if (depth >= 0)
	{
		Depth = depth;
	}
	else
	{
		throw invalid_argument("It is not possible to set a lower zero depth on scope \"" + GetName() + "\".");
	}
}

void Scope::SetParentScope(Scope* scope)
{
	ParentScope = scope;
}

Scope* Scope::GetParentScope()
{
	return ParentScope;
}