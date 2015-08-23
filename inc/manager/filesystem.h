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

#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dlinkedlist.h>
#include <storage.h>
#include <file.h>

class FileSystem {
	public:
		FileSystem( Storage &storage );

		virtual fid_t open( const char *path ) = 0;
		bool close( fid_t fd );
		bool seek( fid_t fd, const size_t offset );
		size_t write( fid_t fd, const char* src, size_t size );
		size_t read( fid_t fd, char* dst, size_t size );
		bool isOpen( fid_t fd );

		virtual void ls( const char *path ) = 0;
		virtual bool rm( const char *path ) = 0;

		virtual bool mkdir( const char *path, size_t size = 1 ) = 0;
		virtual bool touch( const char *path, size_t size = 1 ) = 0;
		virtual bool expand( fid_t fd, size_t nbytes ) = 0;
		virtual bool flush( fid_t fd );

		virtual void format() = 0;
		virtual lba_t getNumberOfFreePages() const = 0;

		inline Storage& getStorage() const;
		inline File* getFile( fid_t fid );
		virtual ~FileSystem();

	protected:
		Storage &storage;
		FileTable files;
};

inline Storage& FileSystem::getStorage() const {
	return storage;
}

inline File* FileSystem::getFile( fid_t fid ){
	return files.getFile( fid );
}

#endif
