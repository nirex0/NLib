// © 2018 NIREX ALL RIGHTS RESERVED

#ifndef _N_REGISTRY_H_
#define _N_REGISTRY_H_

#include "NFunctions.h"

#include "NDefines.h"
#include "NObject.h"
#include "NEventArgs.h"

#include <vector>

namespace NLib
{
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
		NRegistry* Register(RegistryAnnex rhs);
		NRegistry* UnRegister(RegistryAnnex* rhs);
		NRegistry* operator+=(RegistryAnnex rhs);
		NRegistry* operator-=(RegistryAnnex rhs);

		std::vector<RegistryAnnex*> Container(void) const;

	private:
		volatile long m_count;
		std::vector<RegistryAnnex*>* m_registered;
	};
}

#endif // !_N_REGISTRY_H_
