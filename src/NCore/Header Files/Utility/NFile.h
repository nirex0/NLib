//© 2018 NIREX ALL RIGHTS RESERVED

#ifndef _W_FILE_H_
#define _W_FILE_H_

#include "..\System\NDefines.h"
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
		std::int32_t FindFirst(std::string file, std::string val);
		
		std::vector<std::string> ReadAllLines(std::string file);
		NINT WriteAllLines(std::string file, std::vector<std::string> vecstr);
		std::vector<int32_t> FindAll(std::string file, std::string val);
		
		NBOOL SafeFread(void* buffer, NINT size, NINT number, FILE* fp);
	};
}
#endif // !_W_FILE_H_
