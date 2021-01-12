#pragma once

#include <Tools/StringUtils.h>

class CommndLineUtils
{
	public:
		static const int InputPath = 1;
		static const int FrontEndLanguage = 2;
		static const int OutputPath = 3;
		static const int OutputFormats = 4;

		static vector<string> GetArgs(int argNumber, char** argv)
		{
			vector<string> ret;

			if (argv != NULL)
			{
				string argv1(argv[argNumber]);
				vector<int> indexes = StringUtils::IndexesOf(argv1, "\"");

				if (indexes.size() > 0 && indexes[0] == 0)
				{
					for (unsigned int i = 1; i <= indexes.size(); i++)
					{
						if (i % 2 == 1)
						{
							string newArg = argv1.substr(indexes[i - 1] + 1, indexes[i] - indexes[i - 1] - 1);
							ret.push_back(newArg);
						}
					}
				}
				else
				{
					vector<int> spaceIdxs = StringUtils::IndexesOf(argv1, " ");

					for (unsigned int i = 0; i <= spaceIdxs.size(); i++)
					{
						string newArg;
						if (i == 0)
						{
							newArg = argv1.substr(0, spaceIdxs[i]);
						}
						else
						{
							newArg = argv1.substr(spaceIdxs[i - 1] + 1, spaceIdxs[i] - spaceIdxs[i - 1] - 1);
						}
						ret.push_back(newArg);
					}
				}
			}

			return ret;
		}

		static string GetInputPath(vector<string> args)
		{
			return args.size() > InputPath ? args[InputPath] : "";
		}

		static string GetFrontEndLanguage(vector<string> args)
		{
			return args.size() > FrontEndLanguage ? args[FrontEndLanguage] : "";
		}

		static string GetOutputPath(vector<string> args)
		{
			return args.size() > OutputPath ? args[OutputPath] : "";
		}

		static string GetOutputFileFormats(vector<string> args)
		{
			return args.size() > OutputFormats ? args[OutputFormats] : "";
		}
};