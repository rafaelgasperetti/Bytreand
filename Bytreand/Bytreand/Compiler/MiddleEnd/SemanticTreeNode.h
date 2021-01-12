#pragma once

#include<Compiler/FrontEnd/FrontEndToken.h>

#include<Compiler/MiddleEnd/GrammarState.h>
#include<Compiler/MiddleEnd/SemanticTree.h>

class SemanticTree;
class GrammarState;

class SemanticTreeNode : Comparable
{
	private:
		string Name;
		int StateType;
		int RelatedTokenPosition;
		FrontEndToken* RelatedToken;
		GrammarState* RelatedState;
		SemanticTreeNode* Parent;
		vector<SemanticTreeNode*>* Children = new vector<SemanticTreeNode*>();

	public:
		SemanticTreeNode(string, FrontEndToken*, int, GrammarState*);
		void SetName(string);
		string GetName();
		void SetFrontEndToken(FrontEndToken*, int);
		FrontEndToken* GetFrontEndToken();
		int GetRelatedTokenPosition();
		void SetGrammarState(GrammarState*);
		GrammarState* GetGrammarState();
		void SetParentNode(SemanticTreeNode*);
		SemanticTreeNode* GetParentNode();
		void AddChild(SemanticTreeNode*);
		SemanticTreeNode* GetChild(string, int, int);
		vector<SemanticTreeNode*>* GetChildren();
		bool IsLeafNode();
};