#include <Compiler/MiddleEnd/GrammarTokenFlow.h>

GrammarTokenFlow::GrammarTokenFlow(Grammar* relatedGrammar)
{
	SetRelatedGrammar(relatedGrammar);
}

void GrammarTokenFlow::SetRelatedGrammar(Grammar* relatedGrammar)
{
	if (relatedGrammar != NULL)
	{
		RelatedGrammar = relatedGrammar;
	}
	else
	{
		throw invalid_argument("It is not possible to set a NULL related grammar at GrammarTokenFlow.");
	}
}

Grammar* GrammarTokenFlow::GetRelatedGrammar()
{
	return RelatedGrammar;
}

/*
	Adds the accepted tokens of the whole state, including the accepted tokens of lower levels of grammar structure at all the state transitions and its grammar states.
*/
void GrammarTokenFlow::AddAcceptedTokens(GrammarState* state)
{
	for (int i = 0; i < state->GetNextTransitions()->size(); i++)
	{
		vector<pair<int, pair<GrammarState*, vector<CategorizedToken*>*>*>*>* acceptedTokens = GetAcceptedTokens(state);
		vector<pair<GrammarState*, vector<CategorizedToken*>*>*> transitionFlow = GetStateTransitionFlow(acceptedTokens, i);
		for (int j = 0; j < (*state->GetNextTransitions())[i]->GetNextStates()->size(); j++)
		{
			vector<CategorizedToken*>* stateFlow = GetGrammarStateFlow(transitionFlow, (*(*state->GetNextTransitions())[i]->GetNextStates())[j]->first);
			VectorUtils::CopyValues(stateFlow, (*state->GetNextTransitions())[i]->GetAcceptedTokens(j));
		}
	}
}

void GrammarTokenFlow::PushNewFlow(vector<pair<int, pair<GrammarState*, vector<CategorizedToken*>*>*>*>* vec, int stateTransitionIndex, GrammarState* state, vector<CategorizedToken*>* acceptedTokens)
{
	if (vec != NULL && stateTransitionIndex >= 0 && state != NULL && acceptedTokens != NULL)
	{
		vec->push_back(&make_pair(stateTransitionIndex, &make_pair(state, acceptedTokens)));
	}
	else if(vec == NULL)
	{
		throw invalid_argument("Tt is not possible to add the new flow at a NULL vector.");
	}
	else if (stateTransitionIndex < 0)
	{
		throw invalid_argument("Tt is not possible to add the new flow with a lower zero state transition index.");
	}
	else if (state == NULL)
	{
		throw invalid_argument("Tt is not possible to add the new flow within a NULL state.");
	}
	else
	{
		throw invalid_argument("Tt is not possible to add the new flow within a NULL vector of accepted tokens.");
	}
}

vector<pair<GrammarState*, vector<CategorizedToken*>*>*> GrammarTokenFlow::GetStateTransitionFlow(vector<pair<int, pair<GrammarState*, vector<CategorizedToken*>*>*>*>* vec, int stateTransitionIndex)
{
	vector<pair<GrammarState*, vector<CategorizedToken*>*>*> ret;
	if (vec != NULL && stateTransitionIndex >= 0)
	{
		for (int i = 0; i < vec->size(); i++)
		{
			if ((*vec)[i]->first == stateTransitionIndex)
			{
				ret.push_back((*vec)[i]->second);
			}
		}
	}
	else if (vec == NULL)
	{
		throw invalid_argument("Tt is not possible to get the flow at a NULL vector.");
	}
	else
	{
		throw invalid_argument("Tt is not possible to get the flow with a lower zero state transition index.");
	}
	return ret;
}

vector<CategorizedToken*>* GrammarTokenFlow::GetGrammarStateFlow(vector<pair<GrammarState*, vector<CategorizedToken*>*>*> vec, GrammarState* state)
{
	if (state != NULL)
	{
		for (pair<GrammarState*, vector<CategorizedToken*>*>* p : vec)
		{
			if (p->first->GetType() == state->GetType())
			{
				return p->second;
			}
		}
	}
	else
	{
		throw invalid_argument("Tt is not possible to get the transition state flow with NULL GrammarState.");
	}
	return NULL;
}