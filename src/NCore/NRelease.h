// © 2018 NIREX ALL RIGHTS RESERVED

#ifndef _N_RELEASE_H_
#define _N_RELEASE_H_

#include "NWindows.h"

namespace NLib
{
	template <class T>
	HRESULT Release(T** ppResource)
	{
		if (*ppResource)
		{
			(*ppResource)->Release();
			*ppResource = nullptr;
			return S_OK;
		}
		return E_ABORT;
	}
}
#endif // !_N_RELEASE_H_
