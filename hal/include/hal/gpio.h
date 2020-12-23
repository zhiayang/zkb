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

	enum class PullMode { None = 0, Down = 1, Up = 2 };

	void modeOutput(uint32_t pin);
	void modeInput(uint32_t pin, PullMode pull = PullMode::None);

	// well if you have > 64 GPIOs... sorry.
	uint64_t readAll();

	bool read(uint32_t pin);
	void write(uint32_t pin, bool value);
	void toggle(uint32_t pin);
}
