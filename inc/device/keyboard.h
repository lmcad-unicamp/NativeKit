/* ---------------------------------------------------------------------------- *
 * Copyright (C) 2014-2015 Alisson Linhares de Carvalho.                        *
 * All rights reserved.                                                         *
 *                                                                              *
 * This file is part of the Native Kit.                                         *
 *                                                                              *
 * The Native Kit is free software: you can redistribute it and/or modify it    *
 * under the terms of the GNU Lesser General Public License as published by     *
 * the Free Software Foundation, either version 3 of the License, or            *
 * (at your option) any later version.                                          *
 *                                                                              *
 * The Native Kit is distributed in the hope that it will be useful, but        *
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY   *
 * or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for  *
 * more details.                                                                *
 *                                                                              *
 * You should have received a copy of the GNU General Public License along with *
 * the Native Kit. If not, see <http://www.gnu.org/licenses/>.                  *
 * ---------------------------------------------------------------------------- */

#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <inputdevice.h>
#include <keybuffer.h>

#define KEY_ESC         1
#define KEY_BACK_SPACE  14
#define KEY_TAB         15
#define KEY_ENTER       28
#define KEY_SHIFT_R     54
#define KEY_SHIFT_L     42
#define KEY_ALT         56
#define KEY_SPACE       57
#define KEY_F1          59
#define KEY_F2          60
#define KEY_F3          61
#define KEY_F4          62
#define KEY_F5          63
#define KEY_F6          64
#define KEY_F7          65
#define KEY_F8          66
#define KEY_F9          67
#define KEY_F10         68
#define KEY_F11         23639
#define KEY_F12         88
#define KEY_CAPS        58
#define KEY_NUM_LOCK    69
#define KEY_SCROLL_LOCK 70
#define KEY_NULL        0
#define KEY_HOME        14151
#define KEY_INSERT      12370
#define KEY_DELETE      11347
#define KEY_PAUSE_BREAK 29
#define KEY_CTRL        29
#define KEY_PRTSC       0
#define KEY_ALTGR       56
#define KEY_PAGE_UP     14665
#define KEY_PAGE_DOWN   13137
#define KEY_END         12623
#define KEY_UP          14408
#define KEY_LEFT        13387
#define KEY_RIGHT       13901
#define KEY_DOWN        12880
#define KEY_WINDOW      91
#define KEY_WINDOW2     93

	class Keyboard : public InputDevice {
	public:
		Keyboard();

		virtual bool isReady();
		virtual void read( char &c );
		virtual void isr( const SSID ssid, Registers &registers );

		~Keyboard();
	private:
		KeyBuffer buffer;
		bool enabled;
		uint8_t* currentMap;
		static uint8_t shiftEnabledMap[];
		static uint8_t altgrEnabledMap[];
		static uint8_t shiftDisabledMap[];
	};

#endif
