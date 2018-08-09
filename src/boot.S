#include "mm.h"
#include "arm/sysregs.h"

.section ".text.boot"

.globl _start
	mrs 	x0, mpidr_el1
	and 	x0, x0, #0xFF 	// Check processor id
	cbnz 	x0, change_el

	// Init .bss section
	adr		x0, bss_begin
	adr 	x1, bss_end
	sub 	x1, x1, x0
	bl 		memzero

change_el:
	// Change exception level to 1
	ldr		x0, =SCTLR_VALUE_MMU_DISABLED
	msr		sctlr_el1, x0

	ldr 	x0, =HCR_VALUE
	msr 	hcr_el2, x0

	ldr 	x0, =SCR_VALUE
	msr 	scr_el3, x0

	ldr 	x0, =SPSR_VALUE
	msr 	spsr_el3, x0

	adr 	x0, init_stack
	msr 	elr_el3, x0

	eret

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

