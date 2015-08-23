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

#ifndef ILISTENER_H
#define ILISTENER_H

#include <arch.h>
#include <registers.h>
#include <set>

	/**
	 * InterruptionListener is a class responsible for intercept system
	 * interruption and call the right handler. All object that need to use one
	 * interruption line need to extend of InterruptionListener and implement
	 * the isr method that is going to be called.
	 */
	class InterruptionListener {
		public:
			/**
			 * You can use the method call to execute one registered
			 * interruption. This method was created for debug purpose.
			 *
			 * @remarks You can use inline assembly to achieve the same result:
			 * __asm__ __volatile__( "int <ssid>" : <output registers> : <input
			 * registers> : );
			 *
			 * @param ssid - ID of the interruption event.
			 * @param registers - Current machine state.
			 **/
			static void call( const SSID ssid, Registers &registers );

		protected:
			/**
			* You need to call this function to install your isr in an
			* interruption line. After this operation, ISR is going to be
			* executed every time a new interrupt happens.
			*
			* @remarks To prevent faults, you need to uninstall all
			* interruptions before delete the current object.
			*
			* @see stopListening
			* @param ssid - ID of the interruption event.
			**/
			void startListening( SSID ssid );

			/**
			 * The opposite of startListening.
			 * @param ssid - ID of the interruption event.
			 **/
			void stopListening( SSID ssid );

			/**
			* Interrupt service routine - "ISR" is a callback function whose
			* execution is triggered by the reception of an interrupt.
			*
			* @see InterruptionListener for more details.
			* @param ssid - ID of the interruption event.
			* @param registers - State before the interruption.
			**/
			virtual void isr( const SSID ssid, Registers &registers ) = 0;

		private:
			static std::set<InterruptionListener*> listeners[NUMBER_OF_ISR]; /**< Set of all system interruptions. */
	};

#endif
