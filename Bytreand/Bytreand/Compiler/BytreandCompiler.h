#pragma once

#include <Tools/StringUtils.h>
#include <Tools/FileReader.h>
#include <Tools/Message.h>

class BytreandCompiler
{
	private:
		FileReader* Reader;
		int FrontEndLanguage = 0;

	public:
		enum Languages
		{
			C,
			CPlusPlus,
			Java,
			Pascal,
			Delphi,
			HTML,
			CSS,
			CSharp,
			SQL,
			Bytreand
		};

		BytreandCompiler(FileReader*, string);
		void SetFileReader(FileReader*);
		FileReader* GetFileReader();
		void SetFrontEndLanguage(string);
		int GetFrontEndLanguage();
		string GetFrontEndLanguageName();
		vector<Message*>* Compile();

		static int GetLanguage(string);
		static string GetLanguage(int);
};