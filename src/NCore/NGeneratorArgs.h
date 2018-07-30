// © 2018 NIREX ALL RIGHTS RESERVED

#ifndef _N_GENERATOR_ARGS_H_
#define _N_GENERATOR_ARGS_H_

#include "NEventArgs.h"
#include "NDefines.h"

namespace NLib
{
	template <class T>
	class NGeneratorArgs : public NEventArgs
	{
	public:
		NAPI NGeneratorArgs(NINT iteration, T value = {})
			: m_valueHeld(value)
			, m_iterationCount(iteration)
		{
		}

		NAPI bool HasValue(void) const
		{
			return (m_valueHeld != {});
		}

		NAPI T Value(void) const
		{
			return m_valueHeld;
		}

		NAPI NINT Iteration(void) const
		{
			return m_iterationCount;
		}

	private:
		T m_valueHeld;
		NINT m_iterationCount;
	};
}

#endif // !_N_GENERATOR_ARGS_H_