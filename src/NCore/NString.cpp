// © 2018 NIREX ALL RIGHTS RESERVED

#include "NString.h"
#include <locale>
#include <codecvt>

namespace NLib
{
	char* NString::ToUpper(char* temp)
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

	char* NString::ToLower(char* temp)
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

	char* NString::ProperizeWord(char* temp)
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

	char* NString::SubString(char* str, int s_size, int from, int to)
	{
		if (from < 0 || to >= s_size || to < from || from >= s_size || from > to)
		{
			return nullptr;
		}

		std::string tmp = str;
		return (char*)tmp.substr(from, to - from).c_str();
	}

	wchar_t* NString::ToUpper(wchar_t* temp)
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

	wchar_t* NString::ToLower(wchar_t* temp)
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

	wchar_t* NString::ProperizeWord(wchar_t* temp)
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

	wchar_t* NString::SubString(wchar_t* str, int s_size, int from, int to)
	{
		if (from < 0 || to >= s_size || to < from || from >= s_size || from > to)
		{
			return nullptr;
		}

		std::wstring tmp = str;
		return (wchar_t*)tmp.substr(from, to - from).c_str();
	}

	std::string NString::ToUpper(std::string temp)
	{
		int i = 0;
		while (temp[i])
		{
			temp[i] = toupper(temp[i]);
			i++;
		}
		return temp;
	}

	std::string NString::ToLower(std::string temp)
	{
		int i = 0;
		while (temp[i])
		{
			temp[i] = tolower(temp[i]);
			i++;
		}
		return temp;
	}

	std::string NString::ProperizeWord(std::string temp)
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

	std::string NString::SubString(std::string str, int from, int to)
	{
		if (from < 0 || to >= (int)str.length() || to < from || from >= (int)str.length() || from > to)
		{
			return nullptr;
		}

		std::string tmp = str;
		return tmp.substr(from, to - from);
	}

	std::wstring NString::ToUpper(std::wstring temp)
	{
		int i = 0;
		while (temp[i])
		{
			temp[i] = toupper(temp[i]);
			i++;
		}
		return temp;
	}

	std::wstring NString::ToLower(std::wstring temp)
	{
		int i = 0;
		while (temp[i])
		{
			temp[i] = tolower(temp[i]);
			i++;
		}
		return temp;
	}

	std::wstring NString::ProperizeWord(std::wstring temp)
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

	std::wstring NString::SubString(std::wstring str, int from, int to)
	{
		if (from < 0 || to >= (int)str.length() || to < from || from >= (int)str.length() || from > to)
		{
			return nullptr;
		}

		std::wstring tmp = str;
		return tmp.substr(from, to - from);
	}

	std::vector<std::string> NString::Split(std::string in_s, const std::string& delim)
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

	std::vector<std::wstring> NString::Split(std::wstring in_s, const std::wstring & delim)
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

	std::vector<std::string> NString::SplitNoEmpty(std::string in_s, const std::string & delim)
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

	std::vector<std::wstring> NString::SplitNoEmpty(std::wstring in_s, const std::wstring & delim)
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

	std::wstring NString::ToWide(std::string in)
	{
		std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
		return converter.from_bytes(in);
	}

	std::string NString::ToNarrow(std::wstring in)
	{
		std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
		return converter.to_bytes(in);
	}

	std::vector<std::string> NString::ToVector(std::string temp)
	{
		return SplitNoEmpty(temp, "\n");
	}

	std::string NString::FromVector(std::vector<std::string> temp)
	{
		std::string retS;
		for (const auto& p : temp)
		{
			retS += p;
			retS += "\n";
		}
		return retS;
	}

	std::vector<std::wstring> NString::ToVector(std::wstring temp)
	{
		return SplitNoEmpty(temp, L"\n");
	}

	std::wstring NString::FromVector(std::vector<std::wstring> temp)
	{
		std::wstring retS;
		for (const auto& p : temp)
		{
			retS += p;
			retS += L"\n";
		}
		return retS;
	}

	std::string NString::FullTrim(std::string temp)
	{
		return TrimBegin(TrimEnd(temp));
	}

	std::wstring NString::FullTrim(std::wstring temp)
	{
		return TrimBegin(TrimEnd(temp));
	}

	std::string NString::TrimBegin(std::string temp)
	{
		temp.erase(0, temp.find_first_not_of(" \t\n\r\f\v"));
		return temp;
	}

	std::wstring NString::TrimBegin(std::wstring temp)
	{
		temp.erase(0, temp.find_first_not_of(L" \t\n\r\f\v"));
		return temp;
	}

	std::string NString::TrimEnd(std::string temp)
	{
		temp.erase(temp.find_last_not_of(" \t\n\r\f\v") + 1);
		return temp;
	}

	std::wstring NString::TrimEnd(std::wstring temp)
	{
		temp.erase(temp.find_last_not_of(L" \t\n\r\f\v") + 1);
		return temp;
	}
}
