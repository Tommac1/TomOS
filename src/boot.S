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
	// Change exception level to 2
	ldr 	x0, =SCR_RESERVED
	ldr 	x1, =SCR_RW
	ldr 	x2, =SCR_NS
	orr 	x1, x1, x2
	orr 	x0, x0, x1
	msr 	scr_el3, x0

	ldr 	x0, =SPSR_MASK_ALL	// Mask all interrupts
	ldr 	x1, =SPSR_FROM_AARCH64
	ldr 	x2, =SPSR_EL2h  	// Get back to EL2 with EL2 dedicated stack pointer
	orr 	x1, x1, x2
	orr 	x0, x0, x1
	msr 	spsr_el3, x0

	adr 	x0, el2_entry
	msr 	elr_el3, x0

	eret 					// Execute exception and get back to EL2

el2_entry:
	// Change exception level to 1
	ldr 	x0, =HCR_RW 	// Exec state for EL1 is AArch64
	msr		hcr_el2, x0

	ldr 	x0, =SCTLR_VALUE_MMU_DISABLED
	msr 	sctlr_el1, x0

	ldr 	x0, =SPSR_MASK_ALL
	ldr 	x1, =SPSR_EL1h
	ldr 	x2, =SPSR_FROM_AARCH64
	orr 	x1, x1, x2
	orr 	x0, x0, x1
	msr 	spsr_el2, x0

	adr 	x0, el1_entry
	msr 	elr_el2, x0

	eret

el1_entry:
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

