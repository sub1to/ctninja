/*
	Copyright 2025-9999 sub1to

	This file is part of CTNinja

	CTNinja is free software; See LICENSE.MD or https://opensource.org/license/mit
*/

#ifndef _CTNINJA_CONSTEXPR_RNG_H_
#define _CTNINJA_CONSTEXPR_RNG_H_

namespace ctninja
{
	namespace constexpr_rng
	{
		constexpr unsigned char char_to_digit(char c) {
			return c - '0';
		}

		constexpr int create_seed_from_time(const char* time) {
			// time format is "HH:MM:SS"
			return char_to_digit(time[0]) * 10 + char_to_digit(time[1]) * 3600 + // Hours
				   char_to_digit(time[3]) * 10 + char_to_digit(time[4]) * 36000 + // Minutes
				   char_to_digit(time[6]) * 10 + char_to_digit(time[7]) * 360000;  // Seconds
		}

		constexpr auto m_time = __TIME__;
		constexpr auto m_seed = create_seed_from_time(m_time);
	}
}

#endif //_CTNINJA_CONSTEXPR_RNG_H_
