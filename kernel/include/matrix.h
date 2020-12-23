// matrix.h
// Copyright (c) 2020, zhiayang
// Licensed under the Apache License Version 2.0.

#pragma once

#include "keyboard_config.h"

namespace zkb
{
	struct Matrix
	{
		void scan();
		void init();
		bool updated();

		constexpr uint8_t numRows() const { return keyboard_config::NUM_ROWS; }
		constexpr uint8_t numColumns() const { return keyboard_config::NUM_COLS; }

		// TODO: make an array<> class and return that instead of doing this C-style nonsense?
		// 0 = no change
		// 1 = released -> pressed
		// 2 = pressed -> released
		void getMatrixDelta(uint8_t (&output)[keyboard_config::NUM_ROWS][keyboard_config::NUM_COLS]);

	private:
		void updateRow(uint8_t row);
		uint64_t debouncePins(uint8_t row);

		uint8_t m_debounceIndex = 0;
		uint64_t m_debounceBuffer[keyboard_config::NUM_ROWS][keyboard_config::DEBOUNCE_TIME] = { };

		// double buffering OMEGALUL
		int m_currentMatrix = 0;
		bool m_matrices[2][keyboard_config::NUM_ROWS][keyboard_config::NUM_COLS] = { };
	};
}
