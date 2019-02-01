//© 2019 NIREX ALL RIGHTS RESERVED

#ifndef _N_NCIO_H_
#define _N_NCIO_H_

#include "NDefines.h"
#include "NString.h"
#include <string>
#include <iostream>

namespace NLib
{
	class NAPI NCIO final
	{
	public:
		static std::string Input(const std::string& in);
		static std::string Print(const std::string& in);

		static NString Input(const NString& in);
		static NString Print(const NString& in);
	};

	template <class T>
	static T Input(const T& in)
	{
		std::cout << in;

		T outT;
		std::cin >> outT;
		return outT;
	}

	template <class T>
	static T Print(const T& in)
	{
		std::cout << in;
		return in;
	}
}
#endif // _N_NCIO_H_