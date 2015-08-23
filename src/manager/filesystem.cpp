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

#include <filesystem.h>
#include <stdio.h>

FileSystem::FileSystem( Storage &storage ) : storage( storage ) {

}

bool FileSystem::isOpen( fid_t fd ) {
	return files.getFile(fd) != 0;
}

bool FileSystem::seek( fid_t fd, const size_t offset ) {
	File* file = files.getFile( fd );

	if ( !file || ( offset > file->getCapacity() && !expand( fd, offset - file->getCapacity() ) ))
		return false;

	file->setOffset( offset );
	return true;
}

size_t FileSystem::write( fid_t fd, const char* src, size_t size ) {
	File* file = files.getFile( fd );

	if ( file ) {
		Storage &storage = file->storage;
		size_t offset = file->offset + size;

		if ( offset > file->capacity && !expand( fd, offset - file->capacity ) )
			return 0;

		if ( storage.seek( file->position ) && storage.shift( file->displacement + file->offset ) ) {
			size_t nbytes = storage.write( src, size );
			file->offset += nbytes;

			if ( file->offset > file->size )
				file->size = file->offset;

			return nbytes;
		}
	}

	return 0;
}

size_t FileSystem::read( fid_t fd, char* dst, size_t size ) {
	File* file = files.getFile( fd );

	if ( file && !file->isEOF() ) {
		Storage &storage = file->storage;
		size_t max = file->offset + size;

		if ( max > file->size )
			size -= max - file->size;

		if ( storage.seek( file->position ) && storage.shift( file->displacement + file->offset ) ) {
			size_t nbytes = storage.read( dst, size );
			file->offset += nbytes;
			return nbytes;
		}
	}

	return 0;
}

bool FileSystem::flush( fid_t fd ) {
	return true;
}

bool FileSystem::close( fid_t fd ) {
	File* file = files.getFile( fd );

	if ( file && flush( fd ) && files.remove( fd ) ) {
		delete file;
		return true;
	}

	return false;
}

FileSystem::~FileSystem() {
	while ( files.getSize() ) {
		File* file = files.getCurrent();
		flush( file->getID() );
		files.remove( file->getID() );
		delete file;
	}
}
