#include <ktest.h>

TEST( Memory_Layout )
	Memory m;
	size_t storageSize = &_storage_top - &_storage_base;

	// Multiboot specification
	REQUIRE( ((size_t)&_kernel_base == 0x100000) )
	REQUIRE( (uintptr_t) &_kernel_base == (uintptr_t) &_multiboot )
	REQUIRE( _multiboot.magic == 0x1badb002 )

	REQUIRE( !(storageSize & (MEMORY_PAGE_SIZE - 1)) ) //4k Alignment
END

TEST( Memory_AlignmentCheck )
	Memory m;
	size_t freeSize    = m.getFreeSize();
	size_t currentSize = freeSize;

	REQUIRE( freeSize >= MEMORY_MINIMUM_REQUIREMENT )

	REQUIRE( !(freeSize & (MEMORY_PAGE_SIZE - 1)) )
	REQUIRE( m.align( MEMORY_PAGE_SIZE ) == MEMORY_PAGE_SIZE )
	REQUIRE( m.align( MEMORY_PAGE_SIZE + 1 ) == MEMORY_PAGE_SIZE )
	REQUIRE( m.align( MEMORY_PAGE_SIZE * 2 - 1 ) == MEMORY_PAGE_SIZE )
	REQUIRE( m.align( MEMORY_PAGE_SIZE * 3 - 2 ) == MEMORY_PAGE_SIZE * 2 )
	REQUIRE( m.align( MEMORY_PAGE_SIZE * 3 + 2 ) == MEMORY_PAGE_SIZE * 3 )

	uintptr_t pageBlock[5] = {0};

	for ( unsigned int i = 0; i < 5; i++ ) {
		pageBlock[i] =  m.allocate( i + 1 );
		REQUIRE( pageBlock[i] != 0 );
		REQUIRE( (pageBlock[i] & ( MEMORY_PAGE_SIZE - 1 )) == 0 );

		currentSize -= ( i + 1 ) * MEMORY_PAGE_SIZE;
		REQUIRE( m.getFreeSize() == currentSize );
	}

	REQUIRE( m.deallocate( pageBlock[1], 2 ) );
	REQUIRE( m.deallocate( pageBlock[3], 4 ) );
	REQUIRE( m.deallocate( pageBlock[4], 5 ) );
	REQUIRE( m.deallocate( pageBlock[0], 1 ) );
	REQUIRE( m.deallocate( pageBlock[2], 3 ) );

	REQUIRE( m.getFreeSize() == freeSize );
END

TEST( Memory_AllocateAndDeallocate )
	uintptr_t pageBlock[200] = {0};

	Memory m;
	size_t freeSize = m.getFreeSize();

	REQUIRE( freeSize >= MEMORY_MINIMUM_REQUIREMENT )

	SUBTEST( RandomAllocationAndDeallocate )
		srand(rand());

		for ( unsigned int i = 0; i < 80000; i++ ) {
			int pos = rand() % 200;

			if ( pageBlock[pos] == 0 ) {
				pageBlock[pos] =  m.allocate( ( pos % 5 ) + 1 );
				REQUIRE( pageBlock[pos] != 0 );
				REQUIRE( !(((uintptr_t) pageBlock[pos]) & ( MEMORY_PAGE_SIZE - 1 )) );
			} else {
				REQUIRE( m.deallocate( pageBlock[pos], ( pos % 5 ) + 1 ) );
				pageBlock[pos] = 0;
			}
		}
	END

	CALL( RandomAllocationAndDeallocate )
	CALL( RandomAllocationAndDeallocate )
	CALL( RandomAllocationAndDeallocate )
	CALL( RandomAllocationAndDeallocate )

	for ( unsigned int i = 0; i < 200; i++ ) {
		if ( pageBlock[i] ) {
			REQUIRE( m.deallocate( pageBlock[i], ( i % 5 ) + 1 ) );
			pageBlock[i] = 0;
		}
	}
	
	REQUIRE( m.getFreeSize() == freeSize );
END
