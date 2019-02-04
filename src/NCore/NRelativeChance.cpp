#include "NRelativeChance.h"

namespace NLib
{
	NRelativeChance::NRelativeChance(void)
		: currentValue(0)
	{
	}

	NRelativeChance::~NRelativeChance(void)
	{
	}

	int NRelativeChance::AddChance(int pctValue)
	{
		currentValue += pctValue;
		valueVector.push_back(currentValue);
		return valueVector.size() - 1;
	}

	void NRelativeChance::EditChance(int index, int newPctValue)
	{
		// We'll take the difference of the current & the new value
		int tmp = newPctValue - valueVector[index];
		valueVector[index] = newPctValue;

		// We'll add the difference chance to each of the elements
		for (size_t i = index + 1; i < valueVector.size(); i++)
		{
			valueVector[i] += tmp;
		}
	}

	int NRelativeChance::GetIndex(int rndNumber)
	{
		// [0, currentValue)
		if (rndNumber >= currentValue)
		{
			return -1;
		}

		for (size_t i = 0; i < valueVector.size(); i++)
		{
			if (i < valueVector[i])
			{
				return i;
			}
		}

	}
}