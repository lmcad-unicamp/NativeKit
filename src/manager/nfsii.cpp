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

#include <nfsii.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

NFSII::NFSII( Storage &storage ) : FileSystem(storage) {
	storage.seek( NFS_ROOT_NODE_LBA );
	storage.read( (char*) &bootNode, sizeof(bootNode) );

	if ( bootNode.signature != NFS_SIGNATURE )
		format();

	currentDirectory = bootNode.directory;
}

size_t toStoragePageSize( size_t nbytes ) {
	size_t nPages = nbytes / STORAGE_PAGE_SIZE;

	if( nbytes & ( STORAGE_PAGE_SIZE - 1 ) )
		nPages++;

	return nPages;
}

bool NFSII::expand( fid_t fd, size_t nbytes ) {
	if ( flush( fd ) ) {
		File *file = files.getFile( fd );

		tNode node;
		storage.seek( file->getPosition() );
		storage.read( (char*) &node, sizeof(node) );

		if ( expandNode( node, nbytes ) ) {
			file->setCapacity( node.capacity - sizeof(node) );
			file->setPosition( node.addr );
			file->setPosition( node.addr );
			return true;
		}
	}

	return false;
}

bool NFSII::expandNode( tNode &node, size_t nbytes ) {
	lba_t dst;
	size_t srcSize, dstSize;

	if ( !node.isValid() || node.numberOfChildren > 0 )
		return false;

	srcSize = toStoragePageSize( node.capacity );
	dstSize = srcSize + toStoragePageSize(nbytes);

	if ( !(dst = allocate( dstSize )) )
		return false;

	if ( storage.copy( node.addr, dst, srcSize ) && deleteNode( node ) ) {
		tNode parent;
		storage.seek( node.parent );
		storage.read( (char*) &parent, sizeof(parent) );

		node.addr     = dst;
		node.capacity = dstSize * STORAGE_PAGE_SIZE;
		return insertNodeAt( node, parent );
	}

	deallocate( dst, dstSize );
	return true;
}

bool NFSII::insertNodeAt( tNode& node, tNode& directory ) {
	if ( !directory.isValid() || directory.type != FS_DIRECTORY )
		return false;

	if ( directory.size + sizeof(tSubNode) >= directory.capacity && !expandNode( directory, STORAGE_PAGE_SIZE ) )
		return false;

	tSubNode child( node.name, node.addr );

	// update directory
	directory.size += sizeof(child);
	directory.numberOfChildren++;
	node.parent = directory.addr;

	// save node at storage
	storage.seek( node.addr );
	storage.write( (char*) &node, sizeof(node) );

	// inserting node at directory
	storage.seek( directory.addr );
	storage.write( (char*) &directory, sizeof(directory) );
	storage.shift( directory.size -  sizeof(directory) - sizeof(child) );
	storage.write( (char*) &child, sizeof(child) );
	return true;
}

bool NFSII::deleteNode( tNode &node ) {
	tNode directory;
	tSubNode child;

	// can't remove a node if it has children.
	if ( !node.isValid() || node.addr == bootNode.directory || node.numberOfChildren > 0 )
		return false;

	// loading parent directory
	storage.seek( node.parent );
	storage.read( (char*) &directory, sizeof( directory ) );

	if ( !directory.isValid() || !directory.type == FS_DIRECTORY )
		return false;

	for( int i = directory.numberOfChildren; i > 0; i-- ) {
		storage.read( (char*) &child, sizeof(child) );

		// searching for the node. (sequential search).
		// TODO create a dictionary index to improve the performance.
		if ( strcmp( child.name, node.name ) == 0 ) {
			if ( !deallocate( node.addr, toStoragePageSize( node.capacity ) ) )
				return false;

			directory.numberOfChildren--;
			directory.size -= sizeof(child);

			// move the lest element to current position
			storage.seek( directory.addr );
			storage.write( (char*) &directory, sizeof(directory) );
			storage.shift( directory.numberOfChildren * sizeof(child) );
			storage.read( (char*) &child, sizeof(child) );
			
			storage.shift( -i * sizeof(child) );
			storage.write( (char*) &child, sizeof(child) );
			return true;
		}
	}

	return false;
}

bool NFSII::rm( const char *path ) {
	if ( !path )
		return false;

	tNode node;
	storage.seek( currentDirectory );
	storage.read( (char*) &node, sizeof(node) );

	const char* name = decode( path, node );

	if( ( *name == 0 ) && node.isValid() )
		return deleteNode( node );
		
	return false;
}

lba_t NFSII::findNodeAt( const char *name, tNode& directory ) {
	tSubNode child;

	if ( !name || !directory.isValid() || directory.type != FS_DIRECTORY )
		return 0;

	if ( name[0] == 0 || ( name[0] == '.' && name[1] == 0 ) ) {
		return directory.addr;
	} else if ( name[0] == '.' && name[1] == '.' && name[2] == 0 ) {
		return directory.parent;
	} else if ( name[0] == '/' && name[1] == 0 ) {
		return bootNode.directory;
	}

	storage.seek( directory.addr );
	storage.shift( sizeof(directory) );

	// searching for the node. (sequential search).
	// TODO create a dictionary index to improve the performance.
	for ( size_t n = directory.numberOfChildren; n > 0; n-- ) {
		storage.read( (char*) &child, sizeof(child) );

		// checking if the node name is equal to the name present in the path.
		if ( strcmp( child.name, name ) == 0 )
			return child.addr;
	}

	return 0;
}

const char* NFSII::decode( const char *path, tNode &current ) {
	char name[NFS_NAME_LENGTH];
	lba_t position;

	if ( !path || *path == 0 )
		return path;

	if ( *path == '/' ) {
		storage.seek( bootNode.directory );
		storage.read( (char*) &current, sizeof(current) );
	}

	// searching for a node.
	do {
		if ( *path == '/' )
			path++;

		if( *path == 0 )
			return path;

		const char* currentPathPosition = path;

		for ( int i = 0; i < NFS_NAME_LENGTH - 1; i++ ) {
			if ( *path == '/' || *path == 0 ) {
				name[i] = 0;
				break;
			}

			name[i] = *path++;
		}

		if ( !(position = findNodeAt( name, current )) )
			return currentPathPosition;

		storage.seek( position );
		storage.read( (char*) &current, sizeof(current) );
	} while ( true );
}

bool NFSII::isAValidFileName( const char *name ) {
	if ( !name || *name == 0 )
		return false;

	for ( int i = 0; i < NFS_NAME_LENGTH - 1; i++ ) {
		if ( *name == '/' )
			return false;
		else if ( *name == 0 )
			return true;

		name++;
	}
	
	return false;
}

size_t NFSII::createNode( const char *path, size_t size, NodeType type ) {
	if ( !path || !size )
		return 0;

	tNode current;
	storage.seek( currentDirectory );
	storage.read( (char*) &current, sizeof(current) );

	const char* name = decode( path, current );

	if( isAValidFileName(name) && current.isValid() && current.type == FS_DIRECTORY ) {
		tNode node( name, allocate(size), current.addr, type, size * STORAGE_PAGE_SIZE );

		if ( insertNodeAt( node, current ) )
			return node.addr;
		else
			deallocate( node.addr, size );
	}

	return 0;
}

bool NFSII::flush( fid_t fd ) {
	File *file = files.getFile( fd );

	if ( !file )
		return false;

	tNode node;
	storage.seek( file->getPosition() );
	storage.read( (char*) &node, sizeof(tNode) );

	if ( !node.isValid() || (node.addr != file->getPosition()) )
		return false;

	// Only the size matters for now.
	node.size = file->getSize() + sizeof(node);

	// update disk file information.
	storage.seek( node.addr );
	storage.write( (char*) &node, sizeof(node ) );
	return storage.flush();
}

fid_t NFSII::open( const char *path ) {
	if ( !path )
		return -1;

	tNode node;
	storage.seek( currentDirectory );
	storage.read( (char*) &node, sizeof(node) );

	if( *decode( path, node ) == 0 && node.isValid() )
		return files.insert( new File( storage, node.addr, sizeof(tNode), node.size - sizeof(tNode), node.capacity - sizeof(tNode) ) );

	return -1;
}

bool NFSII::mkdir( const char *path, size_t size ) {
	return createNode( path, size, FS_DIRECTORY );
}

bool NFSII::touch( const char *path, size_t size ) {
	return createNode( path, size, FS_FILE );
}

void NFSII::ls( const char *path ) {
	tSubNode child;
	fid_t fd = open( path );

	if ( fd > 0 ) {
		printf( "path: %s;\n", path );
		seek( fd, 0 );

		while( read( fd, (char*) &child, sizeof(child) ) > 0 )
			printf( "   > %s (%llu)\n", child.name, child.addr );
	}

	close( fd );
}

void NFSII::format() {
	// initializing the root node;
	bootNode = tBootNode( NFS_DIRECTORY_LBA, NFS_FREE_NODE_LBA, storage.getNumberOfPages()- 2, storage.getNumberOfPages());
	storage.seek( NFS_ROOT_NODE_LBA );
	storage.write( (char*) &bootNode, sizeof(bootNode) );
	
	// creating a list of freeSize blocks
	tStorageBlock block( 0, bootNode.freeSize );
	storage.seek( NFS_FREE_NODE_LBA );
	storage.write( (char*) &block, sizeof(block) );

	// initializing the first directory.
	tNode directory( "/", NFS_DIRECTORY_LBA, NFS_DIRECTORY_LBA, NodeType::FS_DIRECTORY, STORAGE_PAGE_SIZE );
	storage.seek( NFS_DIRECTORY_LBA );
	storage.write( (char*) &directory, sizeof(directory) );
}

bool NFSII::deallocate( lba_t blockAddr, size_t numberOfPages ) {
	if ( numberOfPages == 0 || blockAddr == 0 )
		return false;

	tStorageBlock newBlock( 0, numberOfPages );

	if ( bootNode.freeSize == 0 ) {
		bootNode.block0 = blockAddr;
	} else {
		tStorageBlock currentBlock;
		lba_t clba = bootNode.block0;
		lba_t plba = 0;

		do {
			storage.seek( clba );
			storage.read( (char*) &currentBlock, sizeof( currentBlock ) );

			if ( blockAddr < clba )
				break;

			plba = clba;
			clba = currentBlock.next;
		} while( clba > 0 );

		if ( clba ) {
			if ( blockAddr + numberOfPages == clba ) {
				newBlock.next  = currentBlock.next;
				newBlock.size += currentBlock.size;
			} else if( blockAddr + numberOfPages < clba ) {
				newBlock.next  = clba;
			} else
				return false; // invalid operation
		}

		if ( plba ) {
			storage.seek( plba );
			storage.read( (char*) &currentBlock, sizeof( currentBlock ) );

			if ( plba + currentBlock.size == blockAddr ) {
				newBlock.size += currentBlock.size;
				blockAddr = plba;
			} else if( plba + currentBlock.size < blockAddr ) {
				currentBlock.next = blockAddr;
				storage.seek( plba );
				storage.write( (char*) &currentBlock, sizeof( currentBlock ) );
			} else
				return false; // invalid operation

		} else if( bootNode.block0 > blockAddr ) {
			bootNode.block0 = blockAddr;
		} else {
			return false;
		}
	}

	bootNode.freeSize += numberOfPages;
	storage.seek( blockAddr );
	storage.write( (char*) &newBlock, sizeof( newBlock ) );
	storage.seek( NFS_ROOT_NODE_LBA );
	storage.write( (char*) &bootNode, sizeof(bootNode) );
	return true;
}

lba_t NFSII::allocate( size_t numberOfPages ) {
	// checking if we have enough memory.
	if ( bootNode.freeSize < numberOfPages || numberOfPages == 0 )
		return 0;

	tStorageBlock block;
	lba_t clba = bootNode.block0;
	lba_t plba = 0;

	// searching for the first freeSize block.
	storage.seek( clba );
	storage.read( (char*) &block, sizeof(block) );

	while ( block.size < numberOfPages ) {
		plba = clba;
		clba = block.next;

		if( clba == 0 )
			return 0;

		storage.seek( clba );
		storage.read( (char*) &block, sizeof(block) );
	}

	lba_t result = clba;

	if ( block.size == numberOfPages ) {
		clba = block.next;

		if ( plba ) {
			storage.seek( plba );
			storage.read( (char*) &block, sizeof(block) );

			block.next = clba;

			storage.shift( -sizeof(tStorageBlock) );
			storage.write( (char*) &block, sizeof(block) );
		} else {
			bootNode.block0 = clba;
		}

	} else {
		block.size -= numberOfPages;
		result += block.size;
		storage.seek( clba );
		storage.write( (char*) &block, sizeof(block) );
	}

	bootNode.freeSize -= numberOfPages;

	storage.seek( NFS_ROOT_NODE_LBA );
	storage.write( (char*) &bootNode, sizeof(bootNode) );
	return result;
}

lba_t NFSII::getNumberOfFreePages() const {
	return bootNode.freeSize;
}

NFSII::~NFSII() {

}
