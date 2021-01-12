#include <Tools/VectorUtils.h>

#include <Compiler/MiddleEnd/GrammarState.h>
#include <Compiler/MiddleEnd/Grammar.h>

GrammarState::GrammarState(string name, int type) : Comparable()
{
	SetName(name);
	SetType(type);
}

GrammarState::GrammarState(string name, int type, int associativityType) : Comparable()
{
	SetName(name);
	SetType(type);
	SetAssociativityType(associativityType);
}

GrammarState::GrammarState(string name, int type, bool literal) : Comparable()
{
	SetName(name);
	SetType(type);
	SetLiteral(literal);
}

GrammarState::GrammarState(string name, int type, int associativityType, bool literal) : Comparable()
{
	SetName(name);
	SetType(type);
	SetAssociativityType(associativityType);
	SetLiteral(literal);
}

void GrammarState::SetName(string name)
{
	Name = name;
}

string GrammarState::GetName()
{
	return Name;
}

void GrammarState::SetType(int type)
{
	if (type >= Grammar::StateType::PrimaryExpression && type <= Grammar::StateType::TypeQualifierControl)
	{
		Type = type;
	}
	else
	{
		throw invalid_argument("The type \"" + StringUtils::ToString(type) + "\" is not allowed at GrammarState \"" + GetName() + "\". Allowed types are between " + StringUtils::ToString(Grammar::StateType::PrimaryExpression) + " and " + StringUtils::ToString(Grammar::StateType::TypeQualifierControl) + ".");
	}
}

int GrammarState::GetType()
{
	return Type;
}

void GrammarState::SetAssociativityType(int associativityType)
{
	if (associativityType == LeftToRight || associativityType == RightToLeft)
	{
		AssociativityType = associativityType;
	}
	else
	{
		throw invalid_argument("Associativity type \"" + StringUtils::ToString(associativityType) + " is not allowed at GrammarState \"" + GetName() + "\".");
	}
}

int GrammarState::GetAssociativityType()
{
	return AssociativityType;
}

void GrammarState::AddNextTransition(StateTransition* transition)
{
	if(!VectorUtils::Exists(transition, NextTransitions))
	{
		NextTransitions->push_back(transition);
	}
	else
	{
		throw invalid_argument("Duplicated next transition \"" + transition->GetName() + "\" (" + StringUtils::ToString(transition->GetHash()) + ") is not allowed at GrammarState \"" + GetName() + "\".");
	}
}

bool GrammarState::HasNextTransition(string token, string name)
{
	for (StateTransition* t : (*GetNextTransitions()))
	{
		if (StringUtils::Equals(t->GetName(), token) && t->GetNextState(name, 0) != NULL)
		{
			return true;
		}
	}
	return false;
}

StateTransition* GrammarState::GetNextTransition(string token, string name, int startSearch)
{
	for (StateTransition* t : (*GetNextTransitions()))
	{
		if (StringUtils::Equals(t->GetName(), token) && t->GetNextState(name, startSearch) != NULL)
		{
			return t;
		}
	}
	return NULL;
}

vector<StateTransition*>* GrammarState::GetNextTransitions()
{
	return NextTransitions;
}

GrammarState* GrammarState::GetNextState(int transitionIndex, int stateIndex)
{
	return (*(*NextTransitions)[transitionIndex]->GetNextStates())[stateIndex]->first;
}

void GrammarState::AddPreviousTransition(StateTransition* transition)
{
	if (!VectorUtils::Exists(transition, PreviousTransitions))
	{
		PreviousTransitions->push_back(transition);
	}
	else
	{
		throw invalid_argument("Duplicated previous transition \"" + transition->GetName() + "\" (" + StringUtils::ToString(transition->GetHash()) + ") is not allowed at GrammarState.");
	}
}

bool GrammarState::HasPreviousTransition(string token, string name)
{
	for (StateTransition* t : (*GetPreviousTransitions()))
	{
		if (StringUtils::Equals(t->GetName(), token) && t->GetNextState(name, 0) != NULL)
		{
			return true;
		}
	}
	return false;
}
StateTransition* GrammarState::GetPreviousTransition(string token, string name, int startSearch)
{
	for (StateTransition* t : (*GetPreviousTransitions()))
	{
		if (StringUtils::Equals(t->GetName(), token) && t->GetNextState(name, startSearch) != NULL)
		{
			return t;
		}
	}
	return NULL;
}

vector<StateTransition*>* GrammarState::GetPreviousTransitions()
{
	return PreviousTransitions;
}

bool GrammarState::IsFinalState()
{
	return NextTransitions->size() == 0;
}

void GrammarState::SetLiteral(bool literal)
{
	Literal = literal;
}

bool GrammarState::IsLiteral()
{
	return Literal;
}

bool GrammarState::Equals(Comparable* c)
{
	if (GrammarState* state = static_cast<GrammarState*>(c))
	{
		return StringUtils::Equals(GetName(), state->GetName()) && GetType() == state->GetType();
	}
	else
	{
		return false;
	}
}