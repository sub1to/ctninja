/*
	Copyright 2025-9999 sub1to

	This file is part of CTNinja

	CTNinja is free software; See LICENSE.txt or https://opensource.org/license/mit
*/

#pragma once

namespace xorstr
{
	void	reg()
	{
		REGISTER_TEST("ctninja::xorstr", [](UNIT_TEST* test)->bool{
			BCASS(strcmp("abcd", "abcd"_X.c_str()) == 0);
			return true;
		});
	}
}
