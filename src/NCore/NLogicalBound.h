// © 2019 NIREX ALL RIGHTS RESERVED

#ifndef _W_LOGICAL_BOUND_H_
#define _W_LOGICAL_BOUND_H_

#include "NObject.h"
#include "NEventArgs.h"

#include "NFunctions.h"
#include "NDefines.h"
#include <vector>

namespace NLib
{
	class NAPI NLogicalBound : public NObject
	{
	public:
		NLogicalBound();
		~NLogicalBound();

		bool Binding(void) const;
		bool Binding(bool intake);

		BindAnnex* Function(void) const;
		BindAnnex* Function(BindAnnex intake);

		void operator=(BindAnnex rhs);
		void operator()(void);

		void Run(void);

	private:
		bool m_binding;
		BindAnnex* m_annex;
	};
}

#endif // !_W_LOGICAL_BOUND_H_