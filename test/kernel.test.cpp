#include <ktest.h>

TEST( System_RandomNewAndFree )
	const int size = 40;
	char **array = new char*[size];

	REQUIRE( array )
	REQUIRE( (uintr_t) array <  (uintr_t) &_heap_top )
	REQUIRE( (uintr_t) array >= (uintr_t) &_heap_base )

	for ( int i = 0; i < size; i++ )
		array[i] = 0;

	srand( 100 );

	for ( int i = 0; i < 1000; i++ ) {
		int pos = rand() % size;

		if ( array[pos] == 0 ) {
			array[pos] = new char[pos + 1];

			REQUIRE( array[pos] )
			REQUIRE( (uintr_t) array <  (uintr_t) &_heap_top  )
			REQUIRE( (uintr_t) array >= (uintr_t) &_heap_base )
		} else {
			delete[] array[pos];
			array[pos] = 0;
		}
	}

	for ( int i = 0; i < size; i++ ) {
		if ( array[i] != 0 )
			delete[] array[i];
	}

	delete[] array;
END


int main() {
	System sys;

	UART uart( COM1 );
	sys.install( uart );

	KTest::init( uart );
	KTest::run();
	return 0;
}
