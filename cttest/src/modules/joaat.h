/*
	Copyright 2025-9999 sub1to

	This file is part of CTNinja

	CTNinja is free software; See LICENSE.txt or https://opensource.org/license/mit
*/

#pragma once

namespace joaat
{
	void	reg()
	{
		REGISTER_TEST("ctninja::constexpr_tolower", [](UNIT_TEST* test)->bool{
			BCASS(ctninja::constexpr_tolower('X') == 'x');
			return true;
		});

		REGISTER_TEST("ctninja::constexpr_wtolower", [](UNIT_TEST* test)->bool{
			BCASS(ctninja::constexpr_wtolower(L'X') == L'x');
			return true;
		});

		REGISTER_TEST("ctninja::\"\"_JOAAT", [](UNIT_TEST* test)->bool{
			BCASS("abcd"_JOAAT == 0xcd8b6206);
			BCASS("aBCd"_JOAAT == 0xcd8b6206);
			BCASS("abcd"_JOAAT == ctninja::joaat("abcd"));
			BCASS("abcd"_JOAAT == ctninja::joaat("aBCd"));
			BCASS("abcd"_JOAAT == ctninja::wjoaat(L"abcd"));
			BCASS("abcd"_JOAAT == ctninja::wjoaat(L"aBCd"));
			BCASS("abcd"_JOAAT == ctninja::wjoaat(L"abcd", 4));
			BCASS("abcd"_JOAAT == ctninja::wjoaat(L"aBCd", 4));
			return true;
		});

		REGISTER_TEST("ctninja::\"\"_JOAAT64", [](UNIT_TEST* test)->bool{
			BCASS("abcd"_JOAAT64 == 0x68056dbf5004f9c2);
			BCASS("aBCd"_JOAAT64 == 0x68056dbf5004f9c2);
			BCASS("abcd"_JOAAT64 == ctninja::joaat64("abcd"));
			BCASS("abcd"_JOAAT64 == ctninja::joaat64("aBCd"));
			BCASS("abcd"_JOAAT64 == ctninja::wjoaat64(L"abcd"));
			BCASS("abcd"_JOAAT64 == ctninja::wjoaat64(L"aBCd"));
			BCASS("abcd"_JOAAT64 == ctninja::wjoaat64(L"abcd", 4));
			BCASS("abcd"_JOAAT64 == ctninja::wjoaat64(L"aBCd", 4));
			return true;
		});
	}
}