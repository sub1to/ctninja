/*
	Copyright 2025-9999 sub1to

	This file is part of CTNinja

	CTNinja is free software; See LICENSE.MD or https://opensource.org/license/mit
*/

#ifndef _CTNINJA_JOAAT_H_
#define _CTNINJA_JOAAT_H_

namespace ctninja
{
	static constexpr char constexpr_tolower(char c)
	{
		return c + 0x20 * (c >= 'A' && c <= 'Z');
	}

	static constexpr wchar_t constexpr_wtolower(wchar_t c)
	{
		return c + 0x20 * (c >= L'A' && c <= L'Z');
	}

	static inline uint32_t	joaat(const char* key, size_t len)
	{
		uint32_t hash = 0;

		for(size_t i = 0; *key && i < len; ++i){
			hash += constexpr_tolower(*key++);
			hash += hash << 10;
			hash ^= hash >> 6;
		}

		hash += hash << 3;
		hash ^= hash >> 11;
		hash += hash << 15;

		return hash;
	}

	static inline uint32_t	joaat(const char* key)
	{
		uint32_t hash = 0;

		while(*key){
			hash += constexpr_tolower(*key++);
			hash += hash << 10;
			hash ^= hash >> 6;
		}

		hash += hash << 3;
		hash ^= hash >> 11;
		hash += hash << 15;

		return hash;
	}

	static inline uint32_t	wjoaat(const wchar_t* key, size_t len)
	{
		uint32_t hash = 0;

		for(size_t i = 0; *key && i < len; ++i){
			hash += constexpr_wtolower(*key++);
			hash += hash << 10;
			hash ^= hash >> 6;
		}

		hash += hash << 3;
		hash ^= hash >> 11;
		hash += hash << 15;

		return hash;
	}

	static inline uint32_t	wjoaat(const wchar_t* key)
	{
		uint32_t hash = 0;

		for(;*key;){
			hash += constexpr_wtolower(*key++);
			hash += hash << 10;
			hash ^= hash >> 6;
		}

		hash += hash << 3;
		hash ^= hash >> 11;
		hash += hash << 15;

		return hash;
	}

	static inline uint64_t	joaat64(const char* key, size_t len)
	{
		uint64_t hash = 0;

		for(size_t i = 0; *key && i < len; ++i){
			hash += constexpr_tolower(*key++);
			hash += hash << 20;
			hash ^= hash >> 12;
		}

		hash += hash << 6;
		hash ^= hash >> 22;
		hash += hash << 30;

		return hash;
	}

	static inline uint64_t	joaat64(const char* key)
	{
		uint64_t hash = 0;

		while(*key){
			hash += constexpr_tolower(*key++);
			hash += hash << 20;
			hash ^= hash >> 12;
		}

		hash += hash << 6;
		hash ^= hash >> 22;
		hash += hash << 30;

		return hash;
	}

	static inline uint64_t	wjoaat64(const wchar_t* key, size_t len)
	{
		uint64_t hash = 0;

		for(size_t i = 0; *key && i < len; ++i){
			hash += constexpr_wtolower(*key++);
			hash += hash << 20;
			hash ^= hash >> 12;
		}

		hash += hash << 6;
		hash ^= hash >> 22;
		hash += hash << 30;

		return hash;
	}

	static inline uint64_t	wjoaat64(const wchar_t* key)
	{
		uint64_t hash = 0;

		for(;*key;){
			hash += constexpr_wtolower(*key++);
			hash += hash << 20;
			hash ^= hash >> 12;
		}

		hash += hash << 6;
		hash ^= hash >> 22;
		hash += hash << 30;

		return hash;
	}
}


consteval uint32_t operator""_JOAAT(const char* str, size_t len)
{
    uint32_t hash = 0;

	for(std::size_t i = 0; i < len; ++i){
		hash += ctninja::constexpr_tolower(*str++);
		hash += hash << 10;
		hash ^= hash >> 6;
	}

	hash += hash << 3;
	hash ^= hash >> 11;
	hash += hash << 15;

	return static_cast<uint32_t>(hash);
}

consteval uint64_t operator""_JOAAT64(const char* str, size_t len)
{
    uint64_t hash = 0;

	for(std::size_t i = 0; i < len; ++i){
		hash += ctninja::constexpr_tolower(*str++);
		hash += hash << 20;
		hash ^= hash >> 12;
	}

	hash += hash << 6;
	hash ^= hash >> 22;
	hash += hash << 30;

	return static_cast<uint64_t>(hash);
}

#endif
