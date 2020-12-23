// layout_config.h
// Copyright (c) 2020, zhiayang
// Licensed under the Apache License Version 2.0.

#pragma once

#include "keys.h"
#include "keyboard_config.h"

namespace layout_config
{
	static constexpr size_t NUM_LAYERS = 1;

	uint8_t KEYMAP_LAYOUT[NUM_LAYERS][keyboard_config::NUM_ROWS][keyboard_config::NUM_COLS] = {
		{
			// { K_ESC,    K_1, K_2, K_3, K_4, K_5 },
			// { K_TAB,    K_Q, K_W, K_E, K_R, K_T },
			// { K_NONE,   K_A, K_S, K_D, K_F, K_G },
			// { K_LSHIFT, K_Z, K_X, K_C, K_V, K_B },
			// { },

			{ K_6,    K_7,     K_8,     K_9,      K_0,         K_MINUS },
			{ K_Y,    K_U,     K_I,     K_O,      K_P,         K_BACKSLASH },
			{ K_H,    K_J,     K_K,     K_L,      K_SEMICOLON, K_APOSTROPHE },
			{ K_N,    K_M,     K_COMMA, K_PERIOD, K_SLASH,     K_RSHIFT },
			{ K_NONE, K_ENTER, K_NONE,  K_NONE,   K_NONE },
		}
	};
}
