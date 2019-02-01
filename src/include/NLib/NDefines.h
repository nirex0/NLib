// © 2019 NIREX ALL RIGHTS RESERVED

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

#define PSIZE_MAX			65535
#define PSIZE_NLIB			4096
#define PSIZE_MTU			1500
	
#define NLIB
#define N_LIB

	typedef void*				NPVOID;

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

	typedef unsigned int		NUBYTE;
	typedef unsigned char		NUWORD;
	typedef unsigned long		NUDWORD;
	typedef unsigned long long	NUQWORD;


#define S_OK 0
#define E_ERR 1
#define E_ABORT 2
#define E_UNKNOWN 3

}

#endif // !_N_DEFINES_H_
