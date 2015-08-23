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

#ifndef SYSCALLS_H
#define SYSCALLS_H

#include <system.h>

	class System;

	class SysCalls {
	public:
		typedef void ( *tSysCall )( System* sys, Registers& registers );
	public:
		SysCalls();
		void init( System *sys );
		void enable();
		void disable();
		static void call( Registers &registers );
	private:
		static tSysCall syscalls[];
		static System *sys;
		static bool enabled;
	};

	extern void sys_default( System *sys, Registers &registers );
	extern void sys_exit( System *sys, Registers &registers );
	extern void sys_fork( System *sys, Registers &registers );
	extern void sys_read( System *sys, Registers &registers );
	extern void sys_write( System *sys, Registers &registers );
	extern void sys_open( System *sys, Registers &registers );
	extern void sys_close( System *sys, Registers &registers );
	extern void sys_wait( System *sys, Registers &registers );
	extern void sys_link( System *sys, Registers &registers );
	extern void sys_unlink( System *sys, Registers &registers );
	extern void sys_execve( System *sys, Registers &registers );
	extern void sys_stat( System *sys, Registers &registers );
	extern void sys_lseek( System *sys, Registers &registers );
	extern void sys_getpid( System *sys, Registers &registers );
	extern void sys_fstat( System *sys, Registers &registers );
	extern void sys_kill( System *sys, Registers &registers );
	extern void sys_times( System *sys, Registers &registers  );
	extern void sys_brk( System *sys, Registers &registers );
	extern void sys_gettimeofday( System *sys, Registers &registers );
	extern void sys_reboot( System *sys, Registers &registers );
	extern void sys_newuname( System *sys, Registers &registers );

#endif
