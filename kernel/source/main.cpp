// main.cpp
// Copyright (c) 2020, zhiayang
// Licensed under the Apache License Version 2.0.

#include "hal.h"
#include "kernel.h"

namespace zkb
{
	static Matrix theMatrix;

	void init()
	{
		using namespace zkb;

		hal::init();
		hal::delayMs(500);
		debug::log("zkb/hal: initialised");

		theMatrix.init();

		int counter = 0;
		while(true)
		{
			debug::log("{} second{} passed", counter, counter == 1 ? " has" : "s have");

			hal::gpio::write(hal::gpio::LED_1, 0);
			hal::delayMs(250);
			hal::gpio::write(hal::gpio::LED_1, 1);
			hal::delayMs(250);

			theMatrix.scan();

			hal::gpio::write(hal::gpio::LED_1, 0);
			hal::delayMs(250);
			hal::gpio::write(hal::gpio::LED_1, 1);
			hal::delayMs(250);

			counter++;
		}
	}
}

int main()
{
	zkb::init();
}
