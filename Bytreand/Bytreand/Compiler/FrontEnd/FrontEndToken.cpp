#include <Compiler/FrontEnd/FrontEndToken.h>

FrontEndToken::FrontEndToken() : Comparable()
{

}

FrontEndToken::FrontEndToken(string value, int type) : Comparable()
{
	SetValue(value);
	SetType(type);
}

void FrontEndToken::SetValue(string value)
{
	if (!StringUtils::IsEmpty(value))
	{
		Value = value;
	}
	else
	{
		throw invalid_argument("Empty values are not allowed at FrontEndToken.");
	}
}

string FrontEndToken::GetValue()
{
	return Value;
}

void FrontEndToken::SetLineNumber(int lineNumber)
{
	if (lineNumber >= 0)
	{
		LineNumber = lineNumber;
	}
	else
	{
		throw invalid_argument("Line numbers below zero are not allower at FrontEndToken.");
	}
}

int FrontEndToken::GetLineNumber()
{
	return LineNumber;
}

void FrontEndToken::SetColumnNumber(int columnNumber)
{
	if (columnNumber >= 0)
	{
		ColumnNumber = columnNumber;
	}
	else
	{
		throw invalid_argument("Column numbers below zero are not allower at FrontEndToken.");
	}
}

int FrontEndToken::GetColumnNumber()
{
	return ColumnNumber;
}

void FrontEndToken::SetType(int type)
{
	if (type == Reserved || type == Identifier || type == StringLiteral || type == Control || type == OpenControl || type == CloseControl ||
		type == UnaryOperation || type == BinaryOperation || type == UnaryBooleanOperation || type == BinaryBooleanOperation || type == Attribution ||
		type == Comment || type == IgnoredToken || type == Literal || type == IntegerLiteral || type == LongLiteral || type == FloatLiteral || type == DoubleLiteral)
	{
		Type = type;
	}
	else
	{
		throw invalid_argument("Invalid front end token type: " + StringUtils::ToString(type) + ".");
	}
}

int FrontEndToken::GetType()
{
	return Type;
}

string FrontEndToken::GetTypeName()
{
	switch (Type)
		{
		case Reserved:
			return "Reserved";
		case Identifier:
			return "Identifier";
		case StringLiteral:
			return "StringLiteral";
		case Control:
			return "Control";
		case OpenControl:
			return "OpenControl";
		case CloseControl:
			return "CloseControl";
		case UnaryOperation:
			return "UnaryOperation";
		case BinaryOperation:
			return "BinaryOperation";
		case UnaryBooleanOperation:
			return "UnaryBooleanOperation";
		case BinaryBooleanOperation:
			return "BinaryBooleanOperation";
		case Attribution:
			return "Attribution";
		case Comment:
			return "Comment";
		case IgnoredToken:
			return "IgnoredToken";
		case Literal:
			return "Literal";
		case IntegerLiteral:
			return "IntegerLiteral";
		case LongLiteral:
			return "LongLiteral";
		case FloatLiteral:
			return "FloatLiteral";
		case DoubleLiteral:
			return "DoubleLiteral";
		default:
			throw invalid_argument("Invalid FrontEndToken type \"" + StringUtils::ToString(Type) + "\".");
	}
}