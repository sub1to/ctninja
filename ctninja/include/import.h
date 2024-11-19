/*
	Copyright 2025-9999 sub1to

	This file is part of CTNinja

	CTNinja is free software; See LICENSE.txt or https://opensource.org/license/mit
*/

#ifndef _CTNINJA_IMPORT_H_
#define _CTNINJA_IMPORT_H_

#include "joaat.h"
#include "def.h"

namespace ctninja
{
	// cannot use "import" as a namespace name :/
	namespace xport
	{
		enum eImportErrors : uint32_t
		{
			IMERR_OK,
			IMERR_NO_MODULE,
			IMERR_NO_EXPORT,
		};

#ifdef _M_IX86
		bool check_and_set_headers(
			_IN_	void* module,
			_OUT_	IMAGE_DOS_HEADER** dos,
			_OUT_	IMAGE_NT_HEADERS32** nt
			);
#else // _M_X64
		bool check_and_set_headers(
			_IN_	void* module,
			_OUT_	IMAGE_DOS_HEADER** dos,
			_OUT_	IMAGE_NT_HEADERS64** nt
			);
#endif

		HMODULE get_module(
			_IN_	const uint32_t hash
			);

		FARPROC get_export(
			_IN_	void* module,
			_IN_	const uint32_t hash
			);

		FARPROC get_export(
			_IN_	const uint32_t module,
			_IN_	const uint32_t hash
			);

		uint32_t get_last_error(
			_OUT_	uint32_t* module	= nullptr,
			_OUT_	uint32_t* function	= nullptr
			);

		void set_last_error(
			_IN_	const uint32_t err,
			_IN_	const uint32_t mod,
			_IN_	const uint32_t fn
			);

		template <typename T>
		T	_$(uint32_t module, uint32_t fn)
		{
			return reinterpret_cast<T>(get_export(module, fn));
		}

#ifdef CTNINJA_MAGIC_IMPORT
		#define $(m, f) ctninja::xport::_$<fp##f>(#m##_JOAAT, #f##_JOAAT)

		//*
		#define $$(m, f, ...)														\
		[&]()->decltype(auto){														\
			using FT = fp##f;														\
			FT	_tmp_##f = ctninja::xport::_$<FT>(#m##_JOAAT, #f##_JOAAT);			\
			if(_tmp_##f) return _tmp_##f(__VA_ARGS__);								\
			return decltype(_tmp_##f(__VA_ARGS__))();								\
		}()
		//*/

		/*
		#define $$(m, f, ...) f(__VA_ARGS__)
		//*/
#endif //CTNINJA_MAGIC_IMPORT
	}
}
#endif // _CTNINJA_IMPORT_H_
