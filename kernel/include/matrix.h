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

	private:
		void updateRow(uint8_t row);
		uint64_t debouncePins(uint8_t row);

		bool m_updated = false;
		uint8_t m_debounceIndex = 0;
		uint64_t m_debounceBuffer[keyboard_config::NUM_ROWS][keyboard_config::DEBOUNCE_TIME] = { };

		bool m_matrix[keyboard_config::NUM_ROWS][keyboard_config::NUM_COLS] = { };
	};
}
