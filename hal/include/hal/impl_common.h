// impl_common.h
// Copyright (c) 2020, zhiayang
// Licensed under the Apache License Version 2.0.

#pragma once

// this is a C header!
#if defined(__cplusplus) && !defined(ZKB_HAL_IMPL)
	#error "don't include this from C++ files!"
#endif

#if defined(__cplusplus)
extern "C" {
#endif

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

__attribute__((noreturn)) void hal_silent_error(void);

uint64_t hal_pin_read_all(void);
bool hal_pin_read(uint32_t pin);
void hal_pin_write(uint32_t pin, bool value);
void hal_pin_toggle(uint32_t pin);
void hal_pin_set_output(uint32_t pin);
void hal_pin_set_input(uint32_t pin, int pull);

void hal_board_init(void);
void hal_delay_ms(uint32_t ms);
void hal_delay_us(uint32_t us);
void hal_debug_write(const char* buf, size_t size);

void hal_usb_hid_key_press(uint8_t keycode);
void hal_usb_hid_key_release(uint8_t keycode);
void hal_usb_hid_modifier_press(uint8_t keycode);
void hal_usb_hid_modifier_release(uint8_t keycode);

#if defined(__cplusplus)
}
#endif
