// © 2018 NIREX ALL RIGHTS RESERVED

#ifndef _W_LOGICAL_BOUND_H_
#define _W_LOGICAL_BOUND_H_

#include "NObject.h"
#include "..\EventArgs\NEventArgs.h"

#include "..\System\NDefines.h"
#include <vector>
#include <functional>

namespace NLib
{
	typedef std::function<void(bool&)> NBinding;

	class NAPI NLogicalBound : public NObject
	{
	public:
		NLogicalBound();
		~NLogicalBound();

		bool Binding(void) const;
		bool Binding(bool intake);

		NBinding* Function(void) const;
		NBinding* Function(NBinding intake);

		void operator=(NBinding rhs);
		void operator()(void);

		void Run(void);

	private:
		bool m_binding;
		NBinding* m_annex;
	};
}

#endif // !_W_LOGICAL_BOUND_H_