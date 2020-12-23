// hid.h
// Copyright (c) 2020, zhiayang
// Licensed under the Apache License Version 2.0.

#pragma once

#include <stdint.h>

namespace zkb::hal::usb::hid
{
	void keyPress(uint8_t keycode);
	void keyRelease(uint8_t keycode);
	void modifierPress(uint8_t keycode);
	void modifierRelease(uint8_t keycode);
}
