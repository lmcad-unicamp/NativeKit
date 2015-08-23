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

#ifndef KTEST_H
#define KTEST_H

#include <debug.h>
#include <keybuffer.h>
#include <dlinkedlist.h>
#include <scheduler.h>
#include <nfsii.h>
#include <filesystem.h>
#include <process.h>
#include <manager.h>
#include <file.h>
#include <memory.h>
#include <syscalls.h>
#include <system.h>
#include <vesa.h>
#include <uart.h>
#include <video.h>
#include <keyboard.h>
#include <device.h>
#include <iodevice.h>
#include <outputdevice.h>
#include <inputdevice.h>
#include <storage.h>
#include <ilistener.h>
#include <types.h>

#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_NUMBER_OF_TESTS 2000

#define TEST( TEST_NAME  ) \
	class TEST_NAME : public KTest {\
	public:\
		TEST_NAME( const char* name );\
		bool test();\
	} CONCAT(TEST_NAME,__LINE__)(#TEST_NAME"\0");\
\
	TEST_NAME::TEST_NAME( const char* name ) : KTest(name) {\
\
	}\
\
	bool TEST_NAME::test() {

#define END \
		return true;\
	};

#define SUBTEST(A,ARGS...)\
	auto A = [&](ARGS...) {

#define CALL(A,ARGS...)\
	if ( !A(ARGS) )\
		return false;

#define WRITELN(VALUE)\
		out->writeln( VALUE );\

#define WRITE(VALUE)\
		out->write( VALUE );\

#define REQUIRE_1( exp )\
	if ( !(exp) ) {\
		out->writeln( "FAILED\n     Error at " __FILE__ ":" TOSTRING( __LINE__ ) " [REQUIRE(" #exp ")]\0" );\
		return false;\
	}

#define REQUIRE_2( exp, msg )\
	if ( !(exp) ) {\
		out->writeln( "FAILED\n     Error at " __FILE__ ":" TOSTRING( __LINE__ ) " ["#msg"]\0" );\
		return false;\
	}

#define REQUIRE_Y(X,Y,Z,...) Z
#define REQUIRE_X(...) REQUIRE_Y(__VA_ARGS__,REQUIRE_2,REQUIRE_1)
#define REQUIRE(...) REQUIRE_X(__VA_ARGS__)(__VA_ARGS__)

	class KTest {
	public:
		KTest( const char* name );
		static void init( OutputDevice &device );
		static void run();
		inline const char* getName();
	protected:
		virtual bool test() = 0;
	protected:
		static OutputDevice *out;
	private:
		const char* name;
		static size_t numberOfTests;
		static KTest* tests[MAX_NUMBER_OF_TESTS];
	};

#endif
