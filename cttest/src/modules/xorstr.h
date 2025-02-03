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

		REGISTER_TEST("ctninja::xorstr generate_global_key", [](UNIT_TEST* test)->bool{
			// The key_char generation needs to give a good distribution, even if the input characters are all the same

			auto secstr_A = "AAAAAAAAAAAAAAAAAAAAAAAAAAAAA"_X;
			auto secstr_B = "AAAAAAAAAAAAAABAAAAAAAAAAAAAA"_X;
			auto secstr_C = "AAAAAABAAAAAAABAAAAAAAAAAAAAA"_X;
			auto secstr_D = "AAAAAABAAAAAAABAAAAAAAABAAAAA"_X;
			auto secstr_E = "ABAAAABAAAAAAABAAAAAAAABAAAAA"_X;
			auto secstr_F = "ABAAAABAAAAAAABAAAAABAABAAAAA"_X;
			auto secstr_G = "ABAAAABABAAAAABAAAAAAAABAAAAA"_X;
			auto secstr_H = "ABAAAABABAAAAABAAAABAAABAAAAA"_X;
			auto secstr_I = "ABC"_X;
			auto secstr_J = "ACD"_X;
			auto secstr_K = "ASDF"_X;
			auto secstr_L = "RDCF"_X;
			auto secstr_M = "asdf"_X;
			auto secstr_N = "jgg"_X;
			auto secstr_O = "dfg"_X;
			auto secstr_P = "dfgdfg"_X;
			auto secstr_Q = "aaaa"_X;
			auto secstr_R = "ffdd"_X;
			auto secstr_S = "asdfasdf"_X;
			auto secstr_T = "ghjk"_X;
			auto secstr_U = "fghj"_X;
			auto secstr_V = "vbnm"_X;
			auto secstr_W = "rtyudfghdfgh"_X;
			auto secstr_X = "ghjk"_X;
			auto secstr_Y = "ghdfhdfghdfghdfgh"_X;
			auto secstr_Z = "fhgjsadfas"_X;

			/*
			printf_s("%02x\n", secstr_A.m_globalkey);
			printf_s("%02x\n", secstr_B.m_globalkey);
			printf_s("%02x\n", secstr_C.m_globalkey);
			printf_s("%02x\n", secstr_D.m_globalkey);
			printf_s("%02x\n", secstr_E.m_globalkey);
			printf_s("%02x\n", secstr_F.m_globalkey);
			printf_s("%02x\n", secstr_G.m_globalkey);
			printf_s("%02x\n", secstr_H.m_globalkey);
			printf_s("%02x\n", secstr_I.m_globalkey);
			printf_s("%02x\n", secstr_J.m_globalkey);
			printf_s("%02x\n", secstr_K.m_globalkey);
			printf_s("%02x\n", secstr_L.m_globalkey);
			printf_s("%02x\n", secstr_M.m_globalkey);
			printf_s("%02x\n", secstr_N.m_globalkey);
			printf_s("%02x\n", secstr_O.m_globalkey);
			printf_s("%02x\n", secstr_P.m_globalkey);
			printf_s("%02x\n", secstr_Q.m_globalkey);
			printf_s("%02x\n", secstr_R.m_globalkey);
			printf_s("%02x\n", secstr_S.m_globalkey);
			printf_s("%02x\n", secstr_T.m_globalkey);
			printf_s("%02x\n", secstr_U.m_globalkey);
			printf_s("%02x\n", secstr_V.m_globalkey);
			printf_s("%02x\n", secstr_W.m_globalkey);
			printf_s("%02x\n", secstr_X.m_globalkey);
			printf_s("%02x\n", secstr_Y.m_globalkey);
			printf_s("%02x\n", secstr_Z.m_globalkey);
			//*/

			return true;
		});
	}
}
