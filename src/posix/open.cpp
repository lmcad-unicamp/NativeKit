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
#include <sys/types.h>

/** Open a file descriptor. */
void sys_open( System *sys, Registers &registers ) {
	FileSystem *fs;

	if ( !sys || !(fs = sys->getFileSystem()) ) {
		registers.r0 = -1;
		return;
	}

	if ( registers.r2 & O_CREAT ) {
		if ( !fs->touch( (const char*) registers.r1 ) && ( registers.r2 & O_EXCL ) ) {
			registers.r0 = -1;
			return;
		}
	}

	registers.r0 = fs->open( (const char*) registers.r1 );
}
