//© 2019 NIREX ALL RIGHTS RESERVED

#ifndef _N_RANDOM_H_
#define _N_RANDOM_H_

#include "NDefines.h"
#include "NObject.h"
#include <random>

namespace NLib
{
	class NAPI NRandom final : public NObject
	{
	public:
		static double Next(void);
		static NULONGLONG Stretch(double number, NULONGLONG min, NULONGLONG max);
	};
}
#endif // !_N_RANDOM_H_



