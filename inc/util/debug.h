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

#ifndef DEBUG_H
#define DEBUG_H

	#ifndef DEBUG
		#define DEBUG 0
	#endif
	
	#define CONCAT(x,y) x ## y
	#define STRCONCAT(x,y) CONCAT(x,y)
	#define STRINGIFY(x) #x
	#define TOSTRING(x) STRINGIFY(x)
	#define FORMAT(msg) __FILE__ ":" TOSTRING( __LINE__ ) " > " msg "\n\0"

	#if DEBUG == 1
		#define warning( msg ) \
			__asm__ __volatile__( "int $0x80" : : "a"(4), "b"(2), "c"(FORMAT( msg )), "d"(sizeof(FORMAT( msg ))) : );

		#define assert_2( exp, msg ) \
			if ( !(exp) ) { \
				warning( msg ) \
				while(true); \
			}

		#define assert_1( exp ) assert_2( exp, "!(" #exp ")" )

	#else
		#define warning(msg)
		#define assert_1(exp)
		#define assert_2(exp,msg)
	#endif

	#define assert_y(x,y,z,...) z
	#define assert_x(...) assert_y(__VA_ARGS__,assert_2,assert_1)
	#define assert(...) assert_x(__VA_ARGS__)(__VA_ARGS__)
#endif
