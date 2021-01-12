#include<Compiler/MiddleEnd/ConsumptionResult.h>

ConsumptionResult::ConsumptionResult(int index, bool success, GrammarState* state)
{
	SetIndex(index);
	SetSuccess(success);
	SetGrammarState(state);
}

void ConsumptionResult::AddMessage(Message* m)
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

vector<Message*>* ConsumptionResult::GetMessages()
{
	return SemanticMessages;
}

void ConsumptionResult::SetIndex(int index)
{
	if (index >= 0)
	{
		Index = index;
	}
	else
	{
		throw invalid_argument("Lower zero indexes are not accepted at ConsumptionResult.");
	}
}

int ConsumptionResult::GetIndex()
{
	return Index;
}

void ConsumptionResult::SetSuccess(bool success)
{
	Success = success;
}

bool ConsumptionResult::IsSuccess()
{
	return Success;
}

void ConsumptionResult::SetGrammarState(GrammarState* state)
{
	State = state;
}

GrammarState* ConsumptionResult::GetGrammarState()
{
	return State;
}