// © 2019 NIREX ALL RIGHTS RESERVED

#include "NFile.h"
#include "NWindows.h"
#include "NStringUtils.h"

namespace NLib
{
	std::string NFile::ReadAllText(const std::string& file)
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

	NINT NFile::WriteAllText(const std::string& file, const std::string& str)
	{
		std::ofstream f;
		f.open(file);
		f << str;
		f.close();
		return 0;
	}

	std::vector<std::string> NFile::ReadAllLines(const std::string& file)
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

	NINT NFile::WriteAllLines(const std::string& file, std::vector<std::string> vecstr)
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
	
	std::vector<NCHAR> NFile::ReadAllBytes(const std::string& fileName)
	{
		std::ifstream ifs(fileName, std::ios::binary | std::ios::ate);
		std::ifstream::pos_type pos = ifs.tellg();

		std::vector<NCHAR> result((const unsigned int)pos);

		ifs.seekg(0, std::ios::beg);
		ifs.read(&result[0], pos);

		return result;
	}

	NINT NFile::WriteAllBytes(const std::string& fileName, std::vector<NCHAR> vecBytes)
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
	
	std::int32_t NFile::FindFirst(const std::string& file, const std::string& val)
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

	std::vector<int32_t> NFile::FindAll(const std::string& file, const std::string& val)
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

	NBOOL NFile::SafeFRead(NPVOID buffer, NINT size, NINT number, FILE* fp)
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

	std::vector<std::string> NFile::GetFiles(const std::string& folder)
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

	std::vector<std::wstring> NFile::GetFiles(const std::wstring& folder)
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

	std::vector<std::string> NFile::GetDirectories(const std::string& folder)
	{
		DIR *dir = opendir(folder.c_str());

		std::vector<std::string> retVec;
		struct dirent *entry = readdir(dir);

		while (entry != NULL)
		{
			if (entry->d_type == DT_DIR)
			{
				retVec.push_back(entry->d_name);
			}
			entry = readdir(dir);
		}

		closedir(dir);
		return retVec;
	}

	std::vector<std::wstring> NFile::GetDirectories(const std::wstring& folder)
	{
		DIR *dir = opendir(NStringUtils::ToNarrow(folder).c_str());

		std::vector<std::wstring> retVec;
		struct dirent *entry = readdir(dir);

		while (entry != NULL)
		{
			if (entry->d_type == DT_DIR)
			{
				retVec.push_back(NStringUtils::ToWide(entry->d_name));
			}
			entry = readdir(dir);
		}

		closedir(dir);
		return retVec;
	}

	std::vector<std::string> NFile::GetEntities(const std::string& folder)
	{
		std::vector<std::string> files = GetFiles(folder);
		std::vector<std::string> folders = GetDirectories(folder);
		std::vector<std::string> retVec;

		for (size_t i = 0; i < folders.size(); i++)
		{
			retVec.push_back(folders[i]);
		}

		for (size_t i = 0; i < files.size(); i++)
		{
			retVec.push_back(files[i]);
		}

		return retVec;
	}

	std::vector<std::wstring> NFile::GetEntities(const std::wstring& folder)
	{
		std::vector<std::wstring> files = GetFiles(folder);
		std::vector<std::wstring> folders = GetDirectories(folder);
		std::vector<std::wstring> retVec;

		for (size_t i = 0; i < folders.size(); i++)
		{
			retVec.push_back(folders[i]);
		}

		for (size_t i = 0; i < files.size(); i++)
		{
			retVec.push_back(files[i]);
		}

		return retVec;
	}
}