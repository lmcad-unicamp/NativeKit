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

#include <system.h>

void sys_brk( System *sys, Registers &registers ) {
	static uintptr_t _heap_ptr = (uintptr_t) &_heap_base;

	if ( registers.r1 == 0 ) {
		registers.r0 = _heap_ptr;
	} else if ((registers.r1 < (uintptr_t) &_heap_top) && (registers.r1 >= (uintptr_t) &_heap_base)) {
		_heap_ptr    = registers.r1;
		registers.r0 = 0;
	} else {
		registers.r0 = (uintr_t) -1;
	}
}
