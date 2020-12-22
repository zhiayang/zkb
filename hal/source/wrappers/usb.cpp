// usb.cpp
// Copyright (c) 2020, zhiayang
// Licensed under the Apache License Version 2.0.

#include "hal/usb.h"

extern "C" bool hal_usb_init();

namespace zkb::hal::usb
{
	bool init()
	{
		return hal_usb_init();
	}
}
