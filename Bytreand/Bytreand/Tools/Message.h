#pragma once

#include <stdexcept>

#include <Tools/StringUtils.h>

class Message
{
	private:
		int MessageType = 0;
		int Code = 0;
		string Text;

	public:
		enum MessageTypes
		{
			Successfull,
			Warning,
			Error
		};

		Message(int, string);
		Message(int, int, string);
		void SetType(int);
		int GetType();
		string GetTypeName();
		void SetCode(int);
		int GetCode();
		void SetText(string);
		string GetText();
		bool IsSucessful();
		bool IsWarning();
		bool IsError();

		static bool HasSuccess(vector<Message*>*);
		static bool HasWarning(vector<Message*>*);
		static bool HasError(vector<Message*>*);
		static bool IsSuccessful(vector<Message*>*);
		static void AddMessage(vector<Message*>*, int, string);
		static void AddMessage(vector<Message*>*, int, int, string);
		static void AddMessages(vector<Message*>*, vector<Message*>*);
};