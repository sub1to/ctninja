/*
	Copyright 2025-9999 sub1to

	This file is part of CTNinja

	CTNinja is free software; See LICENSE.MD or https://opensource.org/license/mit
*/

#pragma once

namespace xorstr
{
	// function to test $vsprintf
	int _test_sprintf(char* buf, size_t size, const char* fmt, ...)
	{
		int		ret;
		va_list	args;

		va_start(args, fmt);
		ret	= ctninja::$vsprintf(buf, size, fmt, args);
		va_end(args);

		return ret;
	}

	// function to test $vswprintf
	int _test_wsprintf(wchar_t* buf, size_t size, const wchar_t* fmt, ...)
	{
		int		ret;
		va_list	args;

		va_start(args, fmt);
		ret	= ctninja::$vswprintf(buf, size, fmt, args);
		va_end(args);

		return ret;
	}

	void	reg()
	{
		REGISTER_TEST("ctninja::$strlen", [](UNIT_TEST* test)->bool{
			BCASS(ctninja::$strlen("abcd") == 4);
			BCASS(ctninja::$strlen("abcdffff") == 8);
			BCASS(ctninja::$strlen("abcd"_X.c_str()) == 4);
			return true;
		});

		REGISTER_TEST("ctninja::xorstr", [](UNIT_TEST* test)->bool{
			BCASS(strcmp("abcd", "abcd"_X.c_str()) == 0);
			BCASS(strcmp("abcd", "ab" "cd"_X.c_str()) == 0);
			BCASS(strcmp("abcd", "CHECK_FOR_THIS_STRING_THE_IN_BINARY"_X.c_str()) != 0);

			BCASS(wcscmp(L"abcd", L"abcd"_Xw.c_str()) == 0);
			BCASS(wcscmp(L"abcd", L"ab" L"cd"_Xw.c_str()) == 0);
			BCASS(wcscmp(L"abcd", L"CHECK_FOR_THIS_STRING_THE_IN_BINARY"_Xw.c_str()) != 0);
			return true;
		});

		REGISTER_TEST("ctninja::$printf", [](UNIT_TEST* test)->bool{
			BCASS(ctninja::$printf("%.2f\n", 1.23456f) == 5);
			BCASS(ctninja::$printf("%d\n", -123456) == 8);
			BCASS(ctninja::$printf("%u\n", 123456) ==  7);
			BCASS(ctninja::$printf("%x\n", 0xabc456) == 7);
			BCASS(ctninja::$printf("%s\n", "test") == 5);
			return true;
		});

		REGISTER_TEST("ctninja::$wprintf", [](UNIT_TEST* test)->bool{
			BCASS(ctninja::$wprintf(L"%.2f\n", 1.23456f) == 5);
			BCASS(ctninja::$wprintf(L"%d\n", -123456) == 8);
			BCASS(ctninja::$wprintf(L"%u\n", 123456) ==  7);
			BCASS(ctninja::$wprintf(L"%x\n", 0xabc456) == 7);
			BCASS(ctninja::$wprintf(L"%s\n", L"test") == 5);
			return true;
		});

		REGISTER_TEST("ctninja::$sprintf float", [](UNIT_TEST* test)->bool{
			char	buf1[0x100];
			char	buf2[0x100];
			
			BCASS(ctninja::$sprintf(nullptr, 0, "%.2f", 1.23456f) == 4);
			BCASS(ctninja::$sprintf(buf1, sizeof(buf1), "%.2f", 1.23456f) == 4);
			sprintf_s(buf2, sizeof(buf2), "%.2f", 1.23456f);
			BCASS(strcmp(buf1, buf2) == 0);
			return true;
		});

		REGISTER_TEST("ctninja::$sprintf hex", [](UNIT_TEST* test)->bool{
			char	buf1[0x100];
			char	buf2[0x100];
			
			BCASS(ctninja::$sprintf(nullptr, 0, "%x", 0x123abc) == 6);
			BCASS(ctninja::$sprintf(buf1, sizeof(buf1), "%x", 0x123abc) == 6);
			sprintf_s(buf2, sizeof(buf2), "%x", 0x123abc);
			BCASS(strcmp(buf1, buf2) == 0);
			return true;
		});

		REGISTER_TEST("ctninja::$sprintf unsigned int", [](UNIT_TEST* test)->bool{
			char	buf1[0x100];
			char	buf2[0x100];
			
			BCASS(ctninja::$sprintf(nullptr, 0, "%u", 123456) == 6);
			BCASS(ctninja::$sprintf(buf1, sizeof(buf1), "%u", 123456) == 6);
			sprintf_s(buf2, sizeof(buf2), "%u", 123456);
			BCASS(strcmp(buf1, buf2) == 0);
			return true;
		});

		REGISTER_TEST("ctninja::$sprintf signed int", [](UNIT_TEST* test)->bool{
			char	buf1[0x100];
			char	buf2[0x100];
			
			BCASS(ctninja::$sprintf(nullptr, 0, "%d", -123456) == 7);
			BCASS(ctninja::$sprintf(buf1, sizeof(buf1), "%d", -123456) == 7);
			sprintf_s(buf2, sizeof(buf2), "%d", -123456);
			BCASS(strcmp(buf1, buf2) == 0);
			return true;
		});

		REGISTER_TEST("ctninja::$sprintf string", [](UNIT_TEST* test)->bool{
			char	buf1[0x100];
			char	buf2[0x100];
			
			BCASS(ctninja::$sprintf(nullptr, 0, "%s", "test") == 4);
			BCASS(ctninja::$sprintf(buf1, sizeof(buf1), "%s", "test") == 4);
			sprintf_s(buf2, sizeof(buf2), "%s", "test");
			BCASS(strcmp(buf1, buf2) == 0);
			return true;
		});

		REGISTER_TEST("ctninja::$swprintf float", [](UNIT_TEST* test)->bool{
			wchar_t	buf1[0x100];
			wchar_t	buf2[0x100];
			
			BCASS(ctninja::$swprintf(nullptr, 0, L"%.2f", 1.23456f) == 4);
			BCASS(ctninja::$swprintf(buf1, sizeof(buf1) / sizeof(*buf1), L"%.2f", 1.23456f) == 4);
			swprintf_s(buf2, sizeof(buf2) / sizeof(*buf2), L"%.2f", 1.23456f);
			BCASS(wcscmp(buf1, buf2) == 0);
			return true;
		});

		REGISTER_TEST("ctninja::$swprintf hex", [](UNIT_TEST* test)->bool{
			wchar_t	buf1[0x100];
			wchar_t	buf2[0x100];
			
			BCASS(ctninja::$swprintf(nullptr, 0, L"%x", 0x123abc) == 6);
			BCASS(ctninja::$swprintf(buf1, sizeof(buf1) / sizeof(*buf1), L"%x", 0x123abc) == 6);
			swprintf_s(buf2, sizeof(buf2) / sizeof(*buf2), L"%x", 0x123abc);
			BCASS(wcscmp(buf1, buf2) == 0);
			return true;
		});

		REGISTER_TEST("ctninja::$swprintf unsigned int", [](UNIT_TEST* test)->bool{
			wchar_t	buf1[0x100];
			wchar_t	buf2[0x100];
			
			BCASS(ctninja::$swprintf(nullptr, 0, L"%u", 123456) == 6);
			BCASS(ctninja::$swprintf(buf1, sizeof(buf1) / sizeof(*buf1), L"%u", 123456) == 6);
			swprintf_s(buf2, sizeof(buf2) / sizeof(*buf2), L"%u", 123456);
			BCASS(wcscmp(buf1, buf2) == 0);
			return true;
		});

		REGISTER_TEST("ctninja::$swprintf signed int", [](UNIT_TEST* test)->bool{
			wchar_t	buf1[0x100];
			wchar_t	buf2[0x100];
			
			BCASS(ctninja::$swprintf(nullptr, 0, L"%d", -123456) == 7);
			BCASS(ctninja::$swprintf(buf1, sizeof(buf1) / sizeof(*buf1), L"%d", -123456) == 7);
			swprintf_s(buf2, sizeof(buf2) / sizeof(*buf2), L"%d", -123456);
			BCASS(wcscmp(buf1, buf2) == 0);
			return true;
		});

		REGISTER_TEST("ctninja::$swprintf string", [](UNIT_TEST* test)->bool{
			wchar_t	buf1[0x100];
			wchar_t	buf2[0x100];
			
			BCASS(ctninja::$swprintf(nullptr, 0, L"%s", L"test") == 4);
			BCASS(ctninja::$swprintf(buf1, sizeof(buf1) / sizeof(*buf1), L"%s", L"test") == 4);
			swprintf_s(buf2, sizeof(buf2) / sizeof(*buf2), L"%s", L"test");
			BCASS(wcscmp(buf1, buf2) == 0);
			return true;
		});

		//
		// $vsprintf
		//
		REGISTER_TEST("ctninja::$vsprintf float", [](UNIT_TEST* test)->bool{
			char	buf1[0x100];
			char	buf2[0x100];
			
			BCASS(_test_sprintf(nullptr, 0, "%.2f", 1.23456f) == 4);
			BCASS(_test_sprintf(buf1, sizeof(buf1), "%.2f", 1.23456f) == 4);
			sprintf_s(buf2, sizeof(buf2), "%.2f", 1.23456f);
			//printf("buf1: %s\n", buf1);
			//printf("buf2: %s\n", buf2);
			BCASS(strcmp(buf1, buf2) == 0);
			return true;
		});

		REGISTER_TEST("ctninja::$vswprintf float", [](UNIT_TEST* test)->bool{
			wchar_t	buf1[0x100];
			wchar_t	buf2[0x100];
			
			BCASS(_test_wsprintf(nullptr, 0, L"%.2f", 1.23456f) == 4);
			BCASS(_test_wsprintf(buf1, sizeof(buf1) / sizeof(*buf1), L"%.2f", 1.23456f) == 4);
			swprintf_s(buf2, sizeof(buf2) / sizeof(*buf2), L"%.2f", 1.23456f);
			//printf("buf1: %s\n", buf1);
			//printf("buf2: %s\n", buf2);
			BCASS(wcscmp(buf1, buf2) == 0);
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

		REGISTER_TEST("ctninja::xorstr key_char wide", [](UNIT_TEST* test)->bool{
			// The key_char generation needs to give a good distribution, even if the input characters are all the same

			auto secstr = L"AAAAAAAAAAAAAAAAAAAAAAAAAAAAA"_Xw;
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

		REGISTER_TEST("ctninja::xorstr generate_global_key wide", [](UNIT_TEST* test)->bool{
			// The key_char generation needs to give a good distribution, even if the input characters are all the same

			auto secstr_A = L"AAAAAAAAAAAAAAAAAAAAAAAAAAAAA"_Xw;
			auto secstr_B = L"AAAAAAAAAAAAAABAAAAAAAAAAAAAA"_Xw;
			auto secstr_C = L"AAAAAABAAAAAAABAAAAAAAAAAAAAA"_Xw;
			auto secstr_D = L"AAAAAABAAAAAAABAAAAAAAABAAAAA"_Xw;
			auto secstr_E = L"ABAAAABAAAAAAABAAAAAAAABAAAAA"_Xw;
			auto secstr_F = L"ABAAAABAAAAAAABAAAAABAABAAAAA"_Xw;
			auto secstr_G = L"ABAAAABABAAAAABAAAAAAAABAAAAA"_Xw;
			auto secstr_H = L"ABAAAABABAAAAABAAAABAAABAAAAA"_Xw;
			auto secstr_I = L"ABC"_Xw;
			auto secstr_J = L"ACD"_Xw;
			auto secstr_K = L"ASDF"_Xw;
			auto secstr_L = L"RDCF"_Xw;
			auto secstr_M = L"asdf"_Xw;
			auto secstr_N = L"jgg"_Xw;
			auto secstr_O = L"dfg"_Xw;
			auto secstr_P = L"dfgdfg"_Xw;
			auto secstr_Q = L"aaaa"_Xw;
			auto secstr_R = L"ffdd"_Xw;
			auto secstr_S = L"asdfasdf"_Xw;
			auto secstr_T = L"ghjk"_Xw;
			auto secstr_U = L"fghj"_Xw;
			auto secstr_V = L"vbnm"_Xw;
			auto secstr_W = L"rtyudfghdfgh"_Xw;
			auto secstr_X = L"ghjk"_Xw;
			auto secstr_Y = L"ghdfhdfghdfghdfgh"_Xw;
			auto secstr_Z = L"fhgjsadfas"_Xw;

			//*
			printf_s("%04x\n", secstr_A.m_globalkey);
			printf_s("%04x\n", secstr_B.m_globalkey);
			printf_s("%04x\n", secstr_C.m_globalkey);
			printf_s("%04x\n", secstr_D.m_globalkey);
			printf_s("%04x\n", secstr_E.m_globalkey);
			printf_s("%04x\n", secstr_F.m_globalkey);
			printf_s("%04x\n", secstr_G.m_globalkey);
			printf_s("%04x\n", secstr_H.m_globalkey);
			printf_s("%04x\n", secstr_I.m_globalkey);
			printf_s("%04x\n", secstr_J.m_globalkey);
			printf_s("%04x\n", secstr_K.m_globalkey);
			printf_s("%04x\n", secstr_L.m_globalkey);
			printf_s("%04x\n", secstr_M.m_globalkey);
			printf_s("%04x\n", secstr_N.m_globalkey);
			printf_s("%04x\n", secstr_O.m_globalkey);
			printf_s("%04x\n", secstr_P.m_globalkey);
			printf_s("%04x\n", secstr_Q.m_globalkey);
			printf_s("%04x\n", secstr_R.m_globalkey);
			printf_s("%04x\n", secstr_S.m_globalkey);
			printf_s("%04x\n", secstr_T.m_globalkey);
			printf_s("%04x\n", secstr_U.m_globalkey);
			printf_s("%04x\n", secstr_V.m_globalkey);
			printf_s("%04x\n", secstr_W.m_globalkey);
			printf_s("%04x\n", secstr_X.m_globalkey);
			printf_s("%04x\n", secstr_Y.m_globalkey);
			printf_s("%04x\n", secstr_Z.m_globalkey);
			//*/

			return true;
		});
	}
}
