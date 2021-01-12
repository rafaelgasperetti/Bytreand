#pragma once

#include <Tools/VectorUtils.h>
#include <Tools/Comparable.h>

#include<Compiler/MiddleEnd/GrammarState.h>

class StateTransition;

class CategorizedToken : Comparable
{
	private:
		string Token;
		int Type;
		CategorizedToken* ParentCategory;
		bool Pointer = false;
		vector<CategorizedToken*>* Children = new vector<CategorizedToken*>();
		bool RegularExpression = false;//True when the token represents a regular expression.

	public:
		CategorizedToken(string, int);
		CategorizedToken(string, int, bool);
		CategorizedToken(string, int, bool, bool);
		void SetToken(string);
		string GetToken();
		void SetType(int);
		int GetType();
		void SetParentCategory(CategorizedToken*);
		CategorizedToken* GetParentCategory();
		void SetPointer(bool);//If is a pointer type.
		bool IsPointer();
		void AddChild(CategorizedToken*);
		CategorizedToken* GetChild(string, int, bool);
		vector<CategorizedToken*>* GetChildren();
		bool IsFinal();
		void SetRegularExpression(bool);
		bool IsRegularExpression();

		static CategorizedToken* GetCategorizedToken(int, bool);
		static vector<CategorizedToken*>* GetCategorizedTokenChildren(CategorizedToken*);
		static vector<CategorizedToken*>* GetCategorizedTokenChildren(int, bool);
		
		enum Types
		{
			TypeHierarchy,
				Reserved,
					TemplateDefinition,
					TypeDefinition,
						LiteralDefinition,
							IntLiteral,
							LongLiteral,
							FloatLiteral,
							DoubleLiteral,
							CharLiteral,
							StringLiteral,
							FilePathLiteral,
						Declarator,
							SystemTypeDefinition,
								TypeNameControl,
							StorageDefinition,
								TypedefControl,
								ExternControl,
								StaticControl,
								AutoControl,
								RegisterControl,
							QualifierDefinition,
								ConstControl,
								VolatileControl,
							VariableDeclarator,
								VariableVoidControl,
								VariableIntControl,
								VariableLongControl,
								VariableFloatControl,
								VariableDoubleControl,
								VariableCharControl,
								VariableStringControl,
							MethodDeclarator,
								MethodVoidControl,
								MethodIntControl,
								MethodLongControl,
								MethodFloatControl,
								MethodDoubleControl,
								MethodCharControl,
								MethodStringControl,
							ExternalDeclarator,
								HashTagControl,
							ExternalDefiner,
								IncludeControl,
								DefineControl,
					Control,
						TypeControl,
							VoidControl,
							IntControl,
							LongControl,
							FloatControl,
							DoubleControl,
							CharControl,
							StringControl,
						ContextControl,
							OpenCurlyBracketControl,
							CloseCurlyBracketControl,
							OpenParenthesesControl,
							CloseParenthesesControl,
							OpenBracketControl,
							CloseBracketControl,
						ConditionalControl,
							IfControl,
							ElseControl,
							SwitchControl,
							CaseControl,
							WhenControl,
							DefaultControl,
							ShorIfControl,
							ShortElseControl,
						LoopControl,
							ForControl,
							WhileControl,
							DoControl,
							ForEachControl,
						Operation,
							TwoOperands,
								ArithmeticOperation,
									SumControl,
									SubtractionControl,
									MultiplicationControl,
									DivisionControl,
									ModControl,
									LeftShiftControl,
									RightShiftControl,
									BitwiseAndControl,
									BitwiseOrControl,
									BitwiseNotControl,
									CompoundSumControl,
									CompoundSubtractionControl,
									CompoundMultiplicationControl,
									CompoundDivisionControl,
									CompoundModControl,
									CompoundLeftShiftControl,
									CompoundRightShiftControl,
								TwoOperandsBooleanOperation,
									AndControl,
									OrControl,
									EqualControl,
									DifferentControl,
									GreaterThanControl,
									LowerThanControl,
									GreaterEqualControl,
									LowerEqualControl,
							OneOperand,
								OneOperandBooleanOperation,
									NotControl,
						ProceduralControl,
							PointerControl,
							DotControl,
							CommaControl,
							EndCommandControl,
				Identifier,
					VariableIdentifier,
						//TypeControls
					MethodIdentifier,
						//TypeControls
					ConstantIdentifier
						//LiteralDefinition
		};
};