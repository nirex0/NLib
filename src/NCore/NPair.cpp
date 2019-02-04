// © 2019 NIREX ALL RIGHTS RESERVED

#include "NPair.h"

namespace NLib
{
	template<class T0, class T1>
	NPair<T0, T1>::NPair(const T0& left, const T1& right)
		: left(left)
		, right(right)
	{
	}

	template<class T0, class T1>
	NPair<T0, T1>::~NPair(void)
	{
	}

	template<class T0, class T1>
	T0 NPair<T0, T1>::GetLeft(void) const
	{
		return left;
	}

	template<class T0, class T1>
	void NPair<T0, T1>::SetLeft(const T0& val)
	{
		left = val;
	}

	template<class T0, class T1>
	T1 NPair<T0, T1>::GetRight(void) const
	{
		return right;
	}

	template<class T0, class T1>
	void NPair<T0, T1>::SetRight(const T1 & val)
	{
		right = val;
	}
}
