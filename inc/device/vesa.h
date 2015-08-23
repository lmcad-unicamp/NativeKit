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

#ifndef VESA_H
#define VESA_H

#include <outputdevice.h>
#include <list>
#include <cmath>
#include <uart.h>
#include <outputdevice.h>

#define VESA_LOW_MEMORY_BUFFER 0x500

#define VESA_MODE_SUPPORTED                 0x1
#define VESA_MODE_INFO_AVAILABLE            0x2
#define VESA_BIOS_OUTPUT_SUPPORTED          0x4
#define VESA_COLOR_MODE_SUPPORTED           0x8
#define VESA_GRAPHICS_MODE                  0x10
#define VESA_VGA_INCOMPATIBLE               0x20
#define VESA_BANK_SWITCHED_NOT_SUPPORTED    0x40
#define VESA_LFB_SUPPORTED                  0x80
#define VESA_DOUBLE_SCAN_AVAILABLE          0x100
#define VESA_INTERLACED_MODE_AVAILABLE      0x200
#define VESA_TRIPLE_BUFFERING_SUPPORTED     0x400
#define VESA_STEREOSCOPIC_DISPLAY_SUPPORTED 0x800
#define VESA_DUAL_DISPLAY_ADDRESS_SUPPORTED 0x1000

#define REALPTR( addr ) (((addr & 0xFFFF0000) >> 12) + (addr & 0xFFFF))

struct VBEInfo {
	char signature[4];
	uint16_t version;
	uint32_t oem;
	uint32_t capabilities;
	uint32_t listOfModesPtr;
	uint16_t memorySize;
	uint32_t vendorNamePtr;
	uint32_t productNamePtr;
	uint32_t productVersionPtr;
	uint16_t vbeafVersion;
	uint32_t acceleratedModesPtr;

	void init() {
		signature[0] = 'V';
		signature[1] = 'B';
		signature[2] = 'E';
		signature[3] = '2';
	}

	bool isValid() {
		return signature[0] == 'V'  &&
			   signature[1] == 'E'  &&
			   signature[2] == 'S'  &&
			   signature[3] == 'A';
	}
} __attribute__((__packed__));

struct VBEMode {
	uint16_t modeAttrib;     // Mode attributes
	uint8_t  winA;           // Window attributes A
	uint8_t  winB;           // Window attributes B
	uint16_t granularity;    // Window granularity in KB
	uint16_t winSize;        // Window size in KB
	uint16_t segmentA;       // Start segment of window A (0000h if not supported)
	uint16_t segmentB;       // Start segment of window B (0000h if not supported)
	uint32_t farWindowFunc;  // FAR window positioning function
	uint16_t bytesPerLine;   // Bytes per scan line
	uint16_t width;
	uint16_t height;
	uint8_t widthChar;       // Width of character cell in pixels
	uint8_t heightChar;      // Height of character cell in pixels
	uint8_t numberOfPlanes;
	uint8_t bpp;             // Number of bits per pixel
	uint8_t numberOfBanks;
	uint8_t memoryModel;
	uint8_t bankSize;
	uint8_t numberOfImagePages; // Number of image pages (less one) that will fit in video RAM
	uint8_t reserved0;
	uint8_t redMaskSize;
	uint8_t redFieldPos;
	uint8_t greenMaskSize;
	uint8_t greenFieldPos;
	uint8_t blueMaskSize;
	uint8_t blueFieldPos;
	uint8_t reservedMaskSize;
	uint8_t reservedMaskPos;
	uint8_t directColorModeInfo;
	uint32_t videoBuffer;
	uint32_t offscreenMemory;
	uint16_t offscreenSize;

	bool isValid() {
		static const uint16_t vesaMask = ( VESA_MODE_SUPPORTED | VESA_MODE_INFO_AVAILABLE | VESA_GRAPHICS_MODE | VESA_LFB_SUPPORTED );
		return (( modeAttrib & vesaMask ) == vesaMask ) && ( bpp == 16 || bpp == 24 || bpp == 32 );
	}

	void copy( VBEMode *mode ) {
		char *dst = (char*) this;
		char *src = (char*) mode;

		for ( unsigned int i = 0; i < sizeof(VBEMode); i++ )
			dst[i] = src[i];
	}
} __attribute__((__packed__));

struct VesaMode {
	unsigned short id;
	unsigned short width;
	unsigned short height;
	unsigned char bpp;

	VesaMode( unsigned short id, unsigned short width, unsigned short height,
			unsigned char bpp ) : id(id), width(width),
			height(height), bpp(bpp) {
	}
};

class Vesa : public OutputDevice {
public:
	Vesa( unsigned short width = 800, unsigned short height = 600, unsigned char bpp = 24 ) : modes(0), width(width), height(height), bpp(bpp) {
		modes.clear();
		reset();
	}

	uint32_t calcResolutionFactor( unsigned short width = 800, unsigned short height = 600, unsigned char bpp = 24 ) {
		if (( width > this->width ) && ( height > this->height ) && ( bpp >= this->bpp ))
			return width * height - this->width * this->height;

		return abs(((uint32_t)( 1 << this->bpp ) + this->width * this->height ) - ((uint32_t)(1 << bpp) + width * height ));
	}

	void reset() {
		VBEInfo *vInfo = (VBEInfo*) VESA_LOW_MEMORY_BUFFER;
		VBEMode *mInfo = (VBEMode*) (VESA_LOW_MEMORY_BUFFER + 0x400);
		uint32_t currRF = 0;
		uint32_t bestRF = -1;

		vInfo->init();

		Registers registers;
		registers.clear();
		registers.r0 = 0x4F00;
		registers.r5 = (uintptr_t) vInfo;
		_callBIOSSubRotine( 0x10, registers );

		if ( vInfo->isValid() ) {
			VesaMode *bestMode = 0;

			for ( uint16_t* listOfModes = (uint16_t*) REALPTR(vInfo->listOfModesPtr); *listOfModes != 0xFFFF; listOfModes++ ) {
				registers.clear();
				registers.r0 = 0x4F01;
				registers.r2 = *listOfModes;
				registers.r5 = (uintptr_t) mInfo;
				_callBIOSSubRotine( 0x10, registers );

				if ( registers.r0 == 0x004F && mInfo->isValid() ) {
					VesaMode *currMode = new VesaMode( *listOfModes, mInfo->width, mInfo->height, mInfo->bpp );
					currRF = calcResolutionFactor( mInfo->width, mInfo->height, mInfo->bpp );

					if ( currRF < bestRF ) {
						bestMode = currMode;
						bestRF   = currRF;
					}

					modes.push_front( currMode );
				}
			}
			
			setVideoMode( bestMode );
		}
	}

	void write( const char value ) {
		while(true);
	}

	bool isReady() {
		return true;
	}

	size_t write( const char* src, size_t size ) {
		char* dst = ((char*) getVBuffer());

		double deltaX = (double) width / (double) vmode.width;
		double deltaY = (double) height / (double) vmode.height;

		int pixelSize  = vmode.bpp  / 8;
		double rRation = (double) vmode.redMaskSize   / 8.0;
		double gRation = (double) vmode.greenMaskSize / 8.0;
		double bRation = (double) vmode.blueMaskSize  / 8.0;

		uint32_t rMask = (1 << vmode.redMaskSize  ) - 1;
		uint32_t gMask = (1 << vmode.greenMaskSize) - 1;
		uint32_t bMask = (1 << vmode.blueMaskSize ) - 1;
		uint32_t rgbMask = 0xFFFFFFFF - ((rMask << vmode.redFieldPos) + (gMask << vmode.greenFieldPos) + (bMask << vmode.blueFieldPos));

		for ( int y = 0; y < vmode.height - 1; y++ ) {
			unsigned int posY = (double) round( deltaY * y );

			for ( int x = 0; x < vmode.width; x++ ) {
				unsigned int posX = (double) round( deltaX * x );
				unsigned int position = ( posY * width + posX ) * 3;

				uint8_t r = (double) round( src[ position + 2 ] * rRation );
				uint8_t g = (double) round( src[ position + 1 ] * gRation );
				uint8_t b = (double) round( src[ position + 0 ] * bRation );

				uint32_t* pixel = (uint32_t*) (dst + y * vmode.bytesPerLine + x * pixelSize);
				*pixel = rgbMask;
				*pixel = r << vmode.redFieldPos | g << vmode.greenFieldPos | b << vmode.blueFieldPos;
			}
		}

		return size;
	}

	char* getVBuffer() {
		return (char*) vmode.videoBuffer;
	}

	const std::list<VesaMode*>& getAllSupportedModes() {
		return this->modes;
	}

	void setWidth( unsigned short width ) {
		this->width = width;
	}

	void setHeight( unsigned short height ) {
		this->height = height;
	}

	bool setVideoMode( VesaMode *mode ) {
		if ( mode ) {
			Registers registers;
			registers.clear();
			registers.r0 = 0x4F01;
			registers.r2 = mode->id;
			registers.r5 = VESA_LOW_MEMORY_BUFFER;
			_callBIOSSubRotine( 0x10, registers );

			if ( registers.r0 != 0x004F )
				return false;

			registers.r0 = 0x4F02;
			registers.r1 = mode->id | 0x4000;
			registers.r5 = VESA_LOW_MEMORY_BUFFER;
			_callBIOSSubRotine( 0x10, registers );

			if ( registers.r0 == 0x004F ) {
				vmode.copy( (VBEMode*) VESA_LOW_MEMORY_BUFFER );
				return true;
			}
		}

		return false;
	}
private:
	std::list<VesaMode*> modes;
	VBEMode vmode;
	unsigned short width;
	unsigned short height;
	unsigned char bpp;
};

#endif

