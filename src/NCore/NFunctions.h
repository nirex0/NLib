// © 2018 NIREX ALL RIGHTS RESERVED

#ifndef _N_FUNCTIONS_H_
#define _N_FUNCTIONS_H_

#include <functional>
#include "NDefines.h"
#include "NObject.h"
#include "NEventArgs.h"

namespace NLib
{
	typedef NAPI std::function<void(void)> BaseAnnex;

	typedef NAPI std::function<void(bool&)> BindAnnex;

	typedef NAPI std::function<void(NObject* sender, NEventArgs* args)> RegistryAnnex;
}

#endif // !_N_FUNCTIONS_H_
