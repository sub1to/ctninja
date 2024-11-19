/*
	Copyright 2025-9999 sub1to

	This file is part of CTNinja

	CTNinja is free software; See LICENSE.txt or https://opensource.org/license/mit
*/

#ifndef _CTNINJA_SECURE_VALUE_H_
#define _CTNINJA_SECURE_VALUE_H_

#include <random>
#include <intrin.h>

namespace ctninja
{

	/*
		This class obfuscates 32bit values with an xor key and a bit rotate
		The key is rerolled every time you get/set the value
		Most operators are implemented

		Example:
			SecureValue<float> sf = 13.37f;
			sf += 1323.63f;
			float f = sf;

			if(f == 1337.f && f == sf){
				// this will be true
			}

	*/
	template <typename T, typename BaseT>
	class SecureValue
	{
	public:
		SecureValue()
		{
			generate_key();
			set_value(0);
		}

		SecureValue(T val)
		{
			generate_key();
			set_value(val);
		}

		SecureValue(SecureValue<T, BaseT>& rhs)
		{
			generate_key();
			set_value((T) rhs);
		}

		~SecureValue()
		{
			//
		}

#ifdef CTNINJA_SECURE_VALUE_DBG
		// Debugging functions (for tests)

		BaseT	_dbg_get_key()
		{
			return m_key;
		}

		T			_dbg_get_val()
		{
			return m_val;
		}

		BaseT	_dbg_get_val_u32()
		{
			return *reinterpret_cast<BaseT*>(&m_val);
		}

		/*
		template <typename RT>
		RT&				operator[](int idx)
		{
			printf_s("operator[]\n");
			return get_value()[idx];
		}

		template <typename RT>
		RT					operator[](int idx) const
		{
			printf_s("operator[] const\n");
			return get_value()[idx];
		}
		*/
#endif

		/*
			Asignment operators:
				The param is `const T rhs` because SecureValue  will implicitly cast to T, making also explicitly
				delcaring assignment operators with `const SecureValue<T>& rhs` is redundant.

				When calling get_value `this` is cast to const, so it only re-rolls the key on set
		*/

		SecureValue&	operator-=(const T rhs)
		{
			T val = static_cast<const SecureValue*>(this)->get_value();
			val -= rhs;
			set_value(val);
			return *this;
		}

		SecureValue&	operator+=(const T rhs)
		{
			T val = static_cast<const SecureValue*>(this)->get_value();
			val += rhs;
			set_value(val);
			return *this;
		}

		SecureValue&	operator/=(const T rhs)
		{
			T val = static_cast<const SecureValue*>(this)->get_value();
			val /= rhs;
			set_value(val);
			return *this;
		}

		SecureValue&	operator%=(const T rhs)
		{
			T val = static_cast<const SecureValue*>(this)->get_value();
			val %= rhs;
			set_value(val);
			return *this;
		}

		SecureValue&	operator*=(const T rhs)
		{
			T val = static_cast<const SecureValue*>(this)->get_value();
			val *= rhs;
			set_value(val);
			return *this;
		}

		SecureValue&	operator^=(const T rhs)
		{
			T val = static_cast<const SecureValue*>(this)->get_value();
			val ^= rhs;
			set_value(val);
			return *this;
		}

		SecureValue&	operator|=(const T rhs)
		{
			T val = static_cast<const SecureValue*>(this)->get_value();
			val |= rhs;
			set_value(val);
			return *this;
		}

		SecureValue&	operator&=(const T rhs)
		{
			T val = static_cast<const SecureValue*>(this)->get_value();
			val &= rhs;
			set_value(val);
			return *this;
		}

		SecureValue&	operator<<=(const T rhs)
		{
			T val = static_cast<const SecureValue*>(this)->get_value();
			val <<= rhs;
			set_value(val);
			return *this;
		}

		SecureValue&	operator>>=(const T rhs)
		{
			T val = static_cast<const SecureValue*>(this)->get_value();
			val >>= rhs;
			set_value(val);
			return *this;
		}

		/*
			Arithmatic operators:
				The same thing applies as the assignment operators.. because of the implicit casts, the
				compiler should be able to figure out how to make it work, even if we declare it inside
				the class (so lhs is always SecureValue<T>, it cannot be T
		*/


		//  warning C4146: unary minus operator applied to unsigned type, result still unsigned
		#pragma warning( push )
		#pragma warning( disable : 4146)
		T		operator- ()
		{
			T val = get_value();
			return -val;
		}
		#pragma warning( pop ) 

		T		operator- (const T rhs)
		{
			T val = get_value();
			return val - rhs;
		}

		T		operator+ (const T rhs)
		{
			T val = get_value();
			return val + rhs;
		}

		T		operator/ (const T rhs)
		{
			T val = get_value();
			return val / rhs;
		}

		T		operator% (const T rhs)
		{
			T val = get_value();
			return val % rhs;
		}

		T		operator* (const T rhs)
		{
			T val = get_value();
			return val * rhs;
		}

		T		operator^ (const T rhs)
		{
			T val = get_value();
			return val ^ rhs;
		}

		T		operator| (const T rhs)
		{
			T val = get_value();
			return val | rhs;
		}

		T		operator& (const T rhs)
		{
			T val = get_value();
			return val & rhs;
		}

		T		operator<< (const T rhs)
		{
			T val = get_value();
			return val << rhs;
		}

		T		operator>> (const T rhs)
		{
			T val = get_value();
			return val >> rhs;
		}

		/*
			Comparison operators
		*/
		bool	operator==(const T rhs)
		{
			return get_value() == rhs;
		}

		bool	operator!=(const T rhs)
		{
			return get_value() != rhs;
		}

		bool	operator<=(const T rhs)
		{
			return get_value() <= rhs;
		}

		bool	operator>=(const T rhs)
		{
			return get_value() >= rhs;
		}

		bool	operator<(const T rhs)
		{
			return get_value() < rhs;
		}

		bool	operator>(const T rhs)
		{
			return get_value() > rhs;
		}

		/*
			Assignment Operator
		*/
		SecureValue&	operator=(const T rhs)
		{
			set_value(rhs);
			return *this;
		}

		/*
			Cast operators:
				It will implicitly cast to T
		*/
		operator T() const
		{
			return get_value();
		}

		operator T()
		{
			return get_value();
		}

	protected:


#pragma warning( push )
#pragma warning( disable : 4244)	// warning C4244: 'argument': conversion from 'const BaseT' to 'unsigned int', possible loss of data

		void	set_value(const T val)
		{
			generate_key();
#ifdef _M_X64
			BaseT	tmp;
			
			if(sizeof(BaseT) > 4) tmp = (BaseT)_rotl64(*reinterpret_cast<const BaseT*>(&val) ^ m_key, (m_key >> 7) & 0xF);
			else tmp = (BaseT)_rotl(*reinterpret_cast<const BaseT*>(&val) ^ m_key, (m_key >> 7) & 0xF);
#else
			BaseT	tmp = (BaseT) _rotl(*reinterpret_cast<const BaseT*>(&val) ^ m_key, (m_key >> 7) & 0xF);
#endif
			m_val	= *reinterpret_cast<T*>(&tmp);
		}

		T		get_value() const
		{
#ifdef _M_X64
			BaseT	r;
			
			if(sizeof(BaseT) > 4) r = (BaseT) _rotr64(*reinterpret_cast<const BaseT*>(&m_val), (m_key >> 7) & 0xF) ^ m_key;
			else r = (BaseT) _rotr(*reinterpret_cast<const BaseT*>(&m_val), (m_key >> 7) & 0xF) ^ m_key;
#else
			BaseT	r	= (BaseT) _rotr(*reinterpret_cast<const BaseT*>(&m_val), (m_key >> 7) & 0xF) ^ m_key;
#endif
			
			return *reinterpret_cast<T*>(&r);
		}

		T		get_value()
		{
#ifdef _M_X64
			BaseT	tmp;
			
			if(sizeof(BaseT) > 4) tmp = (BaseT) _rotr64(*reinterpret_cast<const BaseT*>(&m_val), (m_key >> 7) & 0xF) ^ m_key;
			else tmp = (BaseT) _rotr(*reinterpret_cast<const BaseT*>(&m_val), (m_key >> 7) & 0xF) ^ m_key;
#else
			BaseT	tmp	= (BaseT) _rotr(*reinterpret_cast<const BaseT*>(&m_val), (m_key >> 7) & 0xF) ^ m_key;
#endif
			T		r	= *reinterpret_cast<T*>(&tmp);
			set_value(r);
			return r;
		}

#pragma warning( pop ) 

		void	generate_key()
		{
			static std::random_device rd;	// Secure random device
			static std::mt19937 gen(rd());	// Seed Mersenne Twister 19937 generator
			std::uniform_int_distribution<> distr(INT_MIN, INT_MAX);
			m_key = distr(gen);
#ifdef _M_X64
			m_key ^= ((BaseT) distr(gen)) << (sizeof(BaseT) << 2);
#endif //_M_X64
		}


		BaseT		m_key;
		T			m_val;
	};

	template <typename T>
	class SecureValue32 : public SecureValue<T, uint32_t>
	{
	public:
		SecureValue32()
		: SecureValue<T, uint32_t>()
		{
			//
		}

		SecureValue32(T val)
		: SecureValue<T, uint32_t>(val)
		{
			//
		}

		SecureValue32(SecureValue32<T>& rhs)
		: SecureValue<T, uint32_t>(rhs)
		{
			//
		}

		~SecureValue32()
		{
			//
		}
	};

#ifdef _M_X64

	template <typename T>
	class SecureValue64 : public SecureValue<T, uint64_t>
	{
	public:
		SecureValue64()
		: SecureValue<T, uint64_t>()
		{
			//
		}

		SecureValue64(T val)
		: SecureValue<T, uint64_t>(val)
		{
			//
		}

		SecureValue64(SecureValue64<T>& rhs)
		: SecureValue<T, uint64_t>(rhs)
		{
			//
		}

		~SecureValue64()
		{
			//
		}
	};

#endif //_M_X64
}

#endif // _CTNINJA_SECURE_VALUE_H_
