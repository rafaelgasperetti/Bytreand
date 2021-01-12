#include <Compiler/MiddleEnd/Languages/C/CGrammarTokenFlow.h>

CGrammarTokenFlow::CGrammarTokenFlow(Grammar* relatedGrammar) : GrammarTokenFlow(relatedGrammar)
{

}

vector<pair<int, pair<GrammarState*, vector<CategorizedToken*>*>*>*>* CGrammarTokenFlow::GetAcceptedTokens(GrammarState* state)
{
	vector<pair<int, pair<GrammarState*, vector<CategorizedToken*>*>*>*>* ret = new vector<pair<int, pair<GrammarState*, vector<CategorizedToken*>*>*>*>();
	if (state != NULL)
	{
		int stateTransition = 0;
		switch (state->GetType())
		{
			case Grammar::PrimaryExpression:
				break;
			case Grammar::PostfixExpression:
				break;
			case Grammar::ArgumentExpressionList:
				break;
			case Grammar::UnaryExpression:
				break;
			case Grammar::UnaryOperator:
				break;
			case Grammar::CastExpression:
				break;
			case Grammar::MultiplicativeExpression:
				break;
			case Grammar::AdditiveExpression:
				break;
			case Grammar::ShiftExpression:
				break;
			case Grammar::RelationalExpression:
				break;
			case Grammar::EqualityExpression:
				break;
			case Grammar::AndExpression:
				break;
			case Grammar::ExclusiveOrExpression:
				break;
			case Grammar::InclusiveOrExpression:
				break;
			case Grammar::LogicalAndExpression:
				break;
			case Grammar::LogicalOrExpression:
				break;
			case Grammar::ConditionalExpression:
				break;
			case Grammar::AssignmentExpression:
				break;
			case Grammar::AssignmentOperator:
				break;
			case Grammar::Expression:
				break;
			case Grammar::ConstantExpression:
				break;
			case Grammar::Declaration:
				break;
			case Grammar::DeclarationSpecifiers:
				PushNewFlow(ret, stateTransition, state->GetNextState(stateTransition++, 0), CategorizedToken::GetCategorizedTokenChildren(CategorizedToken::StorageDefinition, false));

				PushNewFlow(ret, stateTransition,  state->GetNextState(stateTransition, 0), CategorizedToken::GetCategorizedTokenChildren(CategorizedToken::StorageDefinition, false));
				PushNewFlow(ret, stateTransition,  state->GetNextState(stateTransition, 1), CategorizedToken::GetCategorizedTokenChildren(CategorizedToken::VariableDeclarator, false));
				PushNewFlow(ret, stateTransition,  state->GetNextState(stateTransition, 1), CategorizedToken::GetCategorizedTokenChildren(CategorizedToken::MethodDeclarator, false));
				PushNewFlow(ret, stateTransition,  state->GetNextState(stateTransition++, 1), CategorizedToken::GetCategorizedTokenChildren(CategorizedToken::QualifierDefinition, false));

				PushNewFlow(ret, stateTransition,  state->GetNextState(stateTransition, 0), CategorizedToken::GetCategorizedTokenChildren(CategorizedToken::VariableDeclarator, false));
				PushNewFlow(ret, stateTransition,  state->GetNextState(stateTransition++, 0), CategorizedToken::GetCategorizedTokenChildren(CategorizedToken::MethodDeclarator, false));

				PushNewFlow(ret, stateTransition, state->GetNextState(stateTransition, 0), CategorizedToken::GetCategorizedTokenChildren(CategorizedToken::VariableDeclarator, false));
				PushNewFlow(ret, stateTransition, state->GetNextState(stateTransition, 0), CategorizedToken::GetCategorizedTokenChildren(CategorizedToken::MethodDeclarator, false));
				PushNewFlow(ret, stateTransition, state->GetNextState(stateTransition, 1), CategorizedToken::GetCategorizedTokenChildren(CategorizedToken::VariableDeclarator, false));
				PushNewFlow(ret, stateTransition, state->GetNextState(stateTransition, 1), CategorizedToken::GetCategorizedTokenChildren(CategorizedToken::MethodDeclarator, false));
				PushNewFlow(ret, stateTransition, state->GetNextState(stateTransition++, 1), CategorizedToken::GetCategorizedTokenChildren(CategorizedToken::QualifierDefinition, false));

				PushNewFlow(ret, stateTransition, state->GetNextState(stateTransition++, 0), CategorizedToken::GetCategorizedTokenChildren(CategorizedToken::QualifierDefinition, false));

				PushNewFlow(ret, stateTransition, state->GetNextState(stateTransition, 0), CategorizedToken::GetCategorizedTokenChildren(CategorizedToken::QualifierDefinition, false));
				PushNewFlow(ret, stateTransition, state->GetNextState(stateTransition, 1), CategorizedToken::GetCategorizedTokenChildren(CategorizedToken::VariableDeclarator, false));
				PushNewFlow(ret, stateTransition, state->GetNextState(stateTransition, 1), CategorizedToken::GetCategorizedTokenChildren(CategorizedToken::MethodDeclarator, false));
				PushNewFlow(ret, stateTransition, state->GetNextState(stateTransition++, 1), CategorizedToken::GetCategorizedTokenChildren(CategorizedToken::QualifierDefinition, false));
				break;
			case Grammar::InitDeclaratorList:
				break;
			case Grammar::InitDeclarator:
				break;
			case Grammar::StorageClassSpecifier:
				break;
			case Grammar::TypeSpecifier:
				break;
			case Grammar::StructOrUnionSpecifier:
				break;
			case Grammar::StructOrUnion:
				break;
			case Grammar::StructDeclarationList:
				break;
			case Grammar::StructDeclaration:
				break;
			case Grammar::SpecifierQualifierList:
				break;
			case Grammar::StructDeclaratorList:
				break;
			case Grammar::StructDeclarator:
				break;
			case Grammar::EnumSpecifier:
				break;
			case Grammar::EnumeratorList:
				break;
			case Grammar::Enumerator:
				break;
			case Grammar::TypeQualifier:
				break;
			case Grammar::Declarator:
				break;
			case Grammar::DirectDeclarator:
				break;
			case Grammar::Pointer:
				break;
			case Grammar::TypeQualifierList:
				break;
			case Grammar::ParameterTypeList:
				break;
			case Grammar::ParameterList:
				break;
			case Grammar::ParameterDeclaration:
				break;
			case Grammar::IdentifierList:
				break;
			case Grammar::TypeName:
				break;
			case Grammar::AbstractDeclarator:
				break;
			case Grammar::DirectAbstractDeclarator:
				break;
			case Grammar::Initializer:
				break;
			case Grammar::InitializerList:
				break;
			case Grammar::Statement:
				break;
			case Grammar::LabeledStatement:
				break;
			case Grammar::CompoundStatement:
				break;
			case Grammar::DeclarationList:
				break;
			case Grammar::StatementList:
				break;
			case Grammar::ExpressionStatement:
				break;
			case Grammar::SelectionStatement:
				break;
			case Grammar::IterationStatement:
				break;
			case Grammar::JumpStatement:
				break;
			case Grammar::TranslationUnit:
				(*state->GetNextTransitions())[0]->AddAcceptedToken(CategorizedToken::GetCategorizedToken(CategorizedToken::VariableDeclarator, false), 0);
				(*state->GetNextTransitions())[0]->AddAcceptedToken(CategorizedToken::GetCategorizedToken(CategorizedToken::VariableDeclarator, true), 0);
				(*state->GetNextTransitions())[0]->AddAcceptedToken(CategorizedToken::GetCategorizedToken(CategorizedToken::MethodDeclarator, false), 0);
				(*state->GetNextTransitions())[0]->AddAcceptedToken(CategorizedToken::GetCategorizedToken(CategorizedToken::MethodDeclarator, true), 0);

				(*state->GetNextTransitions())[1]->AddAcceptedToken(CategorizedToken::GetCategorizedToken(CategorizedToken::TypeHierarchy, false), 0);
				(*state->GetNextTransitions())[1]->AddAcceptedToken(CategorizedToken::GetCategorizedToken(CategorizedToken::HashTagControl, false), 1);
				(*state->GetNextTransitions())[1]->AddAcceptedToken(CategorizedToken::GetCategorizedToken(CategorizedToken::VariableDeclarator, false), 2);
				(*state->GetNextTransitions())[1]->AddAcceptedToken(CategorizedToken::GetCategorizedToken(CategorizedToken::VariableDeclarator, true), 2);
				(*state->GetNextTransitions())[1]->AddAcceptedToken(CategorizedToken::GetCategorizedToken(CategorizedToken::MethodDeclarator, false), 2);
				(*state->GetNextTransitions())[1]->AddAcceptedToken(CategorizedToken::GetCategorizedToken(CategorizedToken::MethodDeclarator, true), 2);

				(*state->GetNextTransitions())[2]->AddAcceptedToken(CategorizedToken::GetCategorizedToken(CategorizedToken::TypeHierarchy, false), 0);
				(*state->GetNextTransitions())[2]->AddAcceptedToken(CategorizedToken::GetCategorizedToken(CategorizedToken::VariableDeclarator, false), 1);
				(*state->GetNextTransitions())[2]->AddAcceptedToken(CategorizedToken::GetCategorizedToken(CategorizedToken::VariableDeclarator, true), 1);
				(*state->GetNextTransitions())[2]->AddAcceptedToken(CategorizedToken::GetCategorizedToken(CategorizedToken::MethodDeclarator, false), 1);
				(*state->GetNextTransitions())[2]->AddAcceptedToken(CategorizedToken::GetCategorizedToken(CategorizedToken::MethodDeclarator, true), 1);

				(*state->GetNextTransitions())[3]->AddAcceptedToken(CategorizedToken::GetCategorizedToken(CategorizedToken::TypeHierarchy, false), 0);
				(*state->GetNextTransitions())[3]->AddAcceptedToken(CategorizedToken::GetCategorizedToken(CategorizedToken::HashTagControl, false), 1);
				break;
			case Grammar::ExternalDeclaration:
				break;
			case Grammar::ExternalDefinition:
				break;
			case Grammar::FunctionDefinition:
				break;
			case Grammar::ExternalInclusionExpression:
				break;
			case Grammar::Control:
				break;
			case Grammar::Identifier:
				break;
			case Grammar::Constant:
				break;
			case Grammar::StringLiteral:
				break;
			case Grammar::IncludePathLiteral:
				break;
			case Grammar::Operation:
				break;
			case Grammar::StorageClassSpecifierControl:
				break;
			case Grammar::TypeSpecifierControl:
				break;
			case Grammar::TypeQualifierControl:
				break;
			default:
				throw invalid_argument("Invalid GrammarState type \"" + StringUtils::ToString(state->GetType()) + "\"");
		}
	}
	else
	{
		throw invalid_argument("It is not possible to identify the accepted tokens of a null GrammarState.");
	}
	return ret;
}