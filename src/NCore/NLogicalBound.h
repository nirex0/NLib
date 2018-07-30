// © 2018 NIREX ALL RIGHTS RESERVED

#ifndef _W_LOGICAL_BOUND_H_
#define _W_LOGICAL_BOUND_H_

#include "NObject.h"
#include "NEventArgs.h"

#include "NDefines.h"
#include <vector>
#include <functional>

namespace NLib
{
	typedef std::function<void(bool&)> NBinding;

	class NLogicalBound : public NObject
	{
	public:
		NAPI NLogicalBound();
		NAPI ~NLogicalBound();

		NAPI bool Binding(void) const;
		NAPI bool Binding(bool intake);

		NAPI NBinding* Function(void) const;
		NAPI NBinding* Function(NBinding intake);

		NAPI void operator=(NBinding rhs);
		NAPI void operator()(void);

		NAPI void Run(void);

	private:
		bool m_binding;
		NBinding* m_annex;
	};
}

#endif // !_W_LOGICAL_BOUND_H_