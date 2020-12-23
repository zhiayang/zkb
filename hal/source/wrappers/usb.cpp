// usb.cpp
// Copyright (c) 2020, zhiayang
// Licensed under the Apache License Version 2.0.

#include <stdint.h>
#include <stddef.h>

#define ZKB_HAL_IMPL
#include "hal/impl_common.h"

#include "hal/usb.h"
#include "hal/hid.h"

extern "C" bool hal_usb_init();

namespace zkb::hal::usb
{
	bool init()
	{
		return hal_usb_init();
	}

	namespace hid
	{
		void keyPress(uint8_t keycode)
		{
			hal_usb_hid_key_press(keycode);
		}

		void keyRelease(uint8_t keycode)
		{
			hal_usb_hid_key_release(keycode);
		}

		void modifierPress(uint8_t modifier)
		{
			hal_usb_hid_modifier_press(modifier);
		}

		void modifierRelease(uint8_t modifier)
		{
			hal_usb_hid_modifier_release(modifier);
		}
	}
}
