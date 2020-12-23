// common.c
// Copyright (c) 2020, zhiayang
// Licensed under the Apache License Version 2.0.

#include <boards.h>
#include <nrf_delay.h>

#include "hal/impl_common.h"

void hal_delay_ms(uint32_t ms)          {   nrf_delay_ms(ms);           }
void hal_delay_us(uint32_t us)          {   nrf_delay_us(us);           }
void hal_pin_write(uint32_t pin, bool x){   nrf_gpio_pin_write(pin, x); }
void hal_pin_toggle(uint32_t pin)       {   nrf_gpio_pin_toggle(pin);   }
void hal_pin_set_output(uint32_t pin)   {   nrf_gpio_cfg_output(pin);   }
bool hal_pin_read(uint32_t pin)         {   return nrf_gpio_pin_read(pin) != 0; }

// TODO: board abstraction layer
uint64_t hal_pin_read_all(void)
{
	uint32_t low = NRF_P0->IN;
	uint32_t high = NRF_P1->IN;

	// this assumes that the `->IN` field returns bits in order of the pin order
	// ie. P0.00 is the LSB, P0.31 is the MSB, P1.00 is the LSB, and P1.31 is the MSB.
	return (((uint64_t) high) << 32) | low;
}

void hal_pin_set_input(uint32_t pin, int pull)
{
	// see enum hal::gpio::PullMode
	if(pull == 1)       nrf_gpio_cfg_input(pin, NRF_GPIO_PIN_PULLDOWN);
	else if(pull == 2)  nrf_gpio_cfg_input(pin, NRF_GPIO_PIN_PULLUP);
	else                nrf_gpio_cfg_input(pin, NRF_GPIO_PIN_NOPULL);
}

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
