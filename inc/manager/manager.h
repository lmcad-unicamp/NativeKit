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

#ifndef MANAGER_H
#define MANAGER_H

#include <ilistener.h>

	/**
	 * The Manager is an interface created to simplify the relationship
	 * between the kernel and the algorithms that controls the system
	 * resources. Every manager needs to implement this interface to work
	 * properly. In the future this interface is going to be more complex, but
	 * for now, it's more than enough.
	 */
	class Manager : public InterruptionListener {
	public:
		/**
		 * Init is a method used to initialize every manager algorithm. You
		 * need to initialize all complex dependencies in this method.
		 *
		 * @remarks  Probably you are asking yourself: why not use
		 * a constructor for this purpose? The reason is complicated. We can't
		 * use a constructor like we do with user level programs because the
		 * constructor, in a kernel mode, could be initialized before other
		 * resources.
		 */
		virtual void init();

		/**
		 * ISR - Interrupt Service Routine: is a function that is called every
		 * time a system event is executed. You need to register what kind of
		 * event you want to listen.
		 *
		 * @see InterruptionListener for more details.
		 * @param ssid - ID of the interruption event.
		 * @param registers - State before the interruption.
		 */
		virtual void isr( const SSID ssid, Registers &registers );
	private:
		
	};

#endif

