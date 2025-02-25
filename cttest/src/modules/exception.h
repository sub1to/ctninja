/*
	Copyright 2025-9999 sub1to

	This file is part of CTNinja

	CTNinja is free software; See LICENSE.MD or https://opensource.org/license/mit
*/

#pragma once

namespace exception
{
	void	reg()
	{
		REGISTER_TEST("ctninja::FormattedException base", [](UNIT_TEST* test)->bool{
			try{
				throw ctninja::FormattedException("Test Exception");
			}
			catch(const ctninja::FormattedException& e){
				BCASS(strcmp(e.what(), "Exception: Test Exception") == 0)
				return true;
			}
			BCASS(false && "FormattedException did not get thrown");
			return true;
		});

		REGISTER_TEST("ctninja::FormattedException float", [](UNIT_TEST* test)->bool{
			try{
				throw ctninja::FormattedException("%.2f", 1.234f);
			}
			catch(const ctninja::FormattedException& e){
				BCASS(strcmp(e.what(), "Exception: 1.23") == 0)
				return true;
			}
			BCASS(false && "FormattedException did not get thrown");
			return true;
		});

		REGISTER_TEST("ctninja::FormattedException int", [](UNIT_TEST* test)->bool{
			try{
				throw ctninja::FormattedException("%d", 123456);
			}
			catch(const ctninja::FormattedException& e){
				BCASS(strcmp(e.what(), "Exception: 123456") == 0)
				return true;
			}
			BCASS(false && "FormattedException did not get thrown");
			return true;
		});

		REGISTER_TEST("ctninja::FormattedException mixed", [](UNIT_TEST* test)->bool{
			try{
#ifdef _M_IX86
				throw ctninja::FormattedException("%s %d %x %.5f %p", "lorem ipsum", 123456, 0xdeadbeef, 3.14159265359f, (void*) 0x7FFF);
#else
				throw ctninja::FormattedException("%s %d %x %.5f %p", "lorem ipsum", 123456, 0xdeadbeef, 3.14159265359f, (void*) 0x7FFF'FFFF'FFFF);
#endif
			}
			catch(const ctninja::FormattedException& e){
#ifdef _M_IX86
				BCASS(strcmp(e.what(), "Exception: lorem ipsum 123456 deadbeef 3.14159 00007FFF") == 0)
#else
				BCASS(strcmp(e.what(), "Exception: lorem ipsum 123456 deadbeef 3.14159 00007FFFFFFFFFFF") == 0)
#endif
				return true;
			}
			BCASS(false && "FormattedException did not get thrown");
			return true;
		});

		REGISTER_TEST("ctninja::CallException ($$)", [](UNIT_TEST* test)->bool{
			try{
				$$(Kernel32.dll, GetLastError);
				$$(spel64.dll, LoadLibraryA, "cheats.dll");
			}
			catch(const ctninja::CallException& e){
				BCASS(strcmp(e.what(), "Call Exception: spel64.dll::LoadLibraryA(\"cheats.dll\")") == 0)
				return true;
			}
			BCASS(false && "CallException did not get thrown");
			return true;
		});
	}
}