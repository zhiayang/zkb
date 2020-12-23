// hal.h
// Copyright (c) 2020, zhiayang
// Licensed under the Apache License Version 2.0.

#pragma once

#include <stddef.h>
#include <stdint.h>

#include "hal/usb.h"
#include "hal/gpio.h"

namespace zkb::hal
{
	void init();
	void delayMs(uint32_t ms);
	void delayUs(uint32_t us);

	namespace debug
	{
		void write(const char* buf, size_t size);
	}
}
