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

#ifndef NFSII_H
#define NFSII_H

#include <filesystem.h>

#define NFS_SIGNATURE 0x32464e21
#define NFS_NAME_LENGTH 24
#define NFS_ROOT_NODE_LBA 0
#define NFS_DIRECTORY_LBA 1
#define NFS_FREE_NODE_LBA 2

	class NFSII : public FileSystem {
		public:
			enum NodeType {
				FS_FREE,
				FS_DIRECTORY,
				FS_FILE,
				FS_INFO,
				FS_INVALID
			};

			struct tBootNode {
				uint32_t signature;
				lba_t directory;
				lba_t block0;
				lba_t freeSize;
				lba_t size;

				tBootNode () : signature( NFS_SIGNATURE ), directory(0),
					block0(0), freeSize(0), size(0) {
				}

				tBootNode( lba_t directory, lba_t block0, lba_t freeSize, lba_t size ) : signature( NFS_SIGNATURE ),
					directory(directory), block0(block0), freeSize(freeSize), size(size) {
				}
			} __attribute__((packed));

			struct tSubNode {
				char name[NFS_NAME_LENGTH];
				lba_t addr;

				tSubNode( const char *name, lba_t addr ) : addr(addr) {
					int i = 0;

					while ( name[i] != 0 && i < NFS_NAME_LENGTH - 1 ) {
						this->name[i] = name[i];
						i++;
					}

					for ( ; i < NFS_NAME_LENGTH; i++ )
						this->name[i] = 0;
				}

				tSubNode() {
						
				}
			};

			struct tNode {
				uint32_t signature;
				char name[NFS_NAME_LENGTH];
				lba_t addr;
				lba_t parent;
				uint8_t type;
				uint32_t size;
				uint32_t capacity;
				uint32_t numberOfChildren;

				tNode( const char *name, lba_t addr, lba_t parent, NodeType type, uint32_t capacity ) :
					signature(NFS_SIGNATURE),addr(addr), parent(parent), type(type),
					size(sizeof(tNode)), capacity(capacity), numberOfChildren(0) {

					int i;
					for ( i = 0; name[i] != 0 && i < NFS_NAME_LENGTH - 1; i++ )
						this->name[i] = name[i];

					for ( ; i < NFS_NAME_LENGTH; i++ )
						this->name[i] = 0;
				}

				tNode() {

				}

				bool isValid() {
					return (addr != 0) && (parent != 0) && (capacity > 0) &&
						(signature == NFS_SIGNATURE) && (type != NodeType::FS_INVALID);
				}
			};

			struct tStorageBlock {
				lba_t addr;
				lba_t next;
				lba_t size;

				tStorageBlock() {
					
				}

				tStorageBlock( lba_t next, lba_t size ) : next(next), size(size) {
					
				}
			} __attribute__((packed));
		public:
			NFSII( Storage &storage );

			void ls( const char *path );
			bool rm( const char *path );

			fid_t open( const char *path );
			bool mkdir( const char *path, size_t size = 1 );
			bool touch( const char *path, size_t size = 1 );
			bool flush( fid_t fd );

			bool expand( fid_t fd, size_t nbytes );

			void format();
			lba_t getNumberOfFreePages() const;

			lba_t allocate( size_t numberOfPages );
			bool deallocate( lba_t offset, size_t numberOfPages );

			~NFSII();
		protected:
			size_t createNode( const char *path, size_t size, NodeType type );
			bool expandNode( tNode &node, size_t nbytes );
			bool deleteNode( tNode &node );
			bool insertNodeAt( tNode &node, tNode& directory );
			lba_t findNodeAt( const char *name, tNode& directory );
			const char* decode( const char *path, tNode &current );

			bool isAValidFileName( const char *name );
		private:
			lba_t currentDirectory;
			tBootNode bootNode;
	};


#endif
