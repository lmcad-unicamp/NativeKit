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

#ifndef ARCH_H
#define ARCH_H

#include <stdint.h>
#include <registers.h>
#include <types.h>

#define NUMBER_OF_ISR 129

	enum SSID {
		DIVIDE_ERROR = 0,
		DEBUG_EXCEPTIONS = 1,
		NONMASKABLE_INTERRUPT_EXCEPTION = 2,
		BREAKPOINT_EXCEPTION = 3,
		OVERFLOW_EXCEPTION = 4,
		BOUNDS_CHECK_EXCEPTION = 5,
		INVALID_OPCODE_EXCEPTION = 6,
		COPROCESSOR_NOT_AVAILABLE_EXCEPTION = 7,
		DOUBLE_FAULT_EXCEPTION = 8,
		COPROCESSOR_SEGMENT_OVERRUN_EXCEPTION = 9,
		INVALID_TSS_EXCEPTION = 10,
		SEGMENT_NOT_PRESENT = 11,
		STACK_EXCEPTION = 12,
		GENERAL_PROTECTION_EXCEPTION = 13,
		PAGE_FAULT_EXCEPTION = 14,
		COPROCESSOR_ERROR = 16,
		ALIGNMENT_CHECK = 17,
		MACHINE_CHECK = 18,
		SYSTEM_TIMER = 32,
		KEYBOARD = 33,
		SERIAL_0 = 35,
		SERIAL_1 = 36,
		LPT_2 = 37,
		FLOPPY_DISK_DRIVE = 38,
		LPT_1 = 39,
		CMOS_REAL_TIMER = 40,
		MOUSE = 44,
		NUMERIC_COPROCESSOR = 45,
		HARD_DISK_DRIVE_M = 46,
		HARD_DISK_DRIVE_S = 47,
		NEUTRINO_SYSCALL = 49,
		LINUX_SYSCALL = 128,
		INVALID = 129
	};

	extern "C" tMultibootHeader _multiboot;
	extern "C" char _kernel_base;
	extern "C" char _kernel_top;
	extern "C" char _stack_base;
	extern "C" char _stack_top;
	extern "C" char _heap_base;
	extern "C" char _heap_top;
	extern "C" char _storage_base;
	extern "C" char _storage_top;

	extern "C" void _reboot();
	extern "C" void _sstate( void* buffer );
	extern "C" void _lstate( void* buffer );
	extern "C" bool _pdupdate( void* pDir, uintptr_t vAddr, uintptr_t pAddr, uint8_t permission, size_t size = 1 );
	extern "C" void _pdprotect( void* pDir, void* vAddr, uint8_t permission, size_t size = 1 );
	extern "C" void _pdcreate( void* vAddr );
	extern "C" void _pdload( void* pDir );
	extern "C" void _pdsave( void* &pDir );
	extern "C" void _ptcreate( void* pTable, void* pDir, uintptr_t base );
	extern "C" void _callBIOSSubRotine( int number, Registers& registers );

#endif
