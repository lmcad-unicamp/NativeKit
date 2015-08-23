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

#include <core.h>
#include <syscalls.h>

void __interrupt_handler( SSID ssid, Registers &registers ) {
	// if ( ssid != 32 && ssid != SSID::LINUX_SYSCALL ){
	// 	System::log( (uint32_t) ssid );
	// 	System::log( '\n' );
	// }

	// while ( ssid <= 17 );
	
	if ( ssid == SSID::LINUX_SYSCALL ) {
		SysCalls::call( registers );
	} else {
		InterruptionListener::call( ssid, registers );
	}
}

void __cxa_pure_virtual() {
	assert( false, "This function cannot be executed!" );
}

void* operator new( const size_t size ) {
	void* ptr = malloc( size );
	assert( ptr != 0, "out of memory" );
	return ptr;
}

void* operator new[]( const size_t size ) {
	void* ptr = malloc( size );
	assert( ptr != 0, "out of memory" );
	return ptr;
}

void operator delete( void *ptr ) {
	assert( ptr != 0 );
	free( ptr );
}

void operator delete[]( void *ptr ) {
	assert( ptr != 0 );
	free( ptr );
}
