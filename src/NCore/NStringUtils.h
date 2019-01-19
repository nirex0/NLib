// © 2018 NIREX ALL RIGHTS RESERVED

#ifndef _N_STRING_UTILS_H_
#define _N_STRING_UTILS_H_

#include "NDefines.h"
#include "NObject.h"
#include <string>
#include <vector>

namespace NLib
{
	class NAPI NStringUtils final : public NObject
	{
	public:
		static char* ToUpper(char* temp);
		static char* ToLower(char* temp);
		static char* ProperizeWord(char* temp);
		static char* SubString(char* str, int size, int from, int to);

		static wchar_t* ToUpper(wchar_t* temp);
		static wchar_t* ToLower(wchar_t* temp);
		static wchar_t* ProperizeWord(wchar_t* temp);
		static wchar_t* SubString(wchar_t* str, int s_size, int from, int to);
		
		static std::string ToUpper(std::string temp);
		static std::string ToLower(std::string temp);
		static std::string ProperizeWord(std::string temp);
		static std::string SubString(std::string str, int from, int to);

		static std::wstring ToUpper(std::wstring temp);
		static std::wstring ToLower(std::wstring temp);
		static std::wstring ProperizeWord(std::wstring temp);
		static std::wstring SubString(std::wstring str, int from, int to);
		
		static std::vector<std::string> Split(std::string in_s, const std::string& delim);
		static std::vector<std::wstring> Split(std::wstring in_s, const std::wstring& delim);
		
		static std::vector<std::string> SplitNoEmpty(std::string in_s, const std::string& delim);
		static std::vector<std::wstring> SplitNoEmpty(std::wstring in_s, const std::wstring& delim);
		
		static std::wstring ToWide(std::string in);
		static std::string ToNarrow(std::wstring in);

		static std::vector<std::string> ToVector(std::string temp);
		static std::string FromVector(std::vector<std::string> temp);

		static std::vector<std::wstring> ToVector(std::wstring temp);
		static std::wstring FromVector(std::vector<std::wstring> temp);

		static std::string FullTrim(std::string temp);
		static std::wstring FullTrim(std::wstring temp);

		static std::string TrimBegin(std::string temp);
		static std::wstring TrimBegin(std::wstring temp);

		static std::string TrimEnd(std::string temp);
		static std::wstring TrimEnd(std::wstring temp);

		static std::string Replace(std::string str, std::string original, std::string rps);
		static std::wstring Replace(std::wstring wstr, std::wstring original, std::wstring rps);
		 	  
		static std::string RegexReplace(std::string str, std::string original, std::string rps);
		static std::wstring RegexReplace(std::wstring wstr, std::wstring original, std::wstring rps);

	};
}

#endif // !_N_STRING_UTILS_H_
