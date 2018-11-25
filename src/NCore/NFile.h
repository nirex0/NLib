//© 2018 NIREX ALL RIGHTS RESERVED

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
		std::string ReadAllText(std::string file);
		NINT WriteAllText(std::string file, std::string str);

		std::vector<std::string> ReadAllLines(std::string file);
		NINT WriteAllLines(std::string file, std::vector<std::string> vecstr);

		std::vector<NCHAR> ReadAllBytes(std::string fileName);
		NINT WriteAllBytes(std::string fileName, std::vector<NCHAR> vecBytes);

		std::int32_t FindFirst(std::string file, std::string val);
		std::vector<int32_t> FindAll(std::string file, std::string val);

		NBOOL SafeFread(NPVOID buffer, NINT size, NINT number, FILE* fp);
		NBOOL SafeFWrite(NPVOID buffer, NINT size, NINT number, FILE* fp);
	};
}
#endif // !_N_FILE_H_
