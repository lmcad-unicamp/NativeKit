#include <ktest.h>

TEST( FileSystem_FileTable )
	size_t size = 0;
	const size_t capacity = 128;

	Storage storage;
	FileTable ft(capacity);

	File **files = new File*[capacity];

	REQUIRE( files )
	REQUIRE( ft.getSize() == size )
	REQUIRE( ft.getCapacity() == capacity )

	for ( size_t i = 0; i < capacity; i++ )
		files[i] = 0;

	srand( 100 );

	for ( int i = 0; i < 2000; i++ ) {
		int pos = rand() % capacity;

		if ( !files[pos] ) {
			files[pos] = new File( storage, 0, 0, 0, 0 );

			REQUIRE( files[pos] != 0 )
			REQUIRE( ft.insert( files[pos] ) == files[pos]->getID() )
			REQUIRE( files[pos]->getID() >= 0 )
			REQUIRE( ft.getCurrent() == files[pos] )

			size++;
		} else {
			REQUIRE( ft.getFile( files[pos]->getID() ) == files[pos] )
			REQUIRE( ft.remove( files[pos]->getID() ) == files[pos] )

			delete files[pos];
			files[pos] = 0;
			size--;
		}

		REQUIRE( ft.getSize() == size  )
	}

	for ( size_t i = 0; i < capacity; i++ ) {
		if ( files[i] )
			delete files[i];
	}

	delete[] files;
END

TEST( FileSystem_FileManipulation )
	Storage storage;
	NFSII nfs( storage );
	FileSystem &fs = nfs;
	size_t size, capacity;
	char c;

	fs.format();
	REQUIRE( fs.touch( "/file" ) )

	fid_t fd = fs.open( "/file" );
	REQUIRE( fd >= 3 )

	File *file = fs.getFile( fd );
	REQUIRE( file )
	REQUIRE( file->getID() == fd )
	REQUIRE( file->getSize() == 0 )
	REQUIRE( file->getOffset() == 0 )
	REQUIRE( file->isEOF() )

	for ( size_t i = 0; i < file->getCapacity(); i++ )
		REQUIRE( fs.write( fd, "@", 1 ) )
	
	REQUIRE( file->isEOF() )
	REQUIRE( file->getSize() == file->getCapacity() )
	REQUIRE( !fs.read( fd, &c, 1 ) )
	REQUIRE( file->isEOF() )
	REQUIRE( fs.write( fd, "@", 1 ) )
	REQUIRE( file->getSize() <= file->getCapacity() )

	fs.seek( fd, 0 );
	REQUIRE( !file->isEOF() )

	for ( size_t i = 0; i < file->getSize(); i++ ) {
		REQUIRE( fs.read( fd, &c, 1 ) )
		REQUIRE( c == '@' )
	}

	REQUIRE( file->isEOF() )

	capacity = file->getCapacity();
	size     = file->getSize();
	REQUIRE( fs.close( fd ) );

	fd = fs.open( "file" );
	REQUIRE( fd >= 3 )

	file = fs.getFile( fd );
	REQUIRE( file );
	REQUIRE( file->getCapacity() == capacity );
	REQUIRE( file->getSize() == size );
	REQUIRE( fs.read( fd, &c, 1 ) )
	REQUIRE( c == '@' )
	REQUIRE( fs.close( fd ) );
END

TEST( FileSystem_CreateFile )
	char buffer[10];

	Storage storage;
	NFSII nfs( storage );
	FileSystem &fs = nfs;
	fs.format();

	REQUIRE( fs.touch("/arquivo1.txt") )
	REQUIRE( fs.touch("/arquivo2.txt") )
	REQUIRE( fs.touch("/arquivo3.txt") )

	fid_t fd = fs.open( "/arquivo1.txt" );
	REQUIRE( fd >= 3 )

	File *file = fs.getFile( fd );
	REQUIRE( file )
	REQUIRE( fs.write( fd, "ARQUIVO", 8 ) == 8 )
	REQUIRE( fs.seek( fd, 0 ) )
	REQUIRE( fs.read( fd, buffer, 4 ) == 4 )
	REQUIRE( ((buffer[0] == 'A') && (buffer[1] == 'R') && (buffer[2] == 'Q') && (buffer[3] == 'U')) )
	REQUIRE( fs.close( fd ) );

	REQUIRE( !fs.write( fd, "ARQUIVO", 8 ) )
	REQUIRE( !fs.seek( fd, 0 ) )
	REQUIRE( !fs.read( fd, buffer, 4 ) )
END

TEST( FileSystem_RamdomFileCreation )
	Storage storage;
	NFSII nfs( storage );

	FileSystem &fs = nfs;
	fs.format();

	lba_t freePages = fs.getNumberOfFreePages();

	bool files[50] = {0};
	char name[2] = {0};

	srand(rand()) ;

	for ( int i = 0; i < 1000; i++ ) {
		int pos  = rand() % sizeof(files);
		name[0] = (char) 'a' + pos;

		if ( !files[pos] ) {
			REQUIRE( !fs.rm( name ) )
			REQUIRE( fs.touch( name ) )
			files[pos] = true;
		} else {
			REQUIRE( !fs.touch( name ) )
			REQUIRE( fs.rm( name ) )
			files[pos] = false;
		}
	}

	for ( size_t i = 0; i < sizeof(files); i++ ) {
		if ( files[i] ) {
			name[0] = (char) 'a' + i;
			REQUIRE( fs.rm( name ) )
		}
	}

	REQUIRE( freePages == fs.getNumberOfFreePages() )
END

TEST( FileSystem_TouchAndRemove )
	Storage storage;
	NFSII nfs( storage );

	FileSystem &fs = nfs;
	fs.format();

	lba_t freePages = fs.getNumberOfFreePages();

	REQUIRE( fs.touch("arquivo") )
	REQUIRE( fs.rm("arquivo") )
	REQUIRE( fs.touch("arquivo") )
	REQUIRE( fs.rm("arquivo") )

	REQUIRE( fs.mkdir("/pasta1") )
	REQUIRE( fs.mkdir("pasta1/pasta2") )
	REQUIRE( fs.touch("pasta1/pasta2/arquivo1") )
	REQUIRE( fs.touch("pasta1/pasta2/arquivo2") )
	REQUIRE( fs.touch("pasta1/pasta2/arquivo3") )
	REQUIRE( fs.touch("pasta1/pasta2/arquivo4") )

	REQUIRE( !fs.rm("pasta1/pasta2") )
	REQUIRE( !fs.rm("pasta1") )
	REQUIRE( fs.rm("pasta1/pasta2/arquivo3") )
	REQUIRE( fs.rm("pasta1/pasta2/arquivo1") )
	REQUIRE( fs.rm("pasta1/pasta2/arquivo2") )
	REQUIRE( fs.rm("pasta1/pasta2/arquivo4") )
	REQUIRE( fs.rm("pasta1/pasta2") )
	REQUIRE( fs.rm("pasta1") )

	REQUIRE( freePages == fs.getNumberOfFreePages() )
END

TEST( FileSystem_Path )
	Storage storage;
	NFSII nfs( storage );

	FileSystem &fs = nfs;
	fs.format();

	REQUIRE( fs.touch("/arquivo1.txt") )
	REQUIRE( fs.touch("./arquivo2.txt") )
	REQUIRE( fs.touch("./././arquivo3.txt") )
	REQUIRE( fs.touch("./.././../arquivo4.txt") )
	REQUIRE( fs.touch("../arquivo5.txt") )
	REQUIRE( fs.touch("arquivo6.txt") )
	REQUIRE( fs.touch("///arquivo7.txt") )
	REQUIRE( fs.touch("..arquivo1.txt") )
	REQUIRE( fs.touch(".arquivo1.txt") )
	REQUIRE( fs.touch("...") )
	REQUIRE( fs.touch(" arquivo") )
	REQUIRE( fs.touch("arquivo ") )
	REQUIRE( fs.touch("arq uivo") )

	REQUIRE( !fs.touch("arquivo1.txt") )
	REQUIRE( !fs.touch("arquivo/") )
	REQUIRE( !fs.touch("//arquivo/") )
	REQUIRE( !fs.touch("/") )
	REQUIRE( !fs.touch(".") )
	REQUIRE( !fs.touch("..") )
	REQUIRE( !fs.touch("//") )
	REQUIRE( !fs.touch("\0") )
	REQUIRE( !fs.touch(0) )
	REQUIRE( !fs.touch("arquivo1.txt/arquivo") )

	REQUIRE( fs.mkdir("pasta1") )
	REQUIRE( fs.mkdir("./pasta2") )
	REQUIRE( fs.mkdir(".pasta2") )
	REQUIRE( fs.mkdir("..pasta2") )
	REQUIRE( fs.mkdir("pasta1/pasta") )
	REQUIRE( fs.mkdir("pasta1/../pasta2/pasta3") )
	REQUIRE( fs.mkdir("../pasta2/.//../pasta1////../pasta2/pasta3/pasta4") )
	REQUIRE( fs.touch("pasta2/pasta3/pasta4/arquivo") )

	REQUIRE( !fs.mkdir("arquivo1.txt/pasta") )
END

TEST( FileSystem_AllocateAndDeallocate )
	lba_t addr1, addr2, addr3, addr4, addr5;
	Storage storage;
	NFSII nfs(storage);

	size_t currentSize = nfs.getNumberOfFreePages();
	REQUIRE( currentSize > 0 )

	addr1 = nfs.allocate(10);
	addr2 = nfs.allocate(10);
	addr3 = nfs.allocate(10);
	addr4 = nfs.allocate(10);
	addr5 = nfs.allocate(10);
	
	REQUIRE( addr1 && addr2 && addr3 && addr4 && addr5 )

	REQUIRE( nfs.deallocate( addr2, 10 ) )
	REQUIRE( nfs.deallocate( addr4, 10 ) )

	addr2 = nfs.allocate(10);
	addr4 = nfs.allocate(10);

	REQUIRE( addr2 && addr4 )

	REQUIRE( nfs.deallocate( addr1, 10 ) )
	REQUIRE( nfs.deallocate( addr3, 10 ) )
	REQUIRE( nfs.deallocate( addr5, 10 ) )

	addr1 = nfs.allocate(10);
	addr3 = nfs.allocate(10);
	addr5 = nfs.allocate(10);

	REQUIRE( nfs.deallocate( addr3, 10 ) )
	REQUIRE( nfs.deallocate( addr4, 10 ) )
	REQUIRE( nfs.deallocate( addr2, 10 ) )
	REQUIRE( nfs.deallocate( addr1, 10 ) )
	REQUIRE( nfs.deallocate( addr5, 10 ) )

	// Invalid operations
	REQUIRE( !nfs.deallocate( addr3, 10 ) )
	REQUIRE( !nfs.deallocate( addr4, 10 ) )
	REQUIRE( !nfs.deallocate( addr2, 10 ) )
	REQUIRE( !nfs.deallocate( addr1, 10 ) )
	REQUIRE( !nfs.deallocate( addr5, 10 ) )
	REQUIRE( !nfs.deallocate( 0, 0 ) )
	REQUIRE( !nfs.deallocate( addr1, 0 ) )
	REQUIRE( !nfs.deallocate( 0, 10 ) )
	REQUIRE( !nfs.allocate( 0 ) )

	REQUIRE( currentSize == nfs.getNumberOfFreePages() )
END

TEST( FileSystem_Fragmentation )
	lba_t blocks[70] = {0};
	Storage storage;

	NFSII nfs(storage);
	nfs.format();

	size_t currentSize = nfs.getNumberOfFreePages();
	REQUIRE( currentSize > 0 )

	SUBTEST(RandomAllocation)
		srand(rand()) ;

		for ( int i = 0; i < 10000; i++ ) {
			int pos = rand() % 70;

			if ( blocks[pos] == 0 ) {
				blocks[pos] = nfs.allocate( (pos % 2) + 1 );
				REQUIRE( blocks[pos] );
			} else {
				REQUIRE( nfs.deallocate( blocks[pos], (pos % 2) + 1) );
				blocks[pos] = 0;
			}
		}
	END

	CALL(RandomAllocation)
	CALL(RandomAllocation)
	CALL(RandomAllocation)
	CALL(RandomAllocation)

	for ( int i = 0; i < 70; i++ ) {
		if ( blocks[i] )
			REQUIRE( nfs.deallocate( blocks[i], (i % 2) + 1 ) );
	}

	REQUIRE( currentSize == nfs.getNumberOfFreePages() )
END

TEST( FileSystem_Directory )
	NFSII::tSubNode child;
	Storage storage;
	NFSII nfs( storage);
	FileSystem &fs = nfs;
	fs.format();

	REQUIRE( fs.touch( "A\0" ) )
	REQUIRE( fs.touch( "B\0" ) )
	REQUIRE( fs.touch( "C\0" ) )
	REQUIRE( fs.mkdir( "D\0" ) )
	REQUIRE( fs.mkdir( "E\0" ) )

	fid_t fd = fs.open( "/\0" );
	REQUIRE( fd >= 3 )

	File *file = fs.getFile( fd );
	REQUIRE( file )
	REQUIRE( file->getSize() > 0 )

	REQUIRE( fs.seek( fd, 0 ) )
	REQUIRE( fs.read( fd, (char*) &child, sizeof(child) ) )
	REQUIRE( child.name[0] == 'A' )

	REQUIRE( fs.seek( fd, file->getSize() - sizeof(child) ) )
	REQUIRE( fs.read( fd, (char*) &child, sizeof(child) ) )
	REQUIRE( child.name[0] == 'E' )
	REQUIRE( fs.close( fd ) )
END

TEST( FileSystem_ExpandFile )
	Storage storage;
	NFSII nfs( storage );
	FileSystem &fs = nfs;
	fs.format();

	size_t size = fs.getNumberOfFreePages();
	fs.touch( "A\0" );
	fs.touch( "B\0" );
	fs.touch( "C\0" );
	fs.touch( "D\0" );
	fs.touch( "E\0" );

	SUBTEST( ExpandFile, const char* name )
		char c;

		fid_t fd = fs.open( name );
		REQUIRE( fd >= 3 )

		File* file = fs.getFile( fd );
		REQUIRE( file )

		size_t capacity = file->getCapacity();
		REQUIRE( fs.seek( fd, capacity + 10 ) )
		REQUIRE( file->getCapacity() > capacity )

		REQUIRE( file->getSize() == 0 )
		REQUIRE( !fs.read( fd, &c, 1 ) )
		REQUIRE( file->getSize() == 0 )
		REQUIRE( file->isEOF() )

		REQUIRE( fs.write( fd, "TEXT\0", 5 ) )
		REQUIRE( file->getSize() == capacity + 15 )
		REQUIRE( fs.seek( fd, capacity + 10 ) )
		REQUIRE( fs.read( fd, &c, 1 ) )
		REQUIRE( !file->isEOF() )

		REQUIRE( fs.close( fd ) )
		REQUIRE( fs.rm(name) )
	END

	CALL( ExpandFile, "C\0" )
	CALL( ExpandFile, "A\0" )
	CALL( ExpandFile, "E\0" )
	CALL( ExpandFile, "B\0" )
	CALL( ExpandFile, "D\0" )

	REQUIRE( size == fs.getNumberOfFreePages() )
END
