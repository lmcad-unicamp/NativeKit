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

#ifndef SYSTEM_H
#define SYSTEM_H

#include <uart.h>
#include <syscalls.h>
#include <device.h>
#include <storage.h>
#include <memory.h>
#include <filesystem.h>
#include <scheduler.h>
#include <inputdevice.h>
#include <outputdevice.h>
#include <iodevice.h>
#include <ilistener.h>
#include <registers.h>
#include <syscalls.h>

#include <stdlib.h>
#include <stdio.h>
#include <unordered_map>
#include <set>

class SysCalls;

class System : public InterruptionListener {
public:
	System();

	virtual void isr( const SSID ssid, Registers &registers );
	void start();

	void reboot() const;
	void install( SysCalls &sysCalls );
	void install( FileSystem &fs );
	void install( Memory &memory );
	void install( Scheduler &scheduler );
	void install( InputDevice &device );
	void install( Device &device );
	void install( OutputDevice &device );
	void install( IODevice &device );
	void install( Manager &manager );
	void uninstall( Device &device );
	bool exec( const char* path );

	inline void setDefaultOutput( OutputDevice &output );
	inline void setDefaultInput( InputDevice &input );
	inline void setDefaultError( OutputDevice &error );
	inline OutputDevice* getDefaultOutput() const;
	inline OutputDevice* getDefaultError() const;
	inline InputDevice* getDefaultInput() const;
	inline FileSystem* getFileSystem() const;

	template <typename T> static void log( T data );
	template <typename T> static void log( T data, uint8_t base );

private:
	FileSystem *fs;
	Memory *memory;
	Scheduler *scheduler;

	static OutputDevice *error;
	static OutputDevice *output;
	static InputDevice *input;
	// std::set<Device*> devices;
};

inline void System::setDefaultOutput( OutputDevice &output ) {
	this->output = &output;
}

inline void System::setDefaultInput( InputDevice &input ) {
	this->input = &input;
}

inline void System::setDefaultError( OutputDevice &error ) {
	this->error = &error;
}

inline OutputDevice* System::getDefaultOutput() const {
	return output;
}

inline OutputDevice* System::getDefaultError() const {
	return error;
}

inline InputDevice* System::getDefaultInput() const {
	return input;
}

inline FileSystem* System::getFileSystem() const {
	return fs;
}

template <typename T> void System::log( T data ) {
	if ( error ) error->write( data );
}

template <typename T> void System::log( T data, uint8_t base ) {
	if ( error ) error->write( data, base );
}

#endif
