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
;                     20[31..11]  3[11..8] 7 6 5 4 3 2 1 0                   *
;                     PAGE_PTR    RESERVED S0ADWURP                          *
;                                   0000   10000011                          *
;     S = Page Size stores the page size for that specific entry. If the bit *
;  is set, then pages are 4 MiB in size. Otherwise, they are 4 KiB. Please   *
;  note that for 4 MiB pages PSE have to be enabled.                         *
;     A = Accessed is used to discover whether a page has been read or       *
;  written to. If it has, then the bit is set, otherwise, it is not. Note    *
;  that, this bit will not be cleared by the CPU, so that burden falls on the*
;  OS (if it needs this bit at all).                                         *
;     D = Cache Disable bit. If the bit is set, the page will not be cached. *
;  Otherwise, it will be.                                                    *
;     W = Write-Through abilities of the page. If the bit is set,            *
;  write-through caching is enabled. If not, then write-back is enabled      *
;  instead.                                                                  *
;     U = User\Supervisor bit, controls access to the page based on          *
;  privilege level. If the bit is set, then the page may be accessed by all; *
;  if the bit is not set, however, only the supervisor can access it.        *
;     R = Read/Write permissions flag. If the bit is set, the page is        *
;  read/write. Otherwise when it is not set, the page is read-only. The WP   *
;  bit in CR0 determines if this is only applied to userland, always giving  *
;  the kernel write access (the default) or both userland and the kernel     *
;  (see Intel Manuals 3A 2-20).                                              *
;     P = Present. If the bit is set, the page is actually in physical mem   *
;  at the moment. For example, when a page is swapped out, it is not in      *
;  physical mem and therefore not 'Present'. If a page is called, but not    *
;  present, a page fault will occur, and the OS should handle it.            *
; -------------------------------------------------------------------------- *
ALIGNMENT     TIMES 4096 - ($-$$) DB 0
pagedirectory TIMES 1024 DD 0

%macro mem_config 0
	; config the kernel mem
	MOV EAX,0x83 ; using 4mb page table to reduce tlb misses.
	MOV EDI,pagedirectory
	MOV ECX,1024

	; initializing the kernel page table
	%%loop:
		MOV DWORD[EDI],EAX
		ADD EDI,4
		ADD EAX,0x400000
	DEC ECX
    JNZ %%loop

	MOV EAX,pagedirectory
	MOV CR3,EAX ; load page directory

	; enable PSE to use 4mb page size.
	MOV EAX, CR4
	OR EAX, 0x00000010
	MOV CR4, EAX

	; enable paging
	MOV EAX,CR0
	OR EAX,0x80000001 ; set PE and PEG bits.
	MOV CR0,EAX
%endmacro

%macro mem_initTable 2
	MOV EDI,%1
	LEA EAX,[EDI + 4096]

	%%loop:
		MOV DWORD[EDI],%2
		ADD EDI,4
	CMP EDI,EAX
	JB %%loop
%endmacro

%macro param 2
	%define %1 DWORD[ESP+%2]
%endmacro

; extern "C" void _ptcreate( pTable, pDir, base );
%macro mem_createPageTable 0
	param %%pTable    ,12
	param %%pDir      ,16
	param %%base      ,20

	PUSH EAX
	PUSH EDI

	mem_initTable %%pTable, 0 ;pTable

	MOV EAX,%%pTable
	OR EAX,7

	MOV EDI,%%base
	AND EDI,0xFFC00000
	SHR EDI,20
	ADD EDI,%%pDir

	MOV DWORD[EDI],EAX

	POP EDI
	POP EAX
%endmacro

; extern "C" void _pdcreate( void *buffer );
%macro mem_createPageDirectory 0
	param %%pTable    ,12

	PUSH EAX
	PUSH EDI

	mem_initTable %%pTable, 0

	POP EDI
	POP EAX
%endmacro

; extern "C" base _pdupdate( void* pDir, void *vAddr, void *pAddr, uint8_t permission, size_t size = 1 );
%macro mem_updatePageTable 0
	param %%pDir        ,12
	param %%vAddr       ,16
	param %%pAddr       ,20
	param %%permissions ,24
	param %%size        ,28

	PUSH EDI
	PUSH EDX

	MOV EDI,%%pDir

	; loading the page table.
	MOV EAX,%%vAddr
	MOV EDX,EAX
	SHR EAX,22
	MOV EDI,DWORD[EDI + EAX*4]

	; checking if the page table is present.
	TEST EDI,1
	JZ %%abort
		; config the physical address
		MOV EAX,%%pAddr
		AND EAX,0xFFFFF000

		TEST %%permissions, 1
		JNZ %%readOnly
			OR EAX,7
			JMP %%continue
		%%readOnly:
			OR EAX,5
		%%continue:

		; finding the right page reference
		AND EDI,0xFFFFFFF8
		AND EDX,0x3FF000
		SHR EDX,10
		ADD EDI,EDX

		; update the page table
		MOV ECX,%%size
		
		%%loop:
			MOV DWORD[EDI],EAX
			ADD EAX,4096
			ADD EDI,4
		DEC ECX
		JNZ %%loop

		XOR EAX,EAX
		JMP %%done
	%%abort:
		MOV EAX,1
	%%done:

	POP EDX
	POP EDI
%endmacro

%macro mem_loadPageDirectory 0
	param %%dir ,8

	PUSH EAX
	MOV EAX,%%dir
	MOV CR3,EAX ; load page directory
	POP EAX
%endmacro

%macro mem_savePageDirectory 0
	param %%dir ,12

	PUSH EDI
	PUSH EAX

	MOV EDI,%%dir
	MOV EAX,CR3
	MOV DWORD[EDI],EAX ; save page directory

	POP EAX
	POP EDI
%endmacro
