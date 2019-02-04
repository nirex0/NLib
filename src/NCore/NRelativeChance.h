// © 2019 NIREX ALL RIGHTS RESERVED

#ifndef _N_RELATIVE_CHANCE_H_
#define _N_RELATIVE_CHANCE_H_

#include "NObject.h"
#include "NDefines.h"
#include <vector>

namespace NLib
{
	class NAPI NRelativeChance : public NObject
	{
	public:
		NRelativeChance(void);
		~NRelativeChance(void);

		int AddChance(int pctValue);
		void EditChance(int index, int newPctValue);
		int GetIndex(int rndNumber);

	private:
		int currentValue;
		std::vector<int> valueVector;
	};
}

#endif // !_N_RELATIVE_CHANCE_H_
