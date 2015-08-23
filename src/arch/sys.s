; ---------------------------------------------------------------------------*
;  Copyright (C) 2011 Alisson Linhares de Carvalho.                          *
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

;-----------------------------------------------------------------------------
;------------------------- extern declarations -------------------------------
[extern _stack_top]
[extern _stack_base]
[extern _init     ]
[extern _fini     ]

;-----------------------------------------------------------------------------
;------------------------- extern declarations -------------------------------
%include "src/arch/debug.s"
%include "src/arch/mem.s"
%include "src/arch/idt.s"
%include "src/arch/gdt.s"
%include "src/arch/isr.s"
%include "src/arch/bios.s"

%macro write_port60 0
	%%writeLoop:
		;Esperando a controlador ficar pronta para escrita
		IN AL,0x64
	AND AL,2
	JNZ %%writeLoop
%endmacro

%macro read_port60 0
	%%readLoop:
		IN AL,064h
	AND AL,1
	JZ %%readLoop
%endmacro

%macro sys_config 0
	CLI

	MOV EAX,CR0
	AND EAX,~12
	MOV CR0,EAX
	FINIT

	gdt_config
	isr_config
	idt_config
	mem_config
	bios_config

	CALL _init
	STI

	CALL main
	CALL _fini
%endmacro

%macro sys_start 0
%endmacro

%macro sys_reboot 0
	;Preparando para escrever na porta 0x60
	write_port60
	
	;Mandando 0xFE para controladora de teclado
	MOV AL,0xFE
	OUT 0x64,AL
%endmacro
