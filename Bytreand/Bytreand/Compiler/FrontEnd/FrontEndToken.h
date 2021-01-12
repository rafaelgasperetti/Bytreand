#pragma once

#include <Tools/StringUtils.h>
#include <Tools/Comparable.h>

class FrontEndToken : public Comparable
{
	private:
		string Value;
		int LineNumber = 0;
		int ColumnNumber = 0;
		int Type = 0;

	public:
		enum FrontEndTokenType
		{
			Reserved,
			Identifier,
			StringLiteral,
			Control,
			OpenControl,
			CloseControl,
			UnaryOperation,
			BinaryOperation,
			UnaryBooleanOperation,
			BinaryBooleanOperation,
			Attribution,
			CompoundAttribution,
			Comment,
			IgnoredToken,
			Literal,//Before constant type definition
			IntegerLiteral,
			LongLiteral,
			FloatLiteral,
			DoubleLiteral
		};

		FrontEndToken();
		FrontEndToken(string, int);
		void SetValue(string);
		string GetValue();
		void SetLineNumber(int);
		int GetLineNumber();
		void SetColumnNumber(int);
		int GetColumnNumber();
		void SetType(int);
		int GetType();
		string GetTypeName();
};