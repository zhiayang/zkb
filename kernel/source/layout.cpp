// layout.cpp
// Copyright (c) 2020, zhiayang
// Licensed under the Apache License Version 2.0.

#include "keys.h"
#include "kernel.h"

namespace zkb
{
	bool x = 0;
	void Layout::update(Matrix& matrix)
	{
		// TODO: this is hackish, since we only have the right side rn, the
		// columns are mirrored; ie. column 0 is the rightmost column, and 5 is the leftmost.

		if(!matrix.updated())
			return;

		debug::log("asdf");

		if(x) hal::usb::hid::keyPress(keys::K_A);
		else  hal::usb::hid::keyRelease(keys::K_A);

		x = !x;
	}
}
