/*
	Copyright 2025-9999 sub1to

	This file is part of CTNinja

	CTNinja is free software; See LICENSE.MD or https://opensource.org/license/mit
*/

#include "pch.h"
#include "exception.h"

#include "import.h"
#include "xorstr.h"


#define FORMATTED_EXCEPTION_CONSTRUCTOR(c, prefix)	\
	c##::##c(const char* const fmt, ...)			\
	{												\
		va_list		args;							\
		va_start(args, fmt);						\
		init(#prefix##_X.c_str(), fmt, args);		\
		va_end(args);								\
	}

namespace ctninja
{
	void FormattedException::init(const char* prefix, const char* const fmt, va_list args)
	{
		char*			pBuffer;
		size_t			size;
		size_t			prefix_len;

		prefix_len	= $strlen(prefix);
		size		= (size_t) $vsprintf(nullptr, 0, fmt, args) + prefix_len + 3;
		pBuffer		= new char[size];
		m_what		= pBuffer;

		memcpy_s(pBuffer, size, prefix, prefix_len);
		pBuffer	+= prefix_len;
		*pBuffer++	= ':';
		*pBuffer++	= ' ';
		$vsprintf(pBuffer, size - (prefix_len + 2), fmt, args);
	}

	FORMATTED_EXCEPTION_CONSTRUCTOR(FormattedException, Exception)
	FORMATTED_EXCEPTION_CONSTRUCTOR(BadArgument, Bad Argument)
	FORMATTED_EXCEPTION_CONSTRUCTOR(IOException, IO Exception)
	FORMATTED_EXCEPTION_CONSTRUCTOR(CallException, Call Exception)
}
