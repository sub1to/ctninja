/*
	Copyright 2025-9999 sub1to

	This file is part of CTNinja

	CTNinja is free software; See LICENSE.MD or https://opensource.org/license/mit
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

		REGISTER_TEST("ctninja::xorstr key_char", [](UNIT_TEST* test)->bool{
			// The key_char generation needs to give a good distribution, even if the input characters are all the same

			auto secstr = "AAAAAAAAAAAAAAAAAAAAAAAAAAAAA"_X;
			auto str = secstr.c_str();

			BYTE	key_occurance_count[0x100];
			size_t	key_duplicate_count;

			memset(&key_occurance_count, 0, sizeof(key_occurance_count));
			key_duplicate_count	= 0;

			for(size_t i = 0; i < secstr.m_keys.size(); ++i){
				if(str[i] == '\0')
					break;

				if(++key_occurance_count[(uint8_t) secstr.m_keys.data()[i]] > 1){
					key_duplicate_count++;
				}

				/*
				printf_s("%c %02u %02x\n",
					str[i],
					(uint32_t) i,
					(uint8_t) secstr.m_keys.data()[i]
				);
				//*/
			}

			BCASS(key_duplicate_count < 2);
			BCASS(key_duplicate_count < 1);

			return true;
		});
	}
}
