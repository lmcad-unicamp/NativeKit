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

[org 0x7C00]
[bits 16]

%macro bios_ConfigSegRegisters 1
	MOV EAX,%1
	MOV DS,EAX
	MOV ES,EAX
	MOV SS,EAX
	MOV FS,EAX
	MOV GS,EAX
%endmacro

%macro bios_EnterRealMode 0
	CLI
	; 16bits protected mode selector
	bios_ConfigSegRegisters 0x10

	; disable paging and enable 16-bit pmode.
	MOV EAX,CR0
	MOV DWORD[REGISTERS.CR0],EAX
	AND EAX,0x7FFFFFFE
	MOV CR0,EAX

	JMP 0x0:%%REAL_MODE
	%%REAL_MODE:

	LIDT [IDT_REAL_MODE]

	MOV SP,0x8000
	bios_ConfigSegRegisters 0x0
%endmacro

%macro bios_ExitRealMode 0
	CLI
	
	MOV EAX,DWORD[REGISTERS.CR0]
	MOV CR0,EAX

	bios_ConfigSegRegisters 0x20 ; kernel mode selector

	JMP 0x18:%%KERNEL_MODE
[bits 32]
	%%KERNEL_MODE:
%endmacro

bios_IsrManager:
	MOV DWORD[REGISTERS.ESP],ESP
	MOV DWORD[REGISTERS.EAX],EAX

	; Change the interruption argument. INT 0xYY is equal to "0xCDYY"
	MOV EAX,DWORD[ESP + 4]
	MOV BYTE[INTERRUPT + 1],AL

	bios_EnterRealMode

	MOV EAX,DWORD[REGISTERS.EAX]

	INTERRUPT:
		INT 0x10

	MOV DWORD[REGISTERS.EAX],EAX

	bios_ExitRealMode

	MOV ESP,DWORD[REGISTERS.ESP]
	MOV EAX,DWORD[REGISTERS.EAX]
	RET

IDT_REAL_MODE:
	.size   DW 0x3FF
	.offset DD 0

REGISTERS:
	.ESP DD 0
	.EAX DD 0
	.CR0 DD 0
