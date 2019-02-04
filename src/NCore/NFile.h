//© 2019 NIREX ALL RIGHTS RESERVED

#ifndef _N_FILE_H_
#define _N_FILE_H_

#include "NDefines.h"
#include <string>
#include <fstream>
#include <vector>
#include <iostream>

namespace NLib
{
	class NAPI NFile final
	{
	public:
		static std::string ReadAllText(std::string file);
		static NINT WriteAllText(std::string file, std::string str);

		static std::vector<std::string> ReadAllLines(std::string file);
		static NINT WriteAllLines(std::string file, std::vector<std::string> vecstr);

		static std::vector<NCHAR> ReadAllBytes(std::string fileName);
		static NINT WriteAllBytes(std::string fileName, std::vector<NCHAR> vecBytes);

		static std::int32_t FindFirst(std::string file, std::string val);
		static std::vector<int32_t> FindAll(std::string file, std::string val);

		static NBOOL SafeFread(NPVOID buffer, NINT size, NINT number, FILE* fp);
		static NBOOL SafeFWrite(NPVOID buffer, NINT size, NINT number, FILE* fp);

		static std::vector<std::string> GetFiles(const std::string& folder);
		static std::vector<std::wstring> GetFiles(const std::wstring& folder);

		static std::vector<std::string> GetDirectories(const std::string& folder);
		static std::vector<std::wstring> GetDirectories(const std::wstring& folder);
	};
}
#endif // !_N_FILE_H_
