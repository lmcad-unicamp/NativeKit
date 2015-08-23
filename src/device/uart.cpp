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

#include <uart.h>

UART::UART( const uint16_t port = COM1 ) : port( port ) {
	assert( port == COM1 || port == COM2 || port == COM3 || port == COM4 );

	outb( port + 1, 0x00 );
	outb( port + 3, 0x80 );
	outb( port + 0, 0x03 );
	outb( port + 1, 0x00 );
	outb( port + 3, 0x03 );
	outb( port + 2, 0xC7 );
	outb( port + 4, 0x0B );

	if ( port == COM1 || port == COM2 )
		this->startListening( SSID::SERIAL_0 );
	else
		this->startListening( SSID::SERIAL_1 );
}

void UART::isr( const SSID ssid, Registers &registers ) {
	warning("uart interruption");
}

bool UART::isReady() {
	return (inb( port + 5 ) & 1);
}

void UART::write( const char value ) {
	while ( !(inb( port + 5 ) & 0x20) );

	outb( port, value );
}

void UART::read( char &c ) {
	while ( !(inb( port + 5 ) & 1));

	c = inb( port );
}

UART::~UART() {
	if ( port == COM1 || port == COM2 )
		this->stopListening( SSID::SERIAL_0 );
	else
		this->stopListening( SSID::SERIAL_1 );
}
