// gpio.h
// Copyright (c) 2020, zhiayang
// Licensed under the Apache License Version 2.0.

#pragma once

#include <stdint.h>

namespace zkb::hal::gpio
{
	// reference: sdk/overrides/board_nice_nano.h
	#if defined(BOARD_NICE_NANO_NRF52840)
		static constexpr uint32_t LED_1     = 15;
	#endif


	void write(uint32_t pin, bool value);
	void toggle(uint32_t pin);
}
