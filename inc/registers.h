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

#ifndef REGISTERS_H
#define REGISTERS_H

#include <debug.h>

	typedef uint32_t uintr_t;

	struct Registers {
		uintr_t r5; // EDI
		uintr_t r6; // ESI
		uintr_t r4; // EBP
		uintr_t sp; // ESP
		uintr_t r1; // EBX
		uintr_t r3; // EDX
		uintr_t r2; // ECX
		uintr_t r0; // EAX
		uintr_t pc; // EIP

		Registers() {
			clear();
		}

		void clear() {
			r6 = r5 = r4 = r3 = r2 = r1 = r0 = pc = sp = 0;
		}

		void copy( Registers &registers ) {
			this->r6 = registers.r6;
			this->r5 = registers.r5;
			this->r4 = registers.r4;
			this->r3 = registers.r3;
			this->r2 = registers.r2;
			this->r1 = registers.r1;
			this->r0 = registers.r0;
			this->sp = registers.sp;
			this->pc = registers.pc;
		}
	} __attribute__((packed));

#endif

