#include <Tools/Message.h>

Message::Message(int type, string text)
{
	SetType(type);
	SetText(text);
}

Message::Message(int type, int code, string text)
{
	SetType(type);
	SetCode(code);
	SetText(text);
}

void Message::SetType(int type)
{
	if (type == Successfull || type == Warning || type == Error)
	{
		MessageType = type;
	}
	else
	{
		throw invalid_argument("Invalid message type \"" + StringUtils::ToString(type) + "\". " +
			"Valid types are: " + StringUtils::ToString(Successfull) + ", " + StringUtils::ToString(Warning) + " or " + StringUtils::ToString(Error));
	}
}

int Message::GetType()
{
	return MessageType;
}

string Message::GetTypeName()
{
	switch (GetType())
	{
		case MessageTypes::Successfull:
			return "Successfull";
		case MessageTypes::Error:
			return "Error";
		case MessageTypes::Warning:
			return "Warning";
	}
}

void Message::SetCode(int code)
{
	Code = code;
}

int Message::GetCode()
{
	return Code;
}

void Message::SetText(string text)
{
	if (!StringUtils::IsEmpty(text) || GetType() == Successfull)
	{
		Text = text;
	}
	else
	{
		throw invalid_argument("Invalid empty message text.");
	}
}

string Message::GetText()
{
	return Text;
}

bool Message::IsSucessful()
{
	return GetType() == Successfull;
}

bool Message::IsWarning()
{
	return GetType() == Warning;
}

bool Message::IsError()
{
	return GetType() == Error;
}


bool Message::HasSuccess(vector<Message*>* messages)
{
	for (Message* m : (*messages))
	{
		if (m->IsSucessful())
		{
			return true;
		}
	}
	return false;
}

bool Message::HasWarning(vector<Message*>* messages)
{
	for (Message* m : (*messages))
	{
		if (m->IsWarning())
		{
			return true;
		}
	}
	return false;
}

bool Message::HasError(vector<Message*>* messages)
{
	for (Message* m : (*messages))
	{
		if (m->IsError())
		{
			return true;
		}
	}
	return false;
}

bool Message::IsSuccessful(vector<Message*>* messages)
{
	for (Message* m : (*messages))
	{
		if (m->IsError())
		{
			return false;
		}
	}
	return true;
}

void Message::AddMessage(vector<Message*>* messages, int type, string message)
{
	messages->push_back(new Message(type, message));
}

void Message::AddMessage(vector<Message*>* messages, int type, int code, string message)
{
	messages->push_back(new Message(type, code, message));
}

void Message::AddMessages(vector<Message*>* from, vector<Message*>* to)
{
	for (Message* m : (*from))
	{
		to->push_back(m);
	}
}