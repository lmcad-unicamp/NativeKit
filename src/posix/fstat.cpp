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
#include <sys/stat.h>
#include <sys/types.h>

/*
 * Obtain information about the named file and write it to the area
 * pointed to by the buf argument.
 * */
void sys_fstat( System *sys, Registers &registers ) {
	FileSystem* fs = sys->getFileSystem();

	if (( registers.r2 == 0 ) || ( fs == 0 )) {
		registers.r0 = -1;
		return;
	}
	
	File* file = fs->getFile( (fid_t) registers.r1 );

	if ( file ) {
		struct stat* st = ((struct stat*) (registers.r2));
		st->st_blksize = 0;

		st->st_dev = 0;
		st->st_ino = 0;
		st->st_mode = S_IFCHR;
		st->st_nlink = 0;
		st->st_uid = 0;
		st->st_gid = 0;
		st->st_rdev = 0;
		st->st_size = file->getSize();
		st->st_blksize = 4096;
		st->st_blocks  = st->st_size / 512;
		st->st_atime = 300;
		st->st_mtime = 300;
		st->st_ctime = 0;

		registers.r0 = 0;
	} else {
		registers.r0 = -1;
	}
}
