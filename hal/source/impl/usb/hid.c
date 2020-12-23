// hid.c
// Copyright (c) 2020, zhiayang
// Licensed under the Apache License Version 2.0.

#include <app_usbd.h>
#include <app_usbd_hid_kbd.h>

#include "hal/impl_common.h"

// the cdc-serial uses EPIN1, EPIN2, and EPOUT1, as well
// as interfaces 0 and 1.

#define HID_INTERFACE       2
#define HID_ENDPOINT        NRF_DRV_USBD_EPIN3
#define HID_SUBCLASS        APP_USBD_HID_SUBCLASS_BOOT  // i guess we support the boot protocol?

static void hid_event_handler(const app_usbd_class_inst_t* instance, app_usbd_hid_user_event_t event);

APP_USBD_HID_KBD_GLOBAL_DEF(appInstanceHID,
	HID_INTERFACE, HID_ENDPOINT, hid_event_handler, HID_SUBCLASS);

bool hal_usb_hid_init(void)
{
	const app_usbd_class_inst_t* inst = app_usbd_hid_kbd_class_inst_get(&appInstanceHID);
	ret_code_t ret = app_usbd_class_append(inst);
	if(ret != NRF_SUCCESS)
		return false;

	return true;
}

void hal_usb_hid_key_press(uint8_t keycode)
{
	app_usbd_hid_kbd_key_control(&appInstanceHID, keycode, /* press: */ true);
}

void hal_usb_hid_key_release(uint8_t keycode)
{
	app_usbd_hid_kbd_key_control(&appInstanceHID, keycode, /* press: */ false);
}

void hal_usb_hid_modifier_press(uint8_t modifier)
{
	app_usbd_hid_kbd_modifier_state_set(&appInstanceHID,
		(app_usbd_hid_kbd_modifier_t) modifier, /* pressed: */ true);
}

void hal_usb_hid_modifier_release(uint8_t modifier)
{
	app_usbd_hid_kbd_modifier_state_set(&appInstanceHID,
		(app_usbd_hid_kbd_modifier_t) modifier, /* pressed: */ false);
}

static void hid_event_handler(const app_usbd_class_inst_t* instance, app_usbd_hid_user_event_t event)
{
	switch(event)
	{
		case APP_USBD_HID_USER_EVT_OUT_REPORT_READY:
			break;

		case APP_USBD_HID_USER_EVT_IN_REPORT_DONE:
			break;

		// TODO: investigate if the app_usbd library handles this properly
		// (ie. does it know how to send a 6-key report when in boot mode,
		//  and send an NKRO report when not in boot mode)
		case APP_USBD_HID_USER_EVT_SET_BOOT_PROTO:
			hid_kbd_clear_buffer(instance);
			break;

		case APP_USBD_HID_USER_EVT_SET_REPORT_PROTO:
			hid_kbd_clear_buffer(instance);
			break;

		default:
			break;
	}
}
