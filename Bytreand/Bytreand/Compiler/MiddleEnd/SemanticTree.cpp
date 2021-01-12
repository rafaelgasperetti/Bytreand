#include <Compiler/MiddleEnd/SemanticTree.h>

void SemanticTree::SetRootNode(SemanticTreeNode* node)
{
	if (node != NULL)
	{
		RootNode = node;
	}
	else
	{
		throw invalid_argument("The semantic tree root node must never be null.");
	}
}

SemanticTreeNode* SemanticTree::GetRootNode()
{
	return RootNode;
}

void SemanticTree::AddMessage(Message* m)
{
	if (m != NULL)
	{
		SemanticMessages->push_back(m);
	}
	else
	{
		throw invalid_argument("NULL messages are not allowed at SemanticTree.");
	}
}

vector<Message*>* SemanticTree::GetMessages()
{
	return SemanticMessages;
}

void SemanticTree::AddIdentifier(Identifier* identifier)
{
	if (identifier != NULL)
	{
		Identifiers->push_back(identifier);
	}
	else
	{
		throw invalid_argument("The identifier list does not accept null identifiers at SemanticTree.");
	}
}

void SemanticTree::AddIdentifiers(vector<FrontEndToken*>* code)
{
	for (int i = 0; i < code->size(); i++)
	{
		if ((*code)[i]->GetType() == FrontEndToken::FrontEndTokenType::Identifier)
		{
			//Identifier* identifier = new Identifier((*code)[i], i, );//The parameter must be the tree because it needs the parent type to define.
			//AddIdentifier(identifier);
		}
	}
}

Identifier* SemanticTree::GetIdentifier(int index)
{
	if (index >= 0)
	{
		return (*Identifiers)[index];
	}
	else
	{
		return NULL;
	}
}

vector<Identifier*>* SemanticTree::GetIdentifiers()
{
	return Identifiers;
}

SemanticTree* SemanticTree::GetSemanticTree(Grammar* grammar, vector<FrontEndToken*>* code)
{
	SemanticTree* tree = new SemanticTree();

	if (grammar != NULL && code != NULL)
	{
		int codeIndex = 0;
		GrammarState* currentState = grammar->GetRootState();
		SemanticTreeNode* rootNode = new SemanticTreeNode("", NULL, 0, currentState);
		tree->SetRootNode(rootNode);
		ConsumptionResult* result = NULL;

		while (codeIndex < code->size() && ((result != NULL && result->IsSuccess()) || codeIndex == 0))
		{
			result = ConsumeCode(tree, grammar, codeIndex == 0 ? NULL : result->GetGrammarState(), currentState, code, codeIndex, true);

			codeIndex = result->GetIndex() + 1;
		}

		if (codeIndex == code->size())
		{
			tree->AddMessage(new Message(Message::MessageTypes::Successfull, "Semantic tree successfully generated."));
		}
		else
		{
			tree->AddMessage(new Message(Message::MessageTypes::Error, "There were semantic erros on the compilation."));
		}
	}
	else if(grammar == NULL && code == NULL)
	{
		tree->AddMessage(new Message(Message::MessageTypes::Error, "It is not possible to compile the semantic tree for NULL grammar and code."));
	}
	else if (grammar == NULL)
	{
		tree->AddMessage(new Message(Message::MessageTypes::Error, "It is not possible to compile the semantic tree for NULL grammar."));
	}
	else
	{
		tree->AddMessage(new Message(Message::MessageTypes::Error, "It is not possible to compile the semantic tree for NULL code."));
	}

	return tree;
}

/*
TODO: Create the "ConsumedCode" variable based on the real code, and the complete algorithm is over when there is not any non literal value on the generated consumed code.
Maybe the recursive call inside the "ConsumeCode" method may not have to exist anymore because it will be recalled again on the next "GetSemanticTree" step, consuming the first non
literal state on the consumed code.
*/
ConsumptionResult* SemanticTree::ConsumeCode
(
	SemanticTree* tree,
	Grammar* grammar,
	GrammarState* parentState,
	GrammarState* state,
	vector<FrontEndToken*>* code,
	int codeIndex,
	int recurse
)
{
	ConsumptionResult* result = new ConsumptionResult(codeIndex, false, state);
	for (StateTransition* transition : (*state->GetNextTransitions()))
	{
		cout << "Visiting " << transition->GetName() << " of " << state->GetName() << " (parent: " << (parentState == NULL ? "NULL" : parentState->GetName())
			<< ")  comparing to \"" << (*code)[codeIndex]->GetValue() << "\" (" << (*code)[codeIndex]->GetTypeName() << ") - Recurse: " << recurse << endl;

		result = ConsumeStateTransition(tree, grammar, parentState, state, code, codeIndex, transition, 0);
		if (result->IsSuccess())
		{
			codeIndex = result->GetIndex();
			//tree->
			cout << "\t\tMatched transition" << endl;
			return result;
		}

		if (recurse > 0)
		{
			for (int i = 0; i < transition->GetNextStates()->size(); i++)
			{
				result = ConsumeCode(tree, grammar, state, (*transition->GetNextStates())[i]->first, code, codeIndex, recurse - 1);
				codeIndex = result->GetIndex();
				i = transition->GetNextStates()->size();
			}
		}
	}
	return result;
}

/**
*	Method created for running all the states on the matched state transition, so it will only be valid if all the states of the transition accept the code
*/
ConsumptionResult* SemanticTree::ConsumeStateTransition
(
	SemanticTree* tree,
	Grammar* grammar,
	GrammarState* parent,
	GrammarState* state,
	vector<FrontEndToken*>* code,
	int codeIndex,
	StateTransition* transition,
	int recurse
)
{
	ConsumptionResult* result = new ConsumptionResult(codeIndex, true, state);

	for (int i = 0; i < transition->GetNextStates()->size(); i++)
	{
		cout << "\tVisiting state \"" << state->GetName() << "\" to analyze \"" << (*transition->GetNextStates())[i]->first->GetName()
			<< "\" comparing to \"" << (*code)[codeIndex]->GetValue() << "\" - Recurse: " << recurse << endl;
		if (!transition->CompareStateAndToken(i, (*code)[codeIndex]))
		{
			result->SetSuccess(false);
			cout << "\t\tSuccess: False" << endl;
			return result;
		}
		else if (!(*transition->GetNextStates())[i]->first->IsLiteral())
		{
			cout << "\t\tSuccess: Not Literal" << endl;
			result = ConsumeCode(tree, grammar, state, (*transition->GetNextStates())[i]->first, code, codeIndex, recurse > 0 ? recurse - 1 : 0);
			codeIndex = result->GetIndex();
			if (!result->IsSuccess())
			{
				result->SetSuccess(false);
				cout << "\t\tSuccess: False" << endl;
				return result;
			}
		}
		else
		{
			cout << "\t\tSuccess: True" << endl;
		}
		codeIndex++;
		result->SetIndex(codeIndex);
	}
	return result;
}