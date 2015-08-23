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

[bits 32           ]

[global _start     ]
[global _reboot    ]
[global _sstate    ]
[global _lstate    ]
[global _pdupdate  ]
[global _pdprotect ]
[global _pdcreate  ]
[global _ptcreate  ]
[global _pdload    ]
[global _pdsave    ]
[global _callBIOSSubRotine ]
[extern main       ]

%include "src/arch/multiboot.s"
%include "src/arch/sys.s"

_start:
	multiboot_config EBX

	sys_config
	sys_start
	JMP $

_reboot:
	sys_reboot
	RET

_sstate:

	RET

_lstate:

	RET

_pdprotect:

	RET

_pdcreate:
	mem_createPageDirectory
	RET

_pdload:
	mem_loadPageDirectory
	RET

_pdsave:
	mem_savePageDirectory
	RET

_ptcreate:
	mem_createPageTable
	RET

_pdupdate:
	mem_updatePageTable
	RET

; void _CallBIOSSubRotine( Register& registers, int number );
_callBIOSSubRotine: EQU bios_call
