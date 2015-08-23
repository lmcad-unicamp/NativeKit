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

#include <storage.h>
#include <stdio.h>

Storage::Storage() : size( &_storage_top - &_storage_base ), buffer((char*) (&_storage_base)), offset(0) {
	
}

Storage::~Storage() {
	flush();
}

bool Storage::flush() {
	return true;
}

bool Storage::isReady() {
	return true;
}

bool Storage::seek( const lba_t lba ) {
	if ( lba >= getNumberOfPages() )
		return false;

	this->offset = lba * STORAGE_PAGE_SIZE;
	return true;
}

bool Storage::shift( const int displacement ) {
	if ( ( this->offset + displacement ) >= getSize() )
		return false;

	this->offset += displacement;
	return true;
}

void Storage::write( const char src ) {
	if ( offset < (size_t) &_storage_top )
		buffer[offset++] = src;
}

size_t Storage::write( const char* src, size_t size ) {
	char* dst = (char*) (((uintptr_t) buffer) + offset );
	char* endOfBlock = dst + size;

	while ( dst < endOfBlock && dst < &_storage_top )
		*dst++ = *src++;

	size_t numberOfBytes = size - (endOfBlock - dst);
	offset += numberOfBytes;
	return numberOfBytes;
}

void Storage::read( char &dst ) {
	if ( offset < (size_t) &_storage_top )
		dst = buffer[offset++];
}

bool Storage::copy( lba_t src, lba_t dst, size_t npages ) {
	char *buffer = new char[STORAGE_PAGE_SIZE];

	if ( !buffer )
		return false;

	for ( size_t i = 0; i < npages; i++ ) {
		seek( src + i );
		read( buffer, STORAGE_PAGE_SIZE );
		seek( dst + i );
		write( buffer, STORAGE_PAGE_SIZE );
	}

	delete[] buffer;
	return true;
}

size_t Storage::read( char* dst, size_t size ) {
	char* src = (char*) (((uintptr_t) buffer) + offset );
	char* endOfBlock = src + size;

	while ( src < endOfBlock && src < &_storage_top )
		*dst++ = *src++;

	size_t numberOfBytes = size - (endOfBlock - src);
	offset += numberOfBytes;
	return numberOfBytes;
}
