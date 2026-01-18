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
			std::array<char, N>	m_data;
			std::array<char, N>	m_keys;
    
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

		template<std::size_t N>
		struct WXString
		{
			const wchar_t m_globalkey;
			std::array<wchar_t, N>	m_data;
			std::array<wchar_t, N>	m_keys;
    
			template <std::size_t... s>
			constexpr WXString(const wchar_t (&arr)[N], std::integer_sequence<std::size_t, s...>)
			: m_globalkey(generate_global_key(arr))
			, m_keys{key_char(arr[s], s)...}
			, m_data{enc_char(arr[s], s)...}
			{
				//
			}
 
			constexpr WXString(wchar_t const(&arr)[N])
			: WXString(arr, std::make_integer_sequence<std::size_t, N>())
			{
				//
			}

			template <std::size_t... s>
			constexpr wchar_t generate_global_key(const wchar_t (&arr)[N])
			{
				// base key
				wchar_t r = static_cast<wchar_t>(0x7A + (N >> 1) + seed);

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

			constexpr wchar_t enc_char(wchar_t c, std::size_t s)
			{
				wchar_t key = static_cast<wchar_t>(((c << 3) | (c >> 5)) + (s + 1) * 31);
				return c ^ key ^ m_globalkey;
			}

			constexpr wchar_t key_char(wchar_t c, std::size_t s)
			{
				return static_cast<wchar_t>(((c << 3) | (c >> 5)) + (s + 1) * 31);
			}

			wchar_t dec_char(wchar_t c, std::size_t s)
			{
				return c ^ m_keys[s] ^ m_globalkey;
			}

			__forceinline decltype(auto) c_str()
			{
				for(size_t i = 0; i < N; ++i){
					m_data[i] = dec_char(m_data[i], i);
				}

				m_data[N]	= L'\0';

				return m_data.data();
			}
		};
	}

	extern "C" {
		size_t	$strlen(const char* str);
		int		$printf(const char* fmt, ...);
		int		$sprintf(char* buf, size_t buf_size, const char* fmt, ...);
		int		$vsprintf(char* buf, size_t buf_size, const char* fmt, va_list args);
		int		$wprintf(const wchar_t* fmt, ...);
		int		$swprintf(wchar_t* buf, size_t buf_size, const wchar_t* fmt, ...);
		int		$vswprintf(wchar_t* buf, size_t buf_size, const wchar_t* fmt, va_list args);
	}
}

template<ctninja::xorstr::XString XS>
constexpr auto operator""_X()
{
	return XS;
}

template<ctninja::xorstr::WXString WXS>
constexpr auto operator""_Xw()
{
	return WXS;
}



// for legacy compat
#ifdef CTNINJA_LEGACY_PRINTF
#define $sprintf_s $sprintf
#define $wprintf_s $wprintf
#define $swprintf_s $swprintf
#endif


#endif //_CTNINJA_XORSTR_H_
