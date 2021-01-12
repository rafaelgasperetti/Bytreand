#include <iostream>

#include <Compiler/BytreandCompiler.h>
#include <Compiler/FrontEnd/Tokenizer.h>

#include <Compiler/MiddleEnd/Grammar.h>
#include <Compiler/MiddleEnd/SemanticTree.h>

BytreandCompiler::BytreandCompiler(FileReader* reader, string frontEndLanguage)
{
	SetFileReader(reader);
	SetFrontEndLanguage(frontEndLanguage);
}

void BytreandCompiler::SetFileReader(FileReader* reader)
{
	if (reader != NULL)
	{
		Reader = reader;
	}
	else
	{
		throw invalid_argument("Bytreand Compiler must never have a NULL file reader.");
	}
}

FileReader* BytreandCompiler::GetFileReader()
{
	return Reader;
}

void BytreandCompiler::SetFrontEndLanguage(string language)
{
	FrontEndLanguage = GetLanguage(language);
}

int BytreandCompiler::GetFrontEndLanguage()
{
	return FrontEndLanguage;
}

string BytreandCompiler::GetFrontEndLanguageName()
{
	return GetLanguage(FrontEndLanguage);
}

vector<Message*>* BytreandCompiler::Compile()
{
	vector<Message*>* ret = new vector<Message*>();
	
	try
	{
		Tokenizer* sourceTokenizer = new Tokenizer();
		vector<FrontEndToken*>* code = sourceTokenizer->GetTokens(GetFileReader(), GetFrontEndLanguage());
		Message::AddMessages(sourceTokenizer->GetMessages(), ret);

		cout << "Tokens" << endl;
		
		for (unsigned int i = 0; i < code->size(); i++)
		{
			cout << Tokenizer::GetFrontEndTokenTypeName((*code)[i]->GetType()) << ": '" << (*code)[i]->GetValue() 
				<< "' (" << (*code)[i]->GetLineNumber() << ":" << (*code)[i]->GetColumnNumber() << ", Type: " << (*code)[i]->GetType() << " Hash: " << (*code)[i]->GetHash() << ")" << endl;
		}

		Grammar* grammar = Grammar::GetGrammar(sourceTokenizer->GetCurrentCursor());

		cout << endl << "Grammar RootState: \"" << grammar->GetRootState()->GetName() << "\" of " << grammar->GetLanguageName() << " language." << endl;

		cout << endl << "Semantic Tree" << endl;

		SemanticTree* semanticTree = SemanticTree::GetSemanticTree(grammar, code);

		VectorUtils::CopyValues(semanticTree->GetMessages(), ret);

		cout << endl;
	}
	catch (invalid_argument& e)
	{
		ret->push_back(new Message(Message::MessageTypes::Error, StringUtils::ToString(e.what()) + "\n\tSource code location: \"" + GetFileReader()->GetPath() + "\""));
	}

	return ret;
}

int BytreandCompiler::GetLanguage(string language)
{
	if (StringUtils::Equals(language, "C"))
	{
		return C;
	}
	else if(StringUtils::Equals(language, "C++"))
	{
		return CPlusPlus;
	}
	else if (StringUtils::Equals(language, "Java"))
	{
		return Java;
	}
	else if (StringUtils::Equals(language, "Pascal"))
	{
		return Pascal;
	}
	else if (StringUtils::Equals(language, "Delphi"))
	{
		return Delphi;
	}
	else if (StringUtils::Equals(language, "HTML"))
	{
		return HTML;
	}
	else if (StringUtils::Equals(language, "CSS"))
	{
		return CSS;
	}
	else if (StringUtils::Equals(language, "SQL"))
	{
		return SQL;
	}
	else if (StringUtils::Equals(language, "Bytreand"))
	{
		return Bytreand;
	}
	else
	{
		throw invalid_argument("Invalid input language \"" + language + "\".");
	}
}

string BytreandCompiler::GetLanguage(int language)
{
	if (language == C)
	{
		return "C";
	}
	else if (language == CPlusPlus)
	{
		return "C++";
	}
	else if (language == Java)
	{
		return "Java";
	}
	else if (language == Pascal)
	{
		return "Pascal";
	}
	else if(language == Delphi)
	{
		return "Delphi";
	}
	else if (language == HTML)
	{
		return "HTML";
	}
	else if (language == CSS)
	{
		return "CSS";
	}
	else if (language == SQL)
	{
		return "SQL";
	}
	else if (language == Bytreand)
	{
		return "Bytreand";
	}
	else
	{
		throw invalid_argument("Invalid input language \"" + StringUtils::ToString(language) + "\".");
	}
}