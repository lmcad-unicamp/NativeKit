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
// #include <sys/utsname.h>
#include <sys/types.h>

#define SYS_NAME           "NKII\0"
#define SYS_NETWORK_NAME   "NONE\0"
#define SYS_KERNEL_VERSION "0.01\0"
#define SYS_MACHINE_NAME   "i686\0"
#define SYS_KERNEL_RELEASE "0.01\0"

/** Returns name and informations about the current kernel. */
void sys_newuname( System *sys, Registers &registers ) {
	if ( registers.r1 != 0 ) {
		// utsname *uname = ((utsname*) (registers.r1));
		// strcpy( uname->sysname , SYS_NAME           );
		// strcpy( uname->nodename, SYS_NETWORK_NAME   );
		// strcpy( uname->release , SYS_KERNEL_RELEASE );
		// strcpy( uname->version , SYS_KERNEL_VERSION );
		// strcpy( uname->machine , SYS_MACHINE_NAME   );

		registers.r0 = 0;
	} else {
		registers.r0 = -1;
	}
}

