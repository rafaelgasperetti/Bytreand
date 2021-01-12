#include <Compiler/FrontEnd/Tokenizer.h>
#include <Tools/StringUtils.h>
#include <Compiler/FrontEnd/Languages/C/CTokenCursor.h>
#include <Compiler/BytreandCompiler.h>

Tokenizer::Tokenizer()
{

}

vector<FrontEndToken*>* Tokenizer::GetTokens(FileReader* reader, int frontEndLanguage)
{
	Messages->clear();
    if(reader != NULL)
    {
		Tokens = new vector<FrontEndToken*>();
        string text = reader->ReadFile();

        if(text.empty())
        {
            throw invalid_argument("It was not possible to get the tokens from the File \"" + reader->GetPath() + "\" because the file is empty.");
        }
        else
        {
			CurrentCursor = GetTokenCursor(text, frontEndLanguage);

            while(CurrentCursor->Read())
            {
				FrontEndToken* frt = new FrontEndToken();

				frt->SetValue(CurrentCursor->GetValue());
				frt->SetLineNumber(CurrentCursor->GetLineNumber());
				frt->SetColumnNumber(CurrentCursor->GetColumnNumber());
				frt->SetType(Tokenizer::GetFrontEndTokenType(CurrentCursor));

				Tokens->push_back(frt);
            }

			CurrentCursor->Reset();

			UnifyCommentsAndStrings();

            return Tokens;
        }
    }
    else
    {
        throw invalid_argument("It was not possible to get the tokens from the FileReader because it is null.");
    }
}

void Tokenizer::UnifyCommentsAndStrings()
{
	//For tokens that makes 2 smaller tokens
	for (unsigned int i = 0, maxSize = Tokens->size(); i < maxSize - 1; i++)
	{
		if (CurrentCursor->MakeUnifiedSeparator((*Tokens)[i], (*Tokens)[i + 1]))
		{
			CurrentCursor->JoinFrontEndTokens((*Tokens)[i], (*Tokens)[i + 1]);
			Tokens->erase(Tokens->begin() + i + 1);
			maxSize--;
		}

		if (CurrentCursor->MakeUnifiedSeparator((*Tokens)[i], (*Tokens)[i + 1]))
		{
			CurrentCursor->JoinFrontEndTokens((*Tokens)[i], (*Tokens)[i + 1]);
			Tokens->erase(Tokens->begin() + i + 1);
			maxSize--;
		}
	}

	//For strings and comments
	for (unsigned int i = 0, maxSize = Tokens->size(); i < maxSize - 1; i++)
	{
		FrontEndToken* newToken = new FrontEndToken();

		//String
		if (StringUtils::Equals((*Tokens)[i]->GetValue(), "\""))
		{
			int startString = i;

			newToken->SetLineNumber((*Tokens)[i]->GetLineNumber());
			newToken->SetColumnNumber((*Tokens)[i]->GetColumnNumber());
			newToken->SetType(FrontEndToken::FrontEndTokenType::StringLiteral);
			i++;
			while(i < Tokens->size() && !StringUtils::Equals((*Tokens)[i]->GetValue(), "\"") && !StringUtils::EndsWith(newToken->GetValue(), "\\"))
			{
				newToken->SetValue(newToken->GetValue() + (*Tokens)[i]->GetValue());
				Tokens->erase(Tokens->begin() + i);
				maxSize--;
			}

			if (i == Tokens->size() || !StringUtils::Equals((*Tokens)[i]->GetValue(), "\""))
			{
				Message::AddMessage(Messages, Message::Error, "String literal \"" + newToken->GetValue() + "\" (" +
					StringUtils::ToString(newToken->GetLineNumber()) + ":" + StringUtils::ToString(newToken->GetColumnNumber()) + ") does not contain an end defined by double quotation.");
			}

			if (i < Tokens->size())
			{
				Tokens->erase(Tokens->begin() + i);
			}
			maxSize--;
			(*Tokens)[startString] = newToken;
		}

		//Char
		if (i < Tokens->size() && StringUtils::Equals((*Tokens)[i]->GetValue(), "'"))
		{
			int startString = i;

			newToken->SetLineNumber((*Tokens)[i]->GetLineNumber());
			newToken->SetColumnNumber((*Tokens)[i]->GetColumnNumber());
			newToken->SetType(FrontEndToken::FrontEndTokenType::StringLiteral);
			i++;
			while (i < Tokens->size() && !StringUtils::Equals((*Tokens)[i]->GetValue(), "'"))
			{
				newToken->SetValue(newToken->GetValue() + (*Tokens)[i]->GetValue());
				Tokens->erase(Tokens->begin() + i);
				maxSize--;
			}

			if (i == Tokens->size() || !StringUtils::Equals((*Tokens)[i]->GetValue(), "'"))
			{
				Message::AddMessage(Messages, Message::Error, "Char literal \"" + newToken->GetValue() + "\" (" +
					StringUtils::ToString(newToken->GetLineNumber()) + ":" + StringUtils::ToString(newToken->GetColumnNumber()) + ") does not contain an end defined by single quotation.");
			}
			else if ((*Tokens)[i]->GetValue().size() > 1 || (StringUtils::StartsWith((*Tokens)[i]->GetValue(),"\\") && (*Tokens)[i]->GetValue().size() > 2))
			{
				Message::AddMessage(Messages, Message::Error, "Char literal \"" + newToken->GetValue() + "\" (" +
					StringUtils::ToString(newToken->GetLineNumber()) + ":" + StringUtils::ToString(newToken->GetColumnNumber()) + ") is bigger than one character.");
			}

			if (i < Tokens->size())
			{
				Tokens->erase(Tokens->begin() + i);
			}
			maxSize--;
			(*Tokens)[startString] = newToken;
		}

		//Line Comment
		if (i < Tokens->size() && StringUtils::Equals((*Tokens)[i]->GetValue(), "//"))
		{
			int startString = i;
			int line = (*Tokens)[i]->GetLineNumber();

			newToken->SetLineNumber((*Tokens)[i]->GetLineNumber());
			newToken->SetColumnNumber((*Tokens)[i]->GetColumnNumber());
			newToken->SetType(FrontEndToken::FrontEndTokenType::Comment);
			i++;
			while ((*Tokens)[i]->GetLineNumber() == line && maxSize > i)
			{
				newToken->SetValue(newToken->GetValue() + (*Tokens)[i]->GetValue());
				Tokens->erase(Tokens->begin() + i);
				maxSize--;
			}

			(*Tokens)[startString] = newToken;
		}

		//Block Comment
		if (i < Tokens->size() && StringUtils::Equals((*Tokens)[i]->GetValue(), "/*"))
		{
			int startString = i;

			newToken->SetLineNumber((*Tokens)[i]->GetLineNumber());
			newToken->SetColumnNumber((*Tokens)[i]->GetColumnNumber());
			newToken->SetType(FrontEndToken::FrontEndTokenType::Comment);
			i++;
			while (!StringUtils::Equals((*Tokens)[i]->GetValue(), "*/") && maxSize > i)
			{
				newToken->SetValue(newToken->GetValue() + (*Tokens)[i]->GetValue());
				Tokens->erase(Tokens->begin() + i);
				maxSize--;
			}

			if (i == Tokens->size() || !StringUtils::Equals((*Tokens)[i]->GetValue(), "*/"))
			{
				Message::AddMessage(Messages, Message::Error, "Comment \"" + newToken->GetValue() + "\" (" +
					StringUtils::ToString(newToken->GetLineNumber()) + ":" + StringUtils::ToString(newToken->GetColumnNumber()) + ") does not contain an end defined \"*/\".");
			}

			if (i < Tokens->size())
			{
				Tokens->erase(Tokens->begin() + i);
			}
			maxSize--;
			(*Tokens)[startString] = newToken;
		}
	}

	//Remove ignored tokens
	for (unsigned int i = 0; i < Tokens->size(); i++)
	{
		if ((*Tokens)[i]->GetType() == FrontEndToken::FrontEndTokenType::IgnoredToken)
		{
			Tokens->erase(Tokens->begin() + i);
			i--;
		}
	}

	//Union of literals
	for (unsigned int i = 0; i < Tokens->size(); i++)
	{
		if//.8
			(
				Tokens->size() > i + 1 &&
				(*Tokens)[i]->GetType() == FrontEndToken::FrontEndTokenType::Control &&
				StringUtils::Equals((*Tokens)[i]->GetValue(), ".") &&
				(*Tokens)[i + 1]->GetType() == FrontEndToken::FrontEndTokenType::Literal
				)
		{
			FrontEndToken* newToken = new FrontEndToken();
			newToken->SetLineNumber((*Tokens)[i]->GetLineNumber());
			newToken->SetColumnNumber((*Tokens)[i]->GetColumnNumber());
			newToken->SetValue("0." + (*Tokens)[i + 1]->GetValue());
			(*Tokens)[i] = newToken;
			Tokens->erase(Tokens->begin() + i + 1);
			if (CurrentCursor->IsFloatLiteral(newToken->GetValue()))
			{
				newToken->SetType(FrontEndToken::FrontEndTokenType::FloatLiteral);
			}
			else
			{
				newToken->SetType(FrontEndToken::FrontEndTokenType::DoubleLiteral);
			}
		}
		else if ((*Tokens)[i]->GetType() == FrontEndToken::FrontEndTokenType::Literal)
		{
			if//1.5
			(
				Tokens->size() > i + 2 &&
				(*Tokens)[i + 1]->GetType() == FrontEndToken::FrontEndTokenType::Control &&
				StringUtils::Equals((*Tokens)[i + 1]->GetValue(), ".") &&
				(*Tokens)[i + 2]->GetType() == FrontEndToken::FrontEndTokenType::Literal
			)
			{
				FrontEndToken* newToken = new FrontEndToken();
				newToken->SetLineNumber((*Tokens)[i]->GetLineNumber());
				newToken->SetColumnNumber((*Tokens)[i]->GetColumnNumber());
				newToken->SetValue((*Tokens)[i]->GetValue() + "." + (*Tokens)[i + 2]->GetValue());
				(*Tokens)[i] = newToken;
				Tokens->erase(Tokens->begin() + i + 1);
				Tokens->erase(Tokens->begin() + i + 1);
				if (CurrentCursor->IsFloatLiteral(newToken->GetValue()))
				{
					newToken->SetType(FrontEndToken::FrontEndTokenType::FloatLiteral);
				}
				else
				{
					newToken->SetType(FrontEndToken::FrontEndTokenType::DoubleLiteral);
				}
			}
			else
			{
				if (CurrentCursor->IsIntegerLiteral((*Tokens)[i]->GetValue()))
				{
					(*Tokens)[i]->SetType(FrontEndToken::FrontEndTokenType::IntegerLiteral);
				}
				else
				{
					(*Tokens)[i]->SetType(FrontEndToken::FrontEndTokenType::LongLiteral);
				}
			}
		}
	}
}

TokenCursor* Tokenizer::GetCurrentCursor()
{
	return CurrentCursor;
}

TokenCursor* Tokenizer::GetTokenCursor(string text, int frontEndLanguage)
{
	TokenCursor* ret;
	switch (frontEndLanguage)
	{
		case BytreandCompiler::C:
			ret = new CTokenCursor(text);
			ret->SetFrontEndLanguage(frontEndLanguage);
			break;
		default:
			throw invalid_argument("Invalid input language \"" + BytreandCompiler::GetLanguage(frontEndLanguage)+ "\".");
	}
	return ret;
}

int Tokenizer::GetFrontEndTokenType(TokenCursor* cursor)
{
	if (cursor->IsReservedToken(cursor->GetValue()))
	{
		return FrontEndToken::Reserved;
	}
	else if (cursor->IsUnaryOperation(cursor->GetValue()))
	{
		return FrontEndToken::UnaryOperation;
	}
	else if (cursor->IsBinaryOperation(cursor->GetValue()))
	{
		return FrontEndToken::BinaryOperation;
	}
	else if (cursor->IsUnaryBooleanOperation(cursor->GetValue()))
	{
		return FrontEndToken::UnaryBooleanOperation;
	}
	else if (cursor->IsBinaryBooleanOperation(cursor->GetValue()))
	{
		return FrontEndToken::BinaryBooleanOperation;
	}
	else if (cursor->IsAttributionOperation(cursor->GetValue()))
	{
		return FrontEndToken::Attribution;
	}
	else if (cursor->IsCompoundAttributionOperation(cursor->GetValue()))
	{
		return FrontEndToken::CompoundAttribution;
	}
	else if (cursor->IsControlToken(cursor->GetValue()))
	{
		return FrontEndToken::Control;
	}
	else if (cursor->IsOpenControlToken(cursor->GetValue()))
	{
		return FrontEndToken::OpenControl;
	}
	else if (cursor->IsCloseControlToken(cursor->GetValue()))
	{
		return FrontEndToken::CloseControl;
	}
	else if (cursor->IsIgnoredToken(cursor->GetValue()))
	{
		return FrontEndToken::IgnoredToken;
	}
	else if (cursor->IsStringLiteral(cursor->GetValue()))
	{
		return FrontEndToken::StringLiteral;
	}
	else if (cursor->IsComment(cursor->GetValue()))
	{
		return FrontEndToken::Comment;
	}
	else if (cursor->IsLiteral(cursor->GetValue()))
	{
		return FrontEndToken::Literal;
	}
	else if (cursor->IsIntegerLiteral(cursor->GetValue()))
	{
		return FrontEndToken::IntegerLiteral;
	}
	else if (cursor->IsLongLiteral(cursor->GetValue()))
	{
		return FrontEndToken::LongLiteral;
	}
	else if (cursor->IsFloatLiteral(cursor->GetValue()))
	{
		return FrontEndToken::FloatLiteral;
	}
	else if (cursor->IsDoubleLiteral(cursor->GetValue()))
	{
		return FrontEndToken::DoubleLiteral;
	}
	else
	{
		return FrontEndToken::Identifier;
	}
}

string Tokenizer::GetFrontEndTokenTypeName(int name)
{
	switch (name)
	{
		case FrontEndToken::Reserved:
			return "ReservedToken";
		case FrontEndToken::UnaryOperation:
			return "UnaryOperation";
		case FrontEndToken::BinaryOperation:
			return "BinaryOperation";
		case FrontEndToken::UnaryBooleanOperation:
			return "UnaryBooleanOperation";
		case FrontEndToken::BinaryBooleanOperation:
			return "BinaryBooleanOperation";
		case FrontEndToken::Attribution:
			return "Attribution";
		case FrontEndToken::CompoundAttribution:
			return "CompoundAttribution";
		case FrontEndToken::Control:
			return "Control";
		case FrontEndToken::OpenControl:
			return "OpenControl";
		case FrontEndToken::CloseControl:
			return "CloseControl";
		case FrontEndToken::Literal:
			return "Literal";
		case FrontEndToken::StringLiteral:
			return "StringLiteral";
		case FrontEndToken::IgnoredToken:
			return "IgnoredToken";
		case FrontEndToken::Comment:
			return "Comment";
		case FrontEndToken::IntegerLiteral:
			return "IntegerLiteral";
		case FrontEndToken::LongLiteral:
			return "LongLiteral";
		case FrontEndToken::FloatLiteral:
			return "FloatLiteral";
		case FrontEndToken::DoubleLiteral:
			return "DoubleLiteral";
		default:
			return "Identifier";
	}
}

vector<Message*>* Tokenizer::GetMessages()
{
	return Messages;
}