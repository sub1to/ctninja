/*
	Copyright 2025-9999 sub1to

	This file is part of CTNinja

	CTNinja is free software; See LICENSE.MD or https://opensource.org/license/mit
*/

#pragma once

namespace xport
{
	void	reg()
	{
		REGISTER_TEST("ctninja::xport::get_module", [](UNIT_TEST* test)->bool{
			BCASS(ctninja::xport::get_module("ntdll.dll"_JOAAT) == GetModuleHandleA("ntdll.dll"));
			BCASS(ctninja::xport::get_module("kErNeLbAsE.dll"_JOAAT) == GetModuleHandleA("KernelBase.dll"));
			return true;
		});

		REGISTER_TEST("ctninja::xport::get_export", [](UNIT_TEST* test)->bool{
			HMODULE hNtDll;
			hNtDll	= ctninja::xport::get_module("ntdll.dll"_JOAAT);
			BCASS(hNtDll != nullptr);
			BCASS(ctninja::xport::get_export(hNtDll, "NtReadVirtualMemory"_JOAAT) == GetProcAddress(hNtDll, "NtReadVirtualMemory"));
			BCASS(ctninja::xport::get_export("ntdll.dll"_JOAAT, "NtReadVirtualMemory"_JOAAT) == GetProcAddress(hNtDll, "NtReadVirtualMemory"));
			return true;
		});

		REGISTER_TEST("ctninja::xport::get_last_error", [](UNIT_TEST* test)->bool{
			uint32_t errmod;
			uint32_t errfunc;
			BCASS(ctninja::xport::get_module("youcantfindme.dll"_JOAAT) == nullptr);
			BCASS(ctninja::xport::get_last_error(&errmod) == ctninja::xport::IMERR_NO_MODULE);
			BCASS(errmod == "youcantfindme.dll"_JOAAT);

			BCASS(ctninja::xport::get_export("ntdll.dll"_JOAAT, "youcantfindme"_JOAAT) == nullptr);
			BCASS(ctninja::xport::get_last_error(&errmod, &errfunc) == ctninja::xport::IMERR_NO_EXPORT);
			BCASS(errmod == "ntdll.dll"_JOAAT);
			BCASS(errfunc == "youcantfindme"_JOAAT);
			return true;
		});
	}
}