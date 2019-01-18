// © 2018 NIREX ALL RIGHTS RESERVED

#ifndef _N_STRING_H_
#define _N_STRING_H_

#include "NDefines.h"
#include <string>
#include <vector>

namespace NLib
{
	class NAPI NString
	{
	public:
		NString(void);
		NString(const std::string& str);
		NString(const std::wstring& wstr);
		NString(char* str);
		NString(wchar_t* str);
		NString(std::vector<char> vecstr);
		NString(std::vector<wchar_t> vecwstr);
		NString(std::vector<std::string> vecstr);
		NString(std::vector<std::wstring> vecwstr);
		NString(std::vector<char*> veccstr);
		NString(std::vector<wchar_t*> vecwcstr);
		~NString(void);

		std::string GetTrimRight(void) const;
		void TrimRight(void);

		std::string GetTrimLeft(void) const;
		void TrimLeft(void);

		std::string GetTrim(void) const;
		void Trim(void);

		std::string GetUpper(void) const;
		void ToUpper(void);

		std::string GetLower(void) const;
		void ToLower(void);

		void Clear(void);

		std::string SubString(size_t from, size_t to) const;
		std::string& GetString(void);
		std::string& operator()(void);
		std::string operator()(size_t from, size_t to) const;
		std::string AsString(void) const;
		std::string& AsStringRef(void);

		void Load(const std::string& str);
		void Load(const std::wstring& wstr);
		void Load(char* str);
		void Load(wchar_t* str);
		void Load(std::vector<char> vecstr);
		void Load(std::vector<wchar_t> vecwstr);
		void Load(std::vector<std::string> vecstr);
		void Load(std::vector<std::wstring> vecwstr);
		void Load(std::vector<char*> veccstr);
		void Load(std::vector<wchar_t*> vecwcstr);

		void Concat(const std::string& rhs);
		void Concat(const std::wstring& rhs);
		void Concat(char* str);
		void Concat(wchar_t* str);
		void Concat(std::vector<char> vecstr);
		void Concat(std::vector<wchar_t> vecwstr);
		void Concat(std::vector<std::string> vecstr);
		void Concat(std::vector<std::wstring> vecwstr);
		void Concat(std::vector<char*> veccstr);
		void Concat(std::vector<wchar_t*> vecwcstr);

		std::string operator+(const std::string& rhs) const;
		std::string operator+(const std::wstring& wstr) const;
		std::string operator+(char* str) const;
		std::string operator+(wchar_t* str) const;
		std::string operator+(std::vector<char> vecstr) const;
		std::string operator+(std::vector<wchar_t> vecwstr) const;
		std::string operator+(std::vector<std::string> vecstr) const;
		std::string operator+(std::vector<std::wstring> vecwstr) const;
		std::string operator+(std::vector<char*> veccstr) const;
		std::string operator+(std::vector<wchar_t*> vecwcstr) const;

		void operator+=(const std::string& rhs);
		void operator+=(const std::wstring& rhs);
		void operator+=(char* str);
		void operator+=(wchar_t* str);
		void operator+=(std::vector<char> vecstr);
		void operator+=(std::vector<wchar_t> vecwstr);
		void operator+=(std::vector<std::string> vecstr);
		void operator+=(std::vector<std::wstring> vecwstr);
		void operator+=(std::vector<char*> veccstr);
		void operator+=(std::vector<wchar_t*> vecwcstr);

		void operator=(const std::string& str);
		void operator=(const std::wstring& wstr);
		void operator=(char* str);
		void operator=(wchar_t* str);
		void operator=(std::vector<char> vecstr);
		void operator=(std::vector<wchar_t> vecwstr);
		void operator=(std::vector<std::string> vecstr);
		void operator=(std::vector<std::wstring> vecwstr);
		void operator=(std::vector<char*> veccstr);
		void operator=(std::vector<wchar_t*> vecwcstr);

		// Special Methods
		std::wstring GetWide(void) const;
		void LoadWide(std::wstring inwstr);

	private:
		// Using a pointer member so we can store huge data
		std::string* m_str;

		void Allocate(void);
		void Release(void);
	};
}

#endif // !_N_STRING_H_
