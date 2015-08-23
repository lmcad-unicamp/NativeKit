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

#include <ilistener.h>

std::set<InterruptionListener*> InterruptionListener::listeners[NUMBER_OF_ISR];

void InterruptionListener::call( const SSID ssid, Registers &registers ) {
	if ( ssid >= NUMBER_OF_ISR )
		return;

	std::set<InterruptionListener*>::iterator it;

	for ( it = listeners[ssid].begin(); it != listeners[ssid].end(); ++it )
		(*it)->isr( ssid, registers );
}

void InterruptionListener::startListening( SSID ssid ) {
	if( ssid < NUMBER_OF_ISR )
		listeners[ssid].insert( this );
}

void InterruptionListener::stopListening( SSID ssid ) {
	if( ssid < NUMBER_OF_ISR )
		listeners[ssid].erase( this );
}
