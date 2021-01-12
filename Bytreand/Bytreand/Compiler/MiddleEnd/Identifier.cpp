#include <Compiler/MiddleEnd/Identifier.h>

Identifier::Identifier(FrontEndToken* token, int index, int category, int type)
{
	SetFrontEndToken(token);
	SetIndex(index);
	SetCategory(category);
	SetType(type);
}

void Identifier::SetFrontEndToken(FrontEndToken* token)
{
	if (token != NULL)
	{
		Token = token;
	}
	else
	{
		throw invalid_argument("It is not possible to set an NULL FrontEndToken to an identifier.");
	}
}

FrontEndToken* Identifier::GetFrontEndToken()
{
	return Token;
}

void Identifier::SetParentScope(Scope* scope)
{
	ParentScope = scope;
}

Scope* Identifier::GetParentScope()
{
	return ParentScope;
}

void Identifier::SetIndex(int index)
{
	if (index >= 0)
	{
		Index = index;
	}
	else
	{
		throw invalid_argument("It is not possible to set lower zero value to Identifier \"" + GetFrontEndToken()->GetValue() + "\" index.");
	}
}

int Identifier::GetIndex()
{
	return Index;
}

void Identifier::SetCategory(int category)
{
	if (category >= Categories::Method || category <= Categories::Variable)
	{
		Category = category;
	}
	else
	{
		throw invalid_argument("Invalid category at Identifier " + GetFrontEndToken()->GetValue()  + ". Available categories are " + StringUtils::ToString(Categories::Method) + " or " + StringUtils::ToString(Categories::Variable));
	}
}

int Identifier::GetCategory()
{
	return Category;
}

void Identifier::SetType(int type)
{
	if (type >= Types::Void && type <= Types::String)
	{
		Type = type;
	}
	else
	{
		throw invalid_argument("Invalid type at Identifier " + GetFrontEndToken()->GetValue() + ". Available categories are " + StringUtils::ToString(Types::Void) + " or " + StringUtils::ToString(Types::String));
	}
}

int Identifier::GetType()
{
	return Type;
}

void Identifier::SetPointer(bool pointer)
{
	Pointer = pointer;
}

bool Identifier::IsPointer()
{
	return Pointer;
}