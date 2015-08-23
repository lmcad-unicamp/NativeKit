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

#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <process.h>
#include <manager.h>
#include <dlinkedlist.h>

#define SCHEDULER_QUANTUM 40

	class Scheduler : public Manager {
	public:
		Scheduler();

		bool kill( const size_t pid );
		bool start( Process &process );

		virtual void init();
		virtual void isr( const SSID ssid, Registers &registers );

		~Scheduler();
	private:
		DLinkedList<Process*> pList;
		unsigned int quantum;
	};

#endif

