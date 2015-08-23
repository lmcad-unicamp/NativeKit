#include <ktest.h>

TEST( Storage_SeekAndShift )
	char test = 'A';

	Storage storage;
	REQUIRE( storage.seek( 0 ) );
	REQUIRE( !storage.shift( -1 ) ); // invalid operation
	REQUIRE( storage.shift( 1 ) );

	REQUIRE( storage.write( "B", 1 ) );
	REQUIRE( storage.shift( -1 ) );
	REQUIRE( storage.read( &test, 1 ) );

	REQUIRE( test == 'B' );

	REQUIRE( storage.seek( storage.getNumberOfPages() - 1 ) );
	REQUIRE( storage.shift( 4095 ) );
	REQUIRE( !storage.shift( 1 ) ); // invalid operation
	REQUIRE( storage.shift( -1 ) );

	REQUIRE( storage.write( "E", 1 ) );
	REQUIRE( storage.shift( -1 ) );
	REQUIRE( storage.read( &test, 1 ) );

	REQUIRE( test == 'E' );
END

TEST( Storage_ReadAndWrite )
	Storage storage;
	char *buffer = new char[STORAGE_PAGE_SIZE];

	REQUIRE( buffer != 0 );
	REQUIRE( storage.getSize() > 0 );
	REQUIRE( storage.getSize() == storage.getNumberOfPages() * STORAGE_PAGE_SIZE );

	SUBTEST( ReadAndWrite, lba_t addr )
		for ( int j = 0; j < STORAGE_PAGE_SIZE; j++ )
			buffer[j] = '@';

		REQUIRE( storage.seek( addr ) );
		REQUIRE( storage.write( buffer, STORAGE_PAGE_SIZE ) );

		for ( int j = 0; j < STORAGE_PAGE_SIZE; j++ )
			buffer[j] = ' ';

		REQUIRE( storage.seek( addr ) );
		REQUIRE( storage.read( buffer, STORAGE_PAGE_SIZE ) );

		for ( int j = 0; j < STORAGE_PAGE_SIZE; j++ )
			REQUIRE( buffer[j] == '@' );
	END

	CALL( ReadAndWrite, 0 )
	CALL( ReadAndWrite, storage.getNumberOfPages() / 2 )
	CALL( ReadAndWrite, storage.getNumberOfPages() - 1 )

	delete buffer;
END

TEST( Storage_Output )
	char buffer[65] = {0};
	const char* maxInt = "4294967295";
	Storage storage;

	REQUIRE( storage.seek(0) )
	storage.write( (uint8_t) 0xFF, 16 );
	storage.write( (uint16_t) 0xFFFF, 16 );
	storage.write( (uint32_t) 0xFFFFFFFF, 16 );
	storage.write( (uint32_t) 0xFFFFFFFF, 2 );
	storage.write( (uint32_t) 0xFFFFFFFF, 10 );
	storage.write( (uint32_t) 0xFFFFFFFF, 1 );
	storage.write( (uint32_t) 0xFFFFFFFF, 17 );
	storage.write( (uint64_t) 0xFFFFFFFFFFFFFFFF, 16 );
	storage.write( (uint64_t) 0xFFFFFFFFFFFFFFFF, 2 );

	REQUIRE( storage.seek(0) )
	REQUIRE( storage.read( buffer, 14 ) == 14 )

	for ( int i = 0; i < 14; i++ )
		REQUIRE( buffer[i] == 'F' )

	REQUIRE( storage.read( buffer, 32 ) == 32 )

	for ( int i = 0; i < 32; i++ )
		REQUIRE( buffer[i] == '1' )

	for ( int i = 0; i < 3; i++ ) {
		REQUIRE( storage.read( buffer, 10 ) == 10 )

		for ( int j = 0; j < 10; j++ )
			REQUIRE( buffer[j] == maxInt[j] )
	}

	REQUIRE( storage.read( buffer, 16 ) == 16 )

	for ( int i = 0; i < 16; i++ )
		REQUIRE( buffer[i] == 'F' )

	REQUIRE( storage.read( buffer, 64 ) == 64 )

	for ( int i = 0; i < 64; i++ )
		REQUIRE( buffer[i] == '1' )
END
