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
; ---------------------------------------------------------------------------*
; ---------------------------------------------------------------------------*
;   The Global Descriptor Table is a structure used by the x86 family        *
;  processor to manage the memory access. The GDT defines base access        *
;  privileges for certain parts of memory. For now we have 3 modes of        *
;  operations:                                                               *
;   1. Real mode: Used for backward compatibility, this is a 16 bits mode    *
; that can access the bios and has 1mb memory limitation.                    *
;   2. Kernel mode: a 32 bits mode that basically can do everything. We need *
; to stay in this mode to access the kernel space. In this mode we can access*
; all memory available ( 4gb of memory ).                                    *
;   3. User mode: a 32 bits mode created for user level purpose. For now the *
; user space has the same permission of the kernel, but we are going to      *
; change that in the future.                                                 *
; -------------------------------------------------------------------------- *

GDT:
	NULL         EQU $ - GDT
		DW 0,0
		DB 0,0,0,0
	REAL_CODE    EQU $ - GDT  ; 16bits Protected Mode "Real Mode"
		DW 0xFFFF,0
		DB 0,0x98,0x0F,0
	REAL_DATA    EQU $ - GDT  ; 16bits Protected Mode "Real Mode"
		DW 0xFFFF,0
		DB 0,0x92,0x0F,0
	KERNEL_CODE  EQU $ - GDT  ; 32bits Protected Mode "Kernel Ring0"
		DW 0xFFFF,0
		DB 0,0x9A,0xCF,0
	KERNEL_DATA  EQU $ - GDT  ; 32bits Protected Mode "Kernel Ring0"
		DW 0xFFFF,0
		DB 0,0x92,0xCF,0
	USER_CODE    EQU $ - GDT  ; 32bits Protected Mode "Users Ring0"
		DW 0xFFFF,0
		DB 0,0x98,0xCF,0
	USER_DATA    EQU $ - GDT  ; 32bits Protected Mode "Users Ring0"
		DW 0xFFFF,0
		DB 0,0x92,0xCF,0
PGDT    DW PGDT - GDT         ; GDT SIZE
		DD GDT                ; GDT OFFSET

; Macro to configure the kernel mode;
%macro gdt_config 0
	; Load GDT
	LGDT [PGDT]

	; Enable 32bits protected mode
	MOV EAX,KERNEL_DATA

	MOV DS,EAX
	MOV ES,EAX
	MOV SS,EAX
	MOV FS,EAX
	MOV GS,EAX
	MOV ESP,_stack_top

	JMP KERNEL_CODE:%%KERNEL_MODE
	%%KERNEL_MODE:
%endmacro
