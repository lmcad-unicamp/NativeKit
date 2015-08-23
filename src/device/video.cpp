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

#include <video.h>

Video::Video() : color( VIDEO_DEFAULT_COLOR ), buffer( (tVideoData*)
		VIDEO_TBUFFER_PTR ), offset(0) {
}

void Video::write( const char value ) {
	if ( value == ASCII_NL ) {
		offset += VIDEO_WIDTH - ( offset % VIDEO_WIDTH );
	} else if ( value == ASCII_TAB ) {
		offset += 3;
	} else if ( value == ASCII_BS ) {
		offset--;
	} else if ( (uint8_t) value > 31 ) {
		buffer[offset].color = this->color;
		buffer[offset].value = value;
		offset++;
	}

	update();
}

void Video::reset() {
	tVideoData element;
	tVideoData* bufferPtr = buffer;
	tVideoData* endPtr    = buffer + VIDEO_WIDTH * VIDEO_HEIGHT;

	element.color = color;
	element.value = ' ';

	do {
		*bufferPtr = element;
	} while ( ++bufferPtr < endPtr );

	offset = 0;
	update();
}

void Video::scrollDown() {
	if ( this->offset < VIDEO_WIDTH )
		return;

	uint16_t* dest    = ((uint16_t*) buffer);
	uint16_t* src     = dest + VIDEO_WIDTH;
	uint16_t* endPtr  = dest + VIDEO_WIDTH * VIDEO_HEIGHT;
	uint16_t value    = ' ' | this->color << 8;

	while( src < endPtr )
		*(dest++) = *(src++);

	while( dest < endPtr )
		*(dest++) = value;

	this->offset -= VIDEO_WIDTH;
}

bool Video::isReady() {
	return true;
}

void Video::update() {
	if( offset >= (VIDEO_WIDTH * VIDEO_HEIGHT ) )
		scrollDown();

	outb( 0x3D4, 0x0F );
	outb( 0x3D5, offset & 0xFF );
	outb( 0x3D4, 0x0E );
	outb( 0x3D5, (offset >> 8) & 0xFF);
}

void Video::seek( const uint16_t offset ) {
	if( offset < VIDEO_WIDTH * VIDEO_HEIGHT ) {
		this->offset = offset;
		update();
	}
}
