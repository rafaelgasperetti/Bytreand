#include <Compiler/MiddleEnd/Languages/C/CGrammar.h>
#include <Compiler/MiddleEnd/Languages/C/CGrammarTokenFlow.h>

const string CGrammar::HASH_TAG_CONTROL = "#";
const string CGrammar::INCLUDE_CONTROL = "include";
const string CGrammar::DEFINE_CONTROL = "define";
const string CGrammar::LESS_THAN_OPERATION = "<";
const string CGrammar::GREATER_THAN_OPERATION = ">";
const string CGrammar::END_CONTROL = ";";

CGrammar::CGrammar(int code, TokenCursor* cursor) : Grammar(code, cursor, (GrammarTokenFlow*) new CGrammarTokenFlow(this))
{

}

bool CGrammar::NodeDecision(GrammarState* parentState, GrammarState* state, vector<FrontEndToken*>* code, int codeIndex)
{
	if (StringUtils::Equals((*code)[codeIndex]->GetValue(), CGrammar::HASH_TAG_CONTROL))
	{
		if
		(
			state->GetType() == Grammar::StateType::ExternalDefinition ||
			state->GetType() == Grammar::StateType::ExternalInclusionExpression ||
			(StringUtils::Equals(state->GetName(), CGrammar::HASH_TAG_CONTROL) && state->GetType() == Grammar::StateType::Control)
		)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else if ((*code)[codeIndex]->GetType() == FrontEndToken::FrontEndTokenType::Identifier)
	{
		switch (state->GetType())
		{
			case CGrammar::StateType::LogicalOrExpression:
				return true;
			case CGrammar::StateType::LogicalAndExpression:
				return true;
			case CGrammar::StateType::InclusiveOrExpression:
				return true;
			case CGrammar::StateType::ExclusiveOrExpression:
				return true;
			case CGrammar::StateType::AndExpression:
				return true;
			default:
				return false;
		}
	}
	else
	{
		return false;
	}
}

GrammarState* CGrammar::FillGrammar()
{
	return GetTranslationUnit();
}

vector<string> CGrammar::GetDataModifiers()
{
	return
	{
		"const","extern","signed","static","unsigned","volatile"
	};
}

vector<string> CGrammar::GetDataTypes()
{
	return
	{
		"auto","char","double","enum","float","int","long","short","struct","void"
	};
}

vector<string> CGrammar::GetAllButDataTypesAndVariables()
{
	return
	{
		"break","case","const","continue","default","define","do","else","extern","for","goto","if","return","signed",
		"sizeof","static","switch","typedef","union","unsigned","volatile","while"
	};
}

vector<string> CGrammar::GetAllButIdentifiers()
{
	return
	{
		"break","case","const","continue","default","define","do","else","extern","for","goto","if","return","signed",
		"sizeof","static","switch","typedef","union","unsigned","volatile","while"
	};
}

GrammarState* CGrammar::GetPrimaryExpression()
{
	string stateName = "PrimaryExpression";
	int stateType = StateType::PrimaryExpression;

	GrammarState* state = GetDeclaredState(stateName, stateType);

	if (state == NULL)
	{
		state = new GrammarState(stateName, stateType);
		AddDeclaredState(state);

		GrammarState* identifier = GetIdentifier();
		GrammarState* constant = GetConstant();
		GrammarState* stringLiteral = GetStringLiteral();
		GrammarState* expression = GetExpression();

		StateTransition* transition1 = new StateTransition("Transition 1");
		transition1->AddNextState(identifier);

		StateTransition* transition2 = new StateTransition("Transition 2");
		transition2->AddNextState(constant);

		StateTransition* transition3 = new StateTransition("Transition 3");
		transition3->AddNextState(stringLiteral);

		StateTransition* transition4 = new StateTransition("Transition 4");
		transition4->AddNextState(expression);

		state->AddNextTransition(transition1);
		state->AddNextTransition(transition2);
		state->AddNextTransition(transition3);
		state->AddNextTransition(transition4);

		GetTokenFlow()->AddAcceptedTokens(state);
	}

	return state;
}

GrammarState* CGrammar::GetPostfixExpression()
{
	string stateName = "PostfixExpression";
	int stateType = StateType::PostfixExpression;

	GrammarState* state = GetDeclaredState(stateName, stateType);

	if (state == NULL)
	{
		state = new GrammarState(stateName, stateType);
		AddDeclaredState(state);

		GrammarState* primaryExpression = GetPrimaryExpression();
		GrammarState* expression = GetExpression();
		GrammarState* argumentExpressionList = GetArgumentExpressionList();
		GrammarState* openBracketControl = GetOpenBracketControl();
		GrammarState* closeBracketControl = GetCloseBracketControl();
		GrammarState* openParenthesesControl = GetOpenParenthesesControl();
		GrammarState* closeParenthesesControl = GetCloseParenthesesControl();
		GrammarState* dotControl = GetDotControl();
		GrammarState* identifier = GetIdentifier();
		GrammarState* pointerOperation = GetPointerOperation();
		GrammarState* incrementOperation = GetIncrementOperation();
		GrammarState* decrementOperation = GetDecrementOperation();

		StateTransition* transition1 = new StateTransition("Transition 1");
		transition1->AddNextState(primaryExpression);

		StateTransition* transition2 = new StateTransition("Transition 2");
		transition2->AddNextState(state);
		transition2->AddNextState(openBracketControl);
		transition2->AddNextState(expression);
		transition2->AddNextState(closeBracketControl);

		StateTransition* transition3 = new StateTransition("Transition 3");
		transition3->AddNextState(state);
		transition3->AddNextState(openParenthesesControl);
		transition3->AddNextState(closeParenthesesControl);

		StateTransition* transition4 = new StateTransition("Transition 4");
		transition4->AddNextState(state);
		transition4->AddNextState(openParenthesesControl);
		transition4->AddNextState(argumentExpressionList);
		transition4->AddNextState(closeParenthesesControl);

		StateTransition* transition5 = new StateTransition("Transition 5");
		transition5->AddNextState(state);
		transition5->AddNextState(dotControl);
		transition5->AddNextState(identifier);

		StateTransition* transition6 = new StateTransition("Transition 6");
		transition6->AddNextState(state);
		transition6->AddNextState(pointerOperation);
		transition6->AddNextState(identifier);

		StateTransition* transition7 = new StateTransition("Transition 7");
		transition7->AddNextState(state);
		transition7->AddNextState(incrementOperation);

		StateTransition* transition8 = new StateTransition("Transition 8");
		transition8->AddNextState(state);
		transition8->AddNextState(decrementOperation);

		state->AddNextTransition(transition1);
		state->AddNextTransition(transition2);
		state->AddNextTransition(transition3);
		state->AddNextTransition(transition4);
		state->AddNextTransition(transition5);
		state->AddNextTransition(transition6);
		state->AddNextTransition(transition7);
		state->AddNextTransition(transition8);

		GetTokenFlow()->AddAcceptedTokens(state);
	}

	return state;
}

GrammarState* CGrammar::GetArgumentExpressionList()
{
	string stateName = "ArgumentxExpressionList";
	int stateType = StateType::ArgumentExpressionList;

	GrammarState* state = GetDeclaredState(stateName, stateType);

	if (state == NULL)
	{
		state = new GrammarState(stateName, stateType);
		AddDeclaredState(state);

		GrammarState* assignmentExpression = GetAssignmentExpression();
		GrammarState* commaControl = GetCommaControl();

		StateTransition* transition1 = new StateTransition("Transition 1");
		transition1->AddNextState(assignmentExpression);

		StateTransition* transition2 = new StateTransition("Transition 2");
		transition2->AddNextState(state);
		transition2->AddNextState(commaControl);
		transition2->AddNextState(assignmentExpression);

		state->AddNextTransition(transition1);
		state->AddNextTransition(transition2);

		GetTokenFlow()->AddAcceptedTokens(state);
	}

	return state;
}

GrammarState* CGrammar::GetUnaryExpression()
{
	string stateName = "UnaryExpression";
	int stateType = StateType::UnaryExpression;

	GrammarState* state = GetDeclaredState(stateName, stateType);

	if (state == NULL)
	{
		state = new GrammarState(stateName, stateType);
		AddDeclaredState(state);

		GrammarState* postfixExpression = GetPostfixExpression();
		GrammarState* incrementOperation = GetIncrementOperation();
		GrammarState* decrementOperation = GetDecrementOperation();
		GrammarState* unaryOperator = GetUnaryOperator();
		GrammarState* castExpression = GetCastExpression();
		GrammarState* sizeOfOperation = GetSizeOfControl();
		GrammarState* typeName = GetTypeName();

		StateTransition* transition1 = new StateTransition("Transition 1");
		transition1->AddNextState(postfixExpression);

		StateTransition* transition2 = new StateTransition("Transition 2");
		transition2->AddNextState(incrementOperation);
		transition2->AddNextState(state);

		StateTransition* transition3 = new StateTransition("Transition 3");
		transition3->AddNextState(decrementOperation);
		transition3->AddNextState(state);

		StateTransition* transition4 = new StateTransition("Transition 4");
		transition4->AddNextState(unaryOperator);
		transition4->AddNextState(state);

		StateTransition* transition5 = new StateTransition("Transition 5");
		transition5->AddNextState(sizeOfOperation);
		transition5->AddNextState(state);

		StateTransition* transition6 = new StateTransition("Transition 6");
		transition6->AddNextState(sizeOfOperation);
		transition6->AddNextState(typeName);

		state->AddNextTransition(transition1);
		state->AddNextTransition(transition2);
		state->AddNextTransition(transition3);
		state->AddNextTransition(transition4);
		state->AddNextTransition(transition5);
		state->AddNextTransition(transition6);

		GetTokenFlow()->AddAcceptedTokens(state);
	}
	
	return state;
}

GrammarState* CGrammar::GetUnaryOperator()
{
	string stateName = "UnaryOperator";
	int stateType = StateType::UnaryOperator;

	GrammarState* state = GetDeclaredState(stateName, stateType);

	if (state == NULL)
	{
		state = new GrammarState(stateName, stateType);
		AddDeclaredState(state);

		GrammarState* bitwiseAndOperation = GetBitwiseAndOperation();
		GrammarState* multiplicationOperation = GetMultiplicationOperation();
		GrammarState* sumOperation = GetSumOperation();
		GrammarState* subtractionOperation = GetSubtractionOperation();
		GrammarState* divisionOperation = GetDivisionOperation();
		GrammarState* bitwiseNotOperation = GetBitwiseNotOperation();
		GrammarState* notOperation = GetNotOperation();

		StateTransition* transition1 = new StateTransition("Transition 1");
		transition1->AddNextState(bitwiseAndOperation);

		StateTransition* transition2 = new StateTransition("Transition 2");
		transition2->AddNextState(multiplicationOperation);

		StateTransition* transition3 = new StateTransition("Transition 3");
		transition3->AddNextState(sumOperation);

		StateTransition* transition4 = new StateTransition("Transition 4");
		transition4->AddNextState(subtractionOperation);

		StateTransition* transition5 = new StateTransition("Transition 5");
		transition5->AddNextState(divisionOperation);

		StateTransition* transition6 = new StateTransition("Transition 6");
		transition6->AddNextState(bitwiseNotOperation);

		StateTransition* transition7 = new StateTransition("Transition 7");
		transition7->AddNextState(notOperation);

		state->AddNextTransition(transition1);
		state->AddNextTransition(transition2);
		state->AddNextTransition(transition3);
		state->AddNextTransition(transition4);
		state->AddNextTransition(transition5);
		state->AddNextTransition(transition6);
		state->AddNextTransition(transition7);

		GetTokenFlow()->AddAcceptedTokens(state);
	}

	return state;
}

GrammarState* CGrammar::GetCastExpression()
{
	string stateName = "CastExpression";
	int stateType = StateType::CastExpression;

	GrammarState* state = GetDeclaredState(stateName, stateType);

	if (state == NULL)
	{
		state = new GrammarState(stateName, stateType);
		AddDeclaredState(state);

		GrammarState* unaryExpression = GetUnaryExpression();
		GrammarState* openParentheses = GetOpenParenthesesControl();
		GrammarState* typeName = GetTypeName();
		GrammarState* closeParentheses = GetCloseParenthesesControl();

		StateTransition* transition1 = new StateTransition("Transition 1");
		transition1->AddNextState(unaryExpression);

		StateTransition* transition2 = new StateTransition("Transition 2");
		transition2->AddNextState(openParentheses);
		transition2->AddNextState(typeName);
		transition2->AddNextState(closeParentheses);
		transition2->AddNextState(state);

		state->AddNextTransition(transition1);
		state->AddNextTransition(transition2);

		GetTokenFlow()->AddAcceptedTokens(state);
	}

	return state;
}

GrammarState* CGrammar::GetMultiplicativeExpression()
{
	string stateName = "MultiplicativeExpression";
	int stateType = StateType::MultiplicativeExpression;

	GrammarState* state = GetDeclaredState(stateName, stateType);

	if (state == NULL)
	{
		state = new GrammarState(stateName, stateType);
		AddDeclaredState(state);

		GrammarState* castExpression = GetCastExpression();
		GrammarState* multiplicationOperation = GetMultiplicationOperation();
		GrammarState* divisionOperation = GetDivisionOperation();
		GrammarState* modOperation = GetModOperation();

		StateTransition* transition1 = new StateTransition("Transition 1");
		transition1->AddNextState(castExpression);

		StateTransition* transition2 = new StateTransition("Transition 2");
		transition2->AddNextState(state);
		transition2->AddNextState(multiplicationOperation);
		transition2->AddNextState(castExpression);

		StateTransition* transition3 = new StateTransition("Transition 3");
		transition3->AddNextState(state);
		transition3->AddNextState(divisionOperation);
		transition3->AddNextState(castExpression);

		StateTransition* transition4 = new StateTransition("Transition 4");
		transition4->AddNextState(state);
		transition4->AddNextState(modOperation);
		transition4->AddNextState(castExpression);

		state->AddNextTransition(transition1);
		state->AddNextTransition(transition2);
		state->AddNextTransition(transition3);
		state->AddNextTransition(transition4);

		GetTokenFlow()->AddAcceptedTokens(state);
	}

	return state;
}

GrammarState* CGrammar::GetAdditiveExpression()
{
	string stateName = "AdditiveExpression";
	int stateType = StateType::AdditiveExpression;

	GrammarState* state = GetDeclaredState(stateName, stateType);

	if (state == NULL)
	{
		state = new GrammarState(stateName, stateType);
		AddDeclaredState(state);

		GrammarState* multiplicativeExpression = GetMultiplicativeExpression();
		GrammarState* sumOperation = GetSumOperation();
		GrammarState* subtractionOperation = GetSubtractionOperation();

		StateTransition* transition1 = new StateTransition("Transition 1");
		transition1->AddNextState(multiplicativeExpression);

		StateTransition* transition2 = new StateTransition("Transition 2");
		transition2->AddNextState(state);
		transition2->AddNextState(sumOperation);
		transition2->AddNextState(multiplicativeExpression);

		StateTransition* transition3 = new StateTransition("Transition 3");
		transition3->AddNextState(state);
		transition3->AddNextState(subtractionOperation);
		transition3->AddNextState(multiplicativeExpression);

		state->AddNextTransition(transition1);
		state->AddNextTransition(transition2);
		state->AddNextTransition(transition3);

		GetTokenFlow()->AddAcceptedTokens(state);
	}

	return state;
}

GrammarState* CGrammar::GetShiftExpression()
{
	string stateName = "ShiftExpression";
	int stateType = StateType::ShiftExpression;

	GrammarState* state = GetDeclaredState(stateName, stateType);

	if (state == NULL)
	{
		state = new GrammarState(stateName, stateType);
		AddDeclaredState(state);

		GrammarState* additiveExpression = GetAdditiveExpression();
		GrammarState* multiplicativeExpression = GetMultiplicativeExpression();
		GrammarState* rightOperation = GetRightOperation();
		GrammarState* leftOperation = GetLeftOpreation();

		StateTransition* transition1 = new StateTransition("Transition 1");
		transition1->AddNextState(additiveExpression);

		StateTransition* transition2 = new StateTransition("Transition 2");
		transition2->AddNextState(state);
		transition2->AddNextState(rightOperation);
		transition2->AddNextState(additiveExpression);

		StateTransition* transition3 = new StateTransition("Transition 3");
		transition3->AddNextState(state);
		transition3->AddNextState(leftOperation);
		transition3->AddNextState(additiveExpression);

		state->AddNextTransition(transition1);
		state->AddNextTransition(transition2);
		state->AddNextTransition(transition3);

		GetTokenFlow()->AddAcceptedTokens(state);
	}

	return state;
}

GrammarState* CGrammar::GetRelationalExpression()
{
	string stateName = "RelationalExpression";
	int stateType = StateType::RelationalExpression;

	GrammarState* state = GetDeclaredState(stateName, stateType);

	if (state == NULL)
	{
		state = new GrammarState(stateName, stateType);
		AddDeclaredState(state);

		GrammarState* shiftExpression = GetShiftExpression();
		GrammarState* lessOperation = GetLessThanOperation();
		GrammarState* greaterOperation = GetGreaterThanOperation();
		GrammarState* lessEqualsOperation = GetLessEqualOperation();
		GrammarState* greaterEqualsOperation = GetGreaterEqualOperation();

		StateTransition* transition1 = new StateTransition("Transition 1");
		transition1->AddNextState(shiftExpression);

		StateTransition* transition2 = new StateTransition("Transition 2");
		transition2->AddNextState(state);
		transition2->AddNextState(lessOperation);
		transition2->AddNextState(shiftExpression);

		StateTransition* transition3 = new StateTransition("Transition 3");
		transition3->AddNextState(state);
		transition3->AddNextState(greaterOperation);
		transition3->AddNextState(shiftExpression);

		StateTransition* transition4 = new StateTransition("Transition 4");
		transition4->AddNextState(state);
		transition4->AddNextState(lessEqualsOperation);
		transition4->AddNextState(shiftExpression);

		StateTransition* transition5 = new StateTransition("Transition 5");
		transition5->AddNextState(greaterEqualsOperation);
		transition5->AddNextState(shiftExpression);

		state->AddNextTransition(transition1);
		state->AddNextTransition(transition2);
		state->AddNextTransition(transition3);
		state->AddNextTransition(transition4);
		state->AddNextTransition(transition5);

		GetTokenFlow()->AddAcceptedTokens(state);
	}

	return state;
}

GrammarState* CGrammar::GetEqualityExpression()
{
	string stateName = "EqualityExpression";
	int stateType = StateType::EqualityExpression;

	GrammarState* state = GetDeclaredState(stateName, stateType);

	if (state == NULL)
	{
		state = new GrammarState(stateName, stateType);
		AddDeclaredState(state);

		GrammarState* relationalExpression = GetRelationalExpression();
		GrammarState* equalsOperation = GetEqualOperation();
		GrammarState* notEqualsOperation = GetNotEqualOperation();

		StateTransition* transition1 = new StateTransition("Transition 1");
		transition1->AddNextState(relationalExpression);

		StateTransition* transition2 = new StateTransition("Transition 2");
		transition2->AddNextState(state);
		transition2->AddNextState(equalsOperation);
		transition2->AddNextState(relationalExpression);

		StateTransition* transition3 = new StateTransition("Transition 3");
		transition3->AddNextState(state);
		transition3->AddNextState(notEqualsOperation);
		transition3->AddNextState(relationalExpression);

		state->AddNextTransition(transition1);
		state->AddNextTransition(transition2);
		state->AddNextTransition(transition3);

		GetTokenFlow()->AddAcceptedTokens(state);
	}

	return state;
}

GrammarState* CGrammar::GetAndExpression()
{
	string stateName = "AndExpression";
	int stateType = StateType::AndExpression;

	GrammarState* state = GetDeclaredState(stateName, stateType);

	if (state == NULL)
	{
		state = new GrammarState(stateName, stateType);
		AddDeclaredState(state);

		GrammarState* equalityExpression = GetEqualityExpression();
		GrammarState* bitwiseAndOperation = GetBitwiseAndOperation();

		StateTransition* transition1 = new StateTransition("Transition 1");
		transition1->AddNextState(equalityExpression);

		StateTransition* transition2 = new StateTransition("Transition 2");
		transition2->AddNextState(state);
		transition2->AddNextState(bitwiseAndOperation);
		transition2->AddNextState(equalityExpression);

		state->AddNextTransition(transition1);
		state->AddNextTransition(transition2);

		GetTokenFlow()->AddAcceptedTokens(state);
	}

	return state;
}

GrammarState* CGrammar::GetExclusiveOrExpression()
{
	string stateName = "ExclusiveOrExpression";
	int stateType = StateType::ExclusiveOrExpression;

	GrammarState* state = GetDeclaredState(stateName, stateType);

	if (state == NULL)
	{
		state = new GrammarState(stateName, stateType);
		AddDeclaredState(state);

		GrammarState* andExpression = GetAndExpression();
		GrammarState* exclusiveOrOperation = GetExclusiveOrOperation();

		StateTransition* transition1 = new StateTransition("Transition 1");
		transition1->AddNextState(andExpression);

		StateTransition* transition2 = new StateTransition("Transition 2");
		transition2->AddNextState(state);
		transition2->AddNextState(exclusiveOrOperation);
		transition2->AddNextState(andExpression);

		state->AddNextTransition(transition1);
		state->AddNextTransition(transition2);

		GetTokenFlow()->AddAcceptedTokens(state);
	}

	return state;
}

GrammarState* CGrammar::GetInclusiveOrExpression()
{
	string stateName = "InclusiveOrExpression";
	int stateType = StateType::InclusiveOrExpression;

	GrammarState* state = GetDeclaredState(stateName, stateType);

	if (state == NULL)
	{
		state = new GrammarState(stateName, stateType);
		AddDeclaredState(state);

		GrammarState* exclusiveOrExpression = GetExclusiveOrExpression();
		GrammarState* bitwiseOrOperation = GetBitwiseOrOperation();

		StateTransition* transition1 = new StateTransition("Transition 1");
		transition1->AddNextState(exclusiveOrExpression);

		StateTransition* transition2 = new StateTransition("Transition 2");
		transition2->AddNextState(state);
		transition2->AddNextState(bitwiseOrOperation);
		transition2->AddNextState(exclusiveOrExpression);

		state->AddNextTransition(transition1);
		state->AddNextTransition(transition2);

		GetTokenFlow()->AddAcceptedTokens(state);
	}

	return state;
}

GrammarState* CGrammar::GetLogicalAndExpression()
{
	string stateName = "LogicalAndExpression";
	int stateType = StateType::LogicalAndExpression;

	GrammarState* state = GetDeclaredState(stateName, stateType);

	if (state == NULL)
	{
		state = new GrammarState(stateName, stateType);
		AddDeclaredState(state);

		GrammarState* inclusiveOrExpression = GetInclusiveOrExpression();
		GrammarState* andOperation = GetAndOperation();

		StateTransition* transition1 = new StateTransition("Transition 1");
		transition1->AddNextState(inclusiveOrExpression);

		StateTransition* transition2 = new StateTransition("Transition 2");
		transition2->AddNextState(state);
		transition2->AddNextState(andOperation);
		transition2->AddNextState(inclusiveOrExpression);

		state->AddNextTransition(transition1);
		state->AddNextTransition(transition2);

		GetTokenFlow()->AddAcceptedTokens(state);
	}

	return state;
}

GrammarState* CGrammar::GetLogicalOrExpression()
{
	string stateName = "LogicalOrExpression";
	int stateType = StateType::LogicalOrExpression;

	GrammarState* state = GetDeclaredState(stateName, stateType);

	if (state == NULL)
	{
		state = new GrammarState(stateName, stateType);
		AddDeclaredState(state);

		GrammarState* logicalAndExpression = GetLogicalAndExpression();
		GrammarState* orOperation = GetOrOperation();

		StateTransition* transition1 = new StateTransition("Transition 1");
		transition1->AddNextState(logicalAndExpression);

		StateTransition* transition2 = new StateTransition("Transition 2");
		transition2->AddNextState(state);
		transition2->AddNextState(orOperation);
		transition2->AddNextState(logicalAndExpression);

		state->AddNextTransition(transition1);
		state->AddNextTransition(transition2);

		GetTokenFlow()->AddAcceptedTokens(state);
	}

	return state;
}

GrammarState* CGrammar::GetConditionalExpression()
{
	string stateName = "ConditionalExpression";
	int stateType = StateType::ConditionalExpression;

	GrammarState* state = GetDeclaredState(stateName, stateType);

	if (state == NULL)
	{
		state = new GrammarState(stateName, stateType);
		AddDeclaredState(state);

		GrammarState* logicalOrExpression = GetLogicalOrExpression();
		GrammarState* logicalConditionOperation = GetLogicalConditionOperation();
		GrammarState* expression = GetExpression();
		GrammarState* elseConditionOperation = GetElseConditionOperation();

		StateTransition* transition1 = new StateTransition("Transition 1");
		transition1->AddNextState(logicalOrExpression);

		StateTransition* transition2 = new StateTransition("Transition 2");
		transition2->AddNextState(logicalOrExpression);
		transition2->AddNextState(logicalConditionOperation);
		transition2->AddNextState(expression);
		transition2->AddNextState(elseConditionOperation);
		transition2->AddNextState(state);

		state->AddNextTransition(transition1);
		state->AddNextTransition(transition2);

		GetTokenFlow()->AddAcceptedTokens(state);
	}

	return state;
}

GrammarState* CGrammar::GetAssignmentExpression()
{
	string stateName = "AssignmentExpression";
	int stateType = StateType::AssignmentExpression;

	GrammarState* state = GetDeclaredState(stateName, stateType);

	if (state == NULL)
	{
		state = new GrammarState(stateName, stateType);
		AddDeclaredState(state);

		GrammarState* conditionalExpression = GetConditionalExpression();
		GrammarState* unaryExpression = GetUnaryExpression();
		GrammarState* assignmentOperator = GetAssignmentOperator();

		StateTransition* transition1 = new StateTransition("Transition 1");
		transition1->AddNextState(conditionalExpression);

		StateTransition* transition2 = new StateTransition("Transition 2");
		transition2->AddNextState(unaryExpression);
		transition2->AddNextState(assignmentOperator);
		transition2->AddNextState(state);

		state->AddNextTransition(transition1);
		state->AddNextTransition(transition2);

		GetTokenFlow()->AddAcceptedTokens(state);
	}

	return state;
}

GrammarState* CGrammar::GetAssignmentOperator()
{
	string stateName = "AssignmentOperator";
	int stateType = StateType::AssignmentOperator;

	GrammarState* state = GetDeclaredState(stateName, stateType);

	if (state == NULL)
	{
		state = new GrammarState(stateName, stateType);
		AddDeclaredState(state);

		GrammarState* assignmentOperation = GetAssignmentOperation();
		GrammarState* multiplicationAssignmentOperation = GetMultiplicationAssignmentOperation();
		GrammarState* divisionAssignmentOperation = GetDivisionAssignmentOperation();
		GrammarState* modAssignmentOperation = GetModAssignmentOperation();
		GrammarState* additionAssignmentOperation = GetAdditionAssignmentOperation();
		GrammarState* subtractionAssignmentOperation = GetSubtractionAssignmentOperation();
		GrammarState* leftAssignmentOperation = GetLeftAssignmentOperation();
		GrammarState* rightAssignmentOperation = GetRightAssignmentOperation();
		GrammarState* andAssignmentOperation = GetAndAssignmentOperation();
		GrammarState* xorAssignmentOperation = GetXorAssignmentOperation();
		GrammarState* orAssignmentOperation = GetOrAssignmentOperation();

		StateTransition* transition1 = new StateTransition("Transition 1");
		transition1->AddNextState(assignmentOperation);

		StateTransition* transition2 = new StateTransition("Transition 2");
		transition2->AddNextState(multiplicationAssignmentOperation);

		StateTransition* transition3 = new StateTransition("Transition 3");
		transition3->AddNextState(divisionAssignmentOperation);

		StateTransition* transition4 = new StateTransition("Transition 4");
		transition4->AddNextState(modAssignmentOperation);

		StateTransition* transition5 = new StateTransition("Transition 5");
		transition5->AddNextState(additionAssignmentOperation);

		StateTransition* transition6 = new StateTransition("Transition 6");
		transition6->AddNextState(subtractionAssignmentOperation);

		StateTransition* transition7 = new StateTransition("Transition 7");
		transition7->AddNextState(leftAssignmentOperation);

		StateTransition* transition8 = new StateTransition("Transition 8");
		transition8->AddNextState(rightAssignmentOperation);

		StateTransition* transition9 = new StateTransition("Transition 9");
		transition9->AddNextState(andAssignmentOperation);

		StateTransition* transition10 = new StateTransition("Transition 10");
		transition10->AddNextState(xorAssignmentOperation);

		StateTransition* transition11 = new StateTransition("Transition 11");
		transition11->AddNextState(orAssignmentOperation);

		state->AddNextTransition(transition1);
		state->AddNextTransition(transition2);
		state->AddNextTransition(transition3);
		state->AddNextTransition(transition4);
		state->AddNextTransition(transition5);
		state->AddNextTransition(transition6);
		state->AddNextTransition(transition7);
		state->AddNextTransition(transition8);
		state->AddNextTransition(transition9);
		state->AddNextTransition(transition10);
		state->AddNextTransition(transition11);

		GetTokenFlow()->AddAcceptedTokens(state);
	}

	return state;
}

GrammarState* CGrammar::GetExpression()
{
	string stateName = "Expression";
	int stateType = StateType::Expression;

	GrammarState* state = GetDeclaredState(stateName, stateType);

	if (state == NULL)
	{
		state = new GrammarState(stateName, stateType);
		AddDeclaredState(state);

		GrammarState* assignmentExpression = GetAssignmentExpression();

		StateTransition* transition1 = new StateTransition("Transition 1");
		transition1->AddNextState(assignmentExpression);

		StateTransition* transition2 = new StateTransition("Transition 2");
		transition2->AddNextState(state);
		transition2->AddNextState(assignmentExpression);

		state->AddNextTransition(transition1);
		state->AddNextTransition(transition2);

		GetTokenFlow()->AddAcceptedTokens(state);
	}

	return state;
}

GrammarState* CGrammar::GetConstantExpression()
{
	string stateName = "ConstantExpression";
	int stateType = StateType::ConstantExpression;

	GrammarState* state = GetDeclaredState(stateName, stateType);

	if (state == NULL)
	{
		state = new GrammarState(stateName, stateType);
		AddDeclaredState(state);

		GrammarState* conditionalExpression = GetConditionalExpression();

		StateTransition* transition1 = new StateTransition("Transition 1");
		transition1->AddNextState(conditionalExpression);

		state->AddNextTransition(transition1);

		GetTokenFlow()->AddAcceptedTokens(state);
	}

	return state;
}

GrammarState* CGrammar::GetDeclaration()
{
	string stateName = "Declaration";
	int stateType = StateType::Declaration;

	GrammarState* state = GetDeclaredState(stateName, stateType);

	if (state == NULL)
	{
		state = new GrammarState(stateName, stateType);
		AddDeclaredState(state);

		GrammarState* declarationSpecifiers = GetDeclarationSpecifiers();
		GrammarState* initDeclaratorList = GetInitDeclaratorList();
		GrammarState* endControl = GetEndControl();

		StateTransition* transition1 = new StateTransition("Transition 1");
		transition1->AddNextState(declarationSpecifiers);
		transition1->AddNextState(endControl);

		StateTransition* transition2 = new StateTransition("Transition 2");
		transition2->AddNextState(declarationSpecifiers);
		transition2->AddNextState(initDeclaratorList);
		transition2->AddNextState(endControl);

		state->AddNextTransition(transition1);
		state->AddNextTransition(transition2);

		GetTokenFlow()->AddAcceptedTokens(state);
	}

	return state;
}

GrammarState* CGrammar::GetDeclarationSpecifiers()
{
	string stateName = "DeclarationSpecifiers";
	int stateType = StateType::DeclarationSpecifiers;

	GrammarState* state = GetDeclaredState(stateName, stateType);

	if (state == NULL)
	{
		state = new GrammarState(stateName, stateType);
		AddDeclaredState(state);

		GrammarState* storageClassSpecifier = GetStorageClassSpecifier();
		GrammarState* typeSpecifier = GetTypeSpecifier();
		GrammarState* typeQualifier = GetTypeQualifier();

		StateTransition* transition1 = new StateTransition("Transition 1");
		transition1->AddNextState(storageClassSpecifier);

		StateTransition* transition2 = new StateTransition("Transition 2");
		transition2->AddNextState(storageClassSpecifier);
		transition2->AddNextState(state);

		StateTransition* transition3 = new StateTransition("Transition 3");
		transition3->AddNextState(typeSpecifier);

		StateTransition* transition4 = new StateTransition("Transition 4");
		transition4->AddNextState(typeSpecifier);
		transition4->AddNextState(state);

		StateTransition* transition5 = new StateTransition("Transition 5");
		transition5->AddNextState(typeQualifier);

		StateTransition* transition6 = new StateTransition("Transition 6");
		transition6->AddNextState(typeQualifier);
		transition6->AddNextState(state);

		state->AddNextTransition(transition1);
		state->AddNextTransition(transition2);
		state->AddNextTransition(transition3);
		state->AddNextTransition(transition4);
		state->AddNextTransition(transition5);
		state->AddNextTransition(transition6);

		GetTokenFlow()->AddAcceptedTokens(state);
	}

	return state;
}

GrammarState* CGrammar::GetInitDeclaratorList()
{
	string stateName = "InitDeclaratorList";
	int stateType = StateType::InitDeclaratorList;

	GrammarState* state = GetDeclaredState(stateName, stateType);

	if (state == NULL)
	{
		state = new GrammarState(stateName, stateType);
		AddDeclaredState(state);

		GrammarState* initDeclarator = GetInitDeclarator();
		GrammarState* commaControl = GetCommaControl();

		StateTransition* transition1 = new StateTransition("Transition 1");
		transition1->AddNextState(initDeclarator);

		StateTransition* transition2 = new StateTransition("Transition 2");
		transition2->AddNextState(state);
		transition2->AddNextState(commaControl);
		transition2->AddNextState(initDeclarator);

		state->AddNextTransition(transition1);
		state->AddNextTransition(transition2);

		GetTokenFlow()->AddAcceptedTokens(state);
	}

	return state;
}

GrammarState* CGrammar::GetInitDeclarator()
{
	string stateName = "InitDeclarator";
	int stateType = StateType::InitDeclarator;

	GrammarState* state = GetDeclaredState(stateName, stateType);

	if (state == NULL)
	{
		state = new GrammarState(stateName, stateType);
		AddDeclaredState(state);

		GrammarState* declarator = GetDeclarator();
		GrammarState* assignmentOperation = GetAssignmentOperation();
		GrammarState* initializer = GetInitializer();

		StateTransition* transition1 = new StateTransition("Transition 1");
		transition1->AddNextState(declarator);

		StateTransition* transition2 = new StateTransition("Transition 2");
		transition2->AddNextState(declarator);
		transition2->AddNextState(assignmentOperation);
		transition1->AddNextState(initializer);

		state->AddNextTransition(transition1);
		state->AddNextTransition(transition2);

		GetTokenFlow()->AddAcceptedTokens(state);
	}

	return state;
}

GrammarState* CGrammar::GetStorageClassSpecifier()
{
	string stateName = "StorageClassSpecifier";
	int stateType = StateType::StorageClassSpecifier;

	GrammarState* state = GetDeclaredState(stateName, stateType);

	if (state == NULL)
	{
		state = new GrammarState(stateName, stateType);
		AddDeclaredState(state);

		GrammarState* typedefSpecifierControl = GetTypedefSpecifierControl();
		GrammarState* externSpecifierControl = GetExternSpecifierControl();
		GrammarState* staticSpecifierControl = GetStaticSpecifierControl();
		GrammarState* autoSpecifierControl = GetAutoSpecifierControl();
		GrammarState* registerSpecifierControl = GetRegisterSpecifierControl();

		StateTransition* transition1 = new StateTransition("Transition 1");
		transition1->AddNextState(typedefSpecifierControl);

		StateTransition* transition2 = new StateTransition("Transition 2");
		transition2->AddNextState(externSpecifierControl);

		StateTransition* transition3 = new StateTransition("Transition 3");
		transition3->AddNextState(staticSpecifierControl);

		StateTransition* transition4 = new StateTransition("Transition 4");
		transition4->AddNextState(autoSpecifierControl);

		StateTransition* transition5 = new StateTransition("Transition 5");
		transition5->AddNextState(registerSpecifierControl);

		state->AddNextTransition(transition1);
		state->AddNextTransition(transition2);
		state->AddNextTransition(transition3);
		state->AddNextTransition(transition4);
		state->AddNextTransition(transition5);

		GetTokenFlow()->AddAcceptedTokens(state);
	}

	return state;
}

GrammarState* CGrammar::GetTypeSpecifier()
{
	string stateName = "TypeSpecifier";
	int stateType = StateType::TypeSpecifier;

	GrammarState* state = GetDeclaredState(stateName, stateType);

	if (state == NULL)
	{
		state = new GrammarState(stateName, stateType);
		AddDeclaredState(state);

		GrammarState* voidTypeControl = GetVoidTypeControl();
		GrammarState* charTypeControl = GetCharTypeControl();
		GrammarState* shortTypeControl = GetShortTypeControl();
		GrammarState* intTypeControl = GetIntTypeControl();
		GrammarState* longTypeControl = GetLongTypeControl();
		GrammarState* floatTypeControl = GetFloatTypeControl();
		GrammarState* doubleTypeControl = GetDoubleTypeControl();
		GrammarState* signedTypeControl = GetSignedTypeControl();
		GrammarState* unsignedTypeControl = GetUnsignedTypeControl();
		GrammarState* structOrUnionSpecifier = GetStructOrUnionSpecifier();
		GrammarState* enumSpecifier = GetEnumSpecifier();
		GrammarState* typenameTypeControl = GetTypenameTypeControl();

		StateTransition* transition1 = new StateTransition("Transition 1");
		transition1->AddNextState(voidTypeControl);

		StateTransition* transition2 = new StateTransition("Transition 2");
		transition2->AddNextState(charTypeControl);

		StateTransition* transition3 = new StateTransition("Transition 3");
		transition3->AddNextState(shortTypeControl);

		StateTransition* transition4 = new StateTransition("Transition 4");
		transition4->AddNextState(intTypeControl);

		StateTransition* transition5 = new StateTransition("Transition 5");
		transition5->AddNextState(longTypeControl);

		StateTransition* transition6 = new StateTransition("Transition 6");
		transition6->AddNextState(floatTypeControl);

		StateTransition* transition7 = new StateTransition("Transition 7");
		transition7->AddNextState(doubleTypeControl);

		StateTransition* transition8 = new StateTransition("Transition 8");
		transition8->AddNextState(signedTypeControl);

		StateTransition* transition9 = new StateTransition("Transition 9");
		transition9->AddNextState(unsignedTypeControl);

		StateTransition* transition10 = new StateTransition("Transition 10");
		transition10->AddNextState(structOrUnionSpecifier);

		StateTransition* transition11 = new StateTransition("Transition 11");
		transition11->AddNextState(enumSpecifier);

		StateTransition* transition12 = new StateTransition("Transition 12");
		transition12->AddNextState(typenameTypeControl);

		state->AddNextTransition(transition1);
		state->AddNextTransition(transition2);
		state->AddNextTransition(transition3);
		state->AddNextTransition(transition4);
		state->AddNextTransition(transition5);
		state->AddNextTransition(transition6);
		state->AddNextTransition(transition7);
		state->AddNextTransition(transition8);
		state->AddNextTransition(transition9);
		state->AddNextTransition(transition10);
		state->AddNextTransition(transition11);
		state->AddNextTransition(transition12);

		GetTokenFlow()->AddAcceptedTokens(state);
	}

	return state;
}

GrammarState* CGrammar::GetStructOrUnionSpecifier()
{
	string stateName = "StructOrUnionSpecifier";
	int stateType = StateType::StructOrUnionSpecifier;

	GrammarState* state = GetDeclaredState(stateName, stateType);

	if (state == NULL)
	{
		state = new GrammarState(stateName, stateType);
		AddDeclaredState(state);

		GrammarState* structOrUnion = GetStructOrUnion();
		GrammarState* identifier = GetIdentifier();
		GrammarState* openCurlyBracketControl = GetOpenCurlyBracketControl();
		GrammarState* structDeclarationList = GetStructDeclarationList();
		GrammarState* closeCurlyBracketControl = GetCloseCurlyBracketControl();

		StateTransition* transition1 = new StateTransition("Transition 1");
		transition1->AddNextState(structOrUnion);
		transition1->AddNextState(identifier);
		transition1->AddNextState(openCurlyBracketControl);
		transition1->AddNextState(structDeclarationList);
		transition1->AddNextState(closeCurlyBracketControl);

		StateTransition* transition2 = new StateTransition("Transition 2");
		transition2->AddNextState(structOrUnion);
		transition2->AddNextState(openCurlyBracketControl);
		transition2->AddNextState(structDeclarationList);
		transition2->AddNextState(closeCurlyBracketControl);

		StateTransition* transition3 = new StateTransition("Transition 3");
		transition3->AddNextState(structOrUnion);
		transition3->AddNextState(identifier);

		state->AddNextTransition(transition1);
		state->AddNextTransition(transition2);
		state->AddNextTransition(transition3);

		GetTokenFlow()->AddAcceptedTokens(state);
	}

	return state;
}

GrammarState* CGrammar::GetStructOrUnion()
{
	string stateName = "StructOrUnion";
	int stateType = StateType::StructOrUnion;

	GrammarState* state = GetDeclaredState(stateName, stateType);

	if (state == NULL)
	{
		state = new GrammarState(stateName, stateType);
		AddDeclaredState(state);

		GrammarState* structTypeControl = GetStructTypeControl();
		GrammarState* unionControl = GetUnionSpecifierControl();

		StateTransition* transition1 = new StateTransition("Transition 1");
		transition1->AddNextState(structTypeControl);

		StateTransition* transition2 = new StateTransition("Transition 2");
		transition2->AddNextState(unionControl);

		state->AddNextTransition(transition1);
		state->AddNextTransition(transition2);

		GetTokenFlow()->AddAcceptedTokens(state);
	}

	return state;
}

GrammarState* CGrammar::GetStructDeclarationList()
{
	string stateName = "StructDeclarationList";
	int stateType = StateType::StructDeclarationList;

	GrammarState* state = GetDeclaredState(stateName, stateType);

	if (state == NULL)
	{
		state = new GrammarState(stateName, stateType);
		AddDeclaredState(state);

		GrammarState* structDeclaration = GetStructDeclaration();

		StateTransition* transition1 = new StateTransition("Transition 1");
		transition1->AddNextState(structDeclaration);

		StateTransition* transition2 = new StateTransition("Transition 2");
		transition2->AddNextState(state);
		transition2->AddNextState(structDeclaration);

		state->AddNextTransition(transition1);
		state->AddNextTransition(transition2);

		GetTokenFlow()->AddAcceptedTokens(state);
	}

	return state;
}

GrammarState* CGrammar::GetStructDeclaration()
{
	string stateName = "StructDeclaration";
	int stateType = StateType::StructDeclaration;

	GrammarState* state = GetDeclaredState(stateName, stateType);

	if (state == NULL)
	{
		state = new GrammarState(stateName, stateType);
		AddDeclaredState(state);

		GrammarState* specifierQualifierList = GetSpecifierQualifierList();
		GrammarState* structDeclarationList =  GetStructDeclarationList();
		GrammarState* endControl = GetEndControl();

		StateTransition* transition1 = new StateTransition("Transition 1");
		transition1->AddNextState(specifierQualifierList);
		transition1->AddNextState(structDeclarationList);
		transition1->AddNextState(endControl);

		state->AddNextTransition(transition1);

		GetTokenFlow()->AddAcceptedTokens(state);
	}

	return state;
}

GrammarState* CGrammar::GetSpecifierQualifierList()
{
	string stateName = "SpecifierQualifierList";
	int stateType = StateType::SpecifierQualifierList;

	GrammarState* state = GetDeclaredState(stateName, stateType);

	if (state == NULL)
	{
		state = new GrammarState(stateName, stateType);
		AddDeclaredState(state);

		GrammarState* typeSpecifier = GetTypeSpecifier();
		GrammarState* typeQualifier = GetTypeQualifier();

		StateTransition* transition1 = new StateTransition("Transition 1");
		transition1->AddNextState(typeSpecifier);
		transition1->AddNextState(state);

		StateTransition* transition2 = new StateTransition("Transition 2");
		transition2->AddNextState(typeSpecifier);

		StateTransition* transition3 = new StateTransition("Transition 3");
		transition3->AddNextState(typeQualifier);
		transition3->AddNextState(state);

		StateTransition* transition4 = new StateTransition("Transition 4");
		transition4->AddNextState(typeQualifier);

		state->AddNextTransition(transition1);
		state->AddNextTransition(transition2);
		state->AddNextTransition(transition3);
		state->AddNextTransition(transition4);

		GetTokenFlow()->AddAcceptedTokens(state);
	}

	return state;
}

GrammarState* CGrammar::GetStructDeclaratorList()
{
	string stateName = "StructDeclaratorList";
	int stateType = StateType::StructDeclaratorList;

	GrammarState* state = GetDeclaredState(stateName, stateType);

	if (state == NULL)
	{
		state = new GrammarState(stateName, stateType);
		AddDeclaredState(state);

		GrammarState* structDeclarator = GetStructDeclarator();
		GrammarState* commaControl = GetCommaControl();

		StateTransition* transition1 = new StateTransition("Transition 1");
		transition1->AddNextState(structDeclarator);

		StateTransition* transition2 = new StateTransition("Transition 2");
		transition2->AddNextState(state);
		transition2->AddNextState(commaControl);
		transition2->AddNextState(structDeclarator);

		state->AddNextTransition(transition1);
		state->AddNextTransition(transition2);

		GetTokenFlow()->AddAcceptedTokens(state);
	}

	return state;
}

GrammarState* CGrammar::GetStructDeclarator()
{
	string stateName = "StructDeclarator";
	int stateType = StateType::StructDeclarator;

	GrammarState* state = GetDeclaredState(stateName, stateType);

	if (state == NULL)
	{
		state = new GrammarState(stateName, stateType);
		AddDeclaredState(state);

		GrammarState* declarator = GetDeclarator();
		GrammarState* doubleDotControl = GetDoubleDotControl();
		GrammarState* constantExpression = GetConstantExpression();

		StateTransition* transition1 = new StateTransition("Transition 1");
		transition1->AddNextState(declarator);

		StateTransition* transition2 = new StateTransition("Transition 2");
		transition2->AddNextState(doubleDotControl);
		transition2->AddNextState(constantExpression);

		StateTransition* transition3 = new StateTransition("Transition 3");
		transition3->AddNextState(declarator);
		transition3->AddNextState(doubleDotControl);
		transition3->AddNextState(constantExpression);

		state->AddNextTransition(transition1);
		state->AddNextTransition(transition2);
		state->AddNextTransition(transition3);

		GetTokenFlow()->AddAcceptedTokens(state);
	}

	return state;
}

GrammarState* CGrammar::GetEnumSpecifier()
{
	string stateName = "EnumSpecifier";
	int stateType = StateType::EnumSpecifier;

	GrammarState* state = GetDeclaredState(stateName, stateType);

	if (state == NULL)
	{
		state = new GrammarState(stateName, stateType);
		AddDeclaredState(state);

		GrammarState* enumTypeControl = GetEnumTypeControl();
		GrammarState* openCurlyBracketControl = GetOpenCurlyBracketControl();
		GrammarState* enumeratorList = GetEnumeratorList();
		GrammarState* closeCurlyBracketControl = GetCloseCurlyBracketControl();
		GrammarState* identifier = GetIdentifier();

		StateTransition* transition1 = new StateTransition("Transition 1");
		transition1->AddNextState(enumTypeControl);
		transition1->AddNextState(openCurlyBracketControl);
		transition1->AddNextState(enumeratorList);
		transition1->AddNextState(closeCurlyBracketControl);

		StateTransition* transition2 = new StateTransition("Transition 2");
		transition2->AddNextState(enumTypeControl);
		transition2->AddNextState(identifier);
		transition2->AddNextState(openCurlyBracketControl);
		transition2->AddNextState(enumeratorList);
		transition2->AddNextState(closeCurlyBracketControl);

		StateTransition* transition3 = new StateTransition("Transition 3");
		transition3->AddNextState(enumTypeControl);
		transition3->AddNextState(identifier);

		state->AddNextTransition(transition1);
		state->AddNextTransition(transition2);
		state->AddNextTransition(transition3);

		GetTokenFlow()->AddAcceptedTokens(state);
	}

	return state;
}

GrammarState* CGrammar::GetEnumeratorList()
{
	string stateName = "EnumeratorList";
	int stateType = StateType::EnumeratorList;

	GrammarState* state = GetDeclaredState(stateName, stateType);

	if (state == NULL)
	{
		state = new GrammarState(stateName, stateType);
		AddDeclaredState(state);

		GrammarState* enumerator = GetEnumerator();
		GrammarState* commaControl = GetCommaControl();

		StateTransition* transition1 = new StateTransition("Transition 1");
		transition1->AddNextState(enumerator);

		StateTransition* transition2 = new StateTransition("Transition 2");
		transition2->AddNextState(state);
		transition2->AddNextState(commaControl);
		transition2->AddNextState(enumerator);

		state->AddNextTransition(transition1);
		state->AddNextTransition(transition2);

		GetTokenFlow()->AddAcceptedTokens(state);
	}

	return state;
}

GrammarState* CGrammar::GetEnumerator()
{
	string stateName = "Enumerator";
	int stateType = StateType::Enumerator;

	GrammarState* state = GetDeclaredState(stateName, stateType);

	if (state == NULL)
	{
		state = new GrammarState(stateName, stateType);
		AddDeclaredState(state);

		GrammarState* identifier = GetIdentifier();
		GrammarState* assignmentOperation = GetAssignmentOperation();
		GrammarState* constantExpression = GetConstantExpression();

		StateTransition* transition1 = new StateTransition("Transition 1");
		transition1->AddNextState(identifier);

		StateTransition* transition2 = new StateTransition("Transition 2");
		transition2->AddNextState(identifier);
		transition2->AddNextState(assignmentOperation);
		transition2->AddNextState(constantExpression);

		state->AddNextTransition(transition1);
		state->AddNextTransition(transition2);

		GetTokenFlow()->AddAcceptedTokens(state);
	}

	return state;
}

GrammarState* CGrammar::GetTypeQualifier()
{
	string stateName = "TypeQualifier";
	int stateType = StateType::TypeQualifier;

	GrammarState* state = GetDeclaredState(stateName, stateType);

	if (state == NULL)
	{
		state = new GrammarState(stateName, stateType);
		AddDeclaredState(state);

		GrammarState* constQualifierControl = GetConstQualifierControl();
		GrammarState* volatileQualifierControl = GetVolatileQualifierControl();

		StateTransition* transition1 = new StateTransition("Transition 1");
		transition1->AddNextState(constQualifierControl);

		StateTransition* transition2 = new StateTransition("Transition 2");
		transition2->AddNextState(volatileQualifierControl);

		state->AddNextTransition(transition1);
		state->AddNextTransition(transition2);

		GetTokenFlow()->AddAcceptedTokens(state);
	}

	return state;
}

GrammarState* CGrammar::GetDeclarator()
{
	string stateName = "Declarator";
	int stateType = StateType::Declarator;

	GrammarState* state = GetDeclaredState(stateName, stateType);

	if (state == NULL)
	{
		state = new GrammarState(stateName, stateType);
		AddDeclaredState(state);

		GrammarState* pointer = GetPointer();
		GrammarState* directDeclarator = GetDirectDeclarator();

		StateTransition* transition1 = new StateTransition("Transition 1");
		transition1->AddNextState(pointer);
		transition1->AddNextState(directDeclarator);

		StateTransition* transition2 = new StateTransition("Transition 2");
		transition2->AddNextState(directDeclarator);

		state->AddNextTransition(transition1);
		state->AddNextTransition(transition2);

		GetTokenFlow()->AddAcceptedTokens(state);
	}

	return state;
}

GrammarState* CGrammar::GetDirectDeclarator()
{
	string stateName = "DirectDeclarator";
	int stateType = StateType::DirectDeclarator;

	GrammarState* state = GetDeclaredState(stateName, stateType);

	if (state == NULL)
	{
		state = new GrammarState(stateName, stateType);
		AddDeclaredState(state);

		GrammarState* identifier = GetIdentifier();
		GrammarState* openParenthesesControl = GetOpenParenthesesControl();
		GrammarState* declarator = GetDeclarator();
		GrammarState* closeParenthesesControl = GetCloseParenthesesControl();
		GrammarState* openBracketControl = GetOpenBracketControl();
		GrammarState* constantExpression = GetConstantExpression();
		GrammarState* closeBracketControl = GetCloseBracketControl();
		GrammarState* parameterTypeList = GetParameterTypeList();
		GrammarState* identifierList = GetIdentifierList();

		StateTransition* transition1 = new StateTransition("Transition 1");
		transition1->AddNextState(identifier);

		StateTransition* transition2 = new StateTransition("Transition 2");
		transition2->AddNextState(openParenthesesControl);
		transition2->AddNextState(declarator);
		transition2->AddNextState(closeParenthesesControl);

		StateTransition* transition3 = new StateTransition("Transition 3");
		transition3->AddNextState(state);
		transition3->AddNextState(openBracketControl);
		transition3->AddNextState(constantExpression);
		transition3->AddNextState(closeBracketControl);

		StateTransition* transition4 = new StateTransition("Transition 4");
		transition4->AddNextState(state);
		transition4->AddNextState(openBracketControl);
		transition4->AddNextState(closeBracketControl);

		StateTransition* transition5 = new StateTransition("Transition 5");
		transition5->AddNextState(state);
		transition5->AddNextState(openParenthesesControl);
		transition5->AddNextState(parameterTypeList);
		transition5->AddNextState(closeParenthesesControl);

		StateTransition* transition6 = new StateTransition("Transition 6");
		transition6->AddNextState(state);
		transition6->AddNextState(openParenthesesControl);
		transition6->AddNextState(identifierList);
		transition6->AddNextState(closeParenthesesControl);

		StateTransition* transition7 = new StateTransition("Transition 7");
		transition7->AddNextState(state);
		transition7->AddNextState(openParenthesesControl);
		transition7->AddNextState(closeParenthesesControl);

		state->AddNextTransition(transition1);
		state->AddNextTransition(transition2);
		state->AddNextTransition(transition3);
		state->AddNextTransition(transition4);
		state->AddNextTransition(transition5);
		state->AddNextTransition(transition6);
		state->AddNextTransition(transition7);

		GetTokenFlow()->AddAcceptedTokens(state);
	}

	return state;
}

GrammarState* CGrammar::GetPointer()
{
	string stateName = "Pointer";
	int stateType = StateType::Pointer;

	GrammarState* state = GetDeclaredState(stateName, stateType);

	if (state == NULL)
	{
		state = new GrammarState(stateName, stateType);
		AddDeclaredState(state);

		GrammarState* pointerControl = GetPointerControl();
		GrammarState* typeQualifierList = GetTypeQualifierList();

		StateTransition* transition1 = new StateTransition("Transition 1");
		transition1->AddNextState(pointerControl);

		StateTransition* transition2 = new StateTransition("Transition 2");
		transition2->AddNextState(pointerControl);
		transition2->AddNextState(typeQualifierList);

		StateTransition* transition3 = new StateTransition("Transition 3");
		transition3->AddNextState(pointerControl);
		transition3->AddNextState(state);

		StateTransition* transition4 = new StateTransition("Transition 4");
		transition4->AddNextState(pointerControl);
		transition4->AddNextState(typeQualifierList);
		transition4->AddNextState(state);

		state->AddNextTransition(transition1);
		state->AddNextTransition(transition2);
		state->AddNextTransition(transition3);
		state->AddNextTransition(transition4);

		GetTokenFlow()->AddAcceptedTokens(state);
	}
	
	return state;
}

GrammarState* CGrammar::GetTypeQualifierList()
{
	string stateName = "TypeQualifierList";
	int stateType = StateType::TypeQualifierList;

	GrammarState* state = GetDeclaredState(stateName, stateType);

	if (state == NULL)
	{
		state = new GrammarState(stateName, stateType);
		AddDeclaredState(state);

		GrammarState* typeQualifier = GetTypeQualifier();

		StateTransition* transition1 = new StateTransition("Transition 1");
		transition1->AddNextState(typeQualifier);

		StateTransition* transition2 = new StateTransition("Transition 2");
		transition2->AddNextState(state);
		transition2->AddNextState(typeQualifier);

		state->AddNextTransition(transition1);
		state->AddNextTransition(transition2);

		GetTokenFlow()->AddAcceptedTokens(state);
	}

	return state;
}

GrammarState* CGrammar::GetParameterTypeList()
{
	string stateName = "ParameterTypeList";
	int stateType = StateType::ParameterTypeList;

	GrammarState* state = GetDeclaredState(stateName, stateType);

	if (state == NULL)
	{
		state = new GrammarState(stateName, stateType);
		AddDeclaredState(state);

		GrammarState* parameterList = GetParameterList();
		GrammarState* commaControl = GetCommaControl();
		GrammarState* ellipsisControl = GetEllipsisControl();

		StateTransition* transition1 = new StateTransition("Transition 1");
		transition1->AddNextState(parameterList);

		StateTransition* transition2 = new StateTransition("Transition 2");
		transition2->AddNextState(parameterList);
		transition2->AddNextState(commaControl);
		transition2->AddNextState(ellipsisControl);

		state->AddNextTransition(transition1);
		state->AddNextTransition(transition2);

		GetTokenFlow()->AddAcceptedTokens(state);
	}

	return state;
}

GrammarState* CGrammar::GetParameterList()
{
	string stateName = "ParameterList";
	int stateType = StateType::ParameterList;

	GrammarState* state = GetDeclaredState(stateName, stateType);

	if (state == NULL)
	{
		state = new GrammarState(stateName, stateType);
		AddDeclaredState(state);

		GrammarState* parameterDeclaration = GetParameterDeclaration();
		GrammarState* commaControl = GetCommaControl();

		StateTransition* transition1 = new StateTransition("Transition 1");
		transition1->AddNextState(parameterDeclaration);

		StateTransition* transition2 = new StateTransition("Transition 2");
		transition2->AddNextState(state);
		transition2->AddNextState(commaControl);
		transition2->AddNextState(parameterDeclaration);

		state->AddNextTransition(transition1);
		state->AddNextTransition(transition2);

		GetTokenFlow()->AddAcceptedTokens(state);
	}

	return state;
}

GrammarState* CGrammar::GetParameterDeclaration()
{
	string stateName = "ParameterDeclaration";
	int stateType = StateType::ParameterDeclaration;

	GrammarState* state = GetDeclaredState(stateName, stateType);

	if (state == NULL)
	{
		state = new GrammarState(stateName, stateType);
		AddDeclaredState(state);

		GrammarState* declarationSpecifiers = GetDeclarationSpecifiers();
		GrammarState* declarator = GetDeclarator();
		GrammarState* abstractDeclarator = GetAbstractDeclarator();

		StateTransition* transition1 = new StateTransition("Transition 1");
		transition1->AddNextState(declarationSpecifiers);
		transition1->AddNextState(declarator);

		StateTransition* transition2 = new StateTransition("Transition 2");
		transition2->AddNextState(declarationSpecifiers);
		transition2->AddNextState(abstractDeclarator);

		StateTransition* transition3 = new StateTransition("Transition 3");
		transition3->AddNextState(declarationSpecifiers);

		state->AddNextTransition(transition1);
		state->AddNextTransition(transition2);
		state->AddNextTransition(transition3);

		GetTokenFlow()->AddAcceptedTokens(state);
	}

	return state;
}

GrammarState* CGrammar::GetIdentifierList()
{
	string stateName = "IdentifierList";
	int stateType = StateType::IdentifierList;

	GrammarState* state = GetDeclaredState(stateName, stateType);

	if (state == NULL)
	{
		state = new GrammarState(stateName, stateType);
		AddDeclaredState(state);

		GrammarState* identifier = GetIdentifier();
		GrammarState* commaControl = GetCommaControl();

		StateTransition* transition1 = new StateTransition("Transition 1");
		transition1->AddNextState(identifier);

		StateTransition* transition2 = new StateTransition("Transition 2");
		transition2->AddNextState(state);
		transition2->AddNextState(commaControl);
		transition2->AddNextState(identifier);

		state->AddNextTransition(transition1);
		state->AddNextTransition(transition2);

		GetTokenFlow()->AddAcceptedTokens(state);
	}

	return state;
}

GrammarState* CGrammar::GetTypeName()
{
	string stateName = "TypeName";
	int stateType = StateType::TypeName;

	GrammarState* state = GetDeclaredState(stateName, stateType);

	if (state == NULL)
	{
		state = new GrammarState(stateName, stateType);
		AddDeclaredState(state);

		GrammarState* specifierQualifierList = GetSpecifierQualifierList();
		GrammarState* abstractDeclarator = GetAbstractDeclarator();

		StateTransition* transition1 = new StateTransition("Transition 1");
		transition1->AddNextState(specifierQualifierList);

		StateTransition* transition2 = new StateTransition("Transition 2");
		transition2->AddNextState(specifierQualifierList);
		transition2->AddNextState(abstractDeclarator);

		state->AddNextTransition(transition1);
		state->AddNextTransition(transition2);

		GetTokenFlow()->AddAcceptedTokens(state);
	}

	return state;
}

GrammarState* CGrammar::GetAbstractDeclarator()
{
	string stateName = "AbstractDeclarator";
	int stateType = StateType::AbstractDeclarator;

	GrammarState* state = GetDeclaredState(stateName, stateType);

	if (state == NULL)
	{
		state = new GrammarState(stateName, stateType);
		AddDeclaredState(state);

		GrammarState* pointer = GetPointer();
		GrammarState* directAbstractDeclarator = GetDirectAbstractDeclarator();

		StateTransition* transition1 = new StateTransition("Transition 1");
		transition1->AddNextState(pointer);

		StateTransition* transition2 = new StateTransition("Transition 2");
		transition2->AddNextState(directAbstractDeclarator);

		StateTransition* transition3 = new StateTransition("Transition 3");
		transition3->AddNextState(pointer);
		transition3->AddNextState(directAbstractDeclarator);

		state->AddNextTransition(transition1);
		state->AddNextTransition(transition2);
		state->AddNextTransition(transition3);

		GetTokenFlow()->AddAcceptedTokens(state);
	}

	return state;
}

GrammarState* CGrammar::GetDirectAbstractDeclarator()
{
	string stateName = "DirectAbstractDeclarator";
	int stateType = StateType::DirectAbstractDeclarator;

	GrammarState* state = GetDeclaredState(stateName, stateType);

	if (state == NULL)
	{
		state = new GrammarState(stateName, stateType);
		AddDeclaredState(state);

		GrammarState* openParenthesesControl  = GetOpenParenthesesControl();
		GrammarState* abstractDeclarator = GetAbstractDeclarator();
		GrammarState* closeParenthesesControl = GetCloseParenthesesControl();
		GrammarState* openBracketControl = GetOpenBracketControl();
		GrammarState* closeBracketControl = GetCloseBracketControl();
		GrammarState* constantExpression = GetConstantExpression();
		GrammarState* parameterTypeList = GetParameterTypeList();

		StateTransition* transition1 = new StateTransition("Transition 1");
		transition1->AddNextState(openParenthesesControl);
		transition1->AddNextState(abstractDeclarator);
		transition1->AddNextState(closeParenthesesControl);

		StateTransition* transition2 = new StateTransition("Transition 2");
		transition2->AddNextState(openBracketControl);
		transition2->AddNextState(closeBracketControl);

		StateTransition* transition3 = new StateTransition("Transition 3");
		transition3->AddNextState(openBracketControl);
		transition3->AddNextState(constantExpression);
		transition3->AddNextState(closeBracketControl);

		StateTransition* transition4 = new StateTransition("Transition 4");
		transition4->AddNextState(state);
		transition4->AddNextState(openBracketControl);
		transition4->AddNextState(closeBracketControl);

		StateTransition* transition5 = new StateTransition("Transition 5");
		transition5->AddNextState(state);
		transition5->AddNextState(openBracketControl);
		transition5->AddNextState(constantExpression);
		transition5->AddNextState(closeBracketControl);

		StateTransition* transition6 = new StateTransition("Transition 6");
		transition6->AddNextState(openParenthesesControl);
		transition6->AddNextState(closeParenthesesControl);

		StateTransition* transition7 = new StateTransition("Transition 7");
		transition7->AddNextState(openParenthesesControl);
		transition7->AddNextState(parameterTypeList);
		transition7->AddNextState(closeParenthesesControl);

		StateTransition* transition8 = new StateTransition("Transition 8");
		transition8->AddNextState(state);
		transition8->AddNextState(openParenthesesControl);
		transition8->AddNextState(closeParenthesesControl);

		StateTransition* transition9 = new StateTransition("Transition 9");
		transition9->AddNextState(state);
		transition9->AddNextState(openParenthesesControl);
		transition9->AddNextState(parameterTypeList);
		transition9->AddNextState(closeParenthesesControl);

		state->AddNextTransition(transition1);
		state->AddNextTransition(transition2);
		state->AddNextTransition(transition3);
		state->AddNextTransition(transition4);
		state->AddNextTransition(transition5);
		state->AddNextTransition(transition6);
		state->AddNextTransition(transition7);
		state->AddNextTransition(transition8);
		state->AddNextTransition(transition9);

		GetTokenFlow()->AddAcceptedTokens(state);
	}

	return state;
}

GrammarState* CGrammar::GetInitializer()
{
	string stateName = "Initializer";
	int stateType = StateType::Initializer;

	GrammarState* state = GetDeclaredState(stateName, stateType);

	if (state == NULL)
	{
		state = new GrammarState(stateName, stateType);
		AddDeclaredState(state);

		GrammarState* assignmentExpression = GetAssignmentExpression();
		GrammarState* openCurlyBracketControl = GetOpenCurlyBracketControl();
		GrammarState* initializerList = GetInitializerList();
		GrammarState* closeCloseCurlyBracketControl = GetCloseCurlyBracketControl();
		GrammarState* commaControl = GetCommaControl();

		StateTransition* transition1 = new StateTransition("Transition 1");
		transition1->AddNextState(assignmentExpression);

		StateTransition* transition2 = new StateTransition("Transition 2");
		transition2->AddNextState(openCurlyBracketControl);
		transition2->AddNextState(initializerList);
		transition2->AddNextState(closeCloseCurlyBracketControl);

		StateTransition* transition3 = new StateTransition("Transition 3");
		transition3->AddNextState(openCurlyBracketControl);
		transition3->AddNextState(initializerList);
		transition3->AddNextState(commaControl);
		transition3->AddNextState(closeCloseCurlyBracketControl);

		state->AddNextTransition(transition1);
		state->AddNextTransition(transition2);
		state->AddNextTransition(transition3);

		GetTokenFlow()->AddAcceptedTokens(state);
	}

	return state;
}

GrammarState* CGrammar::GetInitializerList()
{
	string stateName = "InitializerList";
	int stateType = StateType::InitializerList;

	GrammarState* state = GetDeclaredState(stateName, stateType);

	if (state == NULL)
	{
		state = new GrammarState(stateName, stateType);
		AddDeclaredState(state);

		GrammarState* initializer = GetInitializer();
		GrammarState* commaControl = GetCommaControl();

		StateTransition* transition1 = new StateTransition("Transition 1");
		transition1->AddNextState(initializer);

		StateTransition* transition2 = new StateTransition("Transition 2");
		transition2->AddNextState(state);
		transition2->AddNextState(commaControl);
		transition2->AddNextState(initializer);

		state->AddNextTransition(transition1);
		state->AddNextTransition(transition2);

		GetTokenFlow()->AddAcceptedTokens(state);
	}

	return state;
}

GrammarState* CGrammar::GetStatement()
{
	string stateName = "Statement";
	int stateType = StateType::Statement;

	GrammarState* state = GetDeclaredState(stateName, stateType);

	if (state == NULL)
	{
		state = new GrammarState(stateName, stateType);
		AddDeclaredState(state);

		GrammarState* labeledStatement = GetLabeledStatement();
		GrammarState* compoundStatement = GetCompoundStatement();
		GrammarState* expressionStatement = GetExpressionStatement();
		GrammarState* selectionStatement = GetSelectionStatement();
		GrammarState* iterationStatement = GetIterationStatement();
		GrammarState* jumpStatement = GetJumpStatement();

		StateTransition* transition1 = new StateTransition("Transition 1");
		transition1->AddNextState(labeledStatement);

		StateTransition* transition2 = new StateTransition("Transition 2");
		transition2->AddNextState(compoundStatement);

		StateTransition* transition3 = new StateTransition("Transition 3");
		transition3->AddNextState(expressionStatement);

		StateTransition* transition4 = new StateTransition("Transition 4");
		transition4->AddNextState(selectionStatement);

		StateTransition* transition5 = new StateTransition("Transition 5");
		transition5->AddNextState(iterationStatement);

		StateTransition* transition6 = new StateTransition("Transition 6");
		transition6->AddNextState(jumpStatement);

		state->AddNextTransition(transition1);
		state->AddNextTransition(transition2);
		state->AddNextTransition(transition3);
		state->AddNextTransition(transition4);
		state->AddNextTransition(transition5);
		state->AddNextTransition(transition6);

		GetTokenFlow()->AddAcceptedTokens(state);
	}

	return state;
}

GrammarState* CGrammar::GetLabeledStatement()
{
	string stateName = "LabeledStatement";
	int stateType = StateType::LabeledStatement;

	GrammarState* state = GetDeclaredState(stateName, stateType);

	if (state == NULL)
	{
		state = new GrammarState(stateName, stateType);
		AddDeclaredState(state);

		GrammarState* identifier = GetIdentifier();
		GrammarState* doubleDotControl = GetDoubleDotControl();
		GrammarState* statement = GetStatement();
		GrammarState* caseControl = GetCaseControl();
		GrammarState* constantExpression = GetConstantExpression();
		GrammarState* defaultControl = GetDefaultControl();

		StateTransition* transition1 = new StateTransition("Transition 1");
		transition1->AddNextState(identifier);
		transition1->AddNextState(doubleDotControl);
		transition1->AddNextState(statement);

		StateTransition* transition2 = new StateTransition("Transition 2");
		transition2->AddNextState(caseControl);
		transition2->AddNextState(constantExpression);
		transition2->AddNextState(doubleDotControl);
		transition2->AddNextState(statement);

		StateTransition* transition3 = new StateTransition("Transition 3");
		transition3->AddNextState(defaultControl);
		transition3->AddNextState(doubleDotControl);
		transition3->AddNextState(statement);

		state->AddNextTransition(transition1);
		state->AddNextTransition(transition2);
		state->AddNextTransition(transition3);

		GetTokenFlow()->AddAcceptedTokens(state);
	}

	return state;
}

GrammarState* CGrammar::GetCompoundStatement()
{
	string stateName = "CompoundStatement";
	int stateType = StateType::CompoundStatement;

	GrammarState* state = GetDeclaredState(stateName, stateType);

	if (state == NULL)
	{
		state = new GrammarState(stateName, stateType);
		AddDeclaredState(state);

		GrammarState* openCurlyBracketControl = GetOpenCurlyBracketControl();
		GrammarState* closeCurlyBracketControl = GetCloseCurlyBracketControl();
		GrammarState* statementList = GetStatementList();
		GrammarState* declarationList = GetDeclarationList();

		StateTransition* transition1 = new StateTransition("Transition 1");
		transition1->AddNextState(openCurlyBracketControl);
		transition1->AddNextState(closeCurlyBracketControl);

		StateTransition* transition2 = new StateTransition("Transition 2");
		transition2->AddNextState(openCurlyBracketControl);
		transition2->AddNextState(statementList);
		transition2->AddNextState(closeCurlyBracketControl);

		StateTransition* transition3 = new StateTransition("Transition 3");
		transition3->AddNextState(openCurlyBracketControl);
		transition3->AddNextState(declarationList);
		transition3->AddNextState(closeCurlyBracketControl);

		StateTransition* transition4 = new StateTransition("Transition 4");
		transition4->AddNextState(openCurlyBracketControl);
		transition4->AddNextState(statementList);
		transition4->AddNextState(declarationList);
		transition4->AddNextState(closeCurlyBracketControl);

		state->AddNextTransition(transition1);
		state->AddNextTransition(transition2);
		state->AddNextTransition(transition3);
		state->AddNextTransition(transition4);

		GetTokenFlow()->AddAcceptedTokens(state);
	}

	return state;
}

GrammarState* CGrammar::GetDeclarationList()
{
	string stateName = "DeclarationList";
	int stateType = StateType::DeclarationList;

	GrammarState* state = GetDeclaredState(stateName, stateType);

	if (state == NULL)
	{
		state = new GrammarState(stateName, stateType);
		AddDeclaredState(state);

		GrammarState* declaration = GetDeclaration();

		StateTransition* transition1 = new StateTransition("Transition 1");
		transition1->AddNextState(declaration);

		StateTransition* transition2 = new StateTransition("Transition 2");
		transition2->AddNextState(state);
		transition2->AddNextState(declaration);

		state->AddNextTransition(transition1);
		state->AddNextTransition(transition2);

		GetTokenFlow()->AddAcceptedTokens(state);
	}

	return state;
}

GrammarState* CGrammar::GetStatementList()
{
	string stateName = "StatementList";
	int stateType = StateType::StatementList;

	GrammarState* state = GetDeclaredState(stateName, stateType);

	if (state == NULL)
	{
		state = new GrammarState(stateName, stateType);
		AddDeclaredState(state);

		GrammarState* statement = GetStatement();

		StateTransition* transition1 = new StateTransition("Transition 1");
		transition1->AddNextState(statement);

		StateTransition* transition2 = new StateTransition("Transition 2");
		transition2->AddNextState(state);
		transition2->AddNextState(statement);

		state->AddNextTransition(transition1);
		state->AddNextTransition(transition2);

		GetTokenFlow()->AddAcceptedTokens(state);
	}

	return state;
}

GrammarState* CGrammar::GetExpressionStatement()
{
	string stateName = "ExpressionStatement";
	int stateType = StateType::ExpressionStatement;

	GrammarState* state = GetDeclaredState(stateName, stateType);

	if (state == NULL)
	{
		state = new GrammarState(stateName, stateType);
		AddDeclaredState(state);

		GrammarState* endControl = GetEndControl();
		GrammarState* expression = GetExpression();

		StateTransition* transition1 = new StateTransition("Transition 1");
		transition1->AddNextState(endControl);

		StateTransition* transition2 = new StateTransition("Transition 2");
		transition2->AddNextState(expression);
		transition2->AddNextState(endControl);

		state->AddNextTransition(transition1);
		state->AddNextTransition(transition2);

		GetTokenFlow()->AddAcceptedTokens(state);
	}

	return state;
}

GrammarState* CGrammar::GetSelectionStatement()
{
	string stateName = "SelectionStatement";
	int stateType = StateType::SelectionStatement;

	GrammarState* state = GetDeclaredState(stateName, stateType);

	if (state == NULL)
	{
		state = new GrammarState(stateName, stateType);
		AddDeclaredState(state);

		GrammarState* ifControl = GetIfControl();
		GrammarState* openCurlyBracketControl = GetOpenCurlyBracketControl();
		GrammarState* expression = GetExpression();
		GrammarState* closeCurlyBracketControl = GetCloseCurlyBracketControl();
		GrammarState* elseControl = GetElseControl();
		GrammarState* statement = GetStatement();
		GrammarState* switchControl = GetSwitchControl();

		StateTransition* transition1 = new StateTransition("Transition 1");
		transition1->AddNextState(ifControl);
		transition1->AddNextState(openCurlyBracketControl);
		transition1->AddNextState(expression);
		transition1->AddNextState(closeCurlyBracketControl);
		transition1->AddNextState(statement);

		StateTransition* transition2 = new StateTransition("Transition 2");
		transition2->AddNextState(ifControl);
		transition2->AddNextState(openCurlyBracketControl);
		transition2->AddNextState(expression);
		transition2->AddNextState(closeCurlyBracketControl);
		transition2->AddNextState(statement);
		transition2->AddNextState(elseControl);
		transition2->AddNextState(statement);

		StateTransition* transition3 = new StateTransition("Transition 3");
		transition3->AddNextState(switchControl);
		transition3->AddNextState(openCurlyBracketControl);
		transition3->AddNextState(expression);
		transition3->AddNextState(closeCurlyBracketControl);
		transition3->AddNextState(statement);

		state->AddNextTransition(transition1);
		state->AddNextTransition(transition2);
		state->AddNextTransition(transition3);

		GetTokenFlow()->AddAcceptedTokens(state);
	}

	return state;
}

GrammarState* CGrammar::GetIterationStatement()
{
	string stateName = "IterationStatement";
	int stateType = StateType::IterationStatement;

	GrammarState* state = GetDeclaredState(stateName, stateType);

	if (state == NULL)
	{
		state = new GrammarState(stateName, stateType);
		AddDeclaredState(state);

		GrammarState* whileControl = GetWhileControl();
		GrammarState* openParenthesesControl = GetOpenParenthesesControl();
		GrammarState* expression = GetExpression();
		GrammarState* closeParenthesesControl = GetCloseParenthesesControl();
		GrammarState* statement = GetStatement();
		GrammarState* doControl = GetDoControl();
		GrammarState* endControl = GetEndControl();
		GrammarState* forControl = GetForControl();
		GrammarState* expressionStatement = GetExpressionStatement();

		StateTransition* transition1 = new StateTransition("Transition 1");
		transition1->AddNextState(whileControl);
		transition1->AddNextState(openParenthesesControl);
		transition1->AddNextState(expression);
		transition1->AddNextState(closeParenthesesControl);
		transition1->AddNextState(statement);

		StateTransition* transition2 = new StateTransition("Transition 2");
		transition2->AddNextState(doControl);
		transition2->AddNextState(statement);
		transition2->AddNextState(whileControl);
		transition2->AddNextState(openParenthesesControl);
		transition2->AddNextState(expression);
		transition2->AddNextState(closeParenthesesControl);
		transition2->AddNextState(endControl);

		StateTransition* transition3 = new StateTransition("Transition 3");
		transition3->AddNextState(forControl);
		transition3->AddNextState(openParenthesesControl);
		transition3->AddNextState(expressionStatement);
		transition3->AddNextState(expressionStatement);
		transition3->AddNextState(closeParenthesesControl);
		transition3->AddNextState(statement);

		StateTransition* transition4 = new StateTransition("Transition 4");
		transition4->AddNextState(forControl);
		transition4->AddNextState(openParenthesesControl);
		transition4->AddNextState(expressionStatement);
		transition4->AddNextState(expressionStatement);
		transition4->AddNextState(expression);
		transition4->AddNextState(closeParenthesesControl);
		transition4->AddNextState(statement);

		state->AddNextTransition(transition1);
		state->AddNextTransition(transition2);
		state->AddNextTransition(transition3);
		state->AddNextTransition(transition4);

		GetTokenFlow()->AddAcceptedTokens(state);
	}

	return state;
}

GrammarState* CGrammar::GetJumpStatement()
{
	string stateName = "JumpStatement";
	int stateType = StateType::JumpStatement;

	GrammarState* state = GetDeclaredState(stateName, stateType);

	if (state == NULL)
	{
		state = new GrammarState(stateName, stateType);
		AddDeclaredState(state);

		GrammarState* gotoControl = GetGotoControl();
		GrammarState* identifier = GetIdentifier();
		GrammarState* endControl = GetEndControl();
		GrammarState* continueControl = GetContinueControl();
		GrammarState* breakControl = GetBreakControl();
		GrammarState* returnControl = GetReturnControl();
		GrammarState* expression = GetExpression();

		StateTransition* transition1 = new StateTransition("Transition 1");
		transition1->AddNextState(gotoControl);
		transition1->AddNextState(identifier);
		transition1->AddNextState(endControl);

		StateTransition* transition2 = new StateTransition("Transition 2");
		transition2->AddNextState(continueControl);
		transition2->AddNextState(endControl);

		StateTransition* transition3 = new StateTransition("Transition 3");
		transition3->AddNextState(breakControl);
		transition3->AddNextState(endControl);

		StateTransition* transition4 = new StateTransition("Transition 4");
		transition4->AddNextState(returnControl);
		transition4->AddNextState(endControl);

		StateTransition* transition5 = new StateTransition("Transition 5");
		transition5->AddNextState(returnControl);
		transition5->AddNextState(expression);
		transition5->AddNextState(endControl);

		state->AddNextTransition(transition1);
		state->AddNextTransition(transition2);
		state->AddNextTransition(transition3);
		state->AddNextTransition(transition4);
		state->AddNextTransition(transition5);

		GetTokenFlow()->AddAcceptedTokens(state);
	}

	return state;
}

GrammarState* CGrammar::GetTranslationUnit()
{
	string stateName = "TranslationUnit";
	int stateType = StateType::TranslationUnit;

	GrammarState* state = GetDeclaredState(stateName, stateType);

	if (state == NULL)
	{
		state = new GrammarState(stateName, stateType);
		AddDeclaredState(state);

		GrammarState* externalDeclaration = GetExternalDeclaration();
		GrammarState* externalDefinition = GetExternalDefinition();

		StateTransition* transition1 = new StateTransition("Transition 1");
		transition1->AddNextState(externalDeclaration);

		transition1->AddAcceptedToken(CategorizedToken::GetCategorizedToken(CategorizedToken::VariableDeclarator, false), 0);
		transition1->AddAcceptedToken(CategorizedToken::GetCategorizedToken(CategorizedToken::VariableDeclarator, true), 0);
		transition1->AddAcceptedToken(CategorizedToken::GetCategorizedToken(CategorizedToken::MethodDeclarator, false), 0);
		transition1->AddAcceptedToken(CategorizedToken::GetCategorizedToken(CategorizedToken::MethodDeclarator, true), 0);

		StateTransition* transition2 = new StateTransition("Transition 2");
		transition2->AddNextState(state);
		transition2->AddNextState(externalDefinition);
		transition2->AddNextState(externalDeclaration);

		transition2->AddAcceptedToken(CategorizedToken::GetCategorizedToken(CategorizedToken::TypeHierarchy, false), 0);
		transition2->AddAcceptedToken(CategorizedToken::GetCategorizedToken(CategorizedToken::HashTagControl, false), 1);
		transition2->AddAcceptedToken(CategorizedToken::GetCategorizedToken(CategorizedToken::VariableDeclarator, false), 2);
		transition2->AddAcceptedToken(CategorizedToken::GetCategorizedToken(CategorizedToken::VariableDeclarator, true), 2);
		transition2->AddAcceptedToken(CategorizedToken::GetCategorizedToken(CategorizedToken::MethodDeclarator, false), 2);
		transition2->AddAcceptedToken(CategorizedToken::GetCategorizedToken(CategorizedToken::MethodDeclarator, true), 2);

		StateTransition* transition3 = new StateTransition("Transition 3");
		transition3->AddNextState(state);
		transition3->AddNextState(externalDeclaration);

		transition3->AddAcceptedToken(CategorizedToken::GetCategorizedToken(CategorizedToken::TypeHierarchy, false), 0);
		transition3->AddAcceptedToken(CategorizedToken::GetCategorizedToken(CategorizedToken::VariableDeclarator, false), 1);
		transition3->AddAcceptedToken(CategorizedToken::GetCategorizedToken(CategorizedToken::VariableDeclarator, true), 1);
		transition3->AddAcceptedToken(CategorizedToken::GetCategorizedToken(CategorizedToken::MethodDeclarator, false), 1);
		transition3->AddAcceptedToken(CategorizedToken::GetCategorizedToken(CategorizedToken::MethodDeclarator, true), 1);

		StateTransition* transition4 = new StateTransition("Transition 4");
		transition4->AddNextState(state);
		transition4->AddNextState(externalDefinition);

		transition4->AddAcceptedToken(CategorizedToken::GetCategorizedToken(CategorizedToken::TypeHierarchy, false), 0);
		transition4->AddAcceptedToken(CategorizedToken::GetCategorizedToken(CategorizedToken::HashTagControl, false), 1);

		state->AddNextTransition(transition1);
		state->AddNextTransition(transition2);
		state->AddNextTransition(transition3);
		state->AddNextTransition(transition4);

		GetTokenFlow()->AddAcceptedTokens(state);
	}
	
	return state;
}

GrammarState* CGrammar::GetExternalDeclaration()
{
	string stateName = "ExternalDeclaration";
	int stateType = StateType::ExternalDeclaration;

	GrammarState* state = GetDeclaredState(stateName, stateType);

	if (state == NULL)
	{
		state = new GrammarState(stateName, stateType);
		AddDeclaredState(state);

		GrammarState* functionDefinition = GetFunctionDefinition();
		GrammarState* declaration = GetDeclaration();

		StateTransition* transition1 = new StateTransition("Transition 1");
		transition1->AddNextState(functionDefinition);
		transition1->AddNextState(declaration);

		transition1->AddAcceptedToken(CategorizedToken::GetCategorizedToken(CategorizedToken::QualifierDefinition, false), 0);
		transition1->AddAcceptedToken(CategorizedToken::GetCategorizedToken(CategorizedToken::MethodDeclarator, false), 0);
		transition1->AddAcceptedToken(CategorizedToken::GetCategorizedToken(CategorizedToken::MethodDeclarator, true), 0);

		transition1->AddAcceptedToken(CategorizedToken::GetCategorizedToken(CategorizedToken::QualifierDefinition, false), 1);
		transition1->AddAcceptedToken(CategorizedToken::GetCategorizedToken(CategorizedToken::MethodDeclarator, false), 1);
		transition1->AddAcceptedToken(CategorizedToken::GetCategorizedToken(CategorizedToken::MethodDeclarator, true), 1);

		state->AddNextTransition(transition1);

		GetTokenFlow()->AddAcceptedTokens(state);
	}

	return state;
}

GrammarState* CGrammar::GetExternalInclusionExpression()
{
	string stateName = "ExternalInclusionExpression";
	int stateType = StateType::ExternalInclusionExpression;

	GrammarState* state = GetDeclaredState(stateName, stateType);

	if (state == NULL)
	{
		state = new GrammarState(stateName, stateType);
		AddDeclaredState(state);

		GrammarState* includePathLiteral = GetIncludePathLiteral();//Implement include path literal as same as StringLiteral
		GrammarState* stringLiteral = GetStringLiteral();

		StateTransition* transition1 = new StateTransition("Transition 1");
		transition1->AddNextState(stringLiteral);

		transition1->AddAcceptedToken(CategorizedToken::GetCategorizedToken(CategorizedToken::StringLiteral, false), 0);

		StateTransition* transition2 = new StateTransition("Transition 2");
		transition2->AddNextState(includePathLiteral);

		transition2->AddAcceptedToken(CategorizedToken::GetCategorizedToken(CategorizedToken::FilePathLiteral, false), 0);

		state->AddNextTransition(transition1);
		state->AddNextTransition(transition2);

		GetTokenFlow()->AddAcceptedTokens(state);
	}

	return state;
}

GrammarState* CGrammar::GetExternalDefinition()
{
	string stateName = "ExternalDefinition";
	int stateType = StateType::ExternalDefinition;

	GrammarState* state = GetDeclaredState(stateName, stateType);

	if (state == NULL)
	{
		state = new GrammarState(stateName, stateType);
		AddDeclaredState(state);

		GrammarState* hashTagControl = GetHashTagControl();
		GrammarState* includeControl = GetIncludeControl();
		GrammarState* defineControl = GetDefineControl();
		GrammarState* conditionalExpression = GetConditionalExpression();
		GrammarState* externalInclusionExpression = GetExternalInclusionExpression();

		StateTransition* transition1 = new StateTransition("Transition 1");
		transition1->AddNextState(state);
		transition1->AddNextState(hashTagControl);
		transition1->AddNextState(includeControl);
		transition1->AddNextState(externalInclusionExpression);

		transition1->AddAcceptedToken(CategorizedToken::GetCategorizedToken(CategorizedToken::HashTagControl, false), 0);

		transition1->AddAcceptedToken(CategorizedToken::GetCategorizedToken(CategorizedToken::HashTagControl, false), 1);

		transition1->AddAcceptedToken(CategorizedToken::GetCategorizedToken(CategorizedToken::IncludeControl, false), 2);

		transition1->AddAcceptedToken(CategorizedToken::GetCategorizedToken(CategorizedToken::StringLiteral, false), 3);
		transition1->AddAcceptedToken(CategorizedToken::GetCategorizedToken(CategorizedToken::FilePathLiteral, false), 3);

		StateTransition* transition2 = new StateTransition("Transition 2");
		transition2->AddNextState(hashTagControl);
		transition2->AddNextState(includeControl);
		transition2->AddNextState(externalInclusionExpression);

		transition2->AddAcceptedToken(CategorizedToken::GetCategorizedToken(CategorizedToken::HashTagControl, false), 0);

		transition2->AddAcceptedToken(CategorizedToken::GetCategorizedToken(CategorizedToken::IncludeControl, false), 1);

		transition2->AddAcceptedToken(CategorizedToken::GetCategorizedToken(CategorizedToken::StringLiteral, false), 2);
		transition2->AddAcceptedToken(CategorizedToken::GetCategorizedToken(CategorizedToken::FilePathLiteral, false), 2);

		StateTransition* transition3 = new StateTransition("Transition 3");
		transition3->AddNextState(state);
		transition3->AddNextState(hashTagControl);
		transition3->AddNextState(defineControl);
		transition3->AddNextState(conditionalExpression);

		transition3->AddAcceptedToken(CategorizedToken::GetCategorizedToken(CategorizedToken::HashTagControl, false), 0);
		transition3->AddAcceptedToken(CategorizedToken::GetCategorizedToken(CategorizedToken::HashTagControl, false), 1);
		transition3->AddAcceptedToken(CategorizedToken::GetCategorizedToken(CategorizedToken::DefineControl, false), 2);
		transition3->AddAcceptedToken(CategorizedToken::GetCategorizedToken(CategorizedToken::OpenParenthesesControl, false), 3);
		transition3->AddAcceptedToken(CategorizedToken::GetCategorizedToken(CategorizedToken::Identifier, false), 3);
		transition3->AddAcceptedToken(CategorizedToken::GetCategorizedToken(CategorizedToken::IntLiteral, false), 3);
		transition3->AddAcceptedToken(CategorizedToken::GetCategorizedToken(CategorizedToken::FloatLiteral, false), 3);
		transition3->AddAcceptedToken(CategorizedToken::GetCategorizedToken(CategorizedToken::LongLiteral, false), 3);
		transition3->AddAcceptedToken(CategorizedToken::GetCategorizedToken(CategorizedToken::DoubleLiteral, false), 3);

		StateTransition* transition4 = new StateTransition("Transition 4");
		transition4->AddNextState(hashTagControl);
		transition4->AddNextState(defineControl);
		transition4->AddNextState(conditionalExpression);

		transition4->AddAcceptedToken(CategorizedToken::GetCategorizedToken(CategorizedToken::HashTagControl, false), 0);
		transition4->AddAcceptedToken(CategorizedToken::GetCategorizedToken(CategorizedToken::DefineControl, false), 1);
		transition4->AddAcceptedToken(CategorizedToken::GetCategorizedToken(CategorizedToken::OpenParenthesesControl, false), 2);
		transition4->AddAcceptedToken(CategorizedToken::GetCategorizedToken(CategorizedToken::Identifier, false), 2);
		transition4->AddAcceptedToken(CategorizedToken::GetCategorizedToken(CategorizedToken::IntLiteral, false), 2);
		transition4->AddAcceptedToken(CategorizedToken::GetCategorizedToken(CategorizedToken::FloatLiteral, false), 2);
		transition4->AddAcceptedToken(CategorizedToken::GetCategorizedToken(CategorizedToken::LongLiteral, false), 2);
		transition4->AddAcceptedToken(CategorizedToken::GetCategorizedToken(CategorizedToken::DoubleLiteral, false), 2);

		state->AddNextTransition(transition1);
		state->AddNextTransition(transition2);
		state->AddNextTransition(transition3);
		state->AddNextTransition(transition4);

		GetTokenFlow()->AddAcceptedTokens(state);
	}

	return state;
}

GrammarState* CGrammar::GetFunctionDefinition()
{
	string stateName = "FunctionDefinition";
	int stateType = StateType::FunctionDefinition;

	GrammarState* state = GetDeclaredState(stateName, stateType);

	if (state == NULL)
	{
		state = new GrammarState(stateName, stateType);
		AddDeclaredState(state);

		GrammarState* declarationSpecifiers = GetDeclarationSpecifiers();
		GrammarState* declarator = GetDeclarator();
		GrammarState* declarationList = GetDeclarationList();
		GrammarState* compoundStatement = GetCompoundStatement();

		StateTransition* transition1 = new StateTransition("Transition 1");
		transition1->AddNextState(declarationSpecifiers);
		transition1->AddNextState(declarator);
		transition1->AddNextState(declarationList);
		transition1->AddNextState(compoundStatement);

		StateTransition* transition2 = new StateTransition("Transition 2");
		transition2->AddNextState(declarationSpecifiers);
		transition2->AddNextState(declarator);
		transition2->AddNextState(compoundStatement);

		StateTransition* transition3 = new StateTransition("Transition 3");
		transition3->AddNextState(declarator);
		transition3->AddNextState(declarationList);
		transition3->AddNextState(compoundStatement);

		StateTransition* transition4 = new StateTransition("Transition 4");
		transition4->AddNextState(declarator);
		transition4->AddNextState(compoundStatement);

		state->AddNextTransition(transition1);
		state->AddNextTransition(transition2);
		state->AddNextTransition(transition3);
		state->AddNextTransition(transition4);

		GetTokenFlow()->AddAcceptedTokens(state);
	}

	return state;
}

GrammarState* CGrammar::GetEndControl()
{
	string stateName = ";";
	int stateType = StateType::Control;

	return AddLiteralState(stateName, stateType);
}

GrammarState* CGrammar::GetCommaControl()
{
	string stateName = ",";
	int stateType = StateType::Control;

	return AddLiteralState(stateName, stateType);
}

GrammarState* CGrammar::GetDotControl()
{
	string stateName = ".";
	int stateType = StateType::Control;

	return AddLiteralState(stateName, stateType);
}

GrammarState* CGrammar::GetDoubleDotControl()
{
	string stateName = ":";
	int stateType = StateType::Control;

	return AddLiteralState(stateName, stateType);
}

GrammarState* CGrammar::GetOpenCurlyBracketControl()
{
	string stateName = "{";
	int stateType = StateType::Control;

	return AddLiteralState(stateName, stateType);
}

GrammarState* CGrammar::GetCloseCurlyBracketControl()
{
	string stateName = "}";
	int stateType = StateType::Control;

	return AddLiteralState(stateName, stateType);
}

GrammarState* CGrammar::GetOpenBracketControl()
{
	string stateName = "[";
	int stateType = StateType::Control;

	return AddLiteralState(stateName, stateType);
}

GrammarState* CGrammar::GetCloseBracketControl()
{
	string stateName = "]";
	int stateType = StateType::Control;

	return AddLiteralState(stateName, stateType);
}

GrammarState* CGrammar::GetOpenParenthesesControl()
{
	string stateName = "(";
	int stateType = StateType::Control;

	return AddLiteralState(stateName, stateType);
}

GrammarState* CGrammar::GetCloseParenthesesControl()
{
	string stateName = ")";
	int stateType = StateType::Control;

	return AddLiteralState(stateName, stateType);
}

GrammarState* CGrammar::GetPointerOperation()
{
	string stateName = "->";
	int stateType = StateType::Operation;

	return AddLiteralState(stateName, stateType);
}

GrammarState* CGrammar::GetIncrementOperation()
{
	string stateName = "++";
	int stateType = StateType::Operation;

	return AddLiteralState(stateName, stateType);
}

GrammarState* CGrammar::GetDecrementOperation()
{
	string stateName = "--";
	int stateType = StateType::Operation;

	return AddLiteralState(stateName, stateType);
}

GrammarState* CGrammar::GetMultiplicationOperation()
{
	string stateName = "*";
	int stateType = StateType::Operation;

	return AddLiteralState(stateName, stateType);
}

GrammarState* CGrammar::GetSumOperation()
{
	string stateName = "+";
	int stateType = StateType::Operation;

	return AddLiteralState(stateName, stateType);
}

GrammarState* CGrammar::GetSubtractionOperation()
{
	string stateName = "-";
	int stateType = StateType::Operation;

	return AddLiteralState(stateName, stateType);
}

GrammarState* CGrammar::GetDivisionOperation()
{
	string stateName = "/";
	int stateType = StateType::Operation;

	return AddLiteralState(stateName, stateType);
}

GrammarState* CGrammar::GetModOperation()
{
	string stateName = "%";
	int stateType = StateType::Operation;

	return AddLiteralState(stateName, stateType);
}

GrammarState* CGrammar::GetBitwiseNotOperation()
{
	string stateName = "~";
	int stateType = StateType::Operation;

	return AddLiteralState(stateName, stateType);
}

GrammarState* CGrammar::GetNotOperation()
{
	string stateName = "!";
	int stateType = StateType::Operation;

	return AddLiteralState(stateName, stateType, GrammarState::LeftToRight);
}

GrammarState* CGrammar::GetRightOperation()
{
	string stateName = ">>";
	int stateType = StateType::Operation;

	return AddLiteralState(stateName, stateType);
}

GrammarState* CGrammar::GetLeftOpreation()
{
	string stateName = "<<";
	int stateType = StateType::Operation;

	return AddLiteralState(stateName, stateType);
}

GrammarState* CGrammar::GetLessThanOperation()
{
	string stateName = "<";
	int stateType = StateType::Operation;

	return AddLiteralState(stateName, stateType);
}

GrammarState* CGrammar::GetGreaterThanOperation()
{
	string stateName = ">";
	int stateType = StateType::Operation;

	return AddLiteralState(stateName, stateType);
}

GrammarState* CGrammar::GetLessEqualOperation()
{
	string stateName = "<=";
	int stateType = StateType::Operation;

	return AddLiteralState(stateName, stateType);
}

GrammarState* CGrammar::GetGreaterEqualOperation()
{
	string stateName = ">=";
	int stateType = StateType::Operation;

	return AddLiteralState(stateName, stateType);
}

GrammarState* CGrammar::GetEqualOperation()
{
	string stateName = "==";
	int stateType = StateType::Operation;

	return AddLiteralState(stateName, stateType);
}

GrammarState* CGrammar::GetAndOperation()
{
	string stateName = "&&";
	int stateType = StateType::Operation;

	return AddLiteralState(stateName, stateType);
}

GrammarState* CGrammar::GetOrOperation()
{
	string stateName = "||";
	int stateType = StateType::Operation;

	return AddLiteralState(stateName, stateType);
}

GrammarState* CGrammar::GetNotEqualOperation()
{
	string stateName = "!=";
	int stateType = StateType::Operation;

	return AddLiteralState(stateName, stateType);
}

GrammarState* CGrammar::GetBitwiseAndOperation()
{
	string stateName = "&";
	int stateType = StateType::Operation;

	return AddLiteralState(stateName, stateType);
}

GrammarState* CGrammar::GetBitwiseOrOperation()
{
	string stateName = "|";
	int stateType = StateType::Operation;

	return AddLiteralState(stateName, stateType);
}

GrammarState* CGrammar::GetExclusiveOrOperation()
{
	string stateName = "^";
	int stateType = StateType::Operation;

	return AddLiteralState(stateName, stateType);
}

GrammarState* CGrammar::GetLogicalConditionOperation()
{
	string stateName = "?";
	int stateType = StateType::Operation;

	return AddLiteralState(stateName, stateType);
}

GrammarState* CGrammar::GetElseConditionOperation()
{
	string stateName = ":";
	int stateType = StateType::Operation;

	return AddLiteralState(stateName, stateType);
}

GrammarState* CGrammar::GetAssignmentOperation()
{
	string stateName = "=";
	int stateType = StateType::Operation;

	return AddLiteralState(stateName, stateType);
}

GrammarState* CGrammar::GetMultiplicationAssignmentOperation()
{
	string stateName = "*=";
	int stateType = StateType::Operation;

	return AddLiteralState(stateName, stateType);
}

GrammarState* CGrammar::GetDivisionAssignmentOperation()
{
	string stateName = "/=";
	int stateType = StateType::Operation;

	return AddLiteralState(stateName, stateType);
}

GrammarState* CGrammar::GetModAssignmentOperation()
{
	string stateName = "%=";
	int stateType = StateType::Operation;

	return AddLiteralState(stateName, stateType);
}

GrammarState* CGrammar::GetAdditionAssignmentOperation()
{
	string stateName = "+=";
	int stateType = StateType::Operation;

	return AddLiteralState(stateName, stateType);
}

GrammarState* CGrammar::GetSubtractionAssignmentOperation()
{
	string stateName = "-=";
	int stateType = StateType::Operation;

	return AddLiteralState(stateName, stateType);
}

GrammarState* CGrammar::GetLeftAssignmentOperation()
{
	string stateName = "<<=";
	int stateType = StateType::Operation;

	return AddLiteralState(stateName, stateType);
}

GrammarState* CGrammar::GetRightAssignmentOperation()
{
	string stateName = ">>=";
	int stateType = StateType::Operation;

	return AddLiteralState(stateName, stateType);
}

GrammarState* CGrammar::GetAndAssignmentOperation()
{
	string stateName = "&=";
	int stateType = StateType::Operation;

	return AddLiteralState(stateName, stateType);
}

GrammarState* CGrammar::GetOrAssignmentOperation()
{
	string stateName = "|=";
	int stateType = StateType::Operation;

	return AddLiteralState(stateName, stateType);
}

GrammarState* CGrammar::GetXorAssignmentOperation()
{
	string stateName = "^=";
	int stateType = StateType::Operation;

	return AddLiteralState(stateName, stateType);
}

GrammarState* CGrammar::GetSizeOfControl()
{
	string stateName = "sizeof";
	int stateType = StateType::Control;

	return AddLiteralState(stateName, stateType);
}

GrammarState* CGrammar::GetCaseControl()
{
	string stateName = "case";
	int stateType = StateType::Control;

	return AddLiteralState(stateName, stateType);
}

GrammarState* CGrammar::GetDefaultControl()
{
	string stateName = "default";
	int stateType = StateType::Control;

	return AddLiteralState(stateName, stateType);
}

GrammarState* CGrammar::GetIfControl()
{
	string stateName = "if";
	int stateType = StateType::Control;

	return AddLiteralState(stateName, stateType);
}

GrammarState* CGrammar::GetElseControl()
{
	string stateName = "else";
	int stateType = StateType::Control;

	return AddLiteralState(stateName, stateType);
}

GrammarState* CGrammar::GetSwitchControl()
{
	string stateName = "switch";
	int stateType = StateType::Control;

	return AddLiteralState(stateName, stateType);
}

GrammarState* CGrammar::GetGotoControl()
{
	string stateName = "goto";
	int stateType = StateType::Control;

	return AddLiteralState(stateName, stateType);
}

GrammarState* CGrammar::GetContinueControl()
{
	string stateName = "continue";
	int stateType = StateType::Control;

	return AddLiteralState(stateName, stateType);
}

GrammarState* CGrammar::GetBreakControl()
{
	string stateName = "break";
	int stateType = StateType::Control;

	return AddLiteralState(stateName, stateType);
}

GrammarState* CGrammar::GetReturnControl()
{
	string stateName = "return";
	int stateType = StateType::Control;

	return AddLiteralState(stateName, stateType);
}

GrammarState* CGrammar::GetWhileControl()
{
	string stateName = "while";
	int stateType = StateType::Control;

	return AddLiteralState(stateName, stateType);
}

GrammarState* CGrammar::GetDoControl()
{
	string stateName = "do";
	int stateType = StateType::Control;

	return AddLiteralState(stateName, stateType);
}

GrammarState* CGrammar::GetForControl()
{
	string stateName = "for";
	int stateType = StateType::Control;

	return AddLiteralState(stateName, stateType);
}

GrammarState* CGrammar::GetPointerControl()
{
	string stateName = "*";
	int stateType = StateType::Control;

	return AddLiteralState(stateName, stateType);
}

GrammarState* CGrammar::GetEllipsisControl()
{
	string stateName = "...";
	int stateType = StateType::Control;

	return AddLiteralState(stateName, stateType);
}

GrammarState* CGrammar::GetHashTagControl()
{
	string stateName = "#";
	int stateType = StateType::Control;

	return AddLiteralState(stateName, stateType);
}

GrammarState* CGrammar::GetIncludeControl()
{
	string stateName = "include";
	int stateType = StateType::Control;

	return AddLiteralState(stateName, stateType);
}

GrammarState* CGrammar::GetDefineControl()
{
	string stateName = "define";
	int stateType = StateType::Control;

	return AddLiteralState(stateName, stateType);
}

GrammarState* CGrammar::GetUnionSpecifierControl()
{
	string stateName = "union";
	int stateType = StateType::Control;

	return AddLiteralState(stateName, stateType);
}

GrammarState* CGrammar::GetTypedefSpecifierControl()
{
	string stateName = "typedef";
	int stateType = StateType::Control;

	return AddLiteralState(stateName, stateType);
}

GrammarState* CGrammar::GetExternSpecifierControl()
{
	string stateName = "extern";
	int stateType = StateType::Control;

	return AddLiteralState(stateName, stateType);
}

GrammarState* CGrammar::GetStaticSpecifierControl()
{
	string stateName = "static";
	int stateType = StateType::Control;

	return AddLiteralState(stateName, stateType);
}

GrammarState* CGrammar::GetAutoSpecifierControl()
{
	string stateName = "auto";
	int stateType = StateType::Control;

	return AddLiteralState(stateName, stateType);
}

GrammarState* CGrammar::GetRegisterSpecifierControl()
{
	string stateName = "register";
	int stateType = StateType::Control;

	return AddLiteralState(stateName, stateType);
}

GrammarState* CGrammar::GetConstQualifierControl()
{
	string stateName = "const";
	int stateType = StateType::Control;

	return AddLiteralState(stateName, stateType);
}

GrammarState* CGrammar::GetVolatileQualifierControl()
{
	string stateName = "volatile";
	int stateType = StateType::Control;

	return AddLiteralState(stateName, stateType);
}

GrammarState* CGrammar::GetVoidTypeControl()
{
	string stateName = "void";
	int stateType = StateType::Control;

	return AddLiteralState(stateName, stateType);
}

GrammarState* CGrammar::GetCharTypeControl()
{
	string stateName = "char";
	int stateType = StateType::TypeSpecifierControl;

	return AddLiteralState(stateName, stateType);
}

GrammarState* CGrammar::GetShortTypeControl()
{
	string stateName = "short";
	int stateType = StateType::TypeSpecifierControl;

	return AddLiteralState(stateName, stateType);
}

GrammarState* CGrammar::GetIntTypeControl()
{
	string stateName = "int";
	int stateType = StateType::TypeSpecifierControl;

	return AddLiteralState(stateName, stateType);
}

GrammarState* CGrammar::GetLongTypeControl()
{
	string stateName = "long";
	int stateType = StateType::TypeSpecifierControl;

	return AddLiteralState(stateName, stateType);
}

GrammarState* CGrammar::GetFloatTypeControl()
{
	string stateName = "float";
	int stateType = StateType::TypeSpecifierControl;

	return AddLiteralState(stateName, stateType);
}

GrammarState* CGrammar::GetDoubleTypeControl()
{
	string stateName = "double";
	int stateType = StateType::TypeSpecifierControl;

	return AddLiteralState(stateName, stateType);
}

GrammarState* CGrammar::GetSignedTypeControl()
{
	string stateName = "signed";
	int stateType = StateType::TypeSpecifierControl;

	return AddLiteralState(stateName, stateType);
}

GrammarState* CGrammar::GetUnsignedTypeControl()
{
	string stateName = "unsigned";
	int stateType = StateType::TypeSpecifierControl;

	return AddLiteralState(stateName, stateType);
}

GrammarState* CGrammar::GetTypenameTypeControl()
{
	string stateName = "typename";
	int stateType = StateType::TypeSpecifierControl;

	return AddLiteralState(stateName, stateType);
}

GrammarState* CGrammar::GetStructTypeControl()
{
	string stateName = "struct";
	int stateType = StateType::TypeSpecifierControl;

	return AddLiteralState(stateName, stateType);
}

GrammarState* CGrammar::GetEnumTypeControl()
{
	string stateName = "enum";
	int stateType = StateType::TypeSpecifierControl;

	return AddLiteralState(stateName, stateType);
}

GrammarState* CGrammar::GetIdentifier()
{
	string stateName = "Identifier";
	int stateType = StateType::Identifier;

	return AddLiteralState(stateName, stateType);
}

GrammarState* CGrammar::GetConstant()
{
	string stateName = "Constant";
	int stateType = StateType::Constant;

	return AddLiteralState(stateName, stateType);
}

GrammarState* CGrammar::GetStringLiteral()
{
	string stateName = "StringLiteral";
	int stateType = StateType::StringLiteral;

	return AddLiteralState(stateName, stateType);
}

GrammarState* CGrammar::GetIncludePathLiteral()
{
	string stateName = "IncludePathLiteral";
	int stateType = StateType::IncludePathLiteral;

	return AddLiteralState(stateName, stateType);
}