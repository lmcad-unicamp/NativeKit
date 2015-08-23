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

#include <scheduler.h>

Scheduler::Scheduler() : quantum(0) {

}

void Scheduler::init() {
	assert( pList.getSize(), "Nothing to be done!" );
	this->startListening( SSID::SYSTEM_TIMER );
	while(true);
}

void Scheduler::isr( const SSID ssid, Registers &registers ) {
	assert(ssid == SSID::SYSTEM_TIMER );

	if ( ( pList.getSize() <= 1 ) || ( quantum++ < SCHEDULER_QUANTUM ) )
		return;

	Process *current = pList.getCurrent();
	current->pause();

	pList.rRotate();

	current = pList.getCurrent();
	current->start();

	quantum = 0;
}

bool Scheduler::kill( const size_t pid ) {
	Process *process = pList.remove( pid );

	if ( !process )
		return false;

	delete process;
	return true;
}

bool Scheduler::start( Process &process ) {
	size_t pid = pList.pushb( &process );

	if ( !pid )
		return false;

	process.setID( pid );
	return true;
}

Scheduler::~Scheduler() {
	while ( pList.getSize() > 0 )
		delete pList.popf();
}
