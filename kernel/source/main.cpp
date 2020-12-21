// main.cpp
// Copyright (c) 2020, zhiayang
// Licensed under the Apache License Version 2.0.

#include <stdint.h>

#include "boards.h"
#include "nrf_delay.h"

#define LED_3          NRF_GPIO_PIN_MAP(0,15)

void delay(uint32_t ms)
{
    for(uint32_t i = 0; i < ms * 64000; i++)
        asm volatile ("nop");
}

int main()
{
    // Configure board.
    nrf_gpio_cfg_output(LED_3);

    // Toggle LEDs.
    while(true)
    {
        nrf_gpio_pin_set(LED_3);
        nrf_delay_ms(1500);
        // delay(200);
        nrf_gpio_pin_clear(LED_3);
        nrf_delay_ms(1500);
        // delay(200);
    }
}
