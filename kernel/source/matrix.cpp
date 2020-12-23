// matrix.cpp
// Copyright (c) 2020, zhiayang
// Licensed under the Apache License Version 2.0.

#include "kernel.h"
#include "keyboard_config.h"

namespace zkb::matrix
{
	using namespace keyboard_config;

	static_assert(COLUMNS_TO_ROWS, "row-to-column matrices not supported (yet?)");

	static size_t g_debounceIndex = 0;
	static uint64_t g_debounceBuffer[NUM_ROWS][DEBOUNCE_TIME] = { };

	static bool g_matrixState[NUM_ROWS][NUM_COLS] = { };

	// defined below
	static void update_row(size_t row, uint64_t pins);
	static uint64_t debounce_pins(size_t row, uint64_t pins);

	void init()
	{
		/*
			how this is configured: there is a diode along each "row" connection, biased "toward" the MCU, and
			each column pin is configured to input with pull-up.

			by writing a 0 to the row pin, current flows from the high col-pin to the low row-pin "with" the diode,
			and the column is read as a 0 when the switch is pressed. if the switch is not pressed, it is read as a 1.
		*/

		for(auto col : COL_PINS)
			hal::gpio::modeInput(col, hal::gpio::PullMode::Up);

		// set the pins to input to 'disable' them
		for(auto row : ROW_PINS)
			hal::gpio::modeInput(row);
	}

	void scan()
	{
		for(size_t r = 0; r < NUM_ROWS; r++)
		{
			auto pin_r = ROW_PINS[r];
			hal::gpio::modeOutput(pin_r);
			hal::gpio::write(pin_r, 0);

			// wait a while because "real-world physics"
			hal::delayUs(1);

			auto all_pins = debounce_pins(r, hal::gpio::readAll());
			hal::gpio::modeInput(pin_r);

			update_row(r, all_pins);
		}

		if(++g_debounceIndex > DEBOUNCE_TIME)
			g_debounceIndex = 0;
	}

	static void update_row(size_t row, uint64_t pins)
	{
		for(size_t col = 0; col < NUM_COLS; col++)
		{
			auto x = (pins >> COL_PINS[col]) & 0x1;
			g_matrixState[row][col] = x;
		}
	}

	static uint64_t debounce_pins(size_t row, uint64_t pins)
	{
		auto& buffer = g_debounceBuffer[row];
		buffer[g_debounceIndex] = pins;

		// basically, only record the key as released when there has been no contact
		// for at least DEBOUNCE_TIME iterations. this means that when a switch goes down,
		// it is registered immediately, and any intervening bounces don't un-register it.
		uint64_t ret = 0;
		for(size_t i = 0; i < DEBOUNCE_TIME; i++)
			ret |= buffer[i];

		return ret;
	}
}
