/*
	Copyright 2025-9999 sub1to

	This file is part of CTNinja

	CTNinja is free software; See LICENSE.MD or https://opensource.org/license/mit
*/

#include <iostream>
#include <Windows.h>
#include <conio.h>

// required for the tests in DllMain
#define CTNINJA_SECURE_VALUE_DBG

// Add the $ and $$ macros
#define CTNINJA_MAGIC_IMPORT
#include "ctninja.h"

// Include test framework
#include "exception.h"
#include "bctest.h"

// Include test modules
#include "modules/import.h"
#include "modules/joaat.h"
#include "modules/xorstr.h"
#include "modules/secval.h"

int main(const char* argv[], int argc)
{
	HWND	hWnd	= GetConsoleWindow();

	MoveWindow(hWnd, 100, 100, 1280, 720, true);
	SetWindowTextA(hWnd, "CTNinja Tests");

	try{
		// register modules
		joaat::reg();
		xport::reg();
		xorstr::reg();
		secval::reg();
		
		// run tests
		RUN_TESTS();

		// Tests ended, count passed
		size_t numPassed = 0;
		for(auto it = g_tests.cbegin(); it != g_tests.cend(); ++it){
			if(it->result == false){
				continue;
			}
			++numPassed;
		}

#ifdef _M_IX86
		printf_s("\n%03d / %03d passed\n", numPassed, g_tests.size());
#else // _M_X64
		printf_s("\n%03lld / %03lld passed\n", numPassed, g_tests.size());
#endif

		// Print errors at the end for easier read
		if(numPassed != g_tests.size()){
			printf_s("\n");
			for(auto it = g_tests.cbegin(); it != g_tests.cend(); ++it){
				if(it->result != false){
					continue;
				}

				printf_s("[FAIL] [%s] --> %s\n", it->name.c_str(), it->err.c_str());
			}
		}
	}
	catch(AssertException& e){
		printf_s("\n[ERROR] %s\n", e.what());
	}
	catch(std::logic_error const& e)
	{
		printf_s("\n[ERROR] Logic Error: %s\n", e.what());
	}
	catch(std::exception const& e){
		printf_s("\n[ERROR] Exception: %s\n", e.what());
	}
	catch(...)
	{
		printf_s("\n[ERROR] Unknown exception\n");
	}

	printf_s("\nPress any key to exit...\n");
	fflush(stdout);
	return _getch();
}
