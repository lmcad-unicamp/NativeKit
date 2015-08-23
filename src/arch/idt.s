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

IDT:
	DW 0,KERNEL_CODE,0x8F00,0 ;Divide error
	DW 0,KERNEL_CODE,0x8F00,0 ;Debug exceptions
	DW 0,KERNEL_CODE,0x8F00,0 ;Nonmaskable interrupt exception
	DW 0,KERNEL_CODE,0x8F00,0 ;Breakpoint exception
	DW 0,KERNEL_CODE,0x8F00,0 ;Overflow exception
	DW 0,KERNEL_CODE,0x8F00,0 ;Bounds check exception
	DW 0,KERNEL_CODE,0x8F00,0 ;Invalid opcode exception
	DW 0,KERNEL_CODE,0x8F00,0 ;Coprocessor not available exception
	DW 0,KERNEL_CODE,0x8F00,0 ;Double fault exception
	DW 0,KERNEL_CODE,0x8F00,0 ;Coprocessor segment overrun exception
	DW 0,KERNEL_CODE,0x8F00,0 ;Invalid TSS exception
	DW 0,KERNEL_CODE,0x8F00,0 ;Segment not present
	DW 0,KERNEL_CODE,0x8F00,0 ;Stack exception
	DW 0,KERNEL_CODE,0x8F00,0 ;General protection exception
	DW 0,KERNEL_CODE,0x8F00,0 ;Page fault exception
	DW 0,KERNEL_CODE,0x8F00,0 ;Intel reserved
	DW 0,KERNEL_CODE,0x8F00,0 ;Coprocessor error
	DW 0,KERNEL_CODE,0x8F00,0 ;Intel reserved
	DW 0,KERNEL_CODE,0x8F00,0 ;Intel reserved
	DW 0,KERNEL_CODE,0x8F00,0 ;Intel reserved
	DW 0,KERNEL_CODE,0x8F00,0 ;Intel reserved
	DW 0,KERNEL_CODE,0x8F00,0 ;Intel reserved
	DW 0,KERNEL_CODE,0x8F00,0 ;Intel reserved
	DW 0,KERNEL_CODE,0x8F00,0 ;Intel reserved
	DW 0,KERNEL_CODE,0x8F00,0 ;Intel reserved
	DW 0,KERNEL_CODE,0x8F00,0 ;Intel reserved
	DW 0,KERNEL_CODE,0x8F00,0 ;Intel reserved
	DW 0,KERNEL_CODE,0x8F00,0 ;Intel reserved
	DW 0,KERNEL_CODE,0x8F00,0 ;Intel reserved
	DW 0,KERNEL_CODE,0x8F00,0 ;Intel reserved
	DW 0,KERNEL_CODE,0x8F00,0 ;Intel reserved
	DW 0,KERNEL_CODE,0x8F00,0 ;Intel reserved
	DW 0,KERNEL_CODE,0x8F00,0 ;System Timer
	DW 0,KERNEL_CODE,0x8F00,0 ;Keyboard
	DW 0,KERNEL_CODE,0x8F00,0 ;Intel reserved
	DW 0,KERNEL_CODE,0x8F00,0 ;COM2
	DW 0,KERNEL_CODE,0x8F00,0 ;COM1
	DW 0,KERNEL_CODE,0x8F00,0 ;LPT2
	DW 0,KERNEL_CODE,0x8F00,0 ;Floppy disk drive
	DW 0,KERNEL_CODE,0x8F00,0 ;LPT1
	DW 0,KERNEL_CODE,0x8F00,0 ;CMOS Real Time Clock
	DW 0,KERNEL_CODE,0x8F00,0 ;Intel reserved
	DW 0,KERNEL_CODE,0x8F00,0 ;Intel reserved
	DW 0,KERNEL_CODE,0x8F00,0 ;Intel reserved
	DW 0,KERNEL_CODE,0x8F00,0 ;PS/2 Mouse
	DW 0,KERNEL_CODE,0x8F00,0 ;Numeric coprocessor
	DW 0,KERNEL_CODE,0x8F00,0 ;Hard disk drive IDE1
	DW 0,KERNEL_CODE,0x8F00,0 ;Hard disk drive IDE2
	DW 0,KERNEL_CODE,0x8E00,0 ;Neutrino System Calls
	DW 0,KERNEL_CODE,0x8E00,0 ;Reserved
	DW 0,KERNEL_CODE,0x8E00,0 ;Reserved
	DW 0,KERNEL_CODE,0x8E00,0 ;Reserved
	DW 0,KERNEL_CODE,0x8E00,0 ;Reserved
	DW 0,KERNEL_CODE,0x8E00,0 ;Reserved
	DW 0,KERNEL_CODE,0x8E00,0 ;Reserved
	DW 0,KERNEL_CODE,0x8E00,0 ;Reserved
	DW 0,KERNEL_CODE,0x8E00,0 ;Reserved
	DW 0,KERNEL_CODE,0x8E00,0 ;Reserved
	DW 0,KERNEL_CODE,0x8E00,0 ;Reserved
	DW 0,KERNEL_CODE,0x8E00,0 ;Reserved
	DW 0,KERNEL_CODE,0x8E00,0 ;Reserved
	DW 0,KERNEL_CODE,0x8E00,0 ;Reserved
	DW 0,KERNEL_CODE,0x8E00,0 ;Reserved
	DW 0,KERNEL_CODE,0x8E00,0 ;Reserved
	DW 0,KERNEL_CODE,0x8E00,0 ;Reserved
	DW 0,KERNEL_CODE,0x8E00,0 ;Reserved
	DW 0,KERNEL_CODE,0x8E00,0 ;Reserved
	DW 0,KERNEL_CODE,0x8E00,0 ;Reserved
	DW 0,KERNEL_CODE,0x8E00,0 ;Reserved
	DW 0,KERNEL_CODE,0x8E00,0 ;Reserved
	DW 0,KERNEL_CODE,0x8E00,0 ;Reserved
	DW 0,KERNEL_CODE,0x8E00,0 ;Reserved
	DW 0,KERNEL_CODE,0x8E00,0 ;Reserved
	DW 0,KERNEL_CODE,0x8E00,0 ;Reserved
	DW 0,KERNEL_CODE,0x8E00,0 ;Reserved
	DW 0,KERNEL_CODE,0x8E00,0 ;Reserved
	DW 0,KERNEL_CODE,0x8E00,0 ;Reserved
	DW 0,KERNEL_CODE,0x8E00,0 ;Reserved
	DW 0,KERNEL_CODE,0x8E00,0 ;Reserved
	DW 0,KERNEL_CODE,0x8E00,0 ;Reserved
	DW 0,KERNEL_CODE,0x8E00,0 ;Reserved
	DW 0,KERNEL_CODE,0x8E00,0 ;Reserved
	DW 0,KERNEL_CODE,0x8E00,0 ;Reserved
	DW 0,KERNEL_CODE,0x8E00,0 ;Reserved
	DW 0,KERNEL_CODE,0x8E00,0 ;Reserved
	DW 0,KERNEL_CODE,0x8E00,0 ;Reserved
	DW 0,KERNEL_CODE,0x8E00,0 ;Reserved
	DW 0,KERNEL_CODE,0x8E00,0 ;Reserved
	DW 0,KERNEL_CODE,0x8E00,0 ;Reserved
	DW 0,KERNEL_CODE,0x8E00,0 ;Reserved
	DW 0,KERNEL_CODE,0x8E00,0 ;Reserved
	DW 0,KERNEL_CODE,0x8E00,0 ;Reserved
	DW 0,KERNEL_CODE,0x8E00,0 ;Reserved
	DW 0,KERNEL_CODE,0x8E00,0 ;Reserved
	DW 0,KERNEL_CODE,0x8E00,0 ;Reserved
	DW 0,KERNEL_CODE,0x8E00,0 ;Reserved
	DW 0,KERNEL_CODE,0x8E00,0 ;Reserved
	DW 0,KERNEL_CODE,0x8E00,0 ;Reserved
	DW 0,KERNEL_CODE,0x8E00,0 ;Reserved
	DW 0,KERNEL_CODE,0x8E00,0 ;Reserved
	DW 0,KERNEL_CODE,0x8E00,0 ;Reserved
	DW 0,KERNEL_CODE,0x8E00,0 ;Reserved
	DW 0,KERNEL_CODE,0x8E00,0 ;Reserved
	DW 0,KERNEL_CODE,0x8E00,0 ;Reserved
	DW 0,KERNEL_CODE,0x8E00,0 ;Reserved
	DW 0,KERNEL_CODE,0x8E00,0 ;Reserved
	DW 0,KERNEL_CODE,0x8E00,0 ;Reserved
	DW 0,KERNEL_CODE,0x8E00,0 ;Reserved
	DW 0,KERNEL_CODE,0x8E00,0 ;Reserved
	DW 0,KERNEL_CODE,0x8E00,0 ;Reserved
	DW 0,KERNEL_CODE,0x8E00,0 ;Reserved
	DW 0,KERNEL_CODE,0x8E00,0 ;Reserved
	DW 0,KERNEL_CODE,0x8E00,0 ;Reserved
	DW 0,KERNEL_CODE,0x8E00,0 ;Reserved
	DW 0,KERNEL_CODE,0x8E00,0 ;Reserved
	DW 0,KERNEL_CODE,0x8E00,0 ;Reserved
	DW 0,KERNEL_CODE,0x8E00,0 ;Reserved
	DW 0,KERNEL_CODE,0x8E00,0 ;Reserved
	DW 0,KERNEL_CODE,0x8E00,0 ;Reserved
	DW 0,KERNEL_CODE,0x8E00,0 ;Reserved
	DW 0,KERNEL_CODE,0x8E00,0 ;Reserved
	DW 0,KERNEL_CODE,0x8E00,0 ;Reserved
	DW 0,KERNEL_CODE,0x8E00,0 ;Reserved
	DW 0,KERNEL_CODE,0x8E00,0 ;Reserved
	DW 0,KERNEL_CODE,0x8E00,0 ;Reserved
	DW 0,KERNEL_CODE,0x8E00,0 ;Reserved
	DW 0,KERNEL_CODE,0x8E00,0 ;Reserved
	DW 0,KERNEL_CODE,0x8E00,0 ;Reserved
	DW 0,KERNEL_CODE,0x8E00,0 ;Linux syscalls
	DW 0,KERNEL_CODE,0x8E00,0 ;Reserved
	DW 0,KERNEL_CODE,0x8E00,0 ;Reserved
	DW 0,KERNEL_CODE,0x8E00,0 ;Reserved
	DW 0,KERNEL_CODE,0x8E00,0 ;Reserved
	DW 0,KERNEL_CODE,0x8E00,0 ;Reserved
	DW 0,KERNEL_CODE,0x8E00,0 ;Reserved
	DW 0,KERNEL_CODE,0x8E00,0 ;Reserved
	DW 0,KERNEL_CODE,0x8E00,0 ;Reserved
	DW 0,KERNEL_CODE,0x8E00,0 ;Reserved
	DW 0,KERNEL_CODE,0x8E00,0 ;Reserved
	DW 0,KERNEL_CODE,0x8E00,0 ;Reserved
	DW 0,KERNEL_CODE,0x8E00,0 ;Reserved
	DW 0,KERNEL_CODE,0x8E00,0 ;Reserved
	DW 0,KERNEL_CODE,0x8E00,0 ;Reserved
	DW 0,KERNEL_CODE,0x8E00,0 ;Reserved
	DW 0,KERNEL_CODE,0x8E00,0 ;Reserved
	DW 0,KERNEL_CODE,0x8E00,0 ;Reserved
	DW 0,KERNEL_CODE,0x8E00,0 ;Reserved
	DW 0,KERNEL_CODE,0x8E00,0 ;Reserved
	DW 0,KERNEL_CODE,0x8E00,0 ;Reserved
	DW 0,KERNEL_CODE,0x8E00,0 ;Reserved
	DW 0,KERNEL_CODE,0x8E00,0 ;Reserved
	DW 0,KERNEL_CODE,0x8E00,0 ;Reserved
	DW 0,KERNEL_CODE,0x8E00,0 ;Reserved
	DW 0,KERNEL_CODE,0x8E00,0 ;Reserved
	DW 0,KERNEL_CODE,0x8E00,0 ;Reserved
	DW 0,KERNEL_CODE,0x8E00,0 ;Reserved
	DW 0,KERNEL_CODE,0x8E00,0 ;Reserved
	DW 0,KERNEL_CODE,0x8E00,0 ;Reserved
	DW 0,KERNEL_CODE,0x8E00,0 ;Reserved
	DW 0,KERNEL_CODE,0x8E00,0 ;Reserved
	DW 0,KERNEL_CODE,0x8E00,0 ;Reserved
	DW 0,KERNEL_CODE,0x8E00,0 ;Reserved
	DW 0,KERNEL_CODE,0x8E00,0 ;Reserved
	DW 0,KERNEL_CODE,0x8E00,0 ;Reserved
	DW 0,KERNEL_CODE,0x8E00,0 ;Reserved
	DW 0,KERNEL_CODE,0x8E00,0 ;Reserved
	DW 0,KERNEL_CODE,0x8E00,0 ;Reserved
	DW 0,KERNEL_CODE,0x8E00,0 ;Reserved
	DW 0,KERNEL_CODE,0x8E00,0 ;Reserved
	DW 0,KERNEL_CODE,0x8E00,0 ;Reserved
	DW 0,KERNEL_CODE,0x8E00,0 ;Reserved
	DW 0,KERNEL_CODE,0x8E00,0 ;Reserved
	DW 0,KERNEL_CODE,0x8E00,0 ;Reserved
	DW 0,KERNEL_CODE,0x8E00,0 ;Reserved
	DW 0,KERNEL_CODE,0x8E00,0 ;Reserved
	DW 0,KERNEL_CODE,0x8E00,0 ;Reserved
	DW 0,KERNEL_CODE,0x8E00,0 ;Reserved
	DW 0,KERNEL_CODE,0x8E00,0 ;Reserved
	DW 0,KERNEL_CODE,0x8E00,0 ;Reserved
	DW 0,KERNEL_CODE,0x8E00,0 ;Reserved
	DW 0,KERNEL_CODE,0x8E00,0 ;Reserved
	DW 0,KERNEL_CODE,0x8E00,0 ;Reserved
	DW 0,KERNEL_CODE,0x8E00,0 ;Reserved
	DW 0,KERNEL_CODE,0x8E00,0 ;Reserved
	DW 0,KERNEL_CODE,0x8E00,0 ;Reserved
	DW 0,KERNEL_CODE,0x8E00,0 ;Reserved
	DW 0,KERNEL_CODE,0x8E00,0 ;Reserved
	DW 0,KERNEL_CODE,0x8E00,0 ;Reserved
	DW 0,KERNEL_CODE,0x8E00,0 ;Reserved
	DW 0,KERNEL_CODE,0x8E00,0 ;Reserved
	DW 0,KERNEL_CODE,0x8E00,0 ;Reserved
	DW 0,KERNEL_CODE,0x8E00,0 ;Reserved
	DW 0,KERNEL_CODE,0x8E00,0 ;Reserved
	DW 0,KERNEL_CODE,0x8E00,0 ;Reserved
	DW 0,KERNEL_CODE,0x8E00,0 ;Reserved
	DW 0,KERNEL_CODE,0x8E00,0 ;Reserved
	DW 0,KERNEL_CODE,0x8E00,0 ;Reserved
	DW 0,KERNEL_CODE,0x8E00,0 ;Reserved
	DW 0,KERNEL_CODE,0x8E00,0 ;Reserved
	DW 0,KERNEL_CODE,0x8E00,0 ;Reserved
	DW 0,KERNEL_CODE,0x8E00,0 ;Reserved
	DW 0,KERNEL_CODE,0x8E00,0 ;Reserved
	DW 0,KERNEL_CODE,0x8E00,0 ;Reserved
	DW 0,KERNEL_CODE,0x8E00,0 ;Reserved
	DW 0,KERNEL_CODE,0x8E00,0 ;Reserved
	DW 0,KERNEL_CODE,0x8E00,0 ;Reserved
	DW 0,KERNEL_CODE,0x8E00,0 ;Reserved
	DW 0,KERNEL_CODE,0x8E00,0 ;Reserved
	DW 0,KERNEL_CODE,0x8E00,0 ;Reserved
	DW 0,KERNEL_CODE,0x8E00,0 ;Reserved
	DW 0,KERNEL_CODE,0x8E00,0 ;Reserved
	DW 0,KERNEL_CODE,0x8E00,0 ;Reserved
	DW 0,KERNEL_CODE,0x8E00,0 ;Reserved
	DW 0,KERNEL_CODE,0x8E00,0 ;Reserved
	DW 0,KERNEL_CODE,0x8E00,0 ;Reserved
	DW 0,KERNEL_CODE,0x8E00,0 ;Reserved
	DW 0,KERNEL_CODE,0x8E00,0 ;Reserved
	DW 0,KERNEL_CODE,0x8E00,0 ;Reserved
	DW 0,KERNEL_CODE,0x8E00,0 ;Reserved
	DW 0,KERNEL_CODE,0x8E00,0 ;Reserved
	DW 0,KERNEL_CODE,0x8E00,0 ;Reserved
	DW 0,KERNEL_CODE,0x8E00,0 ;Reserved
	DW 0,KERNEL_CODE,0x8E00,0 ;Reserved
	DW 0,KERNEL_CODE,0x8E00,0 ;Reserved
	DW 0,KERNEL_CODE,0x8E00,0 ;Reserved
	DW 0,KERNEL_CODE,0x8E00,0 ;Reserved
	DW 0,KERNEL_CODE,0x8E00,0 ;Reserved
	DW 0,KERNEL_CODE,0x8E00,0 ;Reserved
	DW 0,KERNEL_CODE,0x8E00,0 ;Reserved
	DW 0,KERNEL_CODE,0x8E00,0 ;Reserved
	DW 0,KERNEL_CODE,0x8E00,0 ;Reserved
	DW 0,KERNEL_CODE,0x8E00,0 ;Reserved
	DW 0,KERNEL_CODE,0x8E00,0 ;Reserved
	DW 0,KERNEL_CODE,0x8E00,0 ;Reserved
	DW 0,KERNEL_CODE,0x8E00,0 ;Reserved
	DW 0,KERNEL_CODE,0x8E00,0 ;Reserved
	DW 0,KERNEL_CODE,0x8E00,0 ;Reserved
	DW 0,KERNEL_CODE,0x8E00,0 ;Reserved
	DW 0,KERNEL_CODE,0x8E00,0 ;Reserved
	DW 0,KERNEL_CODE,0x8E00,0 ;Reserved
	DW 0,KERNEL_CODE,0x8E00,0 ;Reserved
	DW 0,KERNEL_CODE,0x8E00,0 ;Reserved
	DW 0,KERNEL_CODE,0x8E00,0 ;Reserved
	DW 0,KERNEL_CODE,0x8E00,0 ;Reserved
	DW 0,KERNEL_CODE,0x8E00,0 ;Reserved
	DW 0,KERNEL_CODE,0x8E00,0 ;Reserved
	DW 0,KERNEL_CODE,0x8E00,0 ;Reserved
	DW 0,KERNEL_CODE,0x8E00,0 ;Reserved
	DW 0,KERNEL_CODE,0x8E00,0 ;Reserved
	DW 0,KERNEL_CODE,0x8E00,0 ;Reserved
	DW 0,KERNEL_CODE,0x8E00,0 ;Reserved
	DW 0,KERNEL_CODE,0x8E00,0 ;Reserved
	DW 0,KERNEL_CODE,0x8E00,0 ;Reserved
	DW 0,KERNEL_CODE,0x8E00,0 ;Reserved
	DW 0,KERNEL_CODE,0x8E00,0 ;Reserved
	DW 0,KERNEL_CODE,0x8E00,0 ;Reserved
PIDT DW PIDT - IDT
	DD IDT

%macro idt_config 0
	MOV EDI, IDT
	MOV ESI, isr.l0

	%%loop:
		MOV EAX,ESI

		MOV WORD[EDI    ],AX
		SHR EAX,16
		MOV WORD[EDI + 6],AX

		ADD EDI,8

		CMP ESI,isr.master
		JB %%defautMap
		CMP ESI,isr.slave
		JB %%masterPicMap
		CMP ESI,isr.service
		JAE %%defautMap
		%%slavePicMap:
			ADD ESI,SLAVE_ISR_SIZE
			JMP %%continue
		%%masterPicMap:
			ADD ESI,MASTER_ISR_SIZE
			JMP %%continue
		%%defautMap:
			ADD ESI,DEFAULT_ISR_SIZE
		%%continue:

	CMP EDI, PIDT
	JB %%loop

	LIDT [PIDT]
%endmacro
