// common.c
// Copyright (c) 2020, zhiayang
// Licensed under the Apache License Version 2.0.

#include <boards.h>
#include <nrf_delay.h>

#include "hal/impl_common.h"

void hal_delay_ms(uint32_t ms)          {   nrf_delay_ms(ms);           }
void hal_pin_write(uint32_t pin, bool x){   nrf_gpio_pin_write(pin, x); }
void hal_pin_toggle(uint32_t pin)       {   nrf_gpio_pin_toggle(pin);   }

__attribute__((noreturn)) void hal_silent_error(void)
{
	// blink the led 20 times, then halt.
	for(int i = 0; i < 20; i++)
	{
		hal_delay_ms(200);
		hal_pin_toggle(LED_1);
	}

	hal_pin_write(LED_1, 1);
	while(true)
		;
}

void hal_board_init(void)
{
	nrf_gpio_cfg_output(LED_1);
}
