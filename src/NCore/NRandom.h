//© 2019 NIREX ALL RIGHTS RESERVED

#ifndef _N_RANDOM_H_
#define _N_RANDOM_H_

#include "NDefines.h"
#include <random>

namespace NLib
{
	class NAPI NRandom
	{
	public:
		//NRandom(void);
		//~NRandom(void);
		double Next(void);

	private:

	};

	class NAPI NumberManip
	{
	public:
		static NULONGLONG Stretch(double number, NULONGLONG min, NULONGLONG max);
	};
}
#endif // !_N_RANDOM_H_



