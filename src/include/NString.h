// © 2018 NIREX ALL RIGHTS RESERVED

#ifndef _N_STRING_H_
#define _N_STRING_H_

#include "NDefines.h"
#include "NObject.h"
#include <string>
#include <vector>

namespace NLib
{
	class NAPI NString final : public NObject
	{
	public:
		static char* ToUpper(char* temp);
		static char* ToLower(char* temp);
		static char* Proper(char* temp);
		
		static wchar_t* ToUpper(wchar_t* temp);
		static wchar_t* ToLower(wchar_t* temp);
		static wchar_t* Proper(wchar_t* temp);
		
		static std::string ToUpper(std::string temp);
		static std::string ToLower(std::string temp);
		static std::string Proper(std::string temp);
		
		static std::wstring ToUpper(std::wstring temp);
		static std::wstring ToLower(std::wstring temp);
		static std::wstring Proper(std::wstring temp);
		
		static std::vector<std::string> Split(std::string in_s, const std::string& delim);
		static std::vector<std::wstring> Split(std::wstring in_s, const std::wstring& delim);
		
		static std::wstring ToWide(std::string in);
		static std::string ToNarrow(std::wstring in);
	};
}
#endif // !_N_STRING_H_