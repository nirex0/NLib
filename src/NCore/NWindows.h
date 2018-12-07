// © 2018 NIREX ALL RIGHTS RESERVED

#ifndef _N_WINDOWS_H_
#define _N_WINDOWS_H_

#ifdef E_ERR
#undef E_ERR	
#endif // E_ERR

#ifdef S_OK
#undef S_OK
#endif // S_OK

#ifdef E_ABORT
#undef E_ABORT
#endif // E_ABORT

#ifdef E_NOTIMPL
#undef E_NOTIMPL
#endif // E_NOTIMPL

#ifdef E_UNKNOWN
#undef E_UNKNOWN
#endif // E_UNKNOWN

#ifdef UNREFERENCED_PARAMETER
#undef UNREFERENCED_PARAMETER
#endif // UNREFERENCED_PARAMETER

#ifdef WINVER
#undef WINVER 
#endif // WINVER

#define WINVER 0x0501

#ifdef _WIN32_WINNT
#undef _WIN32_WINNT
#endif // _WIN32_WINNT

#define _WIN32_WINNT 0x0501

#define WIN32_LEAN_AND_MEAN

#define NOGDICAPMASKS
#define NOMENUS
#define NOICONS
#define NOSYSCOMMANDS
#define NORASTEROPS
#define OEMRESOURCE
#define NOATOM
#define NOCLIPBOARD
#define NOCOLOR
#define NOCTLMGR
#define NODRAWTEXT
#define NOKERNEL
#define NONLS
#define NOMEMMGR
#define NOMETAFILE
#define NOMINMAX
#define NOOPENFILE
#define NOSCROLL
#define NOSERVICE
#define NOSOUND
#define NOTEXTMETRIC
#define NOWH
#define NOCOMM
#define NOKANJI
#define NOHELP
#define NOPROFILER
#define NODEFERWINDOWPOS
#define NOMCX
#define NORPC
#define NOPROXYSTUB
#define NOIMAGE
#define NOTAPE

#include <Windows.h>

#endif // !_N_WINDOWS_H_