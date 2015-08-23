; ---------------------------------------------------------------------------*
;  Copyright (C) 2015 Alisson Linhares de Carvalho.                          *
;  All rights reserved.                                                      *
;                                                                            *
;  This file is part of the Native Kit.                                      *
;                                                                            *
;  The Native Kit is free software: you can redistribute it and/or           *
;  modify it under the terms of the GNU Lesser General Public License as     *
;  published by the Free Software Foundation, either version 3 of the        *
;  License, or (at your option) any later version.                           *
;                                                                            *
;  The Native Kit is distributed in the hope that it will be useful,         *
;  but WITHOUT ANY WARRANTY; without even the implied warranty of            *
;  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the             *
;  GNU Lesser General Public License for more details.                       *
;                                                                            *
;  You should have received a copy of the GNU Lesser General Public License  *
;  along with the Native Kit. If not, see <http://www.gnu.org/licenses/>.    *
; ---------------------------------------------------------------------------*/

BIOS_EXTENSION_ADDR EQU 0x7C00

BIOS_MANAGER_START:
	incbin "bin/16BitsInterruptColler"
BIOS_MANAGER_END:

%macro bios_config 0
	MOV ESI,BIOS_MANAGER_START
	MOV EDI,BIOS_EXTENSION_ADDR
	MOV ECX,BIOS_MANAGER_END - BIOS_MANAGER_START

	CLD
	REP MOVSB
%endmacro

bios_call:
	CLI
	PUSHAD

	MOV EDI,DWORD[ESP + 0x8 + 0x20] ; Registers &registers
	MOV EAX,DWORD[ESP + 0x4 + 0x20] ; int number

	PUSH EAX

	MOV ESI,DWORD[EDI + 0x04]
	MOV EBP,DWORD[EDI + 0x08]
	MOV EBX,DWORD[EDI + 0x10]
	MOV EDX,DWORD[EDI + 0x14]
	MOV ECX,DWORD[EDI + 0x18]
	MOV EAX,DWORD[EDI + 0x1C]
	MOV EDI,DWORD[EDI + 0x00]

	PUSH DWORD .RETURN
	JMP REAL_CODE:BIOS_EXTENSION_ADDR
.RETURN:

	LIDT [PIDT]

	PUSH EDI
	MOV EDI,DWORD[ESP + 0x10 + 0x20]
	MOV DWORD[EDI + 0x04],ESI
	MOV DWORD[EDI + 0x08],EBP
	MOV DWORD[EDI + 0x10],EBX
	MOV DWORD[EDI + 0x14],EDX
	MOV DWORD[EDI + 0x18],ECX
	MOV DWORD[EDI + 0x1C],EAX
	POP DWORD[EDI + 0x00]
	ADD ESP,0x4

	POPAD
	STI
	RET
