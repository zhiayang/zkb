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
