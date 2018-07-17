#include "mm.h"

.section ".text.boot"

.globl _start
	mrs 	x0, mpidr_el1
	and 	x0, x0, #0xFF 	// Check processor id
	cbnz 	x0, init_stack

	adr		x0, bss_begin	// Init .bss section
	adr 	x1, bss_end
	sub 	x1, x1, x0
	bl 		memzero

init_stack:
	mrs 	x0, mpidr_el1
	and 	x0, x0, #0xFF 	// Check processor id
	mov 	x1, #0x1000		// 4kB stack size
	mul		x2, x0, x1		// get offset
	add		x1, x2, #LOW_MEMORY // add offset to LOW_MEMORY
	mov 	sp, x1 			// set up stack pointer
	bl 		kernel_main
	b 		proc_hang		// Should never be reached

proc_hang:
	b 		proc_hang

