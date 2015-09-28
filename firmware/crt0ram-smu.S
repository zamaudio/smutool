/*
 * LatticeMico32 C startup code.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * Modified for AMD SMU by Damien Zammit
 *
 */

/* From include/sys/signal.h */
#define SIGINT  2   /* interrupt */
#define SIGTRAP 5   /* trace trap */
#define SIGFPE  8   /* arithmetic exception */
#define SIGSEGV 11  /* segmentation violation */

#define SYSEXIT 1

/* Exception handlers - Must be 32 bytes long. */
        .section    .boot, "ax", @progbits

        .global	_start
_start:

        .global _reset_handler
        .type 	_reset_handler, @function
_reset_handler:
	xor 	r0, r0, r0
	xor 	r0, r0, r0
	wcsr    IE, r0
	mvhi    r1, hi(_reset_handler)
	ori     r1, r1, lo(_reset_handler)
	wcsr    EBA, r1
	wcsr    DEBA, r1
	calli   _crt0
        .size	_reset_handler, .-_reset_handler

        .global _breakpoint_handler
        .type 	_breakpoint_handler, @function
_breakpoint_handler:
	rcsr    r7, DEBA
	addi    r7, r7, 32
	b       r7
	nop
	nop
	nop
	nop
	nop
        .size   _breakpoint_handler, .-_breakpoint_handler

        .global _instruction_bus_error_handler
        .type 	_instruction_bus_error_handler, @function
_instruction_bus_error_handler:
	rcsr    r7, DEBA
	addi    r7, r7, 64
	b       r7
	nop
	nop
	nop
	nop
	nop
        .size   _instruction_bus_error_handler, .-_instruction_bus_error_handler

        .global _watchpoint_handler
        .type 	_watchpoint_handler, @function
_watchpoint_handler:
	rcsr    r7, DEBA
	addi    r7, r7, 96
	b       r7
	nop
	nop
	nop
	nop
	nop
        .size   _watchpoint_handler, .-_watchpoint_handler

        .global _data_bus_error_handler
        .type 	_data_bus_error_handler, @function
_data_bus_error_handler:
	rcsr    r7, DEBA
	addi    r7, r7, 128
	b       r7
	nop
	nop
	nop
	nop
	nop
        .size   _data_bus_error_handler, .-_data_bus_error_handler

        .global _divide_by_zero_handler
        .type 	_divide_by_zero_handler, @function
_divide_by_zero_handler:
	rcsr    r7, DEBA
	addi    r7, r7, 160
	b       r7
	nop
	nop
	nop
	nop
	nop
        .size   _divide_by_zero_handler, .-_divide_by_zero_handler

        .global _interrupt_handler
        .type 	_interrupt_handler, @function
_interrupt_handler:
	sw      (sp+0), ra
	calli   _save_all
	mvi     r1, SIGINT
	mvhi	r1, hi(MicoISRHandler)
	ori	r1, r1, lo(MicoISRHandler)
	call	r1
	bi      _restore_all_and_return
	nop
        .size   _interrupt_handler, .-_interrupt_handler
	
        .global _system_call_handler
        .type 	_system_call_handler, @function
_system_call_handler:
	rcsr    r7, DEBA
	addi    r7, r7, 224
	b       r7
	nop
	nop
	nop
	nop
	nop
        .size   _system_call_handler, .-_system_call_handler
	
        .global _crt0
        .type 	_crt0, @function
_crt0:	
	/* Clear r0 */
	xor     r0, r0, r0
	/* Setup stack and global pointer */
	mvhi    sp, hi(_fstack)
	ori     sp, sp, lo(_fstack)
	mvhi    gp, hi(_gp)
	ori     gp, gp, lo(_gp)
	
	/* Relocate text */
	mvhi    r1, hi(_ftext)
	ori     r1, r1, lo(_ftext)
	mvhi    r2, hi(_ftext_rom)
	ori     r2, r2, lo(_ftext_rom)
	be      r1, r2, .L_done_text_relocation
	mvhi    r3, (_etext)
	ori     r3, r3, (_etext)
	calli   _relocate_text
.L_done_text_relocation:

	/* Relocate read-only data */
	mvhi    r1, hi(_frodata)
	ori     r1, r1, lo(_frodata)
	mvhi    r2, hi(_frodata_rom)
	ori     r2, r2, lo(_frodata_rom)
	be      r1, r2, .L_done_rodata_relocation
	mvhi    r3, hi(_erodata)
	ori     r3, r3, lo(_erodata)
	be      r1, r3, .L_done_rodata_relocation
	sub     r3, r3, r1
	mvhi	r4, hi(memcpy)
	ori	r4, r4, lo(memcpy)
	call	r4
.L_done_rodata_relocation:

	/* Relocate data */
	mvhi    r1, hi(_fdata)
	ori     r1, r1, lo(_fdata)
	mvhi    r2, hi(_fdata_rom)
	ori     r2, r2, lo(_fdata_rom)
	be      r1, r2, .L_done_data_relocation
	mvhi    r3, hi(_edata)
	ori     r3, r3, lo(_edata)
	be      r1, r3, .L_done_data_relocation
	sub     r3, r3, r1
	mvhi	r4, hi(memcpy)
	ori	r4, r4, lo(memcpy)
	call	r4
.L_done_data_relocation:

	/* Clear BSS */
	mvhi    r1, hi(_fbss)
	ori     r1, r1, lo(_fbss)
	mvhi    r3, hi(_ebss)
	ori     r3, r3, lo(_ebss)
        .size   _crt0, .-_crt0
	
        .global .ClearBSS
        .type 	.ClearBSS, @function
.ClearBSS:
	be      r1, r3, .CallConstructor
	sw      (r1+0), r0
	addi    r1, r1, 4
	bi      .ClearBSS
        .size   .ClearBSS, .-.ClearBSS
	
        .global .CallConstructor
        .type 	.CallConstructor, @function
.CallConstructor:
	/* Call C++ constructors */
	calli	_init
	/* Call main program */
	mvi     r1, 0
	mvi     r2, 0
	mvi     r3, 0
	calli	main
	/* Call exit, which doesn't return, to perform any clean up */
	calli	_fini
	calli	_exit
	/* Save all registers onto the stack */ 
        .size   .CallConstructor, .-.CallConstructor
	
	.global _relocate_text
	.type 	_relocate_text, @function
_relocate_text:
	lb      r4, (r2+0)
	addi    r2, r2, 1
	sb      (r1+0), r4
	addi    r1, r1, 1
	bne     r1, r3, _relocate_text
	ret
	.size	_relocate_text, .-_relocate_text
	
        .global _save_all
        .type 	_save_all, @function
_save_all:
	addi    sp, sp, -128
	sw      (sp+4), r1
	sw      (sp+8), r2
	sw      (sp+12), r3
	sw      (sp+16), r4
	sw      (sp+20), r5
	sw      (sp+24), r6
	sw      (sp+28), r7
	sw      (sp+32), r8
	sw      (sp+36), r9
	sw      (sp+40), r10
	sw      (sp+44), r11
	sw      (sp+48), r12
	sw      (sp+52), r13
	sw      (sp+56), r14
	sw      (sp+60), r15
	sw      (sp+64), r16
	sw      (sp+68), r17
	sw      (sp+72), r18
	sw      (sp+76), r19
	sw      (sp+80), r20
	sw      (sp+84), r21
	sw      (sp+88), r22
	sw      (sp+92), r23
	sw      (sp+96), r24
	sw      (sp+100), r25
	sw      (sp+104), r26
	sw      (sp+108), r27
	sw      (sp+120), ea
	sw      (sp+124), ba
	/* ra and sp need special handling, as they have been modified */
	lw      r1, (sp+128)
	sw      (sp+116), r1
	mv      r1, sp
	addi    r1, r1, 128
	sw      (sp+112), r1
	xor     r1, r1, r1
	wcsr    ie, r1
	ret
        .size  	_save_all, .-_save_all
	
        .global _restore_all_and_return
        .type 	_restore_all_and_return, @function
    /* Restore all registers and return from exception */
_restore_all_and_return:
	addi    r1, r0, 2
	wcsr    ie, r1
	lw      r1, (sp+4)
	lw      r2, (sp+8)
	lw      r3, (sp+12)
	lw      r4, (sp+16)
	lw      r5, (sp+20)
	lw      r6, (sp+24)
	lw      r7, (sp+28)
	lw      r8, (sp+32)
	lw      r9, (sp+36)
	lw      r10, (sp+40)
	lw      r11, (sp+44)
	lw      r12, (sp+48)
	lw      r13, (sp+52)
	lw      r14, (sp+56)
	lw      r15, (sp+60)
	lw      r16, (sp+64)
	lw      r17, (sp+68)
	lw      r18, (sp+72)
	lw      r19, (sp+76)
	lw      r20, (sp+80)
	lw      r21, (sp+84)
	lw      r22, (sp+88)
	lw      r23, (sp+92)
	lw      r24, (sp+96)
	lw      r25, (sp+100)
	lw      r26, (sp+104)
	lw      r27, (sp+108)
	lw      ra, (sp+116)
	lw      ea, (sp+120)
	lw      ba, (sp+124)
	/* Stack pointer must be restored last, in case it has been updated */
	lw      sp, (sp+112)
	nop
	eret
        .size   _restore_all_and_return, .-_restore_all_and_return

        .global _exit
_exit:
	mvi	r8, SYSEXIT
	scall
        .size   _exit, .-_exit
