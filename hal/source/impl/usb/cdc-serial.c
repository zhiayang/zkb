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


static void check_for_touch_1200(const app_usbd_class_inst_t* instance)
{
	// basically, when the host connects and disconnects the USB serial (cdc thingy) at 1200 baud,
	// we'll take that as a sign to go into DFU mode. With the adafruit-nrfutil tool, it's done
	// using the --touch 1200 option: very simple. this way there's no need to doublepress reset
	// on that tiny button.
	const app_usbd_cdc_acm_t* inst = app_usbd_cdc_acm_class_get(instance);

	uint32_t dtr = 0;
	ret_code_t ret = app_usbd_cdc_acm_line_state_get(inst, APP_USBD_CDC_ACM_LINE_STATE_DTR, &dtr);
	if(ret != NRF_SUCCESS)
		return;

	// check for disconnect:
	if(!dtr)
	{
		// get the line coding (aka baud rate)
		app_usbd_cdc_acm_req_t* req = app_usbd_cdc_acm_class_request_get(inst);
		app_usbd_cdc_line_coding_t line_coding = req->payload.line_coding;

		// it's in little endian.
		uint32_t baud = (((uint32_t) line_coding.dwDTERate[0]) <<  0)
					  | (((uint32_t) line_coding.dwDTERate[1]) <<  8)
					  | (((uint32_t) line_coding.dwDTERate[2]) << 16)
					  | (((uint32_t) line_coding.dwDTERate[3]) << 24);

		if(baud == 1200)
		{
			// this is some magic number that sends the bootloader into serial DFU mode.
			NRF_POWER->GPREGRET = 0x4E;
			sd_nvic_SystemReset();
		}
	}
}

static void cdc_event_handler(const app_usbd_class_inst_t* instance, app_usbd_cdc_acm_user_event_t event)
{
	check_for_touch_1200(instance);

	switch(event)
	{
		case APP_USBD_CDC_ACM_USER_EVT_RX_DONE: {
			ret_code_t ret = NRF_SUCCESS;

			do {
				char buf[2] = { 0 };
				ret = app_usbd_cdc_acm_read(&appInstanceCDC, buf, 2);
			} while(ret == NRF_SUCCESS);
		} break;

		default:
			break;
	}
}
