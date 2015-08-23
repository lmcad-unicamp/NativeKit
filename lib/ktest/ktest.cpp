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

#include <ktest.h>

OutputDevice* KTest::out = 0;
size_t KTest::numberOfTests = 0;
KTest* KTest::tests[MAX_NUMBER_OF_TESTS];

KTest::KTest( const char* name ) : name(name) {
	tests[numberOfTests++] = this;
}

void KTest::init( OutputDevice &device ) {
	out = &device;
}

void KTest::run() {
	size_t errors = 0;
	size_t warnings = 0;

	if ( !out )
		return;

	for ( size_t i = 0; i < numberOfTests; i++ ) {
		out->write( "Test " );
		out->write( i + 1 );
		out->write( '/' );
		out->write( numberOfTests );
		out->write( ": " );
		out->writeln( tests[i]->getName() );
		out->write( "     status: " );

		unsigned int memsize = mallinfo().uordblks;
		
		if ( tests[i]->test() ) {
			if ( memsize != mallinfo().uordblks ) {
				out->writeln( "MEMORY LEAK DETECTED" );
				warnings++;
			} else {
				out->writeln( "PASSED" );
			}
		} else {
			errors++;
		}

		if ( i % 2 )
			out->writeln( "////////////////////////////////////////////////\0" );
		else
			out->writeln( "\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\0" );
	}

	out->write( "Errors: " );
	out->write( errors );
	out->write( " | Warnings: " );
	out->writeln( warnings );
}

const char* KTest::getName() {
	return name;
}
