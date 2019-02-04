// © 2019 NIREX ALL RIGHTS RESERVED

#ifndef _N_PAIR_H_
#define _N_PAIR_H_

#include "NObject.h"
#include "NDefines.h"

namespace NLib
{
	template <class T0, class T1>
	class NAPI NPair : public NObject
	{
	public:
		NPair(const T0& left, const T1& right);
		~NPair(void);

		T0 GetLeft(void) const;
		void SetLeft(const T0& val);

		T1 GetRight(void) const;
		void SetRight(const T1& val);

	private:
		T0 left;
		T1 right;
	};

	using NRange = NPair<int, int>;
	using NFRange = NPair<float, float>;
	using NDRange = NPair<double, double>;
}


#endif // !_N_PAIR_H_
