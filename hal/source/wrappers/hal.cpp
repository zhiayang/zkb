// hal.cpp
// Copyright (c) 2020, zhiayang
// Licensed under the Apache License Version 2.0.

#define ZKB_HAL_IMPL 1

#include "hal.h"
#include "hal/impl_common.h"

namespace zkb::hal
{
	void init()
	{
		hal_board_init();
		usb::init();
	}

	void delayMs(uint32_t ms)
	{
		hal_delay_ms(ms);
	}

	namespace debug
	{
		void write(const char* buf, size_t size)
		{
			hal_debug_write(buf, size);
		}
	}
}
