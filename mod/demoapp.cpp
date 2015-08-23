#include <stdio.h>
#include <stdlib.h>

int main() {
	unsigned int i;

	for ( i = 0; i != 0xFFFFFFFF; i++ )
		printf( " i == %d\n", i );

	return 0;
}

