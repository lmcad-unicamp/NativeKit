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

#include <outputdevice.h>

void OutputDevice::write( const char* str ) {
	while ( *str != '\0' )
		write( *(str++) );
}

size_t OutputDevice::write( const char* buffer, size_t size ) {
	size_t len;

	for ( len = 0; len < size; len++ )
		write( buffer[len] );

	return len;
}

void OutputDevice::reset() {

}

void OutputDevice::write( const char value ) {
	write( value );
}

void OutputDevice::writeln() {
	write( '\n' );
}

void OutputDevice::write( const void* addr, uint8_t base ) {
	write( (uintptr_t) addr, base );
}

void OutputDevice::write( const bool value ) {
	if( value )
		write("true\0");
	else
		write("false\0");
}

void OutputDevice::write( int8_t value, uint8_t base ) {
	write( ( int64_t) value, base );
}

void OutputDevice::write( uint8_t value, uint8_t base ) {
	write( ( uint64_t) value, base );
}

void OutputDevice::write( int16_t value, uint8_t base ) {
	write( ( int64_t) value, base );
}

void OutputDevice::write( uint16_t value, uint8_t base ) {
	write( ( uint64_t) value, base );
}

void OutputDevice::write( int32_t value, uint8_t base ) {
	write( ( int64_t) value, base );
}

void OutputDevice::write( uint32_t value, uint8_t base ) {
	write( ( uint64_t) value, base );
}

void OutputDevice::write( uint64_t value, uint8_t base ) {
	static const char* hash = "0123456789ABCDEF";
	static char buffer[65] = {0}; // Max buffer size 64bits;
	char *stack = buffer + 64;

	if ( base <= 1 || base > 16 )
		base = 10;

	do {
		*(--stack) = hash[value % base];
		value /= base;
	} while ( value > 0 );

	write( stack );
}

void OutputDevice::write( int64_t value, uint8_t base ) {
	if( value < 0 ) {
		write( '-' );
		write( (uint64_t) -value, base );
	} else
		write( (uint64_t) value, base );
}
