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

#include <memory.h>

Memory::Memory() : size(0), freeSize(0), reservedSize(0), blockList(0) {
	tBlock* lastBlock = 0;
	const tMultibootInfo *mbi = _multiboot.mbInfo;

	// Inicializando o sistema de memória.
	for ( tMemoryMap* mmap = mbi->mmapPtr; mmap < mbi->mmapPtr + mbi->mmapLength; mmap++ ) {
		// Verificando se o tamanho da entrada no mapa é válida.
		if ( mmap->size != MEMORY_MMAP_SIZE )
			break;

		this->size += mmap->len;

		// Verifica se a entrada pode ser usada pelo sistema.
		if ( mmap->type == MULTIBOOT_MEMORY_AVAILABLE && mmap->addr >= MEMORY_HIGH_MEMORY_PTR ) {
			tBlock *block = newMemoryBlock( (uintptr_t) mmap->addr, (size_t) mmap->len );

			if ( block ) {
				if ( !this->blockList )
					this->blockList = block;
				else
					lastBlock->next = block;

				lastBlock = block;

				this->freeSize += block->size * MEMORY_PAGE_SIZE;
			}
		}
	}

	// Tamanho da memória retornada pelo grub.
	this->reservedSize = this->size - this->freeSize;
}

uintptr_t Memory::allocate( size_t numberOfPages ) {
	// Verifica se o valor passado em numberOfPages é valido. ( n > 0 );
	if ( (freeSize / MEMORY_PAGE_SIZE) < numberOfPages || numberOfPages == 0 )
		return 0;

	tBlock *previus = 0;
	tBlock *current = blockList;

	// Procura pelo primeiro bloco de páginas livre;
	// O Bloco livre, será em 99% das chamadas feitas pelo kernel, o primeiro elemento da lista.
	while ( current->size <= numberOfPages ) {
		previus = current;
		current = current->next;

		// Se chegar ao final da lista de blocos retorna 0.
		if ( !current )
			return 0;
	}

	// Salvando o endereço do bloco de páginas que será retornado;
	uintptr_t addr = (uintptr_t) current;

	// Total de bytes que será removido.
	size_t totalBytes = numberOfPages * MEMORY_PAGE_SIZE;

	// Configurando os ponteiros de blockList;
	if ( current->size == numberOfPages ) {
		// Verifica se existe um bloco anterior ao bloco que será removido.
		if ( previus )
			previus->next = current->next;
		else
			blockList = current->next;

	} else {
		// Devemos reconfigurar o tamanho, pois ainda temos páginas nesse bloco.
		current->size -= numberOfPages;
		addr += current->size * MEMORY_PAGE_SIZE;
	}

	freeSize -= totalBytes;
	return addr;
}

bool Memory::deallocate( uintptr_t addr, size_t numberOfPages ) {
	// Verifica se o valor passado em numberOfPages é valido. ( n > 0 );
	if ( numberOfPages == 0 || addr == 0 )
		return false;

	tBlock *blockPtr = (tBlock*) addr;
	blockPtr->next = 0;
	blockPtr->size = numberOfPages;

	// Total de bytes que será inserido.
	size_t totalBytes = numberOfPages * MEMORY_PAGE_SIZE;

	if ( !blockList ) {
		// Se a block list está vazia, a blockList aponta para o novo bloco.
		blockList = blockPtr;
	} else {
		tBlock* current = blockList;
		tBlock* previus = 0;

		// Se a block list não estiver vazia, temos que procurar o local
		// onde o bloco será inserido.
		while ( ((uintptr_t) current < (uintptr_t) addr ) && current ) {
			previus = current;
			current = current->next;
		}

		if ( current ) {
			if ( ( (uintptr_t) addr + totalBytes ) == (uintptr_t) current ) {
				blockPtr->next = current->next;
				blockPtr->size += current->size;
			} else {
				blockPtr->next = current;
			}
		}

		if ( previus ) {
			// Se não existir páginas entre o bloco anterior e o bloco que
			// sera inserido, atualizamos o total de páginas do bloco anterior.
			if ( ((( uintptr_t ) previus ) + previus->size * MEMORY_PAGE_SIZE ) == (uintptr_t) addr ) {
				previus->size += blockPtr->size;
				previus->next = blockPtr->next;
			} else {
				// Se existir um espaço entre os blocos, inserimos o bloco
				// de página na lista;
				previus->next = blockPtr;
			}
		} else {
			blockList = blockPtr;
		}
	}

	freeSize += totalBytes;
	return true;
}

void Memory::print() {
	printf( "Memory size: %lu;\n", this->size );
	printf( "Memory free: %lu;\n", this->freeSize );
	printf( "Memory reserved: %lu;\n", this->reservedSize );

	if ( !blockList ) {
		printf( "[U: %lu]\n", this->size / MEMORY_PAGE_SIZE );
		return;
	}

	tBlock* current = blockList;

	do {
		printf( "[F: %lu]", current->size );

		if( current->next == 0 )
			break;

		printf( "[U: %lu]", ((uintptr_t) current->next - (uintptr_t) current ) / MEMORY_PAGE_SIZE - current->size );
		current = current->next;
	} while ( true );

	printf("\n");
}

Memory::tBlock* Memory::newMemoryBlock( uintptr_t addr, size_t size ) {
	if ( addr >= (uintptr_t) &_kernel_base && addr <= (uintptr_t) &_kernel_top ) {
		uintptr_t reserved = addr + size;

		if ( reserved < (uintptr_t) &_kernel_top )
			return 0;

		addr = (uintptr_t) &_kernel_top ;
		size = reserved - (uintptr_t) &_kernel_top;
	}

	// Arredondado addr para primeiro múltiplo de MEMORY_PAGE_SIZE
	uintptr_t base = align( addr + MEMORY_PAGE_SIZE - 1 );
	size = align( size - ( base - addr ) );

	// Verifica se o tamanho, após o arredondamento, continua válido.
	if ( size < MEMORY_PAGE_SIZE  )
		return 0;

	tBlock* newBlock  = (tBlock *) base;
	newBlock->size = size / MEMORY_PAGE_SIZE;
	newBlock->next = 0;
	return newBlock;
}
