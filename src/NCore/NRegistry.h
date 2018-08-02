// © 2018 NIREX ALL RIGHTS RESERVED

#ifndef _N_REGISTRY_H_
#define _N_REGISTRY_H_

#include "NDefines.h"
#include "NObject.h"
#include "NEventArgs.h"

#include <vector>
#include <functional>

namespace NLib
{
	typedef std::function<void(NObject* sender, NEventArgs* args)> Annex;

	class NAPI NRegistry final : public NObject
	{
	public:
		NRegistry();
		NRegistry(const NRegistry& nRegistery);
		NRegistry(NRegistry&& nRegistery);
		~NRegistry();

		long GetCount(void) const;

		NRegistry* operator()(NObject* sender, NEventArgs* args);
		NRegistry* Run(NObject* sender, NEventArgs* args);
		NRegistry* Register(Annex rhs);
		NRegistry* UnRegister(Annex* rhs);
		NRegistry* operator+=(Annex rhs);
		NRegistry* operator-=(Annex rhs);

		std::vector<Annex*> Container(void) const;

	private:
		volatile long m_count;
		std::vector<Annex*>* m_registered;
	};
}

#endif // !_N_REGISTRY_H_
