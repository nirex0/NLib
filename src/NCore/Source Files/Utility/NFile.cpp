//� 2018 NIREX ALL RIGHTS RESERVED

#include "..\..\Header Files\Utility\NFile.h"

namespace NLib
{
	std::string NFile::ReadAllText(std::string file)
	{
		std::ifstream f(file.c_str());

		std::string str = "";
		std::string outstr = "";
		int iter = 0;
		while (std::getline(f, str))
		{
			iter++;
			outstr += str;
			outstr += 10;
		}
		f.close();
		return outstr;
	}

	int NFile::WriteAllText(std::string file, std::string str)
	{
		std::ofstream f;
		f.open(file);
		f << str;
		f.close();
		return 0;
	}

	std::int32_t NFile::FindFirst(std::string file, std::string val)
	{
		std::ifstream f(file.c_str());

		std::string str = "";
		int iter = 0;
		while (std::getline(f, str))
		{
			if (val == str)
			{
				return iter;
			}
			iter++;
		}
		f.close();
		return -1;
	}

	std::vector<std::string> NFile::ReadAllLines(std::string file)
	{
		std::ifstream f(file.c_str());
		std::vector<std::string> retv;

		std::string str = "";
		while (std::getline(f, str))
		{
			retv.push_back(str);
		}

		f.close();
		return retv;
	}

	int NFile::WriteAllLines(std::string file, std::vector<std::string> vecstr)
	{
		std::ofstream f;
		f.open(file);

		for (size_t i = 0; i < vecstr.size(); i++)
		{
			f << vecstr[i];
			f << std::endl;
		}

		f.close();
		return 0;
	}

	std::vector<int32_t> NFile::FindAll(std::string file, std::string val)
	{
		std::ifstream f(file.c_str());
		std::vector<int32_t> retv;

		std::string str = "";
		int iter = 0;

		while (std::getline(f, str))
		{
			if (val == str)
			{
				retv.push_back(iter);
			}
			iter++;
		}

		f.close();
		return retv;
	}

	NBOOL NFile::SafeFread(void* buffer, NINT size, NINT number, FILE* fp)
	{
		using namespace std;
		int ItemsRead;
		if (feof(fp))
		{
			return false;
		}
		ItemsRead = (int)fread(buffer, size, number, fp);
		if (ItemsRead < number)
		{
			return false;
		}
		return true;
	}

	NBOOL NFile::SafeFWrite(void * buffer, NINT size, NINT number, FILE * fp)
	{
		if (fwrite(buffer, size, number, fp) == number)
		{
			return false;
		}
		return true;
	}
	 
}