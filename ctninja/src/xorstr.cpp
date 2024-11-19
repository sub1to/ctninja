/*
	Copyright 2025-9999 sub1to

	This file is part of CTNinja

	CTNinja is free software; See LICENSE.txt or https://opensource.org/license/mit
*/

#include "pch.h"
#include "xorstr.h"
#include "import.h"

namespace ctninja
{
	constexpr long MSVCRT_FLAG_RUN		(1 << 0);
	constexpr long MSVCRT_FLAG_LOADED	(1 << 1);
	constexpr long MSVCRT_FLAG_FAILED	(1 << 2);

	volatile long	m_msvcrt	= 0;


	// this is not guaranteed to be loaded, so gotta check..
	// ntdll should always be loaded.
	bool check_msvcrt()
	{
		long flags;
			
		flags	= _InterlockedOr(&m_msvcrt, MSVCRT_FLAG_RUN);
		if(flags & MSVCRT_FLAG_RUN){
			if(flags & MSVCRT_FLAG_LOADED){
				return true;
			}

			if(flags & MSVCRT_FLAG_FAILED){
				return false;
			}

			// it is pending
			// we will wait 1 ms and if it's still not loaded set the failed flag, so we don't wait again
			$$(Kernel32.dll, Sleep, 1);

			flags	= _InterlockedOr(&m_msvcrt, MSVCRT_FLAG_RUN);

			if(flags & MSVCRT_FLAG_LOADED){
				return true;
			}

			flags	= _InterlockedOr(&m_msvcrt, MSVCRT_FLAG_FAILED);
			return false;
		}

		if(xport::get_module("msvcrt.dll"_JOAAT)){
			flags = _InterlockedOr(&m_msvcrt, MSVCRT_FLAG_LOADED);
			return true;
		}
			
			
		if(!$$(Kernel32.dll, LoadLibraryA, "msvcrt.dll"_X.c_str())){
			flags = _InterlockedOr(&m_msvcrt, MSVCRT_FLAG_FAILED);
			return false;
		}

		flags = _InterlockedOr(&m_msvcrt, MSVCRT_FLAG_LOADED);
		return true;
	}

	extern "C" {
		int $printf(const char* fmt, ...)
		{
			check_msvcrt();

			int ret;
			va_list args;
			va_start(args, fmt);
			//ret = vprintf_s(fmt, args);
			ret = $$(msvcrt.dll, vprintf_s, fmt, args);
			va_end(args);
			return ret;
		}

		int $sprintf_s(char* buf, size_t buf_size, const char* fmt, ...)
		{
			int ret;
			va_list args;
			va_start(args, fmt);
			//ret = vsprintf_s(buf, buf_size, fmt, args);
			ret = $$(ntdll.dll, vsprintf_s, buf, buf_size, fmt, args);
			va_end(args);
			return ret;
		}

		int $wprintf_s(const wchar_t* fmt, ...)
		{
			check_msvcrt();

			int ret;
			va_list args;
			va_start(args, fmt);
			//ret = vwprintf_s(fmt, args);
			ret = $$(msvcrt.dll, vwprintf_s, fmt, args);
			va_end(args);
			return ret;
		}

		int $swprintf_s(wchar_t* buf, size_t buf_size, const wchar_t* fmt, ...)
		{
			int ret;
			va_list args;
			va_start(args, fmt);
			//ret = vswprintf_s(buf, buf_size, fmt, args);
			ret = $$(ntdll.dll, vswprintf_s, buf, buf_size, fmt, args);
			va_end(args);
			return ret;
		}
	}
}
