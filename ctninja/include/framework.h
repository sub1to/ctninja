/*
	Copyright 2025-9999 sub1to

	This file is part of CTNinja

	CTNinja is free software; See LICENSE.txt or https://opensource.org/license/mit
*/

#ifndef _CTNINJA_FRAMEWORK_
#define _CTNINJA_FRAMEWORK_

#define EXTERN_C extern "C"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
#define _WIN32_WINNT 0x0A00 // 0x0A00 corresponds to Windows 10
// Windows Header Files
#include <iostream>
#include <Windows.h>
#include <winternl.h>
#include <vector>
#include <share.h>
#include <intrin.h>

#ifdef _IN_
#undef _IN_
#endif
#define _IN_

#ifdef _OUT_
#undef _OUT_
#endif
#define _OUT_

#ifdef _OPTIONAL_
#undef _OPTIONAL_
#endif
#define _OPTIONAL_

typedef signed char				i8,		*pi8,		*const cpi8;
typedef unsigned char			u8,		*pu8,		*const cpu8;
typedef signed short			i16,	*pi16,		*const cpi16;
typedef unsigned short			u16,	*pu16,		*const cpu16;
typedef signed long				i32,	*pi32,		*const cpi32;
typedef unsigned long			u32,	*pu32,		*const cpu32;
typedef signed long long		i64,	*pi64,		*const cpi64;
typedef unsigned long long		u64,	*pu64,		*const cpu64;
typedef float					f32,	*pf32,		*const cpf32;
typedef double					f64,	*pf64,		*const cpf64;

typedef char*					pch;
typedef const char*				cpch;


#endif
