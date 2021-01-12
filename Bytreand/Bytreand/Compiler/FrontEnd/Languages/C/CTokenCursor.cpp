#include <Compiler/FrontEnd/Languages/C/CTokenCursor.h>

CTokenCursor::CTokenCursor(string text) : TokenCursor(text)
{

}

vector<string> CTokenCursor::GetTokenSeparators()
{
	return
	{
		" ",".",":","{","}","(",")","[","]","\"","'","\n","\t","&","|","+","-","*","/","!","@",",","#","%",";","<",">","=","~","\\","/"
	};
}

vector<string> CTokenCursor::GetIgnoredTokens()
{
	return
	{
		" ","\n","\t"
	};
}

vector<string> CTokenCursor::GetReservedTokens()
{
	return
	{
		"auto","break","case","char","const","continue","default","define","do","double","else","enum","extern","float","for","goto","if","int","long","return","short","signed",
		"sizeof","static","struct","switch","typedef","union","unsigned","void","volatile","while"
	};
}

vector<string> CTokenCursor::GetUnifiedSeparators()
{
	return
	{
		"&&","||","++","--","+=","-=","*=","/=","==","!=",">=","<=","::","//","/*","*/","->","<<",">>",">>=","<<=","%=","&=","..."
	};
}

vector<string> CTokenCursor::GetUnaryOperationTokens()
{
	return
	{
		"++","--"
	};
}

vector<string> CTokenCursor::GetBinaryOperationTokens()
{
	return
	{
		"+","-","*","/","%","|","&"
	};
}

vector<string> CTokenCursor::GetUnaryBooleanOperationTokens()
{
	return
	{
		"!"
	};
}


vector<string> CTokenCursor::GetBinaryBooleanOperationTokens()
{
	return
	{
		"==","!=",">=","<=",">","<","&&","||"
	};
}

vector<string> CTokenCursor::GetAttributionTokens()
{
	return
	{
		"="
	};
}

vector<string> CTokenCursor::GetCompoundAttributionTokens()
{
	return
	{
		"+=","-=","*=","/="
	};
}

vector<string> CTokenCursor::GetControlTokens()
{
	return
	{
		".",":","\"","'","@",",","#",";","~","\\","..."
	};
}

vector<string> CTokenCursor::GetOpenControlTokens()
{
	return
	{
		"{","(","[","<"
	};
}

vector<string> CTokenCursor::GetCloseControlTokens()
{
	return
	{
		"}",")","]",">"
	};
}