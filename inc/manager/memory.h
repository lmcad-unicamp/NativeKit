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

#ifndef MEMORY_H
#define MEMORY_H

#include <manager.h>
#include <stdio.h>

#define MEMORY_MMAP_SIZE 20 /**< Size of the memory map returned by the grub. */
#define MEMORY_PAGE_SIZE 4096 /**< Default memory page size. */
#define MEMORY_HIGH_MEMORY_PTR 0x100000 /**< High memory base addr. */
#define MEMORY_MINIMUM_REQUIREMENT MEMORY_PAGE_SIZE * 10 /**< Minimum memory requirement. */

	class Memory : public Manager {
	private:
		struct tBlock {
			tBlock* next;
			size_t size;
		};

	public:
		Memory();

		inline size_t getSize() const;
		inline size_t getFreeSize() const;
		inline size_t getReservedSize() const;
		inline uintptr_t align( uintptr_t addr ) const;

		void print();
		uintptr_t allocate( size_t numberOfPages = 1 );
		bool deallocate( uintptr_t addr = 0, size_t numberOfPages = 1 );

	protected:
		tBlock* newMemoryBlock( uintptr_t addr, size_t size );

	private:
		size_t size;
		size_t freeSize;
		size_t reservedSize;
		tBlock* blockList;
	};

	size_t Memory::getSize() const {
		return size;
	}

	size_t Memory::getFreeSize() const {
		return freeSize;
	}

	size_t Memory::getReservedSize() const {
		return reservedSize;
	}

	uintptr_t Memory::align( uintptr_t addr ) const {
		return addr - ( addr & ( MEMORY_PAGE_SIZE - 1 ));
	}

#endif
