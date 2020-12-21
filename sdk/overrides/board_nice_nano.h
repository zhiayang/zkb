// board_nice_nano.h
// Copyright (c) 2020, zhiayang
// Licensed under the Apache License Version 2.0.

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "nrf_gpio.h"

// LEDs definitions for PCA10056
#define LEDS_NUMBER    1
#define LED_1          NRF_GPIO_PIN_MAP(0,15)

#define LEDS_ACTIVE_STATE 0
#define LEDS_LIST { LED_1 }

#define LEDS_INV_MASK  LEDS_MASK
#define BSP_LED_0      15

#define RX_PIN_NUMBER  8
#define TX_PIN_NUMBER  6
#define HWFC           true

#ifdef __cplusplus
}
#endif
