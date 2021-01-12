#include <Compiler/BytreandCompiler.h>

#include <Compiler/MiddleEnd/Grammar.h>
#include <Compiler/MiddleEnd/Languages/C/CGrammar.h>

Grammar::Grammar(int code, TokenCursor* cursor, GrammarTokenFlow* tokenFlow)
{
	SetLanguageCode(code);
	SetTokenCursor(cursor);
	SetTokenFlow(tokenFlow);
}

void Grammar::SetRootState(GrammarState* rootState)
{
	RootState = rootState;
}

void Grammar::SetLanguageCode(int code)
{
	if (code >= BytreandCompiler::C && code <= BytreandCompiler::Bytreand)
	{
		LanguageCode = code;
	}
	else
	{
		throw invalid_argument("Invalid input language \"" + StringUtils::ToString(code) + "\".");
	}
}

int Grammar::GetLanguageCode()
{
	return LanguageCode;
}

string Grammar::GetLanguageName()
{
	return BytreandCompiler::GetLanguage(LanguageCode);
}

void Grammar::SetTokenCursor(TokenCursor* cursor)
{
	if (cursor != NULL)
	{
		Cursor = cursor;
	}
	else
	{
		throw invalid_argument("The language name must never have a null TokenCursor.");
	}
}

TokenCursor* Grammar::GetTokenCursor()
{
	return Cursor;
}

GrammarState* Grammar::GetRootState()
{
	return RootState;
}

bool Grammar::IsDataTypeOrVariable(string token)
{
	for (string s : GetAllButDataTypesAndVariables())
	{
		if (s.compare(token) == 0)
		{
			return false;
		}
	}
	return true;
}

bool Grammar::IsIdentifier(string token)
{
	for (string s : GetTokenCursor()->GetReservedTokens())
	{
		if (s.compare(token) == 0)
		{
			return false;
		}
	}
	return true;
}

Grammar* Grammar::GetGrammar(TokenCursor* cursor)
{
	Grammar* grammar;
	grammar = new CGrammar(cursor->GetFrontEndLanguage(), cursor);
	grammar->SetRootState(grammar->FillGrammar());

	return grammar;
}

void Grammar::AddDeclaredState(GrammarState* state)
{
	if (state != NULL)
	{
		if (GetDeclaredState(state->GetName(), state->GetType()) == NULL)
		{
			DeclaredStates->push_back(state);
		}
		else
		{
			throw invalid_argument("Duplicated GrammarStates are now allowed at Grammar DeclaredStates. Duplicated GrammarState: \"" + state->GetName() + " (" + StringUtils::ToString(state->GetType()) + ")\".");
		}
	}
	else
	{
		throw invalid_argument("NULL GrammarStates are now allowed at Grammar DeclaredStates.");
	}
}

GrammarState* Grammar::GetDeclaredState(string name, int type)
{
	int idx = VectorUtils::IndexOf(new GrammarState(name, type), DeclaredStates);
	return idx >= 0 ? (*DeclaredStates)[idx] : NULL;
}

void Grammar::SetTokenFlow(GrammarTokenFlow* tokenFlow)
{
	if (tokenFlow != NULL)
	{
		TokenFlow = tokenFlow;
	}
	else
	{
		throw invalid_argument("NULL GrammarTokenFlow is now allowed at Grammar.");
	}
}

GrammarTokenFlow* Grammar::GetTokenFlow()
{
	return TokenFlow;
}

vector<int> Grammar::TransitionDecision(StateTransition* transition, GrammarState* parentState, vector<FrontEndToken*>* code, int codeIndex)
{
	vector<int> ret;
	for (int i = 0; i < transition->GetNextStates()->size(); i++)
	{
		if (NodeDecision(parentState, (*transition->GetNextStates())[i]->first, code, codeIndex))
		{
			ret.push_back(i);
		}
	}
	return ret;
}

GrammarState* Grammar::AddLiteralState(string name, int type)
{
	GrammarState* state = GetDeclaredState(name, type);

	if (state == NULL)
	{
		state = new GrammarState(name, type, true);
		AddDeclaredState(state);
	}

	return state;
}

GrammarState* Grammar::AddLiteralState(string name, int type, int associativityType)
{
	GrammarState* state = GetDeclaredState(name, type);

	if (state == NULL)
	{
		state = new GrammarState(name, type, associativityType, true);
		AddDeclaredState(state);
	}

	return state;
}