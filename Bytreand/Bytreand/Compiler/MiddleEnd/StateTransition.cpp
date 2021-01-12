#include <Compiler/MiddleEnd/StateTransition.h>

StateTransition::StateTransition() : Comparable()
{

}

StateTransition::StateTransition(string token) : Comparable()
{
	SetName(token);
}

void StateTransition::SetName(string name)
{
	Name = name;
}

string StateTransition::GetName()
{
	return Name;
}

void StateTransition::AddNextState(GrammarState* state)
{
	if (state != NULL)
	{
		NextStates->push_back(&make_pair(state, new vector<CategorizedToken*>()));
		/*if (GetNextState(state->GetName(), GetNextStates().size() - 1) == NULL)//Ignored for now because there are some transitions that must have duplicated ones. Maybe in next implementations this commented block will be removed.
		{
			NextStates.push_back(state);
		}
		else
		{
			throw invalid_argument("The duplicated next state \"" + state->GetName() + "\" is not allowed at the StateTransition" + (StringUtils::IsEmpty(GetName()) ? "" : " \"" + GetName() + "\"") + ".");
		}*/
	}
	else
	{
		throw invalid_argument("NULL next state are not allowed at the StateTransition" + (StringUtils::IsEmpty(GetName()) ? "" : " \"" + GetName() + "\"") +  ".");
	}
}

GrammarState* StateTransition::GetNextState(string name, int  startSearch)
{
	startSearch = startSearch < 0 ? 0 : startSearch;
	for (int i = startSearch; i < NextStates->size(); i++)
	{
		if ((*NextStates)[i]->first->GetName().compare(name) == 0)
		{
			return (*NextStates)[i]->first;
		}
	}
	return NULL;
}

vector<pair<GrammarState*, vector<CategorizedToken*>*>*>* StateTransition::GetNextStates()
{
	return NextStates;
}

bool StateTransition::HasNextStates()
{
	return NextStates->size() > 0;
}

bool StateTransition::CompareStateAndToken(int nextStateIndex, FrontEndToken* token)
{
	if (nextStateIndex >= 0 && nextStateIndex < NextStates->size() && token != NULL)
	{
		return (*NextStates)[nextStateIndex]->first->IsLiteral() && StringUtils::Equals((*NextStates)[nextStateIndex]->first->GetName(), token->GetValue());
	}
	else if(nextStateIndex < 0 || nextStateIndex >= NextStates->size())
	{
		throw invalid_argument("The comparison between GrammarState and FrontEndToken at StateTransition does not allow GrammarState index lower than zero or higher than the vector size. Current value " +
			StringUtils::ToString(nextStateIndex) + " of " + StringUtils::ToString(NextStates->size()) + ".");
	}
	else
	{
		throw invalid_argument("The comparison between GrammarState and FrontEndToken at StateTransition does not allow null FrontEndToken.");
	}
}

void StateTransition::AddAcceptedToken(CategorizedToken* token, int stateIndex)
{
	if (token != NULL && stateIndex >= 0 && stateIndex <= NextStates->size() && GetAcceptedToken(token->GetType(), token->IsPointer(), stateIndex))
	{
		(*NextStates)[stateIndex]->second->push_back(token);
	}
	else if (token == NULL)
	{
		throw invalid_argument("An accepted token must never be null at a GrammarState.");
	}
	else if (stateIndex < 0 || stateIndex >= NextStates->size())
	{
		throw invalid_argument("An accepted token must never have a token index lower than zero or higher than the maximum next states size. Current value: \"" + StringUtils::ToString(stateIndex) + "\".");
	}
	else
	{
		throw invalid_argument("An accepted token must never be duplicated. Duplicated token: \"" + token->GetToken() + "\" at index \"" + StringUtils::ToString(stateIndex) + "\".");
	}
}

CategorizedToken* StateTransition::GetAcceptedToken(int type, bool pointer, int stateIndex)
{
	for (CategorizedToken* token : (*(*NextStates)[stateIndex]->second))
	{
		if (token->GetType() == type && token->IsPointer() == pointer)
		{
			return token;
		}
	}
	return NULL;
}

vector<CategorizedToken*>* StateTransition::GetAcceptedTokens(int stateIndex)
{
	return (*NextStates)[stateIndex]->second;
}

bool StateTransition::IsAcceptedToken(SemanticTree* tree, Grammar* grammar, GrammarState* parent, GrammarState* state, vector<FrontEndToken*>* code, int codeIndex, int stateIndex)
{
	//Implement this method based on the AccpetList, that must be previously filled.
	for (CategorizedToken* token : (*(*NextStates)[stateIndex]->second))
	{
		for (CategorizedToken* child : (*CategorizedToken::GetCategorizedTokenChildren(token)))
		{
			if (StringUtils::Equals(child->GetToken(), (*code)[codeIndex]->GetValue()))
			{
				return true;
			}
		}
	}
	return false;
}