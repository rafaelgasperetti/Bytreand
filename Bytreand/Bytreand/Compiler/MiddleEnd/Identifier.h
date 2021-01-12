#pragma once

#include <Compiler/FrontEnd/FrontEndToken.h>

#include <Compiler/MiddleEnd/Scope.h>

class Identifier
{
	private:
		FrontEndToken* Token;
		Scope* ParentScope;
		int Index;
		int Category;
		int Type;
		bool Pointer;

	public:
		Identifier(FrontEndToken*, int, int, int);
		void SetFrontEndToken(FrontEndToken*);
		FrontEndToken* GetFrontEndToken();
		void SetParentScope(Scope*);
		Scope* GetParentScope();
		void SetIndex(int);
		int GetIndex();
		void SetCategory(int);
		int GetCategory();
		void SetType(int);
		int GetType();
		void SetPointer(bool);
		bool IsPointer();


		enum Categories
		{
			Method,
			Variable
		};
		enum Types
		{
			Void,
			Int,
			Long,
			Float,
			Double,
			Char,
			String
		};
};