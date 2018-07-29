// © 2018 NIREX ALL RIGHTS RESERVED

#ifndef _N_GENERATOR_H_
#define _N_GENERATOR_H_

#include "NObject.h"
#include "NRegistry.h"
#include "NGeneratorArgs.h"

namespace NLib
{
	template <class T>
	class NGenerator : public NObject
	{
	public:
		NGenerator(void)
		{
			m_yield = new NRegistry();
		}

		~NGenerator(void)
		{
			delete m_yield;
		}

		void Generate(T in = {})
		{
			NGeneratorArgs<T>* args = new NGeneratorArgs<T>(m_iterationCount, in);
			m_yield->Run(this, args);
		}

	private:
		int m_iterationCount;
		NRegistry* m_yield;
	};
}

#endif // !_W_GENERATOR_H_