#include <Compiler/BytreandCompiler.h>
#include <Tools/CommandLineUtils.h>

int main(int argc, char** argv)
{
	vector<string> args;// = CommndLineUtils::GetArgs(argc, argv);

	args.push_back("Bytreand.exe");//Just for tests
	args.push_back("../Bytreand/Tests/Dotprod/Dotprod.c");//Just for tests
	args.push_back("C");//Just for tests
	args.push_back("../Bytreand/TestsOutput/Dotprod/Dotprod.exe");//Just for tests
	args.push_back("exe");//Just for tests

	BytreandCompiler* compiler = new BytreandCompiler(new FileReader(CommndLineUtils::GetInputPath(args)), CommndLineUtils::GetFrontEndLanguage(args));
	vector<Message*>* messages = compiler->Compile();

	cout << "Messages: " << endl;
	for (Message* m : (*messages))
	{
		cout << "<" << m->GetTypeName() << ">: " << m->GetText() << endl;
	}

	system("pause");
	
	return Message::HasWarning(messages) || Message::HasError(messages);
}