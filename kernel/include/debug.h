// debug.h
// Copyright (c) 2020, zhiayang
// Licensed under the Apache License Version 2.0.

#include <stddef.h>
#include <stdint.h>

#define ZPR_USE_STD                     0
#define ZPR_FREESTANDING                1
#define ZPR_DECIMAL_LOOKUP_TABLE        0
#define ZPR_HEXADECIMAL_LOOKUP_TABLE    0

#include "zpr.h"

#include "hal.h"

namespace zkb::debug
{
	void debug_write_buffered(const char* buf, size_t size);
	void debug_write_flush_line();
	void debug_write_flush();

	template <typename... Args>
	void log(const char* fmt, Args&&... args)
	{
		zpr::cprint(&debug_write_buffered, fmt, static_cast<Args&&>(args)...);
		debug_write_flush_line();
	}
}
