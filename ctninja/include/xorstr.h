/*
	Copyright 2025-9999 sub1to

	This file is part of CTNinja

	CTNinja is free software; See LICENSE.MD or https://opensource.org/license/mit
*/

#ifndef _CTNINJA_XORSTR_H_
#define _CTNINJA_XORSTR_H_

#include <array>

#include "constexpr_rng.h"

namespace ctninja
{
	namespace xorstr
	{
		constexpr auto seed = constexpr_rng::m_seed * 31;

		template<std::size_t N>
		struct XString
		{
			const char m_globalkey;
			std::array<char, N + 1>	m_data;
			std::array<char, N + 1>	m_keys;
    
			template <std::size_t... s>
			constexpr XString(const char (&arr)[N], std::integer_sequence<std::size_t, s...>)
			: m_globalkey(generate_global_key(arr))
			, m_keys{key_char(arr[s], s)...}
			, m_data{enc_char(arr[s], s)...}
			{
				//
			}
 
			constexpr XString(char const(&arr)[N])
			: XString(arr, std::make_integer_sequence<std::size_t, N>())
			{
				//
			}

			template <std::size_t... s>
			constexpr char generate_global_key(const char (&arr)[N])
			{
				// base key
				char r = static_cast<char>(0x7A + (N >> 1) + seed);

				// single byte hash
				for(std::size_t i = 0; i < N; ++i){
					r += arr[i];
					r ^= r >> 3;
					r += r << 4;
					r ^= r >> 2;
				}

				r ^= r >> 4;
				r += r << 5;
				r ^= r >> 7;

				return r;
			}

			constexpr char enc_char(char c, std::size_t s)
			{
				char key = static_cast<char>(((c << 3) | (c >> 5)) + (s + 1) * 31);
				return c ^ key ^ m_globalkey;
			}

			constexpr char key_char(char c, std::size_t s)
			{
				return static_cast<char>(((c << 3) | (c >> 5)) + (s + 1) * 31);
			}

			char dec_char(char c, std::size_t s)
			{
				return c ^ m_keys[s] ^ m_globalkey;
			}

			__forceinline decltype(auto) c_str()
			{
				for(size_t i = 0; i < N; ++i){
					m_data[i] = dec_char(m_data[i], i);
				}

				m_data[N]	= '\0';

				return m_data.data();
			}
		};
	}

	extern "C" {
		int $printf(const char* fmt, ...);
		int $sprintf_s(char* buf, size_t buf_size, const char* fmt, ...);
		int $wprintf_s(const wchar_t* fmt, ...);
		int $swprintf_s(wchar_t* buf, size_t buf_size, const wchar_t* fmt, ...);
	}
}

template<ctninja::xorstr::XString XS>
constexpr auto operator""_X()
{
	return XS;
}




#endif //_CTNINJA_XORSTR_H_
