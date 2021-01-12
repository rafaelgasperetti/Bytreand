#pragma once

#include <Tools/Message.h>
#include <Tools/Comparable.h>

#include<Compiler/MiddleEnd/GrammarState.h>

class GrammarState;
class SemanticTree;

class ConsumptionResult : Comparable
{
	private:
		vector<Message*>* SemanticMessages = new vector<Message*>();
		int Index;
		bool Success;
		GrammarState* State;

	public:
		ConsumptionResult(int, bool, GrammarState*);
		void AddMessage(Message*);
		vector<Message*>* GetMessages();
		void SetIndex(int);
		int GetIndex();
		void SetSuccess(bool);
		bool IsSuccess();
		void SetGrammarState(GrammarState*);
		GrammarState* GetGrammarState();
};