//© 2019 NIREX ALL RIGHTS RESERVED

#ifndef _N_RANDOM_H_
#define _N_RANDOM_H_

#include <random>

class NRandom
{
public:
	NRandom(void);
	~NRandom(void);
	double Next(void);

private:
	std::mt19937 rng;
	std::uniform_real_distribution<std::mt19937::result_type>* udist;
};

class NumberManip
{
	using ULongLong = unsigned long long;
public:
	static ULongLong Stretch(double number, ULongLong min, ULongLong max);
};

#endif // !_N_RANDOM_H_