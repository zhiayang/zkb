// layout.h
// Copyright (c) 2020, zhiayang
// Licensed under the Apache License Version 2.0.

#pragma once

namespace zkb
{
	struct Matrix;

	struct Layout
	{
		void update(Matrix& matrix);

	private:
		void updateKey(uint8_t key, bool state);
		void updateModifier(uint8_t key, bool state);

		// there are only 255 possible usb hid scancodes (0 does not count)
		uint8_t m_keyState[0xFF];

		// and only 8 modifiers
		uint8_t m_modifierState[8];
	};
}
