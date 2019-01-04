// � 2018 NIREX ALL RIGHTS RESERVED

#ifndef _N_PERFECT_CHANCE_H_
#define _N_PERFECT_CHANCE_H_

#include "NDefines.h"

namespace NLib
{
	class NAPI NPerfectChance
	{
	public:
		NPerfectChance(const size_t& pct_chance = 50);

		size_t GetChance(void) const;
		void SetChance(size_t value);

		size_t GetProcValue(void) const;
		size_t GetIterator(void) const;

		void Reset(void);

		bool operator()(void);
		bool Get(void);
		bool Perform(void);

	private:
		size_t chance;
		size_t iterator;
		size_t proc;
	};
}

#endif // _N_PERFECT_CHANCE_H_
