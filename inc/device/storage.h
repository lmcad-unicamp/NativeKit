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

#ifndef STORAGE_H
#define STORAGE_H

#include <iodevice.h>

#define STORAGE_PAGE_SIZE 4096

typedef uint64_t lba_t;

	class Storage : public IODevice {
		public:
			using OutputDevice::write;
		public:
			Storage();

			bool copy( lba_t src, lba_t dst, size_t npages );

			inline const size_t getSize() const;
			inline const size_t getNumberOfPages() const;
			inline const size_t getOffset() const;

			virtual bool flush();
			virtual bool seek( const lba_t lba );
			virtual bool shift( const int displacement );
			virtual void write( const char src );
			virtual size_t write( const char* src, size_t size );
			virtual void read( char &dst );
			virtual size_t read( char* dst, size_t size );
			virtual bool isReady();

			virtual ~Storage();
		protected:
			size_t size;
			char *buffer;
			size_t offset;
	};

	inline const size_t Storage::getSize() const {
		return size;
	}

	inline const size_t Storage::getNumberOfPages() const {
		return (size / STORAGE_PAGE_SIZE);
	}

	inline const size_t Storage::getOffset() const {
		return offset;
	}

#endif
