#pragma once

#include <Compiler/FrontEnd/FrontEndToken.h>

#include <Compiler/MiddleEnd/GrammarState.h>
#include <Compiler/MiddleEnd/CategorizedToken.h>
#include <Compiler/MiddleEnd/SemanticTree.h>

class GrammarState;
class Grammar;
class SemanticTree;
class CategorizedToken;

class StateTransition : public Comparable
{
	private:
		string Name;
		vector<pair<GrammarState*,vector<CategorizedToken*>*>*>* NextStates;//Each state at a transition must accept some identified tokens to consume.

	public:
		StateTransition();
		StateTransition(string);
		void SetName(string);
		string GetName();
		void AddNextState(GrammarState*);
		GrammarState* GetNextState(string, int);
		vector<pair<GrammarState*, vector<CategorizedToken*>*>*>* GetNextStates();
		bool HasNextStates();
		bool CompareStateAndToken(int, FrontEndToken*);
		void AddAcceptedToken(CategorizedToken*, int);
		CategorizedToken* GetAcceptedToken(int, bool, int);
		vector<CategorizedToken*>* GetAcceptedTokens(int);
		bool IsAcceptedToken(SemanticTree*, Grammar*, GrammarState*, GrammarState*, vector<FrontEndToken*>*, int, int);

		static StateTransition* GetStateTransition(string, string, vector<StateTransition*>, int);
};