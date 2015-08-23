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

#ifndef VIDEO_H
#define VIDEO_H

#include <outputdevice.h>

#define ASCII_NUL 0  // Null char
#define ASCII_SOH 1  // Start of Heading
#define ASCII_STX 2  // Start of Text
#define ASCII_ETX 3  // End of Text
#define ASCII_EOT 4  // End of Transmission
#define ASCII_ENQ 5  // Enquiry
#define ASCII_ACK 6  // Acknowledgment
#define ASCII_BEL 7  // Bell
#define ASCII_BS  8  // Back Space
#define ASCII_TAB 9  // Horizontal Tab
#define ASCII_NL  10 // New Line
#define ASCII_VT  11 // Vertical Tab
#define ASCII_FF  12 // Form Feed
#define ASCII_CR  13 // Carriage Return
#define ASCII_SO  14 // Shift Out / X-On
#define ASCII_SI  15 // Shift In / X-Off
#define ASCII_DLE 16 // Data Line Escape
#define ASCII_DC1 17 // Device Control 1 (oft. XON)
#define ASCII_DC2 18 // Device Control 2
#define ASCII_DC3 19 // Device Control 3 (oft. XOFF)
#define ASCII_DC4 20 // Device Control 4
#define ASCII_NAK 21 // Negative Acknowledgement
#define ASCII_SYN 22 // Synchronous Idle
#define ASCII_ETB 23 // End of Transmit Block
#define ASCII_CAN 24 // Cancel
#define ASCII_EM  25 // End of Medium
#define ASCII_SUB 26 // Substitute
#define ASCII_ESC 27 // Escape
#define ASCII_FS  28 // File Separator
#define ASCII_GS  29 // Group Separator
#define ASCII_RS  30 // Record Separator
#define ASCII_US  31 // Unit Separator
#define ASCII_SP  32 // Unit Separator
#define ASCII_DEL 127 // Delete

#define VIDEO_WIDTH 80
#define VIDEO_HEIGHT 25
#define VIDEO_TBUFFER_PTR 0xB8000
#define VIDEO_DEFAULT_COLOR 0x0F

	class Video : public OutputDevice {
	public:
		enum tColor {
			BLACK,
			DARKBLUE,
			DARKGREEN,
			DARKCYAN,
			DARKRED,
			DARKMAGENTA,
			DARKYELLOW,
			LIGHTGREY,
			DARKGREY,
			BLUE,
			GREEN,
			CYAN,
			RED,
			MAGENTA,
			YELLOW,
			WHITE
		};

	protected:
		struct tVideoData {
			char value;
			char color;
		}__attribute__((__packed__));

	public:
		using OutputDevice::write;
		Video();

		bool isReady();

		/** Clears the screen and moves the cursor to the home position */
		void reset();
		void seek( const uint16_t offset );
		void write( const char value );
		void update();
		void scrollDown();

		inline void setCursorPosition( const uint16_t x, const uint16_t y );
		inline void setBgColor( tColor color );
		inline void setTextColor( const tColor color );

		inline tColor getBgColor() const;
		inline tColor getTextColor() const;
		inline uint16_t getOffset() const;

	private:
		uint8_t color;
		tVideoData* buffer;
		int offset;
	};

	inline uint16_t Video::getOffset() const {
		return this->offset;
	}

	inline Video::tColor Video::getTextColor() const {
		return (tColor) ( this->color & 0xF );
	}

	inline Video::tColor Video::getBgColor() const {
		return (tColor) ( this->color >> 4 );
	}

	inline void Video::setCursorPosition( const uint16_t x, const uint16_t y ) {
		seek( y * VIDEO_WIDTH + x );
	}

	inline void Video::setBgColor( tColor color ) {
		this->color = ( this->color & 0x0F ) | ( ((uint8_t) color) << 4 );
	}

	inline void Video::setTextColor( const tColor color ) {
		this->color = ( this->color & 0xF0 ) | ( (uint8_t) color );
	}

#endif
