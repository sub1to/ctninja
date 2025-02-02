/*
	Copyright 2025-9999 sub1to

	This file is part of CTNinja

	CTNinja is free software; See LICENSE.MD or https://opensource.org/license/mit
*/

#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <exception>
#include <stdarg.h>
#include <stdio.h>

class ExceptionBase : public std::exception
{
public:
	ExceptionBase(){}
};

class HelpException : ExceptionBase
{
	
};

#define FORMATTED_EXCEPTION_CONSTRUCTOR(c, prefix) \
	c(const char* const fmt, ...)\
	{\
		va_list		args;\
		va_start(args, fmt);\
		init(prefix, fmt, args);\
		va_end(args);\
	}


class FormattedException : public ExceptionBase
{
public:
	FormattedException()
	: m_what(nullptr)
	{
	
	}

	FORMATTED_EXCEPTION_CONSTRUCTOR(FormattedException, "Exception")

	void init(const char* prefix, const char* const fmt, va_list args)
	{
		char*		pBuffer;
		size_t		size;
		size_t		prefix_len;

		prefix_len	= strlen(prefix);
		size		= (size_t) vsnprintf(nullptr, 0, fmt, args) + prefix_len + 3;
		pBuffer		= new char[size];
		m_what		= pBuffer;

		memcpy_s(pBuffer, size, prefix, prefix_len);
		pBuffer	+= prefix_len;
		*pBuffer++	= ':';
		*pBuffer++	= ' ';
		vsprintf_s(pBuffer, size - (prefix_len + 2), fmt, args);
	}

	~FormattedException()
	{
		if(m_what){
			delete[] m_what;
		}
	}

	char const* what() const
	{
		return m_what;
	}

	const char*		m_what;
};

class AssertException : public FormattedException
{
public:
	FORMATTED_EXCEPTION_CONSTRUCTOR(AssertException, "Assert Failed")
};


#endif //EXCEPTION_H
