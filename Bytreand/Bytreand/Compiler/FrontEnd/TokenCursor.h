#pragma once

#include <Tools/StringUtils.h>
#include <Compiler/FrontEnd/FrontEndToken.h>

class TokenCursor
{
    public:
        TokenCursor(string);
        bool Read();
        string GetValue();
		void Reset();
		int GetLineNumber();
		int GetColumnNumber();
		void SetFrontEndLanguage(int);
		int GetFrontEndLanguage();

		bool MakeUnifiedSeparator(FrontEndToken*, FrontEndToken*);
		void JoinFrontEndTokens(FrontEndToken*, FrontEndToken*);

		bool IsReservedToken(string);
		bool IsUnaryOperation(string);
		bool IsBinaryOperation(string);
		bool IsUnaryBooleanOperation(string);
		bool IsBinaryBooleanOperation(string);
		bool IsAttributionOperation(string);
		bool IsCompoundAttributionOperation(string);
		bool IsControlToken(string);
		bool IsOpenControlToken(string);
		bool IsCloseControlToken(string);
		bool IsLiteral(string);
		bool IsFloatingLiteral(string);
		bool IsIntegerLiteral(string);
		bool IsLongLiteral(string);
		bool IsFloatLiteral(string);
		bool IsDoubleLiteral(string);
		bool IsStringLiteral(string);
		bool IsComment(string);
		bool IsIgnoredToken(string);

		virtual vector<string> GetTokenSeparators() = 0;
		virtual vector<string> GetIgnoredTokens() = 0;
		virtual vector<string> GetUnifiedSeparators() = 0;

		virtual vector<string> GetReservedTokens() = 0;
		virtual vector<string> GetUnaryOperationTokens() = 0;//Used for token type definition
		virtual vector<string> GetBinaryOperationTokens() = 0;//Used for token type definition
		virtual vector<string> GetUnaryBooleanOperationTokens() = 0;//Used for token type definition
		virtual vector<string> GetBinaryBooleanOperationTokens() = 0;//Used for token type definition
		virtual vector<string> GetAttributionTokens() = 0;//Used for token type definition
		virtual vector<string> GetCompoundAttributionTokens() = 0;//Used for token type definition
		virtual vector<string> GetControlTokens() = 0;//Used for token type definition
		virtual vector<string> GetOpenControlTokens() = 0;//Used for token type definition
		virtual vector<string> GetCloseControlTokens() = 0;//Used for token type definition

    private:
        string Text;
        string Value;
        bool CanRead;
        int CursorIndex = 0;
		int LineNumber = 0;
		int ColumnNumber = 0;
		int FrontEndLanguage = 0;
		int PreviousLinesLength = 0;
        int TokenSeparatorLength(string);
};
