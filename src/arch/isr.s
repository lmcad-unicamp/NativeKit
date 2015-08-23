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
[extern __interrupt_handler]

MASTER_ISR_SIZE  EQU isr.l33 - isr.l32
SLAVE_ISR_SIZE   EQU isr.l41 - isr.l40
DEFAULT_ISR_SIZE EQU isr.l1  - isr.l0

%macro interrupt 1
	PUSHAD

	PUSH DWORD ESP
	PUSH DWORD %1

	CALL __interrupt_handler

	%if %1 >= 0x20
		%if %1 <= 0x2F
			MOV AL,0x20

			%if %1 >= 0x28
				OUT 0xA0,AL
			%endif

			OUT 0x20,AL
		%endif
	%endif

	ADD ESP,8
	POPAD
	IRET
%endmacro

isr:
	.l0   : interrupt 0x0
	.l1   : interrupt 0x1
	.l2   : interrupt 0x2
	.l3   : interrupt 0x3
	.l4   : interrupt 0x4
	.l5   : interrupt 0x5
	.l6   : interrupt 0x6
	.l7   : interrupt 0x7
	.l8   : interrupt 0x8
	.l9   : interrupt 0x9
	.l10  : interrupt 0xa
	.l11  : interrupt 0xb
	.l12  : interrupt 0xc
	.l13  : interrupt 0xd
	.l14  : interrupt 0xe
	.l15  : interrupt 0xf
	.l16  : interrupt 0x10
	.l17  : interrupt 0x11
	.l18  : interrupt 0x12
	.l19  : interrupt 0x13
	.l20  : interrupt 0x14
	.l21  : interrupt 0x15
	.l22  : interrupt 0x16
	.l23  : interrupt 0x17
	.l24  : interrupt 0x18
	.l25  : interrupt 0x19
	.l26  : interrupt 0x1a
	.l27  : interrupt 0x1b
	.l28  : interrupt 0x1c
	.l29  : interrupt 0x1d
	.l30  : interrupt 0x1e
	.l31  : interrupt 0x1f
.master:
	.l32  : interrupt 0x20
	.l33  : interrupt 0x21
	.l34  : interrupt 0x22
	.l35  : interrupt 0x23
	.l36  : interrupt 0x24
	.l37  : interrupt 0x25
	.l38  : interrupt 0x26
	.l39  : interrupt 0x27
.slave:
	.l40  : interrupt 0x28
	.l41  : interrupt 0x29
	.l42  : interrupt 0x2a
	.l43  : interrupt 0x2b
	.l44  : interrupt 0x2c
	.l45  : interrupt 0x2d
	.l46  : interrupt 0x2e
	.l47  : interrupt 0x2f
.service:
	.l48  : interrupt 0x30
	.l49  : interrupt 0x31
	.l50  : interrupt 0x32
	.l51  : interrupt 0x33
	.l52  : interrupt 0x34
	.l53  : interrupt 0x35
	.l54  : interrupt 0x36
	.l55  : interrupt 0x37
	.l56  : interrupt 0x38
	.l57  : interrupt 0x39
	.l58  : interrupt 0x3a
	.l59  : interrupt 0x3b
	.l60  : interrupt 0x3c
	.l61  : interrupt 0x3d
	.l62  : interrupt 0x3e
	.l63  : interrupt 0x3f
	.l64  : interrupt 0x40
	.l65  : interrupt 0x41
	.l66  : interrupt 0x42
	.l67  : interrupt 0x43
	.l68  : interrupt 0x44
	.l69  : interrupt 0x45
	.l70  : interrupt 0x46
	.l71  : interrupt 0x47
	.l72  : interrupt 0x48
	.l73  : interrupt 0x49
	.l74  : interrupt 0x4a
	.l75  : interrupt 0x4b
	.l76  : interrupt 0x4c
	.l77  : interrupt 0x4d
	.l78  : interrupt 0x4e
	.l79  : interrupt 0x4f
	.l80  : interrupt 0x50
	.l81  : interrupt 0x51
	.l82  : interrupt 0x52
	.l83  : interrupt 0x53
	.l84  : interrupt 0x54
	.l85  : interrupt 0x55
	.l86  : interrupt 0x56
	.l87  : interrupt 0x57
	.l88  : interrupt 0x58
	.l89  : interrupt 0x59
	.l90  : interrupt 0x5a
	.l91  : interrupt 0x5b
	.l92  : interrupt 0x5c
	.l93  : interrupt 0x5d
	.l94  : interrupt 0x5e
	.l95  : interrupt 0x5f
	.l96  : interrupt 0x60
	.l97  : interrupt 0x61
	.l98  : interrupt 0x62
	.l99  : interrupt 0x63
	.l100 : interrupt 0x64
	.l101 : interrupt 0x65
	.l102 : interrupt 0x66
	.l103 : interrupt 0x67
	.l104 : interrupt 0x68
	.l105 : interrupt 0x69
	.l106 : interrupt 0x6a
	.l107 : interrupt 0x6b
	.l108 : interrupt 0x6c
	.l109 : interrupt 0x6d
	.l110 : interrupt 0x6e
	.l111 : interrupt 0x6f
	.l112 : interrupt 0x70
	.l113 : interrupt 0x71
	.l114 : interrupt 0x72
	.l115 : interrupt 0x73
	.l116 : interrupt 0x74
	.l117 : interrupt 0x75
	.l118 : interrupt 0x76
	.l119 : interrupt 0x77
	.l120 : interrupt 0x78
	.l121 : interrupt 0x79
	.l122 : interrupt 0x7a
	.l123 : interrupt 0x7b
	.l124 : interrupt 0x7c
	.l125 : interrupt 0x7d
	.l126 : interrupt 0x7e
	.l127 : interrupt 0x7f
	.l128 : interrupt 0x80
	.l129 : interrupt 0x81
	.l130 : interrupt 0x82
	.l131 : interrupt 0x83
	.l132 : interrupt 0x84
	.l133 : interrupt 0x85
	.l134 : interrupt 0x86
	.l135 : interrupt 0x87
	.l136 : interrupt 0x88
	.l137 : interrupt 0x89
	.l138 : interrupt 0x8a
	.l139 : interrupt 0x8b
	.l140 : interrupt 0x8c
	.l141 : interrupt 0x8d
	.l142 : interrupt 0x8e
	.l143 : interrupt 0x8f
	.l144 : interrupt 0x90
	.l145 : interrupt 0x91
	.l146 : interrupt 0x92
	.l147 : interrupt 0x93
	.l148 : interrupt 0x94
	.l149 : interrupt 0x95
	.l150 : interrupt 0x96
	.l151 : interrupt 0x97
	.l152 : interrupt 0x98
	.l153 : interrupt 0x99
	.l154 : interrupt 0x9a
	.l155 : interrupt 0x9b
	.l156 : interrupt 0x9c
	.l157 : interrupt 0x9d
	.l158 : interrupt 0x9e
	.l159 : interrupt 0x9f
	.l160 : interrupt 0xa0
	.l161 : interrupt 0xa1
	.l162 : interrupt 0xa2
	.l163 : interrupt 0xa3
	.l164 : interrupt 0xa4
	.l165 : interrupt 0xa5
	.l166 : interrupt 0xa6
	.l167 : interrupt 0xa7
	.l168 : interrupt 0xa8
	.l169 : interrupt 0xa9
	.l170 : interrupt 0xaa
	.l171 : interrupt 0xab
	.l172 : interrupt 0xac
	.l173 : interrupt 0xad
	.l174 : interrupt 0xae
	.l175 : interrupt 0xaf
	.l176 : interrupt 0xb0
	.l177 : interrupt 0xb1
	.l178 : interrupt 0xb2
	.l179 : interrupt 0xb3
	.l180 : interrupt 0xb4
	.l181 : interrupt 0xb5
	.l182 : interrupt 0xb6
	.l183 : interrupt 0xb7
	.l184 : interrupt 0xb8
	.l185 : interrupt 0xb9
	.l186 : interrupt 0xba
	.l187 : interrupt 0xbb
	.l188 : interrupt 0xbc
	.l189 : interrupt 0xbd
	.l190 : interrupt 0xbe
	.l191 : interrupt 0xbf
	.l192 : interrupt 0xc0
	.l193 : interrupt 0xc1
	.l194 : interrupt 0xc2
	.l195 : interrupt 0xc3
	.l196 : interrupt 0xc4
	.l197 : interrupt 0xc5
	.l198 : interrupt 0xc6
	.l199 : interrupt 0xc7
	.l200 : interrupt 0xc8
	.l201 : interrupt 0xc9
	.l202 : interrupt 0xca
	.l203 : interrupt 0xcb
	.l204 : interrupt 0xcc
	.l205 : interrupt 0xcd
	.l206 : interrupt 0xce
	.l207 : interrupt 0xcf
	.l208 : interrupt 0xd0
	.l209 : interrupt 0xd1
	.l210 : interrupt 0xd2
	.l211 : interrupt 0xd3
	.l212 : interrupt 0xd4
	.l213 : interrupt 0xd5
	.l214 : interrupt 0xd6
	.l215 : interrupt 0xd7
	.l216 : interrupt 0xd8
	.l217 : interrupt 0xd9
	.l218 : interrupt 0xda
	.l219 : interrupt 0xdb
	.l220 : interrupt 0xdc
	.l221 : interrupt 0xdd
	.l222 : interrupt 0xde
	.l223 : interrupt 0xdf
	.l224 : interrupt 0xe0
	.l225 : interrupt 0xe1
	.l226 : interrupt 0xe2
	.l227 : interrupt 0xe3
	.l228 : interrupt 0xe4
	.l229 : interrupt 0xe5
	.l230 : interrupt 0xe6
	.l231 : interrupt 0xe7
	.l232 : interrupt 0xe8
	.l233 : interrupt 0xe9
	.l234 : interrupt 0xea
	.l235 : interrupt 0xeb
	.l236 : interrupt 0xec
	.l237 : interrupt 0xed
	.l238 : interrupt 0xee
	.l239 : interrupt 0xef
	.l240 : interrupt 0xf0
	.l241 : interrupt 0xf1
	.l242 : interrupt 0xf2
	.l243 : interrupt 0xf3
	.l244 : interrupt 0xf4
	.l245 : interrupt 0xf5
	.l246 : interrupt 0xf6
	.l247 : interrupt 0xf7
	.l248 : interrupt 0xf8
	.l249 : interrupt 0xf9
	.l250 : interrupt 0xfa
	.l251 : interrupt 0xfb
	.l252 : interrupt 0xfc
	.l253 : interrupt 0xfd
	.l254 : interrupt 0xfe
	.l255 : interrupt 0xff
.end:

%macro isr_config 0
	;Configurando IRQ 0...15 [Reprogramando o PIC 8259A]
	MOV AL,0x11
	OUT 0xA0,AL
	OUT 0x20,AL

	;Configurando as IRQs 0x0...0x7 para 0x20...0x27
	MOV AL,0x20
	OUT 0x21,AL

	;Configurando as IRQs 0x8...0x15 para 0x28...0x2F
	MOV AL,0x28
	OUT 0xA1,AL

	MOV AL,0x4
	OUT 0x21,AL
	MOV AL,0x2
	OUT 0xA1,AL

	MOV AL,0x1
	OUT 0x21,AL
	OUT 0xA1,AL

	;Notei que em alguns computadores as interrupções ficam desativadas. Limpando a porta 0x21
	; e 0xA1 para ativar as interrupções.
	XOR AL,AL
	OUT 0x21,AL
	OUT 0xA1,AL
%endmacro
