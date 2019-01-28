//© 2018 NIREX ALL RIGHTS RESERVED

#include "NCIO.h"

namespace NLib
{
	std::string NCIO::Input(const std::string& in)
	{
		std::cout << in;

		std::string inputStr;
		std::cin >> inputStr;
		return inputStr;
	}

	std::string NCIO::Print(const std::string& in)
	{
		std::cout << in;
		return in;
	}

	NString NLib::NCIO::Input(const NString& in)
	{
		std::cout << in.AsString();

		std::string inputStr;
		std::cin >> inputStr;
		return NString(inputStr);
	}

	NString NLib::NCIO::Print(const NString& in)
	{
		std::cout << in.AsString();
		return in;
	}
}
