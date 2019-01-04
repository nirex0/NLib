// © 2018 NIREX ALL RIGHTS RESERVED

#include "NPerfectChance.h"
#include <math.h>

namespace NLib
{
	NPerfectChance::NPerfectChance(const size_t& pct_chance)
		: iterator(0)
		, proc(0)
	{
		if (pct_chance > 100)
		{
			chance = 100;
			proc = (size_t)roundf(float(100 / chance));
			return;
		}
		chance = pct_chance;
		proc = (size_t)roundf(float(100 / chance));
	}

	size_t NPerfectChance::GetChance(void) const
	{
		return chance;
	}

	void NPerfectChance::SetChance(size_t value)
	{
		if(chance == value)
		{
			return;
		}

		if (value > 100)
		{
			chance = 100;
			proc = (size_t)roundf(float(100 / chance));
		}
		else
		{
			chance = value;
			proc = (size_t)roundf(float(100 / chance));
		}

		iterator = 0;
	}

	size_t NPerfectChance::GetProcValue(void) const
	{
		return proc;
	}

	size_t NPerfectChance::GetIterator(void) const
	{
		return iterator;
	}

	void NPerfectChance::Reset(void)
	{
		iterator = 0;
		proc = (size_t)roundf(float(100 / chance));
	}

	bool NPerfectChance::operator()(void)
	{
		iterator++;
		if (iterator == proc)
		{
			if (m_annex)
			{
				m_annex();
			}

			iterator = 0;
			return true;
		}
		else
		{
			return false;
		}
	}

	bool NPerfectChance::Get(void)
	{
		iterator++;
		if (iterator == proc)
		{
			if (m_annex)
			{
				m_annex();
			}

			iterator = 0;
			return true;
		}
		else
		{
			return false;
		}
	}

	bool NPerfectChance::Perform(void)
	{
		iterator++;
		if (iterator == proc)
		{
			if (m_annex)
			{
				m_annex();
			}

			iterator = 0;
			return true;
		}
		else
		{
			return false;
		}
	}

	ProcCallee& NPerfectChance::GetCallee(void)
	{
		return m_annex;
	}
}
