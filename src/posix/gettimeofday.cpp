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

#include <system.h>
#include <sys/time.h>

/** Returns the time of a day. */
void sys_gettimeofday( System *sys, Registers &registers ) {
	static unsigned long long int tempSec = 200;

	if (( registers.r1 == 0 ) || ( registers.r2 == 0 )) {
		registers.r0 = (uintr_t) -1;
	} else {
		timeval* tv  = (timeval*) registers.r1;
		tv->tv_sec   = tempSec++;
		tv->tv_usec  = 0;

		timezone* tz = (timezone*) registers.r2;
		tz->tz_minuteswest = 0;
		tz->tz_dsttime     = 0;
	}
}
