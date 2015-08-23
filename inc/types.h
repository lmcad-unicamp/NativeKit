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

#ifndef TYPE_H
#define TYPE_H

#include <stdint.h>
#include <stddef.h>

#define MULTIBOOT_MEMORY_AVAILABLE              1
#define MULTIBOOT_MEMORY_RESERVED               2

struct tMemoryMap {
	uint32_t size;
	uint64_t addr;
	uint64_t len;
	uint32_t type;
} __attribute__((packed));

struct tModuleInfo {
	const uint32_t modStart;
	const uint32_t modEnd;
	const uint32_t cmdline;
	const uint32_t pad;
}__attribute__((packed));

struct tMultibootInfo {
	const uint32_t flags;
	const uint32_t lowerMemory;
	const uint32_t upperMemory;
	const uint32_t bootDevice;
	const uint32_t cmdline;
	const uint32_t numberOfModules;
	const tModuleInfo* listOfModules;
	const uint32_t elfSecNum;
	const uint32_t elfSecSize;
	const uint32_t elfSecAddr;
	const uint32_t elfshndx;
	const uint32_t mmapLength;
	tMemoryMap* mmapPtr;
	const uint32_t drivesLength;
	const uint32_t drivesAddr;
	const uint32_t configTable;
	const uint8_t* name;
	const uint32_t apmTable;
	const uint32_t vbeControlInfo;
	const uint32_t vbeModeInfo;
	const uint16_t vbeMode;
	const uint16_t vbeInterfaceSeg;
	const uint16_t vbeInterfaceOff;
	const uint16_t vbeInterfaceLen;
}__attribute__((packed));

struct tMultibootHeader {
	const uint32_t magic;
	const uint32_t flags;
	const uint32_t checksum;
	tMultibootInfo *mbInfo;
}__attribute__((packed));

#endif
