#pragma once

#include <Compiler/MiddleEnd/Grammar.h>

/*
	Grammar reference guide to this CGrammar rules at https://www.lysator.liu.se/c/ANSI-C-grammar-y.html
*/

class CGrammar : public Grammar
{
	public:
		CGrammar(int, TokenCursor*);

		bool NodeDecision(GrammarState*, GrammarState*, vector<FrontEndToken*>*, int) override;
		GrammarState* FillGrammar() override;

		vector<string> GetDataModifiers() override;
		vector<string> GetDataTypes() override;
		vector<string> GetAllButDataTypesAndVariables() override;
		vector<string> GetAllButIdentifiers() override;

		GrammarState* GetPrimaryExpression();
		GrammarState* GetPostfixExpression();
		GrammarState* GetArgumentExpressionList();
		GrammarState* GetUnaryExpression();
		GrammarState* GetUnaryOperator();
		GrammarState* GetCastExpression();
		GrammarState* GetMultiplicativeExpression();
		GrammarState* GetAdditiveExpression();
		GrammarState* GetShiftExpression();
		GrammarState* GetRelationalExpression();
		GrammarState* GetEqualityExpression();
		GrammarState* GetAndExpression();
		GrammarState* GetExclusiveOrExpression();
		GrammarState* GetInclusiveOrExpression();
		GrammarState* GetLogicalAndExpression();
		GrammarState* GetLogicalOrExpression();
		GrammarState* GetConditionalExpression();
		GrammarState* GetAssignmentExpression();
		GrammarState* GetAssignmentOperator();
		GrammarState* GetExpression();
		GrammarState* GetConstantExpression();
		GrammarState* GetDeclaration();
		GrammarState* GetDeclarationSpecifiers();
		GrammarState* GetInitDeclaratorList();
		GrammarState* GetInitDeclarator();
		GrammarState* GetStorageClassSpecifier();
		GrammarState* GetTypeSpecifier();
		GrammarState* GetStructOrUnionSpecifier();
		GrammarState* GetStructOrUnion();
		GrammarState* GetStructDeclarationList();
		GrammarState* GetStructDeclaration();
		GrammarState* GetSpecifierQualifierList();
		GrammarState* GetStructDeclaratorList();
		GrammarState* GetStructDeclarator();
		GrammarState* GetEnumSpecifier();
		GrammarState* GetEnumeratorList();
		GrammarState* GetEnumerator();
		GrammarState* GetTypeQualifier();
		GrammarState* GetDeclarator();
		GrammarState* GetDirectDeclarator();
		GrammarState* GetPointer();
		GrammarState* GetTypeQualifierList();
		GrammarState* GetParameterTypeList();
		GrammarState* GetParameterList();
		GrammarState* GetParameterDeclaration();
		GrammarState* GetIdentifierList();
		GrammarState* GetTypeName();
		GrammarState* GetAbstractDeclarator();
		GrammarState* GetDirectAbstractDeclarator();
		GrammarState* GetInitializer();
		GrammarState* GetInitializerList();
		GrammarState* GetStatement();
		GrammarState* GetLabeledStatement();
		GrammarState* GetCompoundStatement();
		GrammarState* GetDeclarationList();
		GrammarState* GetStatementList();
		GrammarState* GetExpressionStatement();
		GrammarState* GetSelectionStatement();
		GrammarState* GetIterationStatement();
		GrammarState* GetJumpStatement();
		GrammarState* GetTranslationUnit();
		GrammarState* GetExternalDeclaration();
		GrammarState* GetExternalDefinition();
		GrammarState* GetFunctionDefinition();
		GrammarState* GetExternalInclusionExpression();
		
		GrammarState* GetEndControl();//;
		GrammarState* GetCommaControl();//,
		GrammarState* GetDotControl();//.
		GrammarState* GetDoubleDotControl();//:
		GrammarState* GetOpenCurlyBracketControl();//{
		GrammarState* GetCloseCurlyBracketControl();//}
		GrammarState* GetOpenBracketControl();//[
		GrammarState* GetCloseBracketControl();//]
		GrammarState* GetOpenParenthesesControl();//(
		GrammarState* GetCloseParenthesesControl();//)
		GrammarState* GetSizeOfControl();//sizeof
		GrammarState* GetCaseControl();//case
		GrammarState* GetDefaultControl();//default
		GrammarState* GetIfControl();//if
		GrammarState* GetElseControl();//else
		GrammarState* GetSwitchControl();//switch
		GrammarState* GetGotoControl();//goto
		GrammarState* GetContinueControl();//continue
		GrammarState* GetBreakControl();//break
		GrammarState* GetReturnControl();//return
		GrammarState* GetWhileControl();//while
		GrammarState* GetDoControl();//do
		GrammarState* GetForControl();//for
		GrammarState* GetPointerControl();//*
		GrammarState* GetEllipsisControl();//...
		GrammarState* GetHashTagControl();//#
		GrammarState* GetIncludeControl();//include
		GrammarState* GetDefineControl();//define
		
		GrammarState* GetTypedefSpecifierControl();//typedef
		GrammarState* GetExternSpecifierControl();//extern
		GrammarState* GetStaticSpecifierControl();//static
		GrammarState* GetAutoSpecifierControl();//auto
		GrammarState* GetRegisterSpecifierControl();//register
		GrammarState* GetUnionSpecifierControl();//union

		GrammarState* GetConstQualifierControl();//const
		GrammarState* GetVolatileQualifierControl();//volatile

		GrammarState* GetVoidTypeControl();//void
		GrammarState* GetCharTypeControl();//char
		GrammarState* GetShortTypeControl();//short
		GrammarState* GetIntTypeControl();//int
		GrammarState* GetLongTypeControl();//long
		GrammarState* GetFloatTypeControl();//float
		GrammarState* GetDoubleTypeControl();//double
		GrammarState* GetSignedTypeControl();//signed
		GrammarState* GetUnsignedTypeControl();//unsigned
		GrammarState* GetTypenameTypeControl();//typename
		GrammarState* GetStructTypeControl();//struct
		GrammarState* GetEnumTypeControl();//enum

		GrammarState* GetPointerOperation();//->
		GrammarState* GetIncrementOperation();//++
		GrammarState* GetDecrementOperation();//--
		GrammarState* GetMultiplicationOperation();//*
		GrammarState* GetSumOperation();//+
		GrammarState* GetSubtractionOperation();//-
		GrammarState* GetDivisionOperation();////
		GrammarState* GetModOperation();////
		GrammarState* GetBitwiseNotOperation();//~
		GrammarState* GetNotOperation();//!
		GrammarState* GetRightOperation();//>>
		GrammarState* GetLeftOpreation();//<<
		GrammarState* GetLessThanOperation();//<
		GrammarState* GetGreaterThanOperation();//>
		GrammarState* GetLessEqualOperation();//<=
		GrammarState* GetGreaterEqualOperation();//>=
		GrammarState* GetEqualOperation();//==
		GrammarState* GetAndOperation();//&&
		GrammarState* GetOrOperation();//||
		GrammarState* GetNotEqualOperation();//!=
		GrammarState* GetBitwiseAndOperation();//&
		GrammarState* GetBitwiseOrOperation();//| (called as 'InclusiveOr' at grammar website)
		GrammarState* GetExclusiveOrOperation();//^
		GrammarState* GetLogicalConditionOperation();//?
		GrammarState* GetElseConditionOperation();//:
		GrammarState* GetAssignmentOperation();//=
		GrammarState* GetMultiplicationAssignmentOperation();//*
		GrammarState* GetDivisionAssignmentOperation();///=
		GrammarState* GetModAssignmentOperation();//%
		GrammarState* GetAdditionAssignmentOperation();//+=
		GrammarState* GetSubtractionAssignmentOperation();//-=
		GrammarState* GetLeftAssignmentOperation();//<<=
		GrammarState* GetRightAssignmentOperation();//>>=
		GrammarState* GetAndAssignmentOperation();//&=
		GrammarState* GetOrAssignmentOperation();//|=
		GrammarState* GetXorAssignmentOperation();//^=

		GrammarState* GetIdentifier();
		GrammarState* GetConstant();
		GrammarState* GetStringLiteral();
		GrammarState* GetIncludePathLiteral();//C://...

		static const string HASH_TAG_CONTROL;
		static const string INCLUDE_CONTROL;
		static const string DEFINE_CONTROL;
		static const string LESS_THAN_OPERATION;
		static const string GREATER_THAN_OPERATION;
		static const string END_CONTROL;
};