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

				if(auto x = delta[r][c]; x != 0)
				{
					this->updateKey(k, x == 1);
					this->updateModifier(m, x == 1);
				}
			}
		}
	}

	static uint8_t guard_overflow(uint8_t value, bool inc)
	{
		if(inc && value < 0xFF) return value + 1;
		if(!inc && value > 0)   return value - 1;

		return value;
	}

	enum class KeyUpdate
	{
		None,
		Press,
		Release
	};

	static KeyUpdate get_update(uint8_t x1, uint8_t x2)
	{
		if(x1 == 0 && x2 > 0) return KeyUpdate::Press;
		if(x1 > 0 && x2 == 0) return KeyUpdate::Release;

		return KeyUpdate::None;
	}

	void Layout::updateKey(uint8_t key, bool press)
	{
		// if it's a modifier, then handle it as one.
		if(0xE0 <= key && key <= 0xE7)
		{
			this->updateModifier(1 << (key & 0x7), press);
			return;
		}

		auto old_x = m_keyState[key];
		auto new_x = guard_overflow(old_x, press);
		m_keyState[key] = new_x;

		switch(get_update(old_x, new_x))
		{
			case KeyUpdate::Press:
				hid::keyPress(key);
				break;

			case KeyUpdate::Release:
				hid::keyRelease(key);
				break;

			case KeyUpdate::None:
				break;
		}
	}

	void Layout::updateModifier(uint8_t mod, bool press)
	{
		// TODO: figure out a way to bundle the bitfield changes into one thing
		// as it currently stands, if a some key updates eg. both CTRL and ALT,
		// the dumb nordic API will send two usb reports.

		// time to iterate bits like a poor person
		for(size_t i = 0; i < 8; i++)
		{
			// only update the state if the modifier was part of the bitset
			if((mod >> i) & 0x1)
			{
				auto old_x = m_modifierState[i];
				auto new_x = guard_overflow(old_x, press);
				m_modifierState[i] = new_x;

				switch(get_update(old_x, new_x))
				{
					case KeyUpdate::Press:
						hid::modifierPress((1 << i));
						break;

					case KeyUpdate::Release:
						hid::modifierRelease((1 << i));
						break;

					case KeyUpdate::None:
						break;
				}
			}
		}
	}
}
