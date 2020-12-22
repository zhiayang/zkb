// gpio.cpp
// Copyright (c) 2020, zhiayang
// Licensed under the Apache License Version 2.0.

#define ZKB_HAL_IMPL 1

#include "hal/gpio.h"
#include "hal/impl_common.h"

namespace zkb::hal::gpio
{
	void write(uint32_t pin, bool value)
	{
		hal_pin_write(pin, value);
	}

	void toggle(uint32_t pin)
	{
		hal_pin_toggle(pin);
	}
}
