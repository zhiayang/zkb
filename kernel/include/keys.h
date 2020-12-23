// keys.h
// Copyright (c) 2020, zhiayang
// Licensed under the Apache License Version 2.0.

#pragma once

#include <stdint.h>

namespace keys
{
	static constexpr uint8_t M_NONE         = 0x00;
	static constexpr uint8_t M_LCTRL        = 0x01;
	static constexpr uint8_t M_LSHIFT       = 0x02;
	static constexpr uint8_t M_LALT         = 0x04;
	static constexpr uint8_t M_LGUI         = 0x08;
	static constexpr uint8_t M_RCTRL        = 0x10;
	static constexpr uint8_t M_RSHIFT       = 0x20;
	static constexpr uint8_t M_RALT         = 0x40;
	static constexpr uint8_t M_RGUI         = 0x80;



	static constexpr uint16_t K_NONE        = 0x00;

	static constexpr uint16_t K_A           = 0x04;
	static constexpr uint16_t K_B           = 0x05;
	static constexpr uint16_t K_C           = 0x06;
	static constexpr uint16_t K_D           = 0x07;
	static constexpr uint16_t K_E           = 0x08;
	static constexpr uint16_t K_F           = 0x09;
	static constexpr uint16_t K_G           = 0x0A;
	static constexpr uint16_t K_H           = 0x0B;
	static constexpr uint16_t K_I           = 0x0C;
	static constexpr uint16_t K_J           = 0x0D;
	static constexpr uint16_t K_K           = 0x0E;
	static constexpr uint16_t K_L           = 0x0F;
	static constexpr uint16_t K_M           = 0x10;
	static constexpr uint16_t K_N           = 0x11;
	static constexpr uint16_t K_O           = 0x12;
	static constexpr uint16_t K_P           = 0x13;
	static constexpr uint16_t K_Q           = 0x14;
	static constexpr uint16_t K_R           = 0x15;
	static constexpr uint16_t K_S           = 0x16;
	static constexpr uint16_t K_T           = 0x17;
	static constexpr uint16_t K_U           = 0x18;
	static constexpr uint16_t K_V           = 0x19;
	static constexpr uint16_t K_W           = 0x1A;
	static constexpr uint16_t K_X           = 0x1B;
	static constexpr uint16_t K_Y           = 0x1C;
	static constexpr uint16_t K_Z           = 0x1D;

	static constexpr uint16_t K_1           = 0x1E;
	static constexpr uint16_t K_2           = 0x1F;
	static constexpr uint16_t K_3           = 0x20;
	static constexpr uint16_t K_4           = 0x21;
	static constexpr uint16_t K_5           = 0x22;
	static constexpr uint16_t K_6           = 0x23;
	static constexpr uint16_t K_7           = 0x24;
	static constexpr uint16_t K_8           = 0x25;
	static constexpr uint16_t K_9           = 0x26;
	static constexpr uint16_t K_0           = 0x27;

	static constexpr uint16_t K_ENTER       = 0x28;
	static constexpr uint16_t K_ESC         = 0x29;
	static constexpr uint16_t K_BACKSPACE   = 0x2A;
	static constexpr uint16_t K_TAB         = 0x2B;
	static constexpr uint16_t K_SPACE       = 0x2C;
	static constexpr uint16_t K_MINUS       = 0x2D;
	static constexpr uint16_t K_EQUAL       = 0x2E;
	static constexpr uint16_t K_LEFTBRACE   = 0x2F;
	static constexpr uint16_t K_RIGHTBRACE  = 0x30;
	static constexpr uint16_t K_BACKSLASH   = 0x31;
	static constexpr uint16_t K_HASHTILDE   = 0x32;
	static constexpr uint16_t K_SEMICOLON   = 0x33;
	static constexpr uint16_t K_APOSTROPHE  = 0x34;
	static constexpr uint16_t K_GRAVE       = 0x35;
	static constexpr uint16_t K_COMMA       = 0x36;
	static constexpr uint16_t K_DOT         = 0x37;
	static constexpr uint16_t K_SLASH       = 0x38;
	static constexpr uint16_t K_CAPSLOCK    = 0x39;

	static constexpr uint16_t K_LCTRL       = 0xE0;
	static constexpr uint16_t K_LSHIFT      = 0xE1;
	static constexpr uint16_t K_LALT        = 0xE2;
	static constexpr uint16_t K_LMETA       = 0xE3;
	static constexpr uint16_t K_RCTRL       = 0xE4;
	static constexpr uint16_t K_RSHIFT      = 0xE5;
	static constexpr uint16_t K_RALT        = 0xE6;
	static constexpr uint16_t K_RMETA       = 0xE7;
}

#if 0

#define K_F1 0x3a // Keyboard F1
#define K_F2 0x3b // Keyboard F2
#define K_F3 0x3c // Keyboard F3
#define K_F4 0x3d // Keyboard F4
#define K_F5 0x3e // Keyboard F5
#define K_F6 0x3f // Keyboard F6
#define K_F7 0x40 // Keyboard F7
#define K_F8 0x41 // Keyboard F8
#define K_F9 0x42 // Keyboard F9
#define K_F10 0x43 // Keyboard F10
#define K_F11 0x44 // Keyboard F11
#define K_F12 0x45 // Keyboard F12

#define K_SYSRQ 0x46 // Keyboard Print Screen
#define K_SCROLLLOCK 0x47 // Keyboard Scroll Lock
#define K_PAUSE 0x48 // Keyboard Pause
#define K_INSERT 0x49 // Keyboard Insert
#define K_HOME 0x4a // Keyboard Home
#define K_PAGEUP 0x4b // Keyboard Page Up
#define K_DELETE 0x4c // Keyboard Delete Forward
#define K_END 0x4d // Keyboard End
#define K_PAGEDOWN 0x4e // Keyboard Page Down
#define K_RIGHT 0x4f // Keyboard Right Arrow
#define K_LEFT 0x50 // Keyboard Left Arrow
#define K_DOWN 0x51 // Keyboard Down Arrow
#define K_UP 0x52 // Keyboard Up Arrow

#define K_NUMLOCK 0x53 // Keyboard Num Lock and Clear
#define K_KPSLASH 0x54 // Keypad /
#define K_KPASTERISK 0x55 // Keypad *
#define K_KPMINUS 0x56 // Keypad -
#define K_KPPLUS 0x57 // Keypad +
#define K_KPENTER 0x58 // Keypad ENTER
#define K_KP1 0x59 // Keypad 1 and End
#define K_KP2 0x5a // Keypad 2 and Down Arrow
#define K_KP3 0x5b // Keypad 3 and PageDn
#define K_KP4 0x5c // Keypad 4 and Left Arrow
#define K_KP5 0x5d // Keypad 5
#define K_KP6 0x5e // Keypad 6 and Right Arrow
#define K_KP7 0x5f // Keypad 7 and Home
#define K_KP8 0x60 // Keypad 8 and Up Arrow
#define K_KP9 0x61 // Keypad 9 and Page Up
#define K_KP0 0x62 // Keypad 0 and Insert
#define K_KPDOT 0x63 // Keypad . and Delete

#define K_102ND 0x64 // Keyboard Non-US \ and |
#define K_COMPOSE 0x65 // Keyboard Application
#define K_POWER 0x66 // Keyboard Power
#define K_KPEQUAL 0x67 // Keypad =

#define K_F13 0x68 // Keyboard F13
#define K_F14 0x69 // Keyboard F14
#define K_F15 0x6a // Keyboard F15
#define K_F16 0x6b // Keyboard F16
#define K_F17 0x6c // Keyboard F17
#define K_F18 0x6d // Keyboard F18
#define K_F19 0x6e // Keyboard F19
#define K_F20 0x6f // Keyboard F20
#define K_F21 0x70 // Keyboard F21
#define K_F22 0x71 // Keyboard F22
#define K_F23 0x72 // Keyboard F23
#define K_F24 0x73 // Keyboard F24

#define K_OPEN 0x74 // Keyboard Execute
#define K_HELP 0x75 // Keyboard Help
#define K_PROPS 0x76 // Keyboard Menu
#define K_FRONT 0x77 // Keyboard Select
#define K_STOP 0x78 // Keyboard Stop
#define K_AGAIN 0x79 // Keyboard Again
#define K_UNDO 0x7a // Keyboard Undo
#define K_CUT 0x7b // Keyboard Cut
#define K_COPY 0x7c // Keyboard Copy
#define K_PASTE 0x7d // Keyboard Paste
#define K_FIND 0x7e // Keyboard Find
#define K_MUTE 0x7f // Keyboard Mute
#define K_VOLUMEUP 0x80 // Keyboard Volume Up
#define K_VOLUMEDOWN 0x81 // Keyboard Volume Down
// 0x82  Keyboard Locking Caps Lock
// 0x83  Keyboard Locking Num Lock
// 0x84  Keyboard Locking Scroll Lock
#define K_KPCOMMA 0x85 // Keypad Comma
// 0x86  Keypad Equal Sign
#define K_RO 0x87 // Keyboard International1
#define K_KATAKANAHIRAGANA 0x88 // Keyboard International2
#define K_YEN 0x89 // Keyboard International3
#define K_HENKAN 0x8a // Keyboard International4
#define K_MUHENKAN 0x8b // Keyboard International5
#define K_KPJPCOMMA 0x8c // Keyboard International6
// 0x8d  Keyboard International7
// 0x8e  Keyboard International8
// 0x8f  Keyboard International9
#define K_HANGEUL 0x90 // Keyboard LANG1
#define K_HANJA 0x91 // Keyboard LANG2
#define K_KATAKANA 0x92 // Keyboard LANG3
#define K_HIRAGANA 0x93 // Keyboard LANG4
#define K_ZENKAKUHANKAKU 0x94 // Keyboard LANG5

#define K_KPLEFTPAREN 0xb6 // Keypad (
#define K_KPRIGHTPAREN 0xb7 // Keypad )

#define K_LEFTCTRL 0xe0 // Keyboard Left Control
#define K_LEFTSHIFT 0xe1 // Keyboard Left Shift
#define K_LEFTALT 0xe2 // Keyboard Left Alt
#define K_LEFTMETA 0xe3 // Keyboard Left GUI
#define K_RIGHTCTRL 0xe4 // Keyboard Right Control
#define K_RIGHTSHIFT 0xe5 // Keyboard Right Shift
#define K_RIGHTALT 0xe6 // Keyboard Right Alt
#define K_RIGHTMETA 0xe7 // Keyboard Right GUI

#endif
