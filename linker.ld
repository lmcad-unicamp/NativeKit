
/*---------------------------------------------------------------------------*
 * Copyright (C) 2011-2012 Alisson Linhares de Carvalho.                     *
 * All rights reserved.                                                      *
 *                                                                           *
 * This file is part of the neutrino lib.                                    *
 *                                                                           *
 * The neutrino lib is free software: you can redistribute it and/or         *
 * modify it under the terms of the GNU Lesser General Public License as     *
 * published by the Free Software Foundation, either version 3 of the        *
 * License, or (at your option) any later version.                           *
 *                                                                           *
 * The neutrino lib is distributed in the hope that it will be useful,       *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of            *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the             *
 * GNU Lesser General Public License for more details.                       *
 *                                                                           *
 * You should have received a copy of the GNU Lesser General Public License  *
 * along with the neutrino lib. If not, see <http://www.gnu.org/licenses/>.  *
 *---------------------------------------------------------------------------*/

ENTRY(_start)

SECTIONS {
	. = 1M;

	_kernel_base = . ;

	.text : ALIGN(4k) {
		*(.text)
	}=0

	.rodata : ALIGN(4k) {
		*(.rodata)
	}=0

	.data : ALIGN(4k) {
		*(.data)
		*(.bss)
		*(COMMON)

		_stack_base = . ;
		. += 0xFFFF;
		_stack_top  = . ;

		_heap_base  = . ;
		. += 0xFFFF;
		_heap_top   = . ;

		_storage_base = . ;
		*(.diskimg)
		_storage_top = . ;
	}=0

	_kernel_top = . ;

	/DISCARD/ : {
		*(.comment)
		/* *(.eh_frame) */
	}
}
