//© 2019 NIREX ALL RIGHTS RESERVED

#include "NRandom.h"
#include <time.h>

using ULongLong = unsigned long long;

NRandom::NRandom(void)
{
	udist = new std::uniform_real_distribution<std::mt19937::result_type>(0, 1);
	std::mt19937::result_type const seedval = time(0);
	rng.seed(seedval);
}

NRandom::~NRandom(void)
{
	delete udist;
}

double NRandom::Next(void)
{
	std::mt19937::result_type random_number = (*udist)(rng);
	return random_number;
}

ULongLong NumberManip::Stretch(double number, ULongLong min, ULongLong max)
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
