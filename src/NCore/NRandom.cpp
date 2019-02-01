//© 2019 NIREX ALL RIGHTS RESERVED

#include "NRandom.h"
#include <time.h>

namespace NLib
{
	double NRandom::Next(void)
	{
		static std::mt19937 rng(std::random_device{}());
		return std::generate_canonical<double, 128>(rng);
	}

	NULONGLONG NumberManip::Stretch(double number, NULONGLONG min, NULONGLONG max)
	{
		if (number > 1) number = 1;
		else if (number < 0) number = 0;

		unsigned char numberPct = number * 100;
		unsigned long long range = max - min;
		unsigned long long rangePct = range / 100;
		unsigned long long rangeNumber = rangePct * numberPct;
		unsigned long long llNumber = rangeNumber + min;

		return llNumber;
	}
}