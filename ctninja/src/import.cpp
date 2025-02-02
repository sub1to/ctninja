/*
	Copyright 2025-9999 sub1to

	This file is part of CTNinja

	CTNinja is free software; See LICENSE.MD or https://opensource.org/license/mit
*/

#include "pch.h"
#include "import.h"
#include "joaat.h"

#ifdef _M_X64
// No inline ASM in x64, defined in teb64.asm
extern "C" void* _get_teb();
#endif 

namespace ctninja
{
	namespace xport
	{

		uint32_t	m_errNo		= 0;
		uint32_t	m_errMod	= 0;
		uint32_t	m_errFn		= 0;


#ifdef _M_IX86
		__declspec(noinline) bool	check_and_set_headers(_IN_ void* module, _OUT_ IMAGE_DOS_HEADER** dos, _OUT_ IMAGE_NT_HEADERS32** nt)
		{
			IMAGE_DOS_HEADER*	pDos;
			IMAGE_NT_HEADERS32*	pNT;

			pDos		= reinterpret_cast<IMAGE_DOS_HEADER*>(module);
			*dos		= pDos;

			if(pDos->e_magic != 'ZM') {
				//DBG_MSG("Invalid DOS magic %x", pDos->e_magic);
				return false;
			}

			pNT			= reinterpret_cast<IMAGE_NT_HEADERS32*>(reinterpret_cast<BYTE*>(module) + pDos->e_lfanew);
			*nt			= pNT;

			if(pNT->Signature != 'EP') {
				//DBG_MSG("Invalid NT signature %x", pNT->Signature);
				return false;
			}

			return true;
		}

		__declspec(naked) TEB* _get_teb() {
			__asm {
				mov eax, fs:[0x18]    // Get TEB address from FS:[0x18]
				ret
			}
		}
#else // _M_X64
		__declspec(noinline) bool	check_and_set_headers(_IN_ void* module, _OUT_ IMAGE_DOS_HEADER** dos, _OUT_ IMAGE_NT_HEADERS64** nt)
		{
			IMAGE_DOS_HEADER*	pDos;
			IMAGE_NT_HEADERS64*	pNT;

			pDos		= reinterpret_cast<IMAGE_DOS_HEADER*>(module);
			*dos		= pDos;

			if(pDos->e_magic != 'ZM') {
				//DBG_MSG("Invalid DOS magic %x", pDos->e_magic);
				return false;
			}

			pNT			= reinterpret_cast<IMAGE_NT_HEADERS64*>(reinterpret_cast<BYTE*>(module) + pDos->e_lfanew);
			*nt			= pNT;

			if(pNT->Signature != 'EP') {
				//DBG_MSG("Invalid NT signature %x", pNT->Signature);
				return false;
			}

			return true;
		}
#endif

		__declspec(noinline) HMODULE	get_module(_IN_ const uint32_t hash)
		{
			TEB*				pTeb;
			PEB*				pPeb;
			PEB_LDR_DATA_EX*	pLdr;
			LIST_ENTRY*			pHead;
			LIST_ENTRY*			pCur;

			pTeb	= (TEB*) _get_teb();

			if(pTeb == nullptr){
				return nullptr;
			}

			pPeb	= pTeb->ProcessEnvironmentBlock;

			if(pPeb == nullptr){
				return nullptr;
			}

			pLdr	= reinterpret_cast<PEB_LDR_DATA_EX*>(pPeb->Ldr);

			if(pLdr == nullptr){
				return nullptr;
			}
	
			pHead	= &pLdr->InLoadOrderModuleList;
			pCur	= pHead->Flink;

			for(; pCur != pHead; pCur = pCur->Flink){
				LDR_MODULE*	pModule;

				pModule	= reinterpret_cast<LDR_MODULE*>(pCur);

				if(pModule->BaseDllName.Buffer == nullptr || pModule->BaseDllName.Length == 0)
					continue;

				if(wjoaat(pModule->BaseDllName.Buffer, pModule->BaseDllName.Length >> 1) == hash){
					return (HMODULE)pModule->BaseAddress;
				}
			}

			set_last_error(IMERR_NO_MODULE, hash, 0);
			return nullptr;
		}

		__declspec(noinline) FARPROC	get_export(_IN_ void* module, _IN_ const uint32_t hash)
		{
			IMAGE_DOS_HEADER*		pDos;
#ifdef _M_IX86
			IMAGE_NT_HEADERS32*		pNT;
#else
			IMAGE_NT_HEADERS64*		pNT;
#endif
			uint32_t				rva;
			uint32_t				size;
			IMAGE_EXPORT_DIRECTORY*	exports;
			uint32_t				num_names;
			uint32_t*				names;
			uint16_t*				ordinals;
			uint32_t*				functions;

			if(!check_and_set_headers(module, &pDos, &pNT)){
				return nullptr;
			}

			rva			= pNT->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress;
			size		= pNT->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].Size;

			if(rva == 0 || size == 0){
				return nullptr;
			}

			exports		= reinterpret_cast<IMAGE_EXPORT_DIRECTORY*>(reinterpret_cast<BYTE*>(module) + rva);
			names		= reinterpret_cast<uint32_t*>(reinterpret_cast<BYTE*>(module) + exports->AddressOfNames);
			ordinals	= reinterpret_cast<uint16_t*>(reinterpret_cast<BYTE*>(module) + exports->AddressOfNameOrdinals);
			functions	= reinterpret_cast<uint32_t*>(reinterpret_cast<BYTE*>(module) + exports->AddressOfFunctions);
			num_names	= exports->NumberOfNames;

			for(uint32_t i = 0; i < num_names; ++i){
				const char*	name;
				uint32_t	h;

				name	= reinterpret_cast<const char*>(reinterpret_cast<BYTE*>(module) + names[i]);
				h		= joaat(name);

				if(h == hash){
					uint16_t	ordinal;
				
					ordinal	= ordinals[i];

					if(ordinal > exports->NumberOfFunctions){
						return nullptr;
					}

					rva		= functions[ordinal];

					return reinterpret_cast<FARPROC>(reinterpret_cast<BYTE*>(module) + rva);
				}
			}

			set_last_error(IMERR_NO_EXPORT, 0, hash);
			return nullptr;
		}

		__declspec(noinline) FARPROC	get_export(_IN_ const uint32_t module, _IN_ const uint32_t hash)
		{
			void*	hModule;
			FARPROC	proc;

			hModule		= get_module(module);

			if(hModule == nullptr){
				set_last_error(IMERR_NO_MODULE, module, hash);
				return nullptr;
			}

			proc		= get_export(hModule, hash);

			if(proc == nullptr){
				set_last_error(IMERR_NO_EXPORT, module, hash);
			}

			return proc;
		}

		uint32_t get_last_error(_OUT_ uint32_t* module, _OUT_ uint32_t* function)
		{
			if(m_errNo == IMERR_OK){
				return IMERR_OK;
			}

			if(module)
				*module		= m_errMod;

			if(function)
				*function	= m_errFn;

			return m_errNo;
		}

		void set_last_error(_IN_ const uint32_t err, _IN_ const uint32_t mod, _IN_ const uint32_t fn)
		{
			m_errNo		= err;
			m_errMod	= mod;
			m_errFn		= fn;
		}
	}
}
