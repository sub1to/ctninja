/*
	Copyright 2025-9999 sub1to

	This file is part of CTNinja

	CTNinja is free software; See LICENSE.txt or https://opensource.org/license/mit
*/

#pragma once

#include <vector>

struct _UnitTest;

typedef bool	(*fpUnitTest)(_UnitTest*);

typedef struct _UnitTest
{
	fpUnitTest	test;
	std::string	name;
	std::string	err;
	bool		result;
} UNIT_TEST, *PUNIT_TEST;

typedef std::vector<UNIT_TEST>	vUT;

static vUT			g_tests;

void	REGISTER_TEST(const std::string name, fpUnitTest test)
{
	g_tests.push_back({test, name, "", false});
}

void	RUN_TESTS()
{
	for(auto it = g_tests.begin(); it != g_tests.end(); ++it){
		it->result	= it->test(&*it);

		if(it->result == false){
			// we will show all the errors at the end, because it is easier to read that way..
			continue;
		}

		printf_s("[PASS] %s\n", it->name.c_str());
	}
}

#define BCASS(x) if(!(x)){ test->err = #x; return false; }
