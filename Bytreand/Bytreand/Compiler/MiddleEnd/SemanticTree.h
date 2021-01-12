#pragma once

#include <Tools/Message.h>

#include<Compiler/MiddleEnd/Grammar.h>
#include<Compiler/MiddleEnd/SemanticTreeNode.h>
#include<Compiler/MiddleEnd/Identifier.h>
#include<Compiler/MiddleEnd/ConsumptionResult.h>

class SemanticTreeNode;
class Grammar;
class StateTransition;
class ConsumptionResult;

class SemanticTree
{
	private:
		SemanticTreeNode* RootNode;
		vector<Message*>* SemanticMessages = new vector<Message*>();
		vector<Identifier*>* Identifiers = new vector<Identifier*>();

	public:
		void SetRootNode(SemanticTreeNode*);
		SemanticTreeNode* GetRootNode();
		void AddMessage(Message*);
		vector<Message*>* GetMessages();
		void AddIdentifier(Identifier*);
		void AddIdentifiers(vector<FrontEndToken*>*);
		Identifier* GetIdentifier(int);
		vector<Identifier*>* GetIdentifiers();

		static SemanticTree* GetSemanticTree(Grammar*, vector<FrontEndToken*>*);
		static ConsumptionResult* ConsumeCode(SemanticTree*, Grammar*, GrammarState*, GrammarState*, vector<FrontEndToken*>*, int, int);
		static ConsumptionResult* ConsumeStateTransition(SemanticTree*, Grammar*, GrammarState*, GrammarState*, vector<FrontEndToken*>*, int, StateTransition*, int);
};