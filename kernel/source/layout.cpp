// layout.cpp
// Copyright (c) 2020, zhiayang
// Licensed under the Apache License Version 2.0.

#include "keys.h"
#include "kernel.h"

#include "hal/hid.h"

#include "layout_config.h"
#include "keyboard_config.h"

#include "krt/pair.h"

namespace zkb
{
	using namespace layout_config;
	using namespace keyboard_config;

	namespace hid = hal::usb::hid;

	static_assert(NUM_LAYERS == 1, "no layer support yet");

	constexpr krt::pair<uint8_t, uint8_t> convert_key(uint16_t key)
	{
		// for now, the keycodes are primitive; upper byte is just the modifier
		// bits, and lower byte is just the hid scancode. they correspond exactly
		// to the USB hid codes.
		return { (key & 0xFF00) >> 8, (key & 0xFF) };
	}

	void Layout::update(Matrix& matrix)
	{
		if(!matrix.updated())
			return;

		// TODO: we need to maintain our own key state, since multiple keys may be mapped
		// to the same keycode (or modifier); releasing one should not send a release report!
		// possibly a 256-big array of uint8_ts that just act as a 'refcount' ?

		uint8_t delta[NUM_ROWS][NUM_COLS] = { };
		matrix.getMatrixDelta(delta);

		for(size_t r = 0; r < NUM_ROWS; r++)
		{
			for(size_t c = 0; c < NUM_COLS; c++)
			{
				// TODO: this is hackish, since we only have the right side rn, the
				// columns are mirrored; ie. column 0 is the rightmost column, and 5 is the leftmost.
				auto key = KEYMAP_LAYOUT[0][r][NUM_COLS - c - 1];
				auto [ m, k ] = convert_key(key);

				if(auto x = delta[r][c]; x == 1)
				{
					hid::keyPress(k);
					hid::modifierPress(m);
				}
				else if(x == 2)
				{
					hid::keyRelease(k);
					hid::modifierRelease(m);
				}
			}
		}
	}
}
