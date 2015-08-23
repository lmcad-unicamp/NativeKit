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

#ifndef DEVICE_H
#define DEVICE_H

#include <ilistener.h>

	class Device : public InterruptionListener {
	public:
		virtual void isr( const SSID ssid, Registers &registers );
		virtual bool isReady() = 0;

	protected:
		inline void outb( uint16_t port, uint8_t value ) const;
		inline void outw( uint16_t port, uint16_t value ) const;
		inline uint8_t inb( uint16_t port ) const;
	};

	void Device::outb( uint16_t port, uint8_t value ) const {
		__asm__ __volatile__( ".intel_syntax noprefix\n OUT DX,AL\n .att_syntax\n" : : "d"(port), "a"(value) : );
	}

	void Device::outw( uint16_t port, uint16_t value ) const {
		__asm__ __volatile__( ".intel_syntax noprefix\n OUT DX,AX\n .att_syntax\n" : : "d"(port), "a"(value) : );
	}

	uint8_t Device::inb( uint16_t port ) const {
		uint8_t ret;
		asm volatile ( "inb %1, %0" : "=a"(ret) : "Nd"(port) );
		return ret;
	}

#endif

