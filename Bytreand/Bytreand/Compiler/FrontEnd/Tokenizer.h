#pragma once

#include <Tools/StringUtils.h>
#include <Tools/Message.h>

#include <Tools/FileReader.h>
#include <Compiler/FrontEnd/TokenCursor.h>

class Tokenizer
{
    public:
		Tokenizer();
        vector<FrontEndToken*>* GetTokens(FileReader*, int);
		TokenCursor* GetCurrentCursor();
		vector<Message*>* GetMessages();

		static TokenCursor* GetTokenCursor(string, int);
		static int GetFrontEndTokenType(TokenCursor*);
		static string GetFrontEndTokenTypeName(int);

    private:
        vector<FrontEndToken*>* Tokens;
		TokenCursor* CurrentCursor;
		vector<Message*>* Messages = new vector<Message*>();

		void UnifyCommentsAndStrings();
};
