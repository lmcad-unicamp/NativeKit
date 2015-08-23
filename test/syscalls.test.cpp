#include <ktest.h>

TEST( SysCalls_OpenAndClose )
	// Attention: the newlib doesn't release the memory back to the system!
	// (INVALID_MEMORY_LEAK_ERROR)

	System sys;
	SysCalls syscalls;
	Storage storage;
	UART uart( COM1 );
	NFSII nfs( storage);
	FileSystem &fs = nfs;
	fs.format();

	sys.install( syscalls );
	sys.install( storage );
	sys.install( fs );
	sys.install( uart );

	FILE *fp = fopen ("file.txt", "w");

	REQUIRE( fp != 0 )
	REQUIRE( !fs.touch( "file.txt" ) )
	
	REQUIRE( fprintf( fp, "OK\n" ) == 3 )
	REQUIRE( fclose(fp) == 0 );

	fp = fopen ("file.txt", "r");
	REQUIRE( fp != 0 )
    REQUIRE( !feof( fp ) )
	REQUIRE( fgetc( fp ) == 'O' );
	REQUIRE( fgetc( fp ) == 'K' );
	REQUIRE( fgetc( fp ) == '\n' );
	REQUIRE( fgetc( fp ) == EOF );
    REQUIRE( feof( fp ) )
	REQUIRE( fclose( fp ) == 0 );
END

TEST( SysCalls_LSEEK )
	System sys;
	SysCalls syscalls;
	Storage storage;
	UART uart( COM1 );
	NFSII nfs( storage);
	FileSystem &fs = nfs;
	fs.format();

	sys.install( syscalls );
	sys.install( storage );
	sys.install( fs );
	sys.install( uart );

	FILE *fp = fopen ("file.txt", "w");

	REQUIRE( fp != 0 )
	REQUIRE( !fs.touch( "file.txt" ) )

	fseek(fp, 0, SEEK_END);
	REQUIRE( ftell( fp ) == 0 );
	REQUIRE( fprintf( fp, "TEST\n" ) == 5 )
	REQUIRE( ftell( fp ) == 5 );
	REQUIRE( fprintf( fp, "TEST\n" ) == 5 )
	REQUIRE( fclose( fp ) == 0 );

	fid_t fd = nfs.open( "file.txt" );
	File *file = fs.getFile( fd );
	REQUIRE( file );
	REQUIRE( file->getSize() == 10 );
	REQUIRE( nfs.close( fd ) );

	fp = fopen ("file.txt", "r");
	REQUIRE( fp != 0 )
	fseek(fp, 0, SEEK_END);
	REQUIRE( ftell( fp ) == 10 );
	fseek(fp, 0, SEEK_SET);
	REQUIRE( ftell( fp ) == 0 );
	REQUIRE( fclose( fp ) == 0 );
END

TEST( SysCalls_BRK )
	uintr_t currentSize;
	uintr_t lastSize;
	uintr_t result;

	__asm__ __volatile__( "int $0x80" : "=a"(currentSize) : "a"(45), "b"(0) : );
	REQUIRE( currentSize != (uintr_t) -1 );
	REQUIRE( currentSize <  (uintr_t) &_heap_top  );
	REQUIRE( currentSize >= (uintr_t) &_heap_base );

	lastSize = currentSize;
	__asm__ __volatile__( "int $0x80" : "=a"(result) : "a"(45), "b"(currentSize + 40) : );
	REQUIRE( result == 0 )

	__asm__ __volatile__( "int $0x80" : "=a"(currentSize) : "a"(45), "b"(0) : );
	REQUIRE( currentSize == lastSize + 40 );

	__asm__ __volatile__( "int $0x80" : "=a"(result) : "a"(45), "b"(&_heap_top - 1) : );
	REQUIRE( result == 0 )

	__asm__ __volatile__( "int $0x80" : "=a"(currentSize) : "a"(45), "b"(0) : );
	REQUIRE( currentSize == (uintr_t) &_heap_top - 1 );

	__asm__ __volatile__( "int $0x80" : "=a"(result) : "a"(45), "b"(lastSize) : );
	REQUIRE( result == 0 )

	__asm__ __volatile__( "int $0x80" : "=a"(currentSize) : "a"(45), "b"(0) : );
	REQUIRE( currentSize == lastSize )
END
