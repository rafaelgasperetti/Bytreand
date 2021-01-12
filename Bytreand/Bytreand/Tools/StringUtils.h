#pragma once

#include<string>
#include<vector>
#include<iostream>
#include<limits.h>

using namespace std;

class StringUtils
{
	public:
		static string ToString(char* st)
		{
			string ret(st);
			return ret;
		}

		static string ToString(char const* st)
		{
			string ret(st);
			return ret;
		}

		static string ToString(long long int i)
		{
			return to_string(i);
		}

		static char* ToChar(string st)
		{
			char* ret = &st[0u];
			return ret;
		}

		static int ToInt(string st)
		{
			return atoi(ToChar(st));
		}

		static long ToLong(string st)
		{
			return atol(ToChar(st));
		}

		static float ToFloat(string st)
		{
			return atof(ToChar(st));
		}

		static double ToDouble(string st)
		{
			return stod(st);
		}

		static long long int ToInt64(string st)
		{
			return atoll(ToChar(st));
		}

		static char CharAt(string s, int i)
		{
			return s[i];
		}

		static bool Equals(string str, string cmp)
		{
			if
				(
					str.compare(cmp) == 0
					)
			{
				return true;
			}
			else
			{
				return false;
			}
		}

		static bool EqualsIgnoreCase(string str, string cmp)
		{
			return Equals(ToLower(str), ToLower(cmp));
		}

		static bool StartsWith(string str, string cmp)
		{
			if
				(
					str.length() >= cmp.length() &&
					str.substr(0, cmp.length()).compare(cmp) == 0
					)
			{
				return true;
			}
			else
			{
				return false;
			}
		}

		static bool EndsWith(string str, string cmp)
		{
			if
				(
					str.length() >= cmp.length() &&
					str.substr(str.length() - cmp.length(), cmp.length()).compare(cmp) == 0
					)
			{
				return true;
			}
			else
			{
				return false;
			}
		}

		static string Append(string st1, string st2)
		{
			return st1 + st2;
		}

		static string AppendLine(string st1, string st2, bool newLineBetween, bool newLineAfter, bool whenEmptyIgnoreNewLine)
		{
			string ret = "";
			if (newLineBetween)
			{
				ret = st1 + '\n' + st2;
			}
			else
			{
				ret = st1 + st2;
			}

			if (newLineAfter && (!whenEmptyIgnoreNewLine || (whenEmptyIgnoreNewLine && st2.empty())))
			{
				ret = ret + '\n';
			}
			return ret;
		}

		static string AppendLine(string st1, string st2)
		{
			return AppendLine(st1, st2, false, false, false);
		}

		static bool Contains(string st, vector<string> v)
		{
			for (string &s : v)
			{
				if (Equals(st, s))
				{
					return true;
				}
			}
			return false;
		}

		static bool Contains(string st1, string st2)
		{
			size_t found = st1.find(st2);
			if (found != string::npos)
			{
				return true;
			}
			else
			{
				return false;
			}
		}

		static string LeftTrim(string st)
		{
			int firstIndex = -1;
			for (int i = 0; i < st.size(); i++)
			{
				int asciiSubstring = (int) CharAt(st, i);
				if (asciiSubstring >= 33 && asciiSubstring <= 126)
				{
					if (firstIndex == -1)
					{
						firstIndex = i;
					}
				}
			}
			return Substring(st, firstIndex, st.size());
		}

		static string RightTrim(string st)
		{
			int lastIndex = 0;
			for (int i = 0; i < st.size(); i++)
			{
				int asciiSubstring = (int) CharAt(st, i);
				if (asciiSubstring >= 33 && asciiSubstring <= 126)
				{
					lastIndex = i;
				}
			}
			return Substring(st, 0, lastIndex);
		}

		static string Trim(string st)
		{
			int firstIndex = -1, lastIndex = 0;
			for (int i = 0; i < st.size(); i++)
			{
				int asciiSubstring = (int) CharAt(st, i);
				if (asciiSubstring >= 33 && asciiSubstring <= 126)
				{
					if (firstIndex == -1)
					{
						firstIndex = i;
					}
					lastIndex = i;
				}
			}
			return Substring(st, firstIndex, lastIndex);
		}

		static int IndexOf(string st, vector<string> v)
		{
			for (unsigned int i = 0; i < v.size(); i++)
			{
				if (Equals(st, v[i]))
				{
					return i;
				}
			}
			return -1;
		}

		static int IndexOf(string st1, string st2)
		{
			if (st2.size() <= st1.size())
			{
				for (unsigned int i = 0; i + st2.size() <= st1.size(); i++)
				{
					if (Equals(st1.substr(i, st2.size()), st2))
					{
						return i;
					}
				}
			}
			return -1;
		}

		static vector<int> IndexesOf(string st1, string st2)
		{
			vector<int> indexes;
			if (st2.size() <= st1.size())
			{
				for (unsigned int i = 0; i + st2.size() <= st1.size(); i++)
				{
					if (Equals(st1.substr(i, st2.size()), st2))
					{
						indexes.push_back(i);
					}
				}
			}
			return indexes;
		}

		static int GetNumerOfLines(string st)
		{
			return IndexesOf(st, "\n").size();
		}

		static vector<int> IndexesOf(string st, vector<string> v)
		{
			vector<int> indexes;
			for (unsigned int i = 0; i < v.size(); i++)
			{
				if (Equals(st, v[i]))
				{
					indexes.push_back(i);
				}
			}
			return indexes;
		}

		static int LastIndexOf(string st, vector<string> v)
		{
			int ret = -1;
			for (unsigned int i = 0; i < v.size(); i++)
			{
				if (Equals(st, v[i]))
				{
					ret = i;
				}
			}
			return ret;
		}

		static int LastIndexOf(string st1, string st2)
		{
			int idx = -1;
			if (st2.size() <= st1.size())
			{
				for (unsigned int i = 0; i + st2.size() <= st1.size(); i++)
				{
					if (Equals(st1.substr(i, st2.size()), st2))
					{
						idx = i;
					}
				}
			}
			return idx;
		}

		static string Replace(string base, string from, string to)
		{
			string SecureCopy = base;

			for (size_t start_pos = SecureCopy.find(from); start_pos != string::npos; start_pos = SecureCopy.find(from, start_pos))
			{
				SecureCopy.replace(start_pos, from.length(), to);
			}

			return SecureCopy;
		}

		static string Replicate(string base, int times)
		{
			string ret = "";
			if (times < 0)
			{
				times = 0;
			}

			for (int i = 0; i < times; i++)
			{
				ret += base;
			}

			return ret;
		}

		static string Substring(string s, unsigned int i, unsigned int j)
		{
			if (i < s.size() && i <= j && j < s.size())
			{
				return s.substr(i, j - i + 1);
			}
			else
			{
				return "";
			}
		}

		static string Substring2(string s, unsigned int i, unsigned int j)
		{
			if (i < s.size() && i <= j && j < s.size())
			{
				return s.substr(i, j);
			}
			else
			{
				return "";
			}
		}

		static vector<string> Split(string value, string splitter)
		{
			vector<string> ret;
			if (Contains(value, splitter))
			{
				for (unsigned int i = 0, j = 0; i < value.size(); j++)
				{
					string subValue = Substring(value, i, j);
					if (Equals(subValue, splitter))
					{
						ret.push_back(subValue);
						j++;
						i = j + 1;
					}
				}
			}
			else
			{
				ret.push_back(value);
			}
			return ret;
		}

		static bool IsEmpty(string s)
		{
			return s.empty();
		}

		static bool IsNumber(string s)
		{
			if(!StringUtils::IsEmpty(s))
			{
				for (int i = 0; i < s.size(); i++)
				{
					if ((int)CharAt(s, i) < 48 || (int)CharAt(s, i) > 57)
					{
						return false;
					}
				}
				return true;
			}
			else
			{
				return false;
			}
		}

		static bool IsFloatingNumber(string s)
		{
			if (!StringUtils::IsEmpty(s))
			{
				int floatingPoint = -1;
				for (int i = 0; i < s.size(); i++)
				{
					if ((int)CharAt(s, i) == 46)
					{
						if (floatingPoint == -1)
						{
							floatingPoint = i;
						}
						else
						{
							return false;
						}
					}
					else if ((int)CharAt(s, i) < 48 || (int)CharAt(s, i) > 57)
					{
						return false;
					}
				}
				return true;
			}
			else
			{
				return false;
			}
		}

		static bool IsInteger(string st)
		{
			if (IsNumber(st))
			{
				int min = numeric_limits<int>::min();
				int max = numeric_limits<int>::max();

				long value = ToLong(st);

				if (value >= min && value <= max)
				{
					return true;
				}
				else
				{
					return false;
				}
			}
			else
			{
				return false;
			}
		}

		static bool IsLong(string st)
		{
			return IsNumber(st);
		}

		static bool IsFloat(string st)
		{
			if (IsFloatingNumber(st))
			{
				float min = numeric_limits<float>::lowest();
				float max = numeric_limits<float>::max();

				double value = ToDouble(st);

				if (value >= min && value <= max)
				{
					return true;
				}
				else
				{
					return false;
				}
			}
			else
			{
				return false;
			}
		}

		static bool Isdouble(string st)
		{
			return IsFloatingNumber(st);
		}

		static string ToUpper(string s)
		{
			string ret = "";
			for (int i = 0; i < s.size(); i++)
			{
				int charAt = (int)CharAt(s, i);
				if (charAt >= 97 && charAt <= 122)
				{
					charAt -= 32;
					ret += ToString((char) charAt);
				}
				else
				{
					ret += Substring(s, i, 1);
				}
			}
			return ret;
		}

		static string ToLower(string s)
		{
			string ret = "";
			for (int i = 0; i < s.size(); i++)
			{
				int charAt = (int)CharAt(s, i);
				if (charAt >= 65 && charAt <= 90)
				{
					charAt += 32;
					ret += ToString((char)charAt);
				}
				else
				{
					ret += Substring(s, i, 1);
				}
			}
			return ret;
		}

		template <typename T>
		static string ToBinary(T value, int width) {
			string binary = "";
			int restValue = 0;
			while (value > 0)
			{
				restValue = value % 2;
				value /= 2;
				binary += to_string(restValue);
			}

			auto a = binary.begin();
			auto b = binary.rbegin();

			while (a<b.base())
			{
				std::swap(*a++, *b++);
			}

			while (binary.size() < width)
			{
				binary = "0" + binary;
			}

			return binary;
		}

		template <typename T>
		static T FromBinary(string binary)
		{
			int i = 0;
			T ret = 0;

			while (i < binary.length() && binary.substr(i, 1).compare("0") == 0)
			{
				i++;
			}

			while (i < binary.length())
			{
				if (binary.substr(i, 1).compare("1") == 0)
				{
					ret += pow(2, binary.length() - 1 - i);
				}
				i++;
			}

			return ret;
		}
};