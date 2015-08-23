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

#ifndef OUTPUT_H
#define OUTPUT_H

#include <device.h>

	class OutputDevice : public virtual Device {
	public:
		template <typename T> void writeln( T value, uint8_t base );
		template <typename T> void writeln( T value );

		virtual void write( const char value ) = 0;
		virtual size_t write( const char* buffer, size_t size );
		virtual void reset();

		void write( const char* value );
		void write( const bool value );
		void write( const void* addr, uint8_t base = 10 );
		void write( int8_t   value, uint8_t base = 10 );
		void write( uint8_t  value, uint8_t base = 10 );
		void write( int16_t  value, uint8_t base = 10 );
		void write( uint16_t value, uint8_t base = 10 );
		void write( int32_t  value, uint8_t base = 10 );
		void write( uint32_t value, uint8_t base = 10 );
		void write( int64_t  value, uint8_t base = 10 );
		void write( uint64_t value, uint8_t base = 10 );
		void writeln();
	private:
		
	};

	template <typename T> void OutputDevice::writeln( T value, uint8_t base ) {
		write( value, base );
		writeln();
	}

	template <typename T> void OutputDevice::writeln( T value ) {
		write( value );
		writeln();
	}

#endif

