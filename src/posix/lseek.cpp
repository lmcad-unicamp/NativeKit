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

#include <sys/types.h>
#include <system.h>

/**
 * Repositions the offset of the open file associated with the file
 * descriptor fd to the argument offset.
 * */
void sys_lseek( System *sys, Registers &registers ) {
	FileSystem *fs;
	File* file;

	if ( sys && (fs = (sys->getFileSystem())) && (file = fs->getFile( registers.r1 )) ) {
		size_t offset;

		switch ( registers.r3 ) {
			case SEEK_SET: // The offset is set to offset bytes.
				offset = registers.r2;
				break;
			case SEEK_CUR: // The offset is set to its current location plus offset bytes.
				offset = file->getOffset() + registers.r2;
				break;
			case SEEK_END: // The offset is set to the size of the file plus offset bytes.
				offset = file->getSize() + registers.r2;
				break;
			default: // SEEK_DATA and SEEK_HOLE
				warning( "sys_lseek: unsupported whence value." );
				registers.r0 = (uintr_t) -1;
				return;
		}
		
		if ( fs->seek( registers.r1, offset ) ) {
			registers.r0 = offset;
			return;
		}
	}

	registers.r0 = (uintr_t) -1;
}
