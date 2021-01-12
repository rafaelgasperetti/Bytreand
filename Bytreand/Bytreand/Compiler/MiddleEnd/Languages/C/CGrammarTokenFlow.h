#pragma once

#include <Compiler/MiddleEnd/GrammarTokenFlow.h>

class CGrammarTokenFlow : GrammarTokenFlow
{
	public:
		CGrammarTokenFlow(Grammar*);

		vector<pair<int, pair<GrammarState*, vector<CategorizedToken*>*>*>*>* GetAcceptedTokens(GrammarState*) override;
};