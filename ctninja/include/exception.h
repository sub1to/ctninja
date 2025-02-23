/*
	Copyright 2025-9999 sub1to

	This file is part of CTNinja

	CTNinja is free software; See LICENSE.MD or https://opensource.org/license/mit
*/

#ifndef _CTNINJA_EXCEPTION_H
#define _CTNINJA_EXCEPTION_H

#include <exception>
#include <stdarg.h>
#include <stdio.h>

namespace ctninja
{
	class ExceptionBase : public std::exception
	{
	public:
		ExceptionBase(){}
	};

	class FormattedException : public ExceptionBase
	{
	public:
		FormattedException()
		: m_what(nullptr)
		{
	
		}

		~FormattedException()
		{
			if(m_what){
				delete[] m_what;
			}
		}

		FormattedException(const char* const fmt, ...);

		char const*	what() const
		{
			return m_what;
		}

	protected:
		void		init(const char* prefix, const char* const fmt, va_list args);

		const char*		m_what;
	};

	#define FORMATTED_EXCEPTION_CLASS(name)					\
		class name : public FormattedException {			\
		public:												\
			name(const char* const fmt, ...);				\
		}

	FORMATTED_EXCEPTION_CLASS(BadArgument);
	FORMATTED_EXCEPTION_CLASS(IOException);
	FORMATTED_EXCEPTION_CLASS(CallException);
}


#endif //_CTNINJA_EXCEPTION_H
