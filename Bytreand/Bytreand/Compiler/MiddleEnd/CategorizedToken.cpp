#include <Compiler/MiddleEnd/CategorizedToken.h>

CategorizedToken::CategorizedToken(string token, int type)
{
	SetToken(token);
	SetType(type);
}

CategorizedToken::CategorizedToken(string token, int type, bool pointer)
{
	SetToken(token);
	SetType(type);
	SetPointer(pointer);
}

CategorizedToken::CategorizedToken(string token, int type, bool pointer, bool regularExpression)
{
	SetToken(token);
	SetType(type);
	SetPointer(pointer);
	SetRegularExpression(regularExpression);
}


void CategorizedToken::SetToken(string token)
{
	Token = token;
}

string CategorizedToken::GetToken()
{
	return Token;
}

void CategorizedToken::SetType(int type)
{
	if (type >= Types::Reserved && type <= Types::ConstantIdentifier)
	{
		Type = type;
	}
	else
	{
		throw invalid_argument("Invalid categorized token type \"" + StringUtils::ToString(type) + "\"");
	}
}

int CategorizedToken::GetType()
{
	return Type;
}

void CategorizedToken::SetParentCategory(CategorizedToken* parentCategory)
{
	ParentCategory = parentCategory;
}

CategorizedToken* CategorizedToken::GetParentCategory()
{
	return ParentCategory;
}

void CategorizedToken::SetPointer(bool pointer)
{
	Pointer = pointer;
}

bool CategorizedToken::IsPointer()
{
	return Pointer;
}

void CategorizedToken::AddChild(CategorizedToken* child)
{
	if (child != NULL && GetChild(child->GetToken(), child->GetType(), child->IsPointer()) == NULL)
	{
		Children->push_back(child);
		child->SetParentCategory(this);
	}
	else if (child == NULL)
	{
		throw invalid_argument("It is not possible to add a NULL child at a CategorizedToken.");
	}
	else
	{
		throw invalid_argument("It is not possible to add a duplicated child at CategorizedToken. Duplicated child: \"" + child->GetToken() + "\"");
	}
}

CategorizedToken* CategorizedToken::GetChild(string token, int type, bool pointer)
{
	CategorizedToken* ret = NULL;
	for (CategorizedToken* child : (*Children))
	{
		if (StringUtils::Equals(child->GetToken(), token) && child->GetType() == type && child->IsPointer() == pointer)
		{
			ret = child;
		}
	}
	return ret;
}

vector<CategorizedToken*>* CategorizedToken::GetChildren()
{
	return Children;
}

bool CategorizedToken::IsFinal()
{
	return Children->size() == 0;
}

void CategorizedToken::SetRegularExpression(bool regularExpression)
{
	RegularExpression = regularExpression;
}

bool CategorizedToken::IsRegularExpression()
{
	return RegularExpression;
}

CategorizedToken* CategorizedToken::GetCategorizedToken(int type, bool pointer)
{
	CategorizedToken* ret;
	switch (type)
	{
		case TypeNameControl:
			return new CategorizedToken("typename", type, false);

		case ConstControl:
			return new CategorizedToken("const", type, false);
		case VolatileControl:
			return new CategorizedToken("volatile", type, false);

		case TypedefControl:
			return new CategorizedToken("typedef", type, false);
		case ExternControl:
			return new CategorizedToken("extern", type, pointer);
		case StaticControl:
			return new CategorizedToken("static", type, pointer);
		case AutoControl:
			return new CategorizedToken("auto", type, pointer);
		case RegisterControl:
			return new CategorizedToken("register", type, pointer);

		case MethodVoidControl:
			return new CategorizedToken("void", type, false);
		case MethodIntControl:
			return new CategorizedToken("int", type, pointer);
		case MethodLongControl:
			return new CategorizedToken("long", type, pointer);
		case MethodFloatControl:
			return new CategorizedToken("float", type, pointer);
		case MethodDoubleControl:
			return new CategorizedToken("double", type, pointer);
		case MethodCharControl:
			return new CategorizedToken("char", type, pointer);
		case MethodStringControl:
			return new CategorizedToken("string", type, pointer);

		case VariableIntControl:
			return new CategorizedToken("int", type, pointer);
		case VariableLongControl:
			return new CategorizedToken("long", type, pointer);
		case VariableFloatControl:
			return new CategorizedToken("float", type, pointer);
		case VariableDoubleControl:
			return new CategorizedToken("double", type, pointer);
		case VariableCharControl:
			return new CategorizedToken("char", type, pointer);
		case VariableStringControl:
			return new CategorizedToken("string", type, pointer);

		case IntLiteral:
			return new CategorizedToken("[0-9]*", type, false, true);
		case LongLiteral:
			return new CategorizedToken("[0-9]*", type, false, true);
		case FloatLiteral:
			return new CategorizedToken("[0-9 .]*", type, false, true);
		case DoubleLiteral:
			return new CategorizedToken("[0-9 .]*", type, false, true);
		case CharLiteral:
			return new CategorizedToken("[0-9 a-z A-Z]", type, false, true);
		case StringLiteral:
			return new CategorizedToken("\"\"\"[0-9 a-z A-Z / \]*\"\"\"", type, false, true);//"string"
		case FilePathLiteral:
			return new CategorizedToken("\"<\"[0-9 a-z A-Z / \]*\">\"", type, false, true);//<filePath>

		case OpenCurlyBracketControl:
			return new CategorizedToken("{", type, false);
		case CloseCurlyBracketControl:
			return new CategorizedToken("}", type, false);
		case OpenParenthesesControl:
			return new CategorizedToken("(", type, false);
		case CloseParenthesesControl:
			return new CategorizedToken(")", type, false);
		case OpenBracketControl:
			return new CategorizedToken("[", type, false);
		case CloseBracketControl:
			return new CategorizedToken("]", type, false);

		case IfControl:
			return new CategorizedToken("if", type, false);
		case ElseControl:
			return new CategorizedToken("else", type, false);
		case SwitchControl:
			return new CategorizedToken("switch", type, false);
		case CaseControl:
			return new CategorizedToken("case", type, false);
		case WhenControl:
			return new CategorizedToken("when", type, false);
		case DefaultControl:
			return new CategorizedToken("default", type, false);
		case ShorIfControl:
			return new CategorizedToken("?", type, false);
		case ShortElseControl:
			return new CategorizedToken(":", type, false);

		case ForControl:
			return new CategorizedToken("for", type, false);
		case WhileControl:
			return new CategorizedToken("while", type, false);
		case DoControl:
			return new CategorizedToken("do", type, false);
		case ForEachControl:
			return new CategorizedToken(":", type, false);

		case SumControl:
			return new CategorizedToken("+", type, false);
		case SubtractionControl:
			return new CategorizedToken("-", type, false);
		case MultiplicationControl:
			return new CategorizedToken("*", type, false);
		case DivisionControl:
			return new CategorizedToken("/", type, false);
		case ModControl:
			return new CategorizedToken("%", type, false);
		case LeftShiftControl:
			return new CategorizedToken("<<", type, false);
		case RightShiftControl:
			return new CategorizedToken(">>", type, false);
		case BitwiseAndControl:
			return new CategorizedToken("&", type, false);
		case BitwiseOrControl:
			return new CategorizedToken("|", type, false);
		case BitwiseNotControl:
			return new CategorizedToken("~", type, false);
		case CompoundSumControl:
			return new CategorizedToken("+=", type, false);
		case CompoundSubtractionControl:
			return new CategorizedToken("-=", type, false);
		case CompoundMultiplicationControl:
			return new CategorizedToken("*=", type, false);
		case CompoundDivisionControl:
			return new CategorizedToken("/=", type, false);
		case CompoundModControl:
			return new CategorizedToken("%=", type, false);
		case CompoundLeftShiftControl:
			return new CategorizedToken("<<=", type, false);
		case CompoundRightShiftControl:
			return new CategorizedToken(">>=", type, false);

		case AndControl:
			return new CategorizedToken("&&", type, false);
		case OrControl:
			return new CategorizedToken("||", type, false);
		case EqualControl:
			return new CategorizedToken("==", type, false);
		case DifferentControl:
			return new CategorizedToken("!=", type, false);
		case GreaterThanControl:
			return new CategorizedToken(">", type, false);
		case LowerThanControl:
			return new CategorizedToken("<", type, false);
		case GreaterEqualControl:
			return new CategorizedToken(">=", type, false);
		case LowerEqualControl:
			return new CategorizedToken("<=", type, false);

		case NotControl:
			return new CategorizedToken("!", type, false);

		case PointerControl:
			return new CategorizedToken("->", type, false);
		case DotControl:
			return new CategorizedToken(".", type, false);
		case CommaControl:
			return new CategorizedToken(",", type, false);
		case EndCommandControl:
			return new CategorizedToken(";", type, false);

		/*---------------------------------------------------End of final Categorized Tokens---------------------------------------------------*/

		case SystemTypeDefinition:
			ret = new CategorizedToken("SystemTypeDefinition", type, false);

			ret->AddChild(GetCategorizedToken(TypeNameControl, false));

			return ret;
		case StorageDefinition:
			ret = new CategorizedToken("StorageDefinition", type, false);

			ret->AddChild(GetCategorizedToken(TypedefControl, false));
			ret->AddChild(GetCategorizedToken(ExternControl, false));
			ret->AddChild(GetCategorizedToken(StaticControl, false));
			ret->AddChild(GetCategorizedToken(AutoControl, false));
			ret->AddChild(GetCategorizedToken(RegisterControl, false));

			return ret;
		case QualifierDefinition:
			ret = new CategorizedToken("QualifierDefinition", type, false);

			ret->AddChild(GetCategorizedToken(ConstControl, false));
			ret->AddChild(GetCategorizedToken(VolatileControl, false));

			return ret;
		case VariableDeclarator:
			ret = new CategorizedToken("VariableDeclarator", type, false);
			
			ret->AddChild(GetCategorizedToken(VariableIntControl, false));
			ret->AddChild(GetCategorizedToken(VariableLongControl, false));
			ret->AddChild(GetCategorizedToken(VariableFloatControl, false));
			ret->AddChild(GetCategorizedToken(VariableDoubleControl, false));
			ret->AddChild(GetCategorizedToken(VariableCharControl, false));
			ret->AddChild(GetCategorizedToken(VariableStringControl, false));
			ret->AddChild(GetCategorizedToken(VariableIntControl, true));
			ret->AddChild(GetCategorizedToken(VariableLongControl, true));
			ret->AddChild(GetCategorizedToken(VariableFloatControl, true));
			ret->AddChild(GetCategorizedToken(VariableDoubleControl, true));
			ret->AddChild(GetCategorizedToken(VariableCharControl, true));
			ret->AddChild(GetCategorizedToken(VariableStringControl, true));

			return ret;
		case MethodDeclarator:
			ret = new CategorizedToken("MethodDeclarator", type, false);

			ret->AddChild(GetCategorizedToken(MethodVoidControl, false));
			ret->AddChild(GetCategorizedToken(MethodIntControl, false));
			ret->AddChild(GetCategorizedToken(MethodLongControl, false));
			ret->AddChild(GetCategorizedToken(MethodFloatControl, false));
			ret->AddChild(GetCategorizedToken(MethodDoubleControl, false));
			ret->AddChild(GetCategorizedToken(MethodCharControl, false));
			ret->AddChild(GetCategorizedToken(MethodStringControl, false));
			ret->AddChild(GetCategorizedToken(MethodIntControl, true));
			ret->AddChild(GetCategorizedToken(MethodLongControl, true));
			ret->AddChild(GetCategorizedToken(MethodFloatControl, true));
			ret->AddChild(GetCategorizedToken(MethodDoubleControl, true));
			ret->AddChild(GetCategorizedToken(MethodCharControl, true));
			ret->AddChild(GetCategorizedToken(MethodStringControl, true));

			return ret;
		case ExternalDeclarator:
			ret = new CategorizedToken("ExternalDeclarator", type, false);

			ret->AddChild(GetCategorizedToken(HashTagControl, false));

			return ret;
		case ExternalDefiner:
			ret = new CategorizedToken("ExternalDefiner", type, false);

			ret->AddChild(GetCategorizedToken(IncludeControl, false));
			ret->AddChild(GetCategorizedToken(DefineControl, false));

			return ret;
		case LiteralDefinition:
			ret = new CategorizedToken("LiteralDefinition", type, false);

			ret->AddChild(GetCategorizedToken(IntLiteral, false));
			ret->AddChild(GetCategorizedToken(LongLiteral, false));
			ret->AddChild(GetCategorizedToken(FloatLiteral, false));
			ret->AddChild(GetCategorizedToken(DoubleLiteral, false));
			ret->AddChild(GetCategorizedToken(CharLiteral, false));
			ret->AddChild(GetCategorizedToken(StringLiteral, false));
			ret->AddChild(GetCategorizedToken(FilePathLiteral, false));

			return ret;
		case TypeControl:
			ret = new CategorizedToken("TypeControl", type, false);

			ret->AddChild(GetCategorizedToken(MethodVoidControl, false));
			ret->AddChild(GetCategorizedToken(MethodIntControl, false));
			ret->AddChild(GetCategorizedToken(MethodLongControl, false));
			ret->AddChild(GetCategorizedToken(MethodFloatControl, false));
			ret->AddChild(GetCategorizedToken(MethodDoubleControl, false));
			ret->AddChild(GetCategorizedToken(MethodCharControl, false));
			ret->AddChild(GetCategorizedToken(MethodStringControl, false));
			ret->AddChild(GetCategorizedToken(VariableIntControl, true));
			ret->AddChild(GetCategorizedToken(VariableLongControl, true));
			ret->AddChild(GetCategorizedToken(VariableFloatControl, true));
			ret->AddChild(GetCategorizedToken(VariableDoubleControl, true));
			ret->AddChild(GetCategorizedToken(VariableCharControl, true));
			ret->AddChild(GetCategorizedToken(VariableStringControl, true));

			return ret;
		case ContextControl:
			ret = new CategorizedToken("ContextControl", type, false);

			ret->AddChild(GetCategorizedToken(OpenCurlyBracketControl, false));
			ret->AddChild(GetCategorizedToken(CloseCurlyBracketControl, false));
			ret->AddChild(GetCategorizedToken(OpenParenthesesControl, false));
			ret->AddChild(GetCategorizedToken(CloseParenthesesControl, false));
			ret->AddChild(GetCategorizedToken(OpenBracketControl, false));
			ret->AddChild(GetCategorizedToken(CloseBracketControl, false));

			return ret;
		case ConditionalControl:
			ret = new CategorizedToken("ConditionalControl", type, false);

			ret->AddChild(GetCategorizedToken(IfControl, false));
			ret->AddChild(GetCategorizedToken(ElseControl, false));
			ret->AddChild(GetCategorizedToken(SwitchControl, false));
			ret->AddChild(GetCategorizedToken(CaseControl, false));
			ret->AddChild(GetCategorizedToken(WhenControl, false));
			ret->AddChild(GetCategorizedToken(DefaultControl, false));
			ret->AddChild(GetCategorizedToken(ShorIfControl, false));
			ret->AddChild(GetCategorizedToken(ShortElseControl, false));

			return ret;
		case LoopControl:
			ret = new CategorizedToken("LoopControl", type, false);

			ret->AddChild(GetCategorizedToken(ForControl, false));
			ret->AddChild(GetCategorizedToken(WhileControl, false));
			ret->AddChild(GetCategorizedToken(DoControl, false));
			ret->AddChild(GetCategorizedToken(ForEachControl, false));

			return ret;
		case ArithmeticOperation:
			ret = new CategorizedToken("ArithmeticOperation", type, false);

			ret->AddChild(GetCategorizedToken(SumControl, false));
			ret->AddChild(GetCategorizedToken(SubtractionControl, false));
			ret->AddChild(GetCategorizedToken(MultiplicationControl, false));
			ret->AddChild(GetCategorizedToken(DivisionControl, false));
			ret->AddChild(GetCategorizedToken(ModControl, false));
			ret->AddChild(GetCategorizedToken(LeftShiftControl, false));
			ret->AddChild(GetCategorizedToken(RightShiftControl, false));
			ret->AddChild(GetCategorizedToken(BitwiseAndControl, false));
			ret->AddChild(GetCategorizedToken(BitwiseOrControl, false));
			ret->AddChild(GetCategorizedToken(BitwiseNotControl, false));
			ret->AddChild(GetCategorizedToken(CompoundSumControl, false));
			ret->AddChild(GetCategorizedToken(CompoundSubtractionControl, false));
			ret->AddChild(GetCategorizedToken(CompoundMultiplicationControl, false));
			ret->AddChild(GetCategorizedToken(CompoundDivisionControl, false));
			ret->AddChild(GetCategorizedToken(CompoundModControl, false));
			ret->AddChild(GetCategorizedToken(CompoundLeftShiftControl, false));
			ret->AddChild(GetCategorizedToken(CompoundRightShiftControl, false));

			return ret;
		case TwoOperandsBooleanOperation:
			ret = new CategorizedToken("TwoOperandBooleanOperation", type, false);

			ret->AddChild(GetCategorizedToken(AndControl, false));
			ret->AddChild(GetCategorizedToken(OrControl, false));
			ret->AddChild(GetCategorizedToken(SwitchControl, false));
			ret->AddChild(GetCategorizedToken(EqualControl, false));
			ret->AddChild(GetCategorizedToken(DifferentControl, false));
			ret->AddChild(GetCategorizedToken(GreaterThanControl, false));
			ret->AddChild(GetCategorizedToken(LowerThanControl, false));
			ret->AddChild(GetCategorizedToken(GreaterEqualControl, false));
			ret->AddChild(GetCategorizedToken(LowerEqualControl, false));

			return ret;
		case OneOperandBooleanOperation:
			ret = new CategorizedToken("OneOperandBooleanOperation", type, false);

			ret->AddChild(GetCategorizedToken(NotControl, false));

			return ret;
		case ProceduralControl:
			ret = new CategorizedToken("ProceduralControl", type, false);

			ret->AddChild(GetCategorizedToken(PointerControl, false));
			ret->AddChild(GetCategorizedToken(DotControl, false));
			ret->AddChild(GetCategorizedToken(CommaControl, false));
			ret->AddChild(GetCategorizedToken(EndCommandControl, false));

			return ret;
		case Declarator:
			ret = new CategorizedToken("Declarator", type, false);

			ret->AddChild(GetCategorizedToken(SystemTypeDefinition, false));
			ret->AddChild(GetCategorizedToken(StorageDefinition, false));
			ret->AddChild(GetCategorizedToken(QualifierDefinition, false));
			ret->AddChild(GetCategorizedToken(VariableDeclarator, false));
			ret->AddChild(GetCategorizedToken(MethodDeclarator, false));
			ret->AddChild(GetCategorizedToken(ExternalDeclarator, false));
			ret->AddChild(GetCategorizedToken(ExternalDefiner, false));

			return ret;
		case TwoOperands:
			ret = new CategorizedToken("TwoOperands", type, false);

			ret->AddChild(GetCategorizedToken(ArithmeticOperation, false));
			ret->AddChild(GetCategorizedToken(TwoOperandsBooleanOperation, false));

			return ret;
		case OneOperand:
			ret = new CategorizedToken("OneOperand", type, false);

			ret->AddChild(GetCategorizedToken(OneOperandBooleanOperation, false));

			return ret;
		case Operation:
			ret = new CategorizedToken("Operation", type, false);

			ret->AddChild(GetCategorizedToken(TwoOperands, false));
			ret->AddChild(GetCategorizedToken(OneOperand, false));

			return ret;
		case VariableIdentifier:
			ret = new CategorizedToken("VariableIdentifier", type, false);

			ret->AddChild(GetCategorizedToken(VariableDeclarator, false));

			return ret;
		case MethodIdentifier:
			ret = new CategorizedToken("MethodIdentifier", type, false);

			ret->AddChild(GetCategorizedToken(MethodDeclarator, false));

			return ret;
		case ConstantIdentifier:
			ret = new CategorizedToken("ConstantIdentifier", type, false);

			ret->AddChild(GetCategorizedToken(LiteralDefinition, false));

			return ret;
		case Identifier:
			ret = new CategorizedToken("Identifier", type, false);
			
			ret->AddChild(GetCategorizedToken(VariableIdentifier, false));
			ret->AddChild(GetCategorizedToken(MethodIdentifier, false));
			ret->AddChild(GetCategorizedToken(ConstantIdentifier, false));

			return ret;
		case TypeDefinition:
			ret = new CategorizedToken("TypeDefinition", type, false);

			ret->AddChild(GetCategorizedToken(LiteralDefinition, false));
			ret->AddChild(GetCategorizedToken(Declarator, false));

			return ret;
		case Control:
			ret = new CategorizedToken("TypeDefinition", type, false);

			ret->AddChild(GetCategorizedToken(TypeControl, false));
			ret->AddChild(GetCategorizedToken(ContextControl, false));
			ret->AddChild(GetCategorizedToken(ConditionalControl, false));
			ret->AddChild(GetCategorizedToken(LoopControl, false));
			ret->AddChild(GetCategorizedToken(Operation, false));
			ret->AddChild(GetCategorizedToken(ProceduralControl, false));

			return ret;
		case TypeHierarchy:
			ret = new CategorizedToken("TypeHierarchy", type, false);

			ret->AddChild(GetCategorizedToken(Reserved, false));
			ret->AddChild(GetCategorizedToken(Identifier, false));
		default:
			throw invalid_argument("Invalid categorized token type \"" + StringUtils::ToString(type) + "\"");
	}
}

vector<CategorizedToken*>* CategorizedToken::GetCategorizedTokenChildren(CategorizedToken* token)
{
	if (token != NULL)
	{
		vector<CategorizedToken*>* ret = new vector<CategorizedToken*>();
		for (CategorizedToken* child : (*token->GetChildren()))
		{
			if (child->GetChildren()->size() > 0)
			{
				VectorUtils::CopyValues(GetCategorizedTokenChildren(child), ret);
			}
			else
			{
				ret->push_back(child);
			}
		}
		return ret;
	}
	else
	{
		throw invalid_argument("NULL CategorizedToken are not allowed CategorizedToken::GetCategorizedTokenChildren.");
	}
}

vector<CategorizedToken*>* CategorizedToken::GetCategorizedTokenChildren(int type, bool pointer)
{
	return GetCategorizedTokenChildren(GetCategorizedToken(type, pointer));
}