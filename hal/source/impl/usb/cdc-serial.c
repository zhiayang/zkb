// cdc-serial.c
// Copyright (c) 2020, zhiayang
// Licensed under the Apache License Version 2.0.

#include <app_usbd.h>
#include <app_usbd_cdc_acm.h>

#include "hal/impl_common.h"

#define CDC_ACM_COMM_INTERFACE  0
#define CDC_ACM_COMM_EPIN       NRF_DRV_USBD_EPIN2

#define CDC_ACM_DATA_INTERFACE  1
#define CDC_ACM_DATA_EPIN       NRF_DRV_USBD_EPIN1
#define CDC_ACM_DATA_EPOUT      NRF_DRV_USBD_EPOUT1

static void cdc_event_handler(const app_usbd_class_inst_t* instance, app_usbd_cdc_acm_user_event_t event);

// class instance for cdc acm
APP_USBD_CDC_ACM_GLOBAL_DEF(appInstanceCDC, cdc_event_handler,
	CDC_ACM_COMM_INTERFACE, CDC_ACM_DATA_INTERFACE,
	CDC_ACM_COMM_EPIN, CDC_ACM_DATA_EPIN,
	CDC_ACM_DATA_EPOUT, APP_USBD_CDC_COMM_PROTOCOL_AT_V250);


bool hal_usb_debug_init(void)
{
	const app_usbd_class_inst_t* inst = app_usbd_cdc_acm_class_inst_get(&appInstanceCDC);
	ret_code_t ret = app_usbd_class_append(inst);
	if(ret != NRF_SUCCESS)
		return false;

	return true;
}

void hal_debug_write(const char* buf, size_t size)
{
	app_usbd_cdc_acm_write(&appInstanceCDC, buf, size);
}

static void cdc_event_handler(const app_usbd_class_inst_t* instance, app_usbd_cdc_acm_user_event_t event)
{
	char buf[2] = { 0 };

	switch(event)
	{
		case APP_USBD_CDC_ACM_USER_EVT_PORT_OPEN:
			break;

		case APP_USBD_CDC_ACM_USER_EVT_RX_DONE: {
			ret_code_t ret = NRF_SUCCESS;

			do {
				ret = app_usbd_cdc_acm_read(&appInstanceCDC, buf, 2);
			} while(ret == NRF_SUCCESS);
		} break;

		default:
			break;
	}
}





#if 0
#include <boards.h>
#include <nrf_delay.h>
#include <nrf_drv_clock.h>

#include <app_usbd.h>
#include <app_usbd_cdc_acm.h>
#include <app_usbd_serial_num.h>

#define CDC_ACM_COMM_INTERFACE  0
#define CDC_ACM_COMM_EPIN       NRF_DRV_USBD_EPIN2

#define CDC_ACM_DATA_INTERFACE  1
#define CDC_ACM_DATA_EPIN       NRF_DRV_USBD_EPIN1
#define CDC_ACM_DATA_EPOUT      NRF_DRV_USBD_EPOUT1

// since these are called from library code, they probably need to be extern C
static void cdc_event_handler(const app_usbd_class_inst_t* instance, app_usbd_cdc_acm_user_event_t event);
static void usb_event_handler(app_usbd_event_type_t event);

// class instance for cdc acm
APP_USBD_CDC_ACM_GLOBAL_DEF(appInstanceCDC, cdc_event_handler,
	CDC_ACM_COMM_INTERFACE, CDC_ACM_DATA_INTERFACE,
	CDC_ACM_COMM_EPIN, CDC_ACM_DATA_EPIN,
	CDC_ACM_DATA_EPOUT, APP_USBD_CDC_COMM_PROTOCOL_AT_V250);


int cdcWrite(const char* buf, size_t size)
{
	ret_code_t ret = app_usbd_cdc_acm_write(&appInstanceCDC, buf, size);
	return ret != NRF_SUCCESS;
}


int initialiseUSB()
{
	app_usbd_config_t usbd_config = {
		.ev_state_proc = usb_event_handler
	};

	// TODO: check errors
	ret_code_t ret = nrf_drv_clock_init();
	if(ret != NRF_SUCCESS)
	{
		nrf_gpio_pin_set(LED_1);
		return 1;
	}

	nrf_drv_clock_lfclk_request(NULL);

	// wait for the clock
	while(!nrf_drv_clock_lfclk_is_running())
		;

	app_usbd_serial_num_generate();
	ret = app_usbd_init(&usbd_config);
	if(ret != NRF_SUCCESS)
	{
		nrf_gpio_pin_set(LED_1);
		return 1;
	}

	const app_usbd_class_inst_t* inst = app_usbd_cdc_acm_class_inst_get(&appInstanceCDC);
	ret = app_usbd_class_append(inst);
	if(ret != NRF_SUCCESS)
	{
		nrf_gpio_pin_set(LED_1);
		return 1;
	}

	ret = app_usbd_power_events_enable();

	// app_usbd_enable();
	// app_usbd_start();

	if(ret != NRF_SUCCESS)
	{
		nrf_gpio_pin_set(LED_1);
		return 1;
	}

	return 0;
}


static void cdc_event_handler(const app_usbd_class_inst_t* instance, app_usbd_cdc_acm_user_event_t event)
{
	char buf[2];

	const app_usbd_cdc_acm_t* p_cdc_acm = app_usbd_cdc_acm_class_get(instance);
	switch(event)
	{
		case APP_USBD_CDC_ACM_USER_EVT_PORT_OPEN:
			// app_usbd_cdc_acm_read(&appInstanceCDC, buf, 2);
			break;

		case APP_USBD_CDC_ACM_USER_EVT_RX_DONE:
		{
			ret_code_t ret;
			do
			{
				// size_t size = app_usbd_cdc_acm_rx_size(p_cdc_acm);

				/* Fetch data until internal buffer is empty */
				ret = app_usbd_cdc_acm_read(&appInstanceCDC,
											buf, 2);
			} while (ret == NRF_SUCCESS);

			break;
		}
		default:
			break;
	}
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
			break;

		default:
			break;
	}
}
#endif
