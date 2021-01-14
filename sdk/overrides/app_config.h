// app_config.h
// Copyright (c) 2020, zhiayang
// Licensed under the Apache License Version 2.0.

#define USBD_ENABLED 1
#define POWER_ENABLED 1

#define NRFX_USBD_ENABLED 1
#define NRFX_POWER_ENABLED 1

#define APP_USBD_ENABLED 1
#define APP_USBD_HID_ENABLED 1
#define APP_USBD_HID_KBD_ENABLED 1
#define APP_USBD_CDC_ACM_ENABLED 1

// 0 -- event queue.
// 1 -- compressed event queue
// 2 -- interrupts
#define APP_USBD_CONFIG_SOF_HANDLING_MODE 2

// disable the event queue. these family of functions cannot be called outside
// of an interrupt context now: sleep, wakeup, start, stop, enable, and disable.
#define APP_USBD_CONFIG_EVENT_QUEUE_ENABLE 0

#define NRFX_TWI_ENABLED 1
#define NRFX_TWI0_ENABLED 1
#define NRFX_TWI1_ENABLED 1
#define NRFX_TWI_DEFAULT_CONFIG_FREQUENCY 26738688      // 100k

#define TWI_ENABLED 1
#define TWI0_ENABLED 1
#define TWI1_ENABLED 1
#define TWI_DEFAULT_CONFIG_FREQUENCY 26738688

#define NRFX_PRS_ENABLED 0
#define NRF_LOG_ENABLED 0

#define APP_USBD_STRING_SERIAL APP_USBD_STRING_DESC("1410")
