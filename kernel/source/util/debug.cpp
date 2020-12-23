// debug.cpp
// Copyright (c) 2020, zhiayang
// Licensed under the Apache License Version 2.0.

#include <string.h>

#include "hal.h"
#include "kernel.h"

namespace zkb::debug
{
	static constexpr size_t BUFFER_SIZE = 512;

	// imagine being thread-safe in 2020
	static size_t idx = 0;
	static char global_buffer[BUFFER_SIZE + 1] = { };

	void debug_write_buffered(const char* buf, size_t size)
	{
		auto num = (BUFFER_SIZE - idx > size ? size : BUFFER_SIZE - idx - 1);
		memcpy(global_buffer + idx, buf, num);
		idx += num;
	}

	void debug_write_flush()
	{
		hal::debug::write(global_buffer, idx);
		idx = 0;
	}

	void debug_write_flush_line()
	{
		global_buffer[idx] = '\n';
		hal::debug::write(global_buffer, idx + 1);
		idx = 0;
	}
}
