#pragma once

#include <Tools/VectorUtils.h>

#include <Compiler/FrontEnd/TokenCursor.h>

#include <Compiler/MiddleEnd/GrammarState.h>
#include <Compiler/MiddleEnd/StateTransition.h>
#include <Compiler/MiddleEnd/GrammarTokenFlow.h>

class SemanticTree;
class GrammarState;
class StateTransition;
class GrammarTokenFlow;

class Grammar
{
	private:
		string LanguageName;
		int LanguageCode = -1;
		TokenCursor* Cursor;
		GrammarState* RootState;
		void SetRootState(GrammarState*);
		virtual GrammarState* FillGrammar() = 0;//Fills al lthe GrammarStates of the language and returns the root grammar kind that originates all of the others
		vector<GrammarState*>* DeclaredStates = new vector<GrammarState*>();
		GrammarTokenFlow* TokenFlow;

	public:
		Grammar(int, TokenCursor*, GrammarTokenFlow*);
		string GetLanguageName();
		void SetLanguageCode(int);
		int GetLanguageCode();
		void SetTokenCursor(TokenCursor*);
		TokenCursor* GetTokenCursor();
		GrammarState* GetRootState();
		bool IsDataTypeOrVariable(string);
		bool IsIdentifier(string);
		void AddDeclaredState(GrammarState*);
		GrammarState* GetDeclaredState(string, int);
		void SetTokenFlow(GrammarTokenFlow*);
		GrammarTokenFlow* GetTokenFlow();

		vector<int> TransitionDecision(StateTransition*, GrammarState*, vector<FrontEndToken*>*, int);
		virtual bool NodeDecision(GrammarState*, GrammarState*, vector<FrontEndToken*>*, int) = 0;//Decides wich state to follow according to the grammar

		static Grammar* GetGrammar(TokenCursor*);

		enum StateType
		{
			PrimaryExpression,
			PostfixExpression,
			ArgumentExpressionList,
			UnaryExpression,
			UnaryOperator,
			CastExpression,
			MultiplicativeExpression,
			AdditiveExpression,
			ShiftExpression,
			RelationalExpression,
			EqualityExpression,
			AndExpression,
			ExclusiveOrExpression,
			InclusiveOrExpression,
			LogicalAndExpression,
			LogicalOrExpression,
			ConditionalExpression,
			AssignmentExpression,
			AssignmentOperator,
			Expression,
			ConstantExpression,
			Declaration,
			DeclarationSpecifiers,
			InitDeclaratorList,
			InitDeclarator,
			StorageClassSpecifier,
			TypeSpecifier,
			StructOrUnionSpecifier,
			StructOrUnion,
			StructDeclarationList,
			StructDeclaration,
			SpecifierQualifierList,
			StructDeclaratorList,
			StructDeclarator,
			EnumSpecifier,
			EnumeratorList,
			Enumerator,
			TypeQualifier,
			Declarator,
			DirectDeclarator,
			Pointer,
			TypeQualifierList,
			ParameterTypeList,
			ParameterList,
			ParameterDeclaration,
			IdentifierList,
			TypeName,
			AbstractDeclarator,
			DirectAbstractDeclarator,
			Initializer,
			InitializerList,
			Statement,
			LabeledStatement,
			CompoundStatement,
			DeclarationList,
			StatementList,
			ExpressionStatement,
			SelectionStatement,
			IterationStatement,
			JumpStatement,
			TranslationUnit,
			ExternalDeclaration,
			ExternalDefinition,
			FunctionDefinition,
			ExternalInclusionExpression,
			Control,
			Identifier,
			Constant,
			StringLiteral,
			IncludePathLiteral,
			Operation,
			StorageClassSpecifierControl,
			TypeSpecifierControl,
			TypeQualifierControl
		};

	protected:
		GrammarState* AddLiteralState(string, int);
		GrammarState* AddLiteralState(string, int, int);

		virtual vector<string> GetDataModifiers() = 0;
		virtual vector<string> GetDataTypes() = 0;
		virtual vector<string> GetAllButDataTypesAndVariables() = 0;
		virtual vector<string> GetAllButIdentifiers() = 0;
};