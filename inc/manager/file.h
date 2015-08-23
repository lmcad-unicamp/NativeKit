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

#ifndef FILE_H
#define FILE_H

#include <storage.h>
#include <dlinkedlist.h>

typedef int fid_t;

	class File {
		friend class FileTable;
		friend class FileSystem;
		friend class NFSII;
	public:
		File( Storage &storage, lba_t position, int displacement, size_t size, size_t capacity ) :
			storage(storage), position(position), displacement(displacement), offset(0), capacity(capacity),
			size(size), id(-1) {
		}

		inline const lba_t getPosition() const {
			return this->position;
		}

		inline const size_t getSize() const {
			return this->size;
		}

		inline const size_t getOffset() const {
			return this->offset;
		}

		inline const size_t getCapacity() {
			return this->capacity;
		}

		inline const fid_t getID() const {
			return this->id;
		}

		inline void setOffset( const size_t offset ) {
			if ( offset < capacity )
				this->offset = offset;
		}

		inline void clear() {
			this->size   = 0;
			this->offset = 0;
		}

		bool isEOF() {
			return this->offset >= this->size;
		}

		~File() {
			this->id = -1;
		}

	protected:
		inline void setPosition( const lba_t position ) {
			this->position = position;
		}

		inline void setCapacity( size_t capacity ) {
			this->capacity = capacity;
		}

		inline void setID( fid_t id ) {
			this->id = id;
		}

	private:
		Storage &storage;
		lba_t position;
		int displacement;
		size_t offset;
		size_t capacity;
		size_t size;
		fid_t id;
	};

#define FILE_TABLE_DEFAULT_CAPACITY 128

	class FileTable {
	public:
		FileTable( const size_t capacity = FILE_TABLE_DEFAULT_CAPACITY ) : capacity(capacity) {
			keys = new size_t[capacity];

			for ( unsigned int i = 3; i < capacity; i++ )
				keys[i] = 0;

			keys[0] = -1;
			keys[1] = -1;
			keys[2] = -1;
		}

		/**
		 * Normally a program does not open more than 128 files. Therefore, the insert
		 * procedure increments the index of the array, and only start using the free
		 * space when the index is bigger than the size.
		 * */
		fid_t insert( File *file ) {
			static size_t index = 0;
			size_t key;

			if ( files.getSize() >= capacity - 1 || !file || !(key = files.pushf( file )) )
				return -1;

			while ( keys[index] != 0  )
				index = index >= capacity - 1 ? 0 : index + 1;

			file->setID( index );
			keys[index] = key;
			return index;
		}

		File* getFile( const fid_t fid ) {
			 if ( (size_t) fid >= capacity || fid < 0 || keys[fid] == 0 || keys[fid] == (size_t) -1 )
				return 0;

			return files.getElement( keys[fid] );
		}

		File* remove( fid_t fid ) {
			if ( (size_t) fid >= capacity || fid < 0 || keys[fid] == 0 )
				return 0;

			size_t key = keys[fid];
			keys[fid] = 0;
			return files.remove(key);
		}

		inline File* getCurrent() const {
			return files.getCurrent();
		}

		inline size_t getCapacity() const {
			return capacity;
		}

		inline size_t getSize() const {
			return files.getSize();
		}

		~FileTable() {
			while ( files.getSize() > 0 )
				files.popf();

			delete[] keys;
		}
		
	private:
		size_t capacity;
		size_t* keys;
		DLinkedList<File*> files;
	};

#endif

