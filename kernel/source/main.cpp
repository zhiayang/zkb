// main.cpp
// Copyright (c) 2020, zhiayang
// Licensed under the Apache License Version 2.0.

#include <stdint.h>

#include "boards.h"
#include "nrf_delay.h"

#define LED_3          NRF_GPIO_PIN_MAP(0,15)

int main()
{
    // Configure board.
    nrf_gpio_cfg_output(LED_1);

    // Toggle LEDs.
    while(true)
    {
        nrf_gpio_pin_set(LED_1);
        nrf_delay_ms(300);
        nrf_gpio_pin_clear(LED_1);
        nrf_delay_ms(300);
    }
}
