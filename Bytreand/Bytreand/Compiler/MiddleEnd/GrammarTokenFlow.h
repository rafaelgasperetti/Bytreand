#pragma once

#include <Tools/Comparable.h>
#include <Tools/StringUtils.h>
#include <Tools/VectorUtils.h>

#include <Compiler/MiddleEnd/GrammarState.h>
#include <Compiler/MiddleEnd/CategorizedToken.h>

class Grammar;
class GrammarState;

class GrammarTokenFlow : Comparable
{
	private:
		Grammar* RelatedGrammar;

	public:
		GrammarTokenFlow(Grammar*);
		void SetRelatedGrammar(Grammar*);
		Grammar* GetRelatedGrammar();
		void AddAcceptedTokens(GrammarState*);

		/*
			Evaluates all the GrammarStates, states transitions and next states. The combination rule is:
				-The external pair contains the integer that represents wich StateTransition it represents;
				-The internal pair represents the GrammarState of the related StateTransition as well as it's accepted token list.
		*/
		virtual vector<pair<int, pair<GrammarState*, vector<CategorizedToken*>*>*>*>* GetAcceptedTokens(GrammarState*) = 0;

		static void PushNewFlow(vector<pair<int, pair<GrammarState*, vector<CategorizedToken*>*>*>*>*, int, GrammarState*, vector<CategorizedToken*>*);
		static vector<pair<GrammarState*, vector<CategorizedToken*>*>*> GetStateTransitionFlow(vector<pair<int, pair<GrammarState*, vector<CategorizedToken*>*>*>*>*, int);
		static vector<CategorizedToken*>* GetGrammarStateFlow(vector<pair<GrammarState*, vector<CategorizedToken*>*>*>, GrammarState*);
};