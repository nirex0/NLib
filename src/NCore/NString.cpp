// © 2018 NIREX ALL RIGHTS RESERVED

#include "NString.h"

namespace NLib
{
	NString::NString(void)
	{
		Allocate();
	}

	NString::NString(const std::string& str)
	{
		Allocate();
		*m_str = str;
	}

	NString::NString(const std::wstring& wstr)
	{
		Allocate();
		*m_str = NStringUtils::ToNarrow(wstr);
	}

	NString::NString(char* str)
	{
		Allocate();
		*m_str = std::string(str);
	}

	NString::NString(wchar_t* str)
	{
		Allocate();
		*m_str = NStringUtils::ToNarrow(std::wstring(str));
	}

	NString::NString(std::vector<char> vecstr)
	{
		Allocate();
		*m_str = "";
		for (const auto& c : vecstr)
		{
			*m_str += c;
		}
	}

	NString::NString(std::vector<wchar_t> vecwstr)
	{
		Allocate();
		std::wstring wstr;
		for (const auto& c : vecwstr)
		{
			wstr += c;
		}
		*m_str = NStringUtils::ToNarrow(wstr);
	}

	NString::NString(std::vector<std::string> vecstr)
	{
		Allocate();
		*m_str = "";
		for (const auto& s : vecstr)
		{
			*m_str += s;
		}
	}

	NString::NString(std::vector<std::wstring> vecwstr)
	{
		Allocate();
		*m_str = "";
		for (const auto& s : vecwstr)
		{
			*m_str += NStringUtils::ToNarrow(s);
		}
	}

	NString::NString(std::vector<char*> veccstr)
	{
		Allocate();
		*m_str = "";
		for (size_t i = 0; i < veccstr.size(); i++)
		{
			std::string tmp = veccstr[i];
			*m_str += tmp;
		}
	}

	NString::NString(std::vector<wchar_t*> vecwcstr)
	{
		Allocate();
		*m_str = "";
		for (size_t i = 0; i < vecwcstr.size(); i++)
		{
			std::wstring tmp = vecwcstr[i];
			*m_str += NStringUtils::ToNarrow(tmp);
		}
	}

	NString::~NString(void)
	{
		Release();
	}

	std::string NString::GetTrimRight(void) const
	{
		return NStringUtils::TrimEnd(*m_str);
	}

	void NString::TrimRight(void)
	{
		*m_str = NStringUtils::TrimEnd(*m_str);
	}

	std::string NString::GetTrimLeft(void) const
	{
		return NStringUtils::TrimBegin(*m_str);
	}

	void NString::TrimLeft(void)
	{
		*m_str = NStringUtils::TrimBegin(*m_str);
	}

	std::string NString::GetTrim(void) const
	{
		return NStringUtils::FullTrim(*m_str);
	}

	void NString::Trim(void)
	{
		*m_str = NStringUtils::FullTrim(*m_str);
	}

	std::string NString::GetUpper(void) const
	{
		return NStringUtils::ToUpper(*m_str);
	}

	void NString::ToUpper(void)
	{
		*m_str = NStringUtils::ToUpper(*m_str);
	}

	std::string NString::GetLower(void) const
	{
		return NStringUtils::ToLower(*m_str);
	}

	void NString::ToLower(void)
	{
		*m_str = NStringUtils::ToLower(*m_str);
	}

	void NString::Clear(void)
	{
		*m_str = "";
	}

	std::string NString::SubString(size_t from, size_t to) const
	{
		return NStringUtils::SubString(*m_str, from, to);
	}

	std::string& NString::GetString(void)
	{
		return *m_str;
	}

	std::string& NString::operator()(void)
	{
		return *m_str;
	}

	std::string NString::operator()(size_t from, size_t to) const
	{
		return SubString(from, to);
	}

	std::string NString::AsString(void) const
	{
		return *m_str;
	}

	std::string& NString::AsStringRef(void)
	{
		return *m_str;
	}

	void NString::Load(const std::string& str)
	{
		*m_str = str;
	}

	void NString::Load(const std::wstring& wstr)
	{
		*m_str = NStringUtils::ToNarrow(wstr);
	}

	void NString::Load(char* str)
	{
		*m_str = str;
	}

	void NString::Load(wchar_t* str)
	{
		*m_str = NStringUtils::ToNarrow(std::wstring(str));
	}

	void NString::Load(std::vector<char> vecstr)
	{
		*m_str = "";
		for (const auto& c : vecstr)
		{
			*m_str += c;
		}
	}

	void NString::Load(std::vector<wchar_t> vecwstr)
	{
		std::wstring wstr;
		for (const auto& c : vecwstr)
		{
			wstr += c;
		}
		*m_str = NStringUtils::ToNarrow(wstr);
	}

	void NString::Load(std::vector<std::string> vecstr)
	{
		*m_str = "";
		for (const auto& s : vecstr)
		{
			*m_str += s;
		}
	}

	void NString::Load(std::vector<std::wstring> vecwstr)
	{
		*m_str = "";
		for (const auto& s : vecwstr)
		{
			*m_str += NStringUtils::ToNarrow(s);
		}
	}

	void NString::Load(std::vector<char*> veccstr)
	{
		*m_str = "";
		for (size_t i = 0; i < veccstr.size(); i++)
		{
			std::string tmp = veccstr[i];
			*m_str += tmp;
		}
	}

	void NString::Load(std::vector<wchar_t*> vecwcstr)
	{
		*m_str = "";
		for (size_t i = 0; i < vecwcstr.size(); i++)
		{
			std::wstring tmp = vecwcstr[i];
			*m_str += NStringUtils::ToNarrow(tmp);
		}
	}

	void NString::Concat(const std::string& rhs)
	{
		*m_str += rhs;
	}

	void NString::Concat(const std::wstring& rhs)
	{
		*m_str += NStringUtils::ToNarrow(rhs);
	}

	void NString::Concat(char* str)
	{
		*m_str += std::string(str);
	}

	void NString::Concat(wchar_t* str)
	{
		*m_str += NStringUtils::ToNarrow(std::wstring(str));
	}

	void NString::Concat(std::vector<char> vecstr)
	{
		for (const auto& c : vecstr)
		{
			*m_str += c;
		}
	}

	void NString::Concat(std::vector<wchar_t> vecwstr)
	{
		std::wstring tmp = NStringUtils::ToWide(*m_str);
		for (const auto& c : vecwstr)
		{
			tmp += c;
		}
		*m_str = NStringUtils::ToNarrow(tmp);
	}

	void NString::Concat(std::vector<std::string> vecstr)
	{
		for (const auto& p : vecstr)
		{
			*m_str += p;
		}
	}

	void NString::Concat(std::vector<std::wstring> vecwstr)
	{
		for (const auto& p : vecwstr)
		{
			*m_str += NStringUtils::ToNarrow(p);
		}
	}

	void NString::Concat(std::vector<char*> veccstr)
	{
		for (size_t i = 0; i < veccstr.size(); i++)
		{
			std::string tmp = veccstr[i];
			*m_str += tmp;
		}
	}

	void NString::Concat(std::vector<wchar_t*> vecwcstr)
	{
		for (size_t i = 0; i < vecwcstr.size(); i++)
		{
			std::wstring tmp = vecwcstr[i];
			*m_str += NStringUtils::ToNarrow(tmp);
		}
	}

	std::string NString::operator+(const std::string& rhs) const
	{
		return *m_str + rhs;
	}

	std::string NString::operator+(const std::wstring& wstr) const
	{
		return *m_str + NStringUtils::ToNarrow(wstr);
	}

	std::string NString::operator+(char* str) const
	{
		return *m_str + std::string(str);
	}

	std::string NString::operator+(wchar_t* str) const
	{
		return *m_str + NStringUtils::ToNarrow(std::wstring(str));
	}

	std::string NString::operator+(std::vector<char> vecstr) const
	{
		std::string out = *m_str;
		for (const auto& c : vecstr)
		{
			out += c;
		}
		return out;
	}

	std::string NString::operator+(std::vector<wchar_t> vecwstr) const
	{
		std::wstring out = NStringUtils::ToWide(*m_str);
		for (const auto& c : vecwstr)
		{
			out += c;
		}
		return NStringUtils::ToNarrow(out);
	}

	std::string NString::operator+(std::vector<std::string> vecstr) const
	{
		std::string out = *m_str;
		for (const auto& c : vecstr)
		{
			out += c;
		}
		return out;
	}

	std::string NString::operator+(std::vector<std::wstring> vecstr) const
	{
		std::string out = *m_str;
		for (const auto& c : vecstr)
		{
			out += NStringUtils::ToNarrow(c);
		}
		return out;
	}

	std::string NString::operator+(std::vector<char*> veccstr) const
	{
		std::string out = *m_str;
		for (size_t i = 0; i < veccstr.size(); i++)
		{
			std::string tmp = veccstr[i];
			out += tmp;
		}
		return out;
	}

	std::string NString::operator+(std::vector<wchar_t*> vecwcstr) const
	{
		std::string out = *m_str;
		for (size_t i = 0; i < vecwcstr.size(); i++)
		{
			std::wstring tmp = vecwcstr[i];
			out += NStringUtils::ToNarrow(tmp);
		}
		return out;
	}

	void NString::operator+=(const std::string& rhs)
	{
		*m_str += rhs;
	}

	void NString::operator+=(const std::wstring& rhs)
	{
		*m_str += NStringUtils::ToNarrow(rhs);
	}

	void NString::operator+=(char* str)
	{
		*m_str += std::string(str);
	}

	void NString::operator+=(wchar_t* str)
	{
		*m_str += NStringUtils::ToNarrow(std::wstring(str));
	}

	void NString::operator+=(std::vector<char> vecstr)
	{
		for (const auto& c : vecstr)
		{
			*m_str += c;
		}
	}

	void NString::operator+=(std::vector<wchar_t> vecwstr)
	{
		std::wstring tmp = NStringUtils::ToWide(*m_str);
		for (const auto& c : vecwstr)
		{
			tmp += c;
		}
		*m_str = NStringUtils::ToNarrow(tmp);
	}

	void NString::operator+=(std::vector<std::string> vecstr)
	{
		for (const auto& p : vecstr)
		{
			*m_str += p;
		}
	}

	void NString::operator+=(std::vector<std::wstring> vecwstr)
	{
		for (const auto& p : vecwstr)
		{
			*m_str += NStringUtils::ToNarrow(p);
		}
	}

	void NString::operator+=(std::vector<char*> veccstr)
	{
		for (size_t i = 0; i < veccstr.size(); i++)
		{
			std::string tmp = veccstr[i];
			*m_str += tmp;
		}
	}

	void NString::operator+=(std::vector<wchar_t*> vecwcstr)
	{
		for (size_t i = 0; i < vecwcstr.size(); i++)
		{
			std::wstring tmp = vecwcstr[i];
			*m_str += NStringUtils::ToNarrow(tmp);
		}
	}

	void NString::operator=(const std::string& str)
	{
		*m_str = str;
	}

	void NString::operator=(const std::wstring& wstr)
	{
		*m_str = NStringUtils::ToNarrow(wstr);
	}

	void NString::operator=(char* str)
	{
		*m_str = str;
	}

	void NString::operator=(wchar_t* str)
	{
		*m_str = NStringUtils::ToNarrow(std::wstring(str));
	}

	void NString::operator=(std::vector<char> vecstr)
	{
		*m_str = "";
		for (const auto& c : vecstr)
		{
			*m_str += c;
		}
	}

	void NString::operator=(std::vector<wchar_t> vecwstr)
	{
		std::wstring wstr;
		for (const auto& c : vecwstr)
		{
			wstr += c;
		}
		*m_str = NStringUtils::ToNarrow(wstr);
	}

	void NString::operator=(std::vector<std::string> vecstr)
	{
		*m_str = "";
		for (const auto& s : vecstr)
		{
			*m_str += s;
		}
	}

	void NString::operator=(std::vector<std::wstring> vecwstr)
	{
		*m_str = "";
		for (const auto& s : vecwstr)
		{
			*m_str += NStringUtils::ToNarrow(s);
		}
	}

	void NString::operator=(std::vector<char*> veccstr)
	{
		*m_str = "";
		for (size_t i = 0; i < veccstr.size(); i++)
		{
			std::string tmp = veccstr[i];
			*m_str += tmp;
		}
	}

	void NString::operator=(std::vector<wchar_t*> vecwcstr)
	{
		*m_str = "";
		for (size_t i = 0; i < vecwcstr.size(); i++)
		{
			std::wstring tmp = vecwcstr[i];
			*m_str += NStringUtils::ToNarrow(tmp);
		}
	}

	std::wstring NString::GetWide(void) const
	{
		return NStringUtils::ToWide(*m_str);
	}

	void NString::LoadWide(std::wstring inwstr)
	{
		*m_str = NStringUtils::ToNarrow(inwstr);
	}

	void NString::Allocate(void)
	{
		if (m_str)
		{
			Release();
		}

		m_str = new std::string();
		*m_str = "";
	}

	void NString::Release(void)
	{
		delete m_str;
	}
}