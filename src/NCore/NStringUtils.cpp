// © 2018 NIREX ALL RIGHTS RESERVED

#include "NStringUtils.h"
#include <algorithm> 
#include <cctype>
#include <locale>
#include <codecvt>
#include <regex>

namespace NLib
{
	char* NStringUtils::ToUpper(char* temp)
	{
		char* retc = temp;

		int i = 0;
		while (retc[i])
		{
			retc[i] = toupper(retc[i]);
			i++;
		}
		return retc;
	}

	char* NStringUtils::ToLower(char* temp)
	{
		char* retc = temp;

		int i = 0;
		while (retc[i])
		{
			retc[i] = tolower(retc[i]);
			i++;
		}
		return retc;
	}

	char* NStringUtils::ProperizeWord(char* temp)
	{
		char* retc = temp;

		int i = 0;
		while (retc[i])
		{
			retc[i] = tolower(retc[i]);
			i++;
		}
		retc[0] = toupper(retc[0]);
		return retc;
	}

	char* NStringUtils::SubString(char* str, int s_size, int from, int to)
	{
		if (from < 0 || to >= s_size || to < from || from >= s_size || from > to)
		{
			return nullptr;
		}

		std::string tmp = str;
		return (char*)tmp.substr(from, to - from).c_str();
	}

	wchar_t* NStringUtils::ToUpper(wchar_t* temp)
	{
		wchar_t* retc = temp;

		int i = 0;
		while (retc[i])
		{
			retc[i] = toupper(retc[i]);
			i++;
		}
		return retc;
	}

	wchar_t* NStringUtils::ToLower(wchar_t* temp)
	{
		wchar_t* retc = temp;

		int i = 0;
		while (retc[i])
		{
			retc[i] = tolower(retc[i]);
			i++;
		}
		return retc;
	}

	wchar_t* NStringUtils::ProperizeWord(wchar_t* temp)
	{
		wchar_t* retc = temp;

		int i = 0;
		while (retc[i])
		{
			retc[i] = tolower(retc[i]);
			i++;
		}
		retc[0] = toupper(retc[0]);
		return retc;
	}

	wchar_t* NStringUtils::SubString(wchar_t* str, int s_size, int from, int to)
	{
		if (from < 0 || to >= s_size || to < from || from >= s_size || from > to)
		{
			return nullptr;
		}

		std::wstring tmp = str;
		return (wchar_t*)tmp.substr(from, to - from).c_str();
	}

	std::string NStringUtils::ToUpper(std::string temp)
	{
		int i = 0;
		while (temp[i])
		{
			temp[i] = toupper(temp[i]);
			i++;
		}
		return temp;
	}

	std::string NStringUtils::ToLower(std::string temp)
	{
		int i = 0;
		while (temp[i])
		{
			temp[i] = tolower(temp[i]);
			i++;
		}
		return temp;
	}

	std::string NStringUtils::ProperizeWord(std::string temp)
	{
		int i = 0;
		while (temp[i])
		{
			temp[i] = tolower(temp[i]);
			i++;
		}
		temp[0] = toupper(temp[0]);
		return temp;
	}

	std::string NStringUtils::SubString(std::string str, int from, int to)
	{
		if (from < 0 || to >= (int)str.length() || to < from || from >= (int)str.length() || from > to)
		{
			return nullptr;
		}

		std::string tmp = str;
		return tmp.substr(from, to - from);
	}

	std::wstring NStringUtils::ToUpper(std::wstring temp)
	{
		int i = 0;
		while (temp[i])
		{
			temp[i] = toupper(temp[i]);
			i++;
		}
		return temp;
	}

	std::wstring NStringUtils::ToLower(std::wstring temp)
	{
		int i = 0;
		while (temp[i])
		{
			temp[i] = tolower(temp[i]);
			i++;
		}
		return temp;
	}

	std::wstring NStringUtils::ProperizeWord(std::wstring temp)
	{
		int i = 0;
		while (temp[i])
		{
			temp[i] = tolower(temp[i]);
			i++;
		}
		temp[0] = toupper(temp[0]);
		return temp;
	}

	std::wstring NStringUtils::SubString(std::wstring str, int from, int to)
	{
		if (from < 0 || to >= (int)str.length() || to < from || from >= (int)str.length() || from > to)
		{
			return nullptr;
		}

		std::wstring tmp = str;
		return tmp.substr(from, to - from);
	}

	std::vector<std::string> NStringUtils::Split(std::string in_s, const std::string& delim)
	{
		std::vector <std::string> retvec;
		size_t pos = 0;
		std::string token;

		while ((pos = in_s.find(delim)) != std::string::npos)
		{
			token = in_s.substr(0, pos);
			retvec.push_back(token);
			in_s.erase(0, pos + delim.length());
		}

		retvec.push_back(in_s);
		return retvec;
	}

	std::vector<std::wstring> NStringUtils::Split(std::wstring in_s, const std::wstring & delim)
	{
		std::vector <std::wstring> retvec;
		size_t pos = 0;
		std::wstring token;

		while ((pos = in_s.find(delim)) != std::wstring::npos)
		{
			token = in_s.substr(0, pos);
			retvec.push_back(token);
			in_s.erase(0, pos + delim.length());
		}

		retvec.push_back(in_s);
		return retvec;
	}

	std::vector<std::string> NStringUtils::SplitNoEmpty(std::string in_s, const std::string & delim)
	{
		std::vector <std::string> retvec;
		size_t pos = 0;
		std::string token;

		while ((pos = in_s.find(delim)) != std::string::npos)
		{
			token = in_s.substr(0, pos);
			retvec.push_back(token);
			in_s.erase(0, pos + delim.length());
		}

		retvec.push_back(in_s);
		
		std::vector<std::string> propervec;
		for (const std::string& val : retvec)
		{
			if (val != "")
			{
				propervec.push_back(val);
			}
		}
		return propervec;
	}

	std::vector<std::wstring> NStringUtils::SplitNoEmpty(std::wstring in_s, const std::wstring & delim)
	{
		std::vector <std::wstring> retvec;
		size_t pos = 0;
		std::wstring token;

		while ((pos = in_s.find(delim)) != std::wstring::npos)
		{
			token = in_s.substr(0, pos);
			retvec.push_back(token);
			in_s.erase(0, pos + delim.length());
		}

		retvec.push_back(in_s);

		std::vector<std::wstring> propervec;
		for (const std::wstring& val : retvec)
		{
			if (val != L"")
			{
				propervec.push_back(val);
			}
		}
		return propervec;
	}

	std::wstring NStringUtils::ToWide(std::string in)
	{
		std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
		return converter.from_bytes(in);
	}

	std::string NStringUtils::ToNarrow(std::wstring in)
	{
		std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
		return converter.to_bytes(in);
	}

	std::vector<std::string> NStringUtils::ToVector(std::string temp)
	{
		return SplitNoEmpty(temp, "\n");
	}

	std::string NStringUtils::FromVector(std::vector<std::string> temp)
	{
		std::string retS;
		for (const auto& p : temp)
		{
			retS += p;
			retS += "\n";
		}
		return retS;
	}

	std::vector<std::wstring> NStringUtils::ToVector(std::wstring temp)
	{
		return SplitNoEmpty(temp, L"\n");
	}

	std::wstring NStringUtils::FromVector(std::vector<std::wstring> temp)
	{
		std::wstring retS;
		for (const auto& p : temp)
		{
			retS += p;
			retS += L"\n";
		}
		return retS;
	}

	std::string NStringUtils::FullTrim(std::string temp)
	{
		return TrimBegin(TrimEnd(temp));
	}

	std::wstring NStringUtils::FullTrim(std::wstring temp)
	{
		return TrimBegin(TrimEnd(temp));
	}

	std::string NStringUtils::TrimBegin(std::string temp)
	{
		temp.erase(temp.begin(), std::find_if(temp.begin(), temp.end(), [](int ch) {
			return !std::isspace(ch);
		}));
		return temp;
	}

	std::wstring NStringUtils::TrimBegin(std::wstring temp)
	{
		temp.erase(temp.begin(), std::find_if(temp.begin(), temp.end(), [](int ch) {
			return !std::isspace(ch);
		}));
		return temp;
	}

	std::string NStringUtils::TrimEnd(std::string temp)
	{
		temp.erase(std::find_if(temp.rbegin(), temp.rend(), [](int ch) {
			return !std::isspace(ch);
		}).base(), temp.end());
		return temp;
	}

	std::wstring NStringUtils::TrimEnd(std::wstring temp)
	{
		temp.erase(std::find_if(temp.rbegin(), temp.rend(), [](int ch) {
			return !std::isspace(ch);
		}).base(), temp.end());
		return temp;
	}

	std::string NStringUtils::Replace(std::string str, std::string original, std::string rps)
	{
		str.replace(str.find(original), original.length(), rps);
		return str;
	}

	std::wstring NStringUtils::Replace(std::wstring wstr, std::wstring original, std::wstring rps)
	{
		wstr.replace(wstr.find(original), original.length(), rps);
		return wstr;
	}

	std::string NStringUtils::RegexReplace(std::string str, std::string original, std::string rps)
	{
		return std::regex_replace(str, std::regex(original), rps);
	}

	std::wstring NStringUtils::RegexReplace(std::wstring wstr, std::wstring original, std::wstring rps)
	{
		return ToWide(std::regex_replace(ToNarrow(wstr), std::regex(ToNarrow(original)), ToNarrow(rps)));
	}

}
