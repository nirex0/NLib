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

	class NRegistry final : public NObject
	{
	public:
		NAPI NRegistry();
		NAPI NRegistry(const NRegistry& nRegistery);
		NAPI NRegistry(NRegistry&& nRegistery);
		NAPI ~NRegistry();

		NAPI long GetCount(void) const;

		NAPI NRegistry* operator()(NObject* sender, NEventArgs* args);
		NAPI NRegistry* Run(NObject* sender, NEventArgs* args);
		NAPI NRegistry* Register(Annex rhs);
		NAPI NRegistry* UnRegister(Annex* rhs);
		NAPI NRegistry* operator+=(Annex rhs);
		NAPI NRegistry* operator-=(Annex rhs);

	private:
		volatile long m_count;
		std::vector<Annex*> m_registered;
	};
}

#endif // !_N_REGISTRY_H_
