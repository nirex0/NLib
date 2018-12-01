// © 2018 NIREX ALL RIGHTS RESERVED

#ifndef _N_AUDIO_H_
#define _N_AUDIO_H_

#include "NWindows.h"
#include "NObject.h"
#include <string>

#include "NMCILinkage.h" // NOTE: Include after "Windows.h"

namespace NLib
{
	class NAudio : public NObject
	{
	public:
		NAudio(const wchar_t* name, const wchar_t* path, HWND handle);
		NAudio(const std::wstring& name, const std::wstring& path, HWND handle);
		~NAudio(void);

		// Getters
		const wchar_t* Path(void) const;
		const wchar_t* Name(void) const;

		// Functions
		void Play(void);
		void Pause(void);
		void Resume(void);
		void Stop(void);
		void PlayOnRepeat(void);

	private:
		const wchar_t* m_name;
		const wchar_t* m_path;
		HWND m_handle;
	};
}

#endif // !_N_AUDIO_H_
