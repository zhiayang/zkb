// matrix.cpp
// Copyright (c) 2020, zhiayang
// Licensed under the Apache License Version 2.0.

#include <string.h>

#include "kernel.h"
#include "keyboard_config.h"

namespace zkb
{
	using namespace keyboard_config;

	static_assert(NUM_ROWS <= 0xFF, "too many rows");
	static_assert(NUM_COLS <= 0xFF, "too many columns");
	static_assert(DEBOUNCE_TIME <= 0xFF, "debounce time too long");
	static_assert(COLUMNS_TO_ROWS, "row-to-column matrices not supported (yet?)");

	void Matrix::init()
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

	void Matrix::scan()
	{
		// reset the flag
		m_updated = false;

		static constexpr auto MATRIX_SIZE = NUM_ROWS * NUM_COLS * sizeof(bool);

		// make a copy of the old matrix
		bool old_matrix[NUM_ROWS][NUM_COLS] = { };
		memcpy(old_matrix, m_matrix, MATRIX_SIZE);

		for(uint8_t r = 0; r < NUM_ROWS; r++)
		{
			auto pin_r = ROW_PINS[r];
			hal::gpio::modeOutput(pin_r);
			hal::gpio::write(pin_r, 0);

			// wait a while because "real-world physics"
			hal::delayUs(1);
			this->updateRow(r);

			hal::gpio::modeInput(pin_r);
		}

		if(++m_debounceIndex >= DEBOUNCE_TIME)
			m_debounceIndex = 0;

		// check if we need updating
		m_updated = (0 != memcmp(old_matrix, m_matrix, MATRIX_SIZE));
	}

	bool Matrix::updated()
	{
		return m_updated;
	}

	uint64_t Matrix::debouncePins(uint8_t row)
	{
		// note: invert all the bits here, so 1 = pressed, and 0 = released.
		auto pins = ~hal::gpio::readAll();

		auto& buffer = m_debounceBuffer[row];
		buffer[m_debounceIndex] = pins;

		// basically, only record the key as released when there has been no contact
		// for at least DEBOUNCE_TIME iterations. this means that when a switch goes down,
		// it is registered immediately, and any intervening bounces don't un-register it.
		uint64_t ret = 0;
		for(size_t i = 0; i < DEBOUNCE_TIME; i++)
			ret |= buffer[i];

		return ret;
	}

	void Matrix::updateRow(uint8_t row)
	{
		auto pin_state = this->debouncePins(row);

		for(size_t col = 0; col < NUM_COLS; col++)
		{
			auto x = (pin_state >> COL_PINS[col]) & 0x1;
			m_matrix[row][col] = x;

			if(x)
			{
				// debug::log("({}, {}) pressed", row, col);
			}
		}
	}
}
