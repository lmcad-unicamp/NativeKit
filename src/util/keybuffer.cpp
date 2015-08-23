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

#include <keybuffer.h>

uint16_t KeyBuffer::remove() {
	if ( size > 0 ) {
		uint16_t result = buffer[begin];

		if ( begin >= MAX_BUFFER_SIZE - 1 )
			begin = 0;
		else
			begin++;

		size--;

		return result;
	}

	return 0;
}

void KeyBuffer::insert( uint16_t key ) {
	if ( size < MAX_BUFFER_SIZE ) {
		buffer[end] = key;

		if ( end >= MAX_BUFFER_SIZE - 1 )
			end = 0;
		else
			end++;

		size++;
	}
}

bool KeyBuffer::isEmpty() const {
	return ( size == 0 );
}
