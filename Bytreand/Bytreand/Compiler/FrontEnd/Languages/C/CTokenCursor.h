#pragma once

#include <Compiler/FrontEnd/TokenCursor.h>

class CTokenCursor : public TokenCursor
{
	public:
		CTokenCursor(string);

		vector<string> GetTokenSeparators() override;
		vector<string> GetIgnoredTokens() override;
		vector<string> GetUnifiedSeparators() override;

		vector<string> GetReservedTokens() override;
		vector<string> GetUnaryOperationTokens() override;
		vector<string> GetBinaryOperationTokens() override;//Used for token type definition
		vector<string> GetUnaryBooleanOperationTokens() override;//Used for token type definition
		vector<string> GetBinaryBooleanOperationTokens() override;//Used for token type definition
		vector<string> GetAttributionTokens() override;//Used for token type definition
		vector<string> GetCompoundAttributionTokens() override;//Used for token type definition
		vector<string> GetControlTokens() override;//Used for token type definition
		vector<string> GetOpenControlTokens() override;//Used for token type definition
		vector<string> GetCloseControlTokens() override;//Used for token type definition
};