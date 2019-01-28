//© 2018 NIREX ALL RIGHTS RESERVED

#include "NFile.h"
#include "NWindows.h"
#include "NStringUtils.h"

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

	NINT NFile::WriteAllText(std::string file, std::string str)
	{
		std::ofstream f;
		f.open(file);
		f << str;
		f.close();
		return 0;
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

	NINT NFile::WriteAllLines(std::string file, std::vector<std::string> vecstr)
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
	
	std::vector<NCHAR> NFile::ReadAllBytes(std::string fileName)
	{
		std::ifstream ifs(fileName, std::ios::binary | std::ios::ate);
		std::ifstream::pos_type pos = ifs.tellg();

		std::vector<NCHAR> result((const unsigned int)pos);

		ifs.seekg(0, std::ios::beg);
		ifs.read(&result[0], pos);

		return result;
	}

	NINT NFile::WriteAllBytes(std::string fileName, std::vector<NCHAR> vecBytes)
	{
		std::ofstream ofs(fileName, std::ios::binary | std::ios::out);

		ofs.write(vecBytes.data(), vecBytes.size());

		if (ofs.bad()) //bad() function will check for badbit
		{
			return 1;
		}

		ofs.close();
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

	NBOOL NFile::SafeFread(NPVOID buffer, NINT size, NINT number, FILE* fp)
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

	NBOOL NFile::SafeFWrite(NPVOID buffer, NINT size, NINT number, FILE* fp)
	{
		if (fwrite(buffer, size, number, fp) == number)
		{
			return false;
		}
		return true;
	}

	std::vector<std::string> NFile::GetFiles(std::string folder)
	{
		std::vector<std::string> names;
		std::wstring search_path = NStringUtils::ToWide(folder) + L"/*.*";

		WIN32_FIND_DATA fd;
		HANDLE hFind = FindFirstFileW(search_path.c_str(), &fd);

		if (hFind != INVALID_HANDLE_VALUE)
		{
			do
			{
				if (!(fd.dwFileAttributes& FILE_ATTRIBUTE_DIRECTORY))
				{
					names.push_back(NStringUtils::ToNarrow(fd.cFileName));
				}
			} while (FindNextFile(hFind, &fd));
			FindClose(hFind);
		}
		return names;
	}

	std::vector<std::wstring> NFile::GetFiles(std::wstring folder)
	{
		std::vector<std::wstring> names;
		std::wstring search_path = folder + L"/*.*";

		WIN32_FIND_DATA fd;
		HANDLE hFind = FindFirstFileW(search_path.c_str(), &fd);

		if (hFind != INVALID_HANDLE_VALUE)
		{
			do
			{
				if (!(fd.dwFileAttributes& FILE_ATTRIBUTE_DIRECTORY))
				{
					names.push_back(fd.cFileName);
				}
			} while (FindNextFile(hFind, &fd));
			FindClose(hFind);
		}
		return names;
	}

	NBOOL NFile::Validate(const std::string& str, const std::set<std::string>& set)
	{
		for (const auto& s : set)
		{
			if (s == str) return true;
		}
		return false;
	}

	NBOOL NFile::Validate(const std::wstring& str, const std::set<std::wstring>& set)
	{
		for (const auto& s : set)
		{
			if (s == str) return true;
		}
		return false;
	}
	 
}