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
#include <string.h>
#include <elf.h>

OutputDevice*  System::error  = 0;
InputDevice*   System::input  = 0;
OutputDevice*  System::output = 0;

System::System() : fs(0), memory(0), scheduler(0) {

}

void System::install( SysCalls &sysCalls ) {
	sysCalls.init( this );
}

void System::install( FileSystem &fs ) {
	assert( this->fs == 0 );
	this->fs = &fs;
}

void System::install( Memory &memory ) {
	assert( this->memory == 0 );
	this->memory = &memory;
}

void System::install( Scheduler &scheduler ) {
	assert( this->scheduler == 0 );
	this->scheduler = &scheduler;
}

void System::install( InputDevice &device ) {
	if ( !input )
		input = &device;

	// devices.insert( &device );
}

void System::install( OutputDevice &device ) {
	if ( !output )
		output = &device;

	if ( !error )
		error = &device;

	// devices.insert( &device );
}

void System::install( IODevice &device ) {
	install( (InputDevice&) device );
	install( (OutputDevice&) device );
}

void System::install( Manager &service ) {

}

void System::uninstall( Device &device ) {
	warning("Before uninstall a device make sure it is not input use!");

	if ( &device == input )
		input = 0;
	if ( &device == output )
		output = 0;
	if ( &device == error )
		error = 0;

	// devices.erase( &device );
}

void System::isr( const SSID ssid, Registers &registers ) {

}

void System::reboot() const {
	_reboot();
}

void System::start() {
	memory->init();
	scheduler->init();
}

class ProgramSection {
public:
	ProgramSection( FileSystem &fs, fid_t fd, uintptr_t offset ) : fs(fs), fd(fd) {
		fs.seek( fd, offset );
		fs.read( fd, (char*) &ph, sizeof(ph) );
	}

	uintptr_t getVirtualAddress() {
		return ph.p_vaddr;
	}

	size_t getSize() {
		return ph.p_memsz;
	}

	size_t getPageSize() {
		size_t size = ( ph.p_memsz / MEMORY_PAGE_SIZE );

		if ( ph.p_memsz && ( MEMORY_PAGE_SIZE - 1 ) )
			size++;

		return size;
	}

	uintptr_t load( Memory &memory ) {
		uintptr_t page = memory.allocate( getPageSize() );

		if ( !page )
			return 0;

		fs.seek( fd, ph.p_offset );
		fs.read( fd, (char*) (ph.p_vaddr), ph.p_filesz );
		return page;
	}

	bool isLoadable() {
		return ph.p_type == PT_LOAD;
	}

private:
	FileSystem& fs;
	fid_t fd;
	Elf32_Phdr ph;
};

class ELF {
public:
	ELF ( FileSystem &fs, fid_t fd ) : fs(fs), fd(fd) {
		fs.seek( fd, 0 );
		fs.read( fd, (char*) &eh, sizeof(eh) );
	}

	int getNumberOfProgramSections() {
		return eh.e_phnum;
	}

	void* getEntryPointAddr() {
		return (void*) eh.e_entry;
	}

	const ProgramSection getProgramSection( int index ) const {
		return ProgramSection( fs, fd, (eh.e_phoff + sizeof(Elf32_Phdr) * index) );
	}

	bool isValid() {
		if ( eh.e_phentsize         != sizeof(Elf32_Phdr) ||
			 eh.e_ident[EI_MAG0]    != ELFMAG0 ||
			 eh.e_ident[EI_MAG1]    != ELFMAG1 ||
			 eh.e_ident[EI_MAG2]    != ELFMAG2 ||
			 eh.e_ident[EI_MAG3]    != ELFMAG3 ||
			 eh.e_ident[EI_CLASS]   != ELFCLASS32 ||
			 eh.e_ident[EI_DATA]    != ELFDATA2LSB ||
			 eh.e_ident[EI_VERSION] == EV_NONE ||
			 eh.e_type              != ET_EXEC ||
			 eh.e_machine           != EM_386 ) {
			return false;
		}

		return true;
	}

private:
	FileSystem &fs;
	fid_t fd;
	Elf32_Ehdr eh;
};


			// printf( "\nSEG%d\n", i );
			// printf( "offset: %d vAddr:%d fsize: %d msize: %d ", elfph.p_offset, elfph.p_vaddr, elfph.p_filesz, elfph.p_memsz );
			// printf( "flags: %c%c%c ", elfph.p_flags & PF_X ? 'X' : '_'
			// 						 , elfph.p_flags & PF_W ? 'W' : '_'
			// 						 , elfph.p_flags & PF_R ? 'R' : '_' );
			// printf( "align: %d\n", elfph.p_align );

bool System::exec( const char* path ) {
	if ( !( memory && scheduler && fs ) )
		return false;

	fid_t fd = fs->open( path );

	if ( fd < 0 )
		return false;

	ELF elf( *fs, fd );

	if ( !elf.isValid() )
		return false;

	for ( int i = 0; i < elf.getNumberOfProgramSections(); i++ ) {
		ProgramSection ps = elf.getProgramSection( i );
		
		if ( ps.isLoadable() )
			ps.load( *memory );
	}

	fs->close( fd );
	((void (*)()) elf.getEntryPointAddr())();
	return true;
}
