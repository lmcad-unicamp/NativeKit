OUTPUT_FORMAT("binary")
ENTRY(_start)

SECTIONS {
	. = 0x0;

	.text : {
		*(.text)
	}

	.rodata : {
		*(.rodata)
	}

	.data : {
		*(.data)
		*(.bss)
		*(COMMON)
	}

	/DISCARD/ : {
		*(.comment)
		*(.eh_frame)
	}

	_stack_base = . ;
	. = . + 0x1000;
	_stack_top = . ;

	_heap_base = . ;
	. = . + 0x400;
	. = ALIGN(4k);
	_heap_top = . ;
}
