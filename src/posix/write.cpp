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

/** Write to a file descriptor. */
void sys_write( System *sys, Registers &registers ) {
	registers.r0 = 0;

	if ( !sys )
		return;

	if ( registers.r1 >= 3 ) {
		FileSystem *fs = sys->getFileSystem();

		if ( fs )
			registers.r0 = fs->write( registers.r1, (const char*) registers.r2, registers.r3 );
	} else {
		OutputDevice* out = 0;

		if ( registers.r1 == 1 ) {
			out = sys->getDefaultOutput();
		} else if ( registers.r1 == 2 ) {
			out = sys->getDefaultError();
		}

		if ( out )
			registers.r0 = out->write( (const char*) registers.r2, registers.r3 );
	}
}
