// © 2018 NIREX ALL RIGHTS RESERVED

#ifndef _N_DEFINES_H_
#define _N_DEFINES_H_

namespace NLib
{
#define NEXPORT

#ifdef NEXPORT  
#define NAPI __declspec(dllexport)   
#else  
#define NAPI __declspec(dllimport)   
#endif 

#define NCALL				__stdcall
#define NENTRY				__stdcall
#define N_CALL				__stdcall
#define N_ENTRY				__stdcall

#define NLIB
#define N_LIB

	typedef int					NINT;
	typedef char				NCHAR;
	typedef bool				NBOOL;
	typedef float				NFLOAT;
	typedef double				NDOUBLE;
	typedef long				NLONG;
	typedef long long			NLONGLONG;

	typedef unsigned int		NUINT;
	typedef unsigned char		NUCHAR;
	typedef unsigned long		NULONG;
	typedef unsigned long long	NULONGLONG;

	typedef int					NSBYTE;
	typedef char				NSWORD;
	typedef long				NSDWORD;
	typedef long long			NSQWORD;

	typedef int					NUBYTE;
	typedef char				NUWORD;
	typedef long				NUDWORD;
	typedef long long			NUQWORD;
}

#endif // !_N_DEFINES_H_
