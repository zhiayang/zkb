// asdf.c
// Copyright (c) 2020, zhiayang
// Licensed under the Apache License Version 2.0.

#include <nrf_drv_clock.h>

#include <app_usbd.h>
#include <app_usbd_serial_num.h>

#include "hal/impl_common.h"

// defined in impl/usb/cdc-serial.c
extern bool hal_usb_debug_init(void);
static void usb_event_handler(app_usbd_event_type_t event);

// it doesn't need to be synchronised, just volatile -- since there's ever only 1 reader and 1 writer.
volatile bool hal_usb_is_available;

bool hal_usb_init(void)
{
	hal_usb_is_available = false;

	app_usbd_config_t usbd_config = {
		.ev_state_proc = usb_event_handler
	};

	ret_code_t ret = nrf_drv_clock_init();
	if(ret != NRF_SUCCESS)
		return false;

	// wait for the clock to come up
	nrf_drv_clock_lfclk_request(NULL);
	while(!nrf_drv_clock_lfclk_is_running())
		;

	app_usbd_serial_num_generate();
	ret = app_usbd_init(&usbd_config);
	if(ret != NRF_SUCCESS)
		return false;

	if(hal_usb_debug_init() == false)
		return false;

	ret = app_usbd_power_events_enable();
	if(ret != NRF_SUCCESS)
		return false;

	return true;
}

static void usb_event_handler(app_usbd_event_type_t event)
{
	switch(event)
	{
		case APP_USBD_EVT_STOPPED:
			app_usbd_disable();
			break;

		case APP_USBD_EVT_POWER_DETECTED:
			app_usbd_enable();
			break;

		case APP_USBD_EVT_POWER_REMOVED:
			app_usbd_stop();
			break;

		case APP_USBD_EVT_POWER_READY:
			app_usbd_start();
			hal_usb_is_available = true;
			break;

		default:
			break;
	}
}
