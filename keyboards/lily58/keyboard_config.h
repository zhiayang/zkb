// keyboard_config.h
// Copyright (c) 2020, zhiayang
// Licensed under the Apache License Version 2.0.

#pragma once

#include <stdint.h>
#include <stddef.h>

namespace keyboard_config
{
	static constexpr bool IS_SPLIT = true;
	static constexpr bool COLUMNS_TO_ROWS = true;

	static constexpr uint32_t COL_PINS[] = {  2, 47, 45, 43, 10, 9 };
	static constexpr uint32_t ROW_PINS[] = { 24, 32, 11, 36, 38 };

	static constexpr size_t NUM_COLS = sizeof(COL_PINS) / sizeof(COL_PINS[0]);
	static constexpr size_t NUM_ROWS = sizeof(ROW_PINS) / sizeof(ROW_PINS[0]);

	// in milliseconds
	static constexpr size_t MATRIX_SCAN_INTERVAL = 1;

	// in intervals of MATRIX_SCAN_INTERVAL
	static constexpr size_t DEBOUNCE_TIME = 2;
}
