#include <stdexcept>

#include <Compiler/FrontEnd/TokenCursor.h>

TokenCursor::TokenCursor(string text)
{
    if(!text.empty())
    {
        Text = text;
        CanRead = false;
    }
    else
    {
        throw invalid_argument("The file reader must never be null on a TokenCursor.");
    }
}

int TokenCursor::TokenSeparatorLength(string token)
{
    for(int i = 0; i < GetTokenSeparators().size(); i++)
    {
        if(StringUtils::EndsWith(token, GetTokenSeparators()[i]))
        {
            return GetTokenSeparators()[i].size();
        }
    }
    return -1;
}

bool TokenCursor::Read()
{
	unsigned int moves = 0;
	int separatorLen = TokenSeparatorLength(Text.substr(CursorIndex, moves));
    while(separatorLen == -1 && CursorIndex + moves < Text.length())
    {
        moves++;
        separatorLen = TokenSeparatorLength(Text.substr(CursorIndex, moves));
    }
    if(separatorLen > 0)
    {
        bool valueIsSeparator = StringUtils::Contains(Text.substr(CursorIndex, moves), GetTokenSeparators());
        Value =  valueIsSeparator ? Text.substr(CursorIndex, moves) : Text.substr(CursorIndex, (moves - separatorLen >= 0 ? moves - separatorLen : 0));
        CursorIndex = valueIsSeparator ? CursorIndex + moves : CursorIndex + moves - separatorLen;

		if (StringUtils::Equals(Value, "\n"))
		{
			LineNumber++;
			PreviousLinesLength = CursorIndex;
			ColumnNumber = 0;
		}
		else
		{
			ColumnNumber = (valueIsSeparator ? CursorIndex - moves : CursorIndex - moves + separatorLen) - PreviousLinesLength;
		}

        CanRead = true;
    }
    else
    {
        CanRead = false;
    }

	return CanRead;
}

string TokenCursor::GetValue()
{
    if(CanRead)
    {
        return Value;
    }
    else
    {
        throw invalid_argument("The cursor was not readable at the moment.");
    }
}

void TokenCursor::Reset()
{
	CanRead = false;
	CursorIndex = 0;
	LineNumber = 0;
	ColumnNumber = 0;
}

int TokenCursor::GetLineNumber()
{
	return LineNumber;
}

int TokenCursor::GetColumnNumber()
{
	return ColumnNumber;
}

void TokenCursor::SetFrontEndLanguage(int language)
{
	FrontEndLanguage = language;
}

int TokenCursor::GetFrontEndLanguage()
{
	return FrontEndLanguage;
}

bool TokenCursor::MakeUnifiedSeparator(FrontEndToken* current, FrontEndToken* next)
{
	for(unsigned int i = 0; i < GetUnifiedSeparators().size(); i++)
	{
		if (StringUtils::Equals(current->GetValue() + next->GetValue(), GetUnifiedSeparators()[i]))
		{
			return true;
		}
	}
	return false;
}

void TokenCursor::JoinFrontEndTokens(FrontEndToken* current, FrontEndToken* next)
{
	current->SetValue(current->GetValue() + next->GetValue());
}

bool TokenCursor::IsReservedToken(string token)
{
	for (string s : GetReservedTokens())
	{
		if (StringUtils::Equals(token, s))
		{
			return true;
		}
	}
	return false;
}

bool TokenCursor::IsUnaryOperation(string token)
{
	for (string s : GetUnaryOperationTokens())
	{
		if (StringUtils::Equals(token, s))
		{
			return true;
		}
	}
	return false;
}

bool TokenCursor::IsBinaryOperation(string token)
{
	for (string s : GetBinaryOperationTokens())
	{
		if (StringUtils::Equals(token, s))
		{
			return true;
		}
	}
	return false;
}

bool TokenCursor::IsUnaryBooleanOperation(string token)
{
	for (string s : GetUnaryBooleanOperationTokens())
	{
		if (StringUtils::Equals(token, s))
		{
			return true;
		}
	}
	return false;
}

bool TokenCursor::IsBinaryBooleanOperation(string token)
{
	for (string s : GetBinaryBooleanOperationTokens())
	{
		if (StringUtils::Equals(token, s))
		{
			return true;
		}
	}
	return false;
}

bool TokenCursor::IsAttributionOperation(string token)
{
	for (string s : GetAttributionTokens())
	{
		if (StringUtils::Equals(token, s))
		{
			return true;
		}
	}
	return false;
}

bool TokenCursor::IsCompoundAttributionOperation(string token)
{
	for (string s : GetCompoundAttributionTokens())
	{
		if (StringUtils::Equals(token, s))
		{
			return true;
		}
	}
	return false;
}

bool TokenCursor::IsControlToken(string token)
{
	for (string s : GetControlTokens())
	{
		if (StringUtils::Equals(token, s))
		{
			return true;
		}
	}
	return false;
}

bool TokenCursor::IsOpenControlToken(string token)
{
	for (string s : GetOpenControlTokens())
	{
		if (StringUtils::Equals(token, s))
		{
			return true;
		}
	}
	return false;
}

bool TokenCursor::IsCloseControlToken(string token)
{
	for (string s : GetCloseControlTokens())
	{
		if (StringUtils::Equals(token, s))
		{
			return true;
		}
	}
	return false;
}

bool TokenCursor::IsLiteral(string token)
{
	return StringUtils::IsNumber(StringUtils::Substring(token, 0, 0));
}

bool TokenCursor::IsFloatingLiteral(string token)
{
	return StringUtils::IsNumber(StringUtils::Substring(token, 0, 0)) && StringUtils::IsFloatingNumber(token);
}

bool TokenCursor::IsIntegerLiteral(string token)
{
	return IsLiteral(token) && StringUtils::IsInteger(token);
}

bool TokenCursor::IsLongLiteral(string token)
{
	return IsLiteral(token) && StringUtils::IsLong(token);
}

bool TokenCursor::IsFloatLiteral(string token)
{
	return IsFloatingLiteral(token) && StringUtils::IsFloat(token);
}

bool TokenCursor::IsDoubleLiteral(string token)
{
	return IsFloatingLiteral(token) && StringUtils::Isdouble(token);
}

bool TokenCursor::IsStringLiteral(string token)
{
	return StringUtils::StartsWith(token, "\"") && StringUtils::EndsWith(token, "\"");
}

bool TokenCursor::IsComment(string token)
{
	return (StringUtils::StartsWith(token, "/*") && StringUtils::EndsWith(token, "*/")) || StringUtils::StartsWith(token, "//");
}

bool TokenCursor::IsIgnoredToken(string token)
{
	for (string s : GetIgnoredTokens())
	{
		if (StringUtils::Equals(token, s))
		{
			return true;
		}
	}
	return false;
}