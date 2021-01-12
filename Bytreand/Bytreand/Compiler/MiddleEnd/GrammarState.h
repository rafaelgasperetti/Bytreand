#pragma once

#include <Tools/StringUtils.h>
#include <Tools/CommandLineUtils.h>
#include <Tools/Comparable.h>

#include <Compiler/MiddleEnd/Grammar.h>

#include <Compiler/MiddleEnd/StateTransition.h>
#include <Compiler/MiddleEnd/SemanticTree.h>
#include <Compiler/MiddleEnd/CategorizedToken.h>

class StateTransition;
class Grammar;
class ConsumptionResult;
class SemanticTreeNode;
class GrammarTokenFlow;

using namespace std;

class GrammarState : public Comparable
{
	private:
		string Name;
		int Type = 0;
		int AssociativityType = LeftToRight;
		bool Literal = false;//Must be true when the name represents it's literal token name, false otherwise.
		vector<StateTransition*>* NextTransitions = new vector<StateTransition*>();
		vector<StateTransition*>* PreviousTransitions = new vector<StateTransition*>();
	
	public:
		GrammarState(string, int);
		GrammarState(string, int, int);
		GrammarState(string, int, bool);
		GrammarState(string, int, int, bool);
		void SetName(string);
		string GetName();
		void SetType(int);
		int GetType();
		void SetAssociativityType(int);
		int GetAssociativityType();
		void AddNextTransition(StateTransition*);
		bool HasNextTransition(string, string);
		StateTransition* GetNextTransition(string, string, int);
		vector<StateTransition*>* GetNextTransitions();
		GrammarState* GetNextState(int, int);
		void AddPreviousTransition(StateTransition*);
		bool HasPreviousTransition(string, string);
		StateTransition* GetPreviousTransition(string, string, int);
		vector<StateTransition*>* GetPreviousTransitions();
		bool IsFinalState();
		void SetLiteral(bool);
		bool IsLiteral();//Returns true when the name represents it's literal token name, false otherwise.
		bool Equals(Comparable*);

		enum AssociativityType
		{
			LeftToRight,
			RightToLeft
		};
};