// main.cpp
// Copyright (c) 2020, zhiayang
// Licensed under the Apache License Version 2.0.

#include "hal.h"
#include "kernel.h"
#include "keyboard_config.h"

namespace zkb
{
	static Matrix theMatrix;
	static Layout theLayout;

	void init()
	{
		using namespace zkb;

		hal::init();
		hal::delayMs(500);
		debug::log("zkb/hal: initialised");

		theMatrix.init();

		while(true)
		{
			theMatrix.scan();
			theLayout.update(theMatrix);

			// TODO: probably don't delay
			hal::delayUs(keyboard_config::MATRIX_SCAN_INTERVAL);
		}
	}
}

int main()
{
	zkb::init();
}
