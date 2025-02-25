/*
	Copyright 2025-9999 sub1to

	This file is part of CTNinja

	CTNinja is free software; See LICENSE.MD or https://opensource.org/license/mit
*/

#include "pch.h"
#include "xorstr.h"
#include "import.h"

namespace ctninja
{
	// Interlocked operations are used to make the functions threadsafe
	constexpr long DLL_FLAG_RUN		(1 << 0);	// Indicated that the first thread has requested check
	constexpr long DLL_FLAG_LOADED	(1 << 1);	// Indicates that the library is loaded
	constexpr long DLL_FLAG_FAILED	(1 << 2);	// Indicates the library has failed to load

	volatile long	m_msvcrt	= 0;
	volatile long	m_ucrtbase	= 0;


	// this is not guaranteed to be loaded, so gotta check..
	// ntdll should always be loaded.
	bool check_dll(uint32_t hash, const char* name, volatile long* lock)
	{
		long		flags;
		uint32_t	errmod;
			
		errmod	= 0;
		flags	= _InterlockedOr(lock, DLL_FLAG_RUN);

		if(flags & DLL_FLAG_RUN){
			if(flags & DLL_FLAG_LOADED){
				return true;
			}

			if(flags & DLL_FLAG_FAILED){
				xport::set_last_error(xport::IMERR_NO_MODULE, hash, 0);
				return false;
			}

			// it is pending
			// we will wait 1 ms and if it's still not loaded set the failed flag, so we don't wait again
			$$(Kernel32.dll, Sleep, 1);

			flags	= _InterlockedOr(lock, DLL_FLAG_RUN);

			if(flags & DLL_FLAG_LOADED){
				return true;
			}

			flags	= _InterlockedOr(lock, DLL_FLAG_FAILED);
			xport::set_last_error(xport::IMERR_NO_MODULE, "msvcrt.dll"_JOAAT, 0);
			return false;
		}

		if(xport::get_module("msvcrt.dll"_JOAAT)){
			flags = _InterlockedOr(lock, DLL_FLAG_LOADED);
			return true;
		}
			
		if(!$$(Kernel32.dll, LoadLibraryA, "msvcrt.dll"_X.c_str())){
			flags = _InterlockedOr(lock, DLL_FLAG_FAILED);
			return false;
		}
			
		// reset the error for msvcrt not being loaded, because it will be loaded now.
		if(xport::get_last_error(&errmod) == xport::IMERR_NO_MODULE && errmod == "msvcrt.dll"_JOAAT){
			xport::set_last_error(0, 0, 0);
		}

		flags = _InterlockedOr(lock, DLL_FLAG_LOADED);
		return true;
	}

	#define	CHECK_DLL(x, lock) if(!check_dll(#x##_JOAAT, #x##_X.c_str(), &##lock)){ return 0; }

	// 0x24 is the value the compiler sets when you link vsprintf_s / vswprintf_s
	// the wrapper function calls a function that returns a pointer to this static value
	// then it derefs it, to pass the value in the first param
	// The compiler generates `| 2` for the "unsafe" variants
	constexpr __int64	_stdio_common_vsprintf_s_flags		= 0x24;
	constexpr __int64	_stdio_common_vswprintf_s_flags		= 0x24;

	extern "C" {
		size_t $strlen(const char* str)
		{
			return $$(ntdll.dll, strlen, str);
		}

		int $printf(const char* fmt, ...)
		{
			CHECK_DLL(msvcrt.dll, m_msvcrt)

			int ret;
			va_list args;
			va_start(args, fmt);
			//ret = vprintf_s(fmt, args);
			ret = $$(msvcrt.dll, vprintf_s, fmt, args);
			va_end(args);
			return ret;
		}

		int $sprintf(char* buf, size_t buf_size, const char* fmt, ...)
		{
			CHECK_DLL(ucrtbase.dll, m_ucrtbase)

			int ret;
			va_list args;
			va_start(args, fmt);
			if(buf == nullptr || buf_size == 0){
				ret	= (int) $$(ucrtbase.dll, __stdio_common_vsprintf, _stdio_common_vsprintf_s_flags | 2, buf, buf_size, fmt, 0, args);
			} else {
				ret = (int) $$(ucrtbase.dll, __stdio_common_vsprintf_s, _stdio_common_vsprintf_s_flags, buf, buf_size, fmt, 0, args);
			}
			va_end(args);
			return ret;
		}

		int $vsprintf(char* buf, size_t buf_size, const char* fmt, va_list args)
		{
			CHECK_DLL(ucrtbase.dll, m_ucrtbase)

			if(buf == nullptr || buf_size == 0){
				return (int) $$(ucrtbase.dll, __stdio_common_vsprintf, _stdio_common_vsprintf_s_flags | 2, buf, buf_size, fmt, 0, args);
			}
			return (int) $$(ucrtbase.dll, __stdio_common_vsprintf_s, _stdio_common_vsprintf_s_flags, buf, buf_size, fmt, 0, args);
		}

		int $wprintf(const wchar_t* fmt, ...)
		{
			CHECK_DLL(msvcrt.dll, m_msvcrt)

			int ret;
			va_list args;
			va_start(args, fmt);
			//ret = vwprintf_s(fmt, args);
			ret = $$(msvcrt.dll, vwprintf_s, fmt, args);
			va_end(args);
			return ret;
		}

		int $swprintf(wchar_t* buf, size_t buf_size, const wchar_t* fmt, ...)
		{
			CHECK_DLL(ucrtbase.dll, m_ucrtbase)

			int ret;
			va_list args;
			va_start(args, fmt);
			if(buf == nullptr || buf_size == 0){
				ret	= (int) $$(ucrtbase.dll, __stdio_common_vswprintf, _stdio_common_vswprintf_s_flags | 2, buf, buf_size, fmt, 0, args);
			} else {
				ret = (int) $$(ucrtbase.dll, __stdio_common_vswprintf_s, _stdio_common_vswprintf_s_flags, buf, buf_size, fmt, 0, args);
			}
			va_end(args);
			return ret;
		}

		int $vswprintf(wchar_t* buf, size_t buf_size, const wchar_t* fmt, va_list args)
		{
			CHECK_DLL(ucrtbase.dll, m_ucrtbase)

			if(buf == nullptr || buf_size == 0){
				return (int) $$(ucrtbase.dll, __stdio_common_vswprintf, _stdio_common_vswprintf_s_flags | 2, buf, buf_size, fmt, 0, args);
			}
			return (int) $$(ucrtbase.dll, __stdio_common_vswprintf_s, _stdio_common_vswprintf_s_flags, buf, buf_size, fmt, 0, args);
		}
	}
}
