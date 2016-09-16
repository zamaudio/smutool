/*
 * Link script for LatticeMico32 programs.
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
 * Modified for SMU by Damien Zammit
 *
 */

OUTPUT_FORMAT("elf32-lm32")
ENTRY(_start)
INPUT(crti.o crtbegin.o crtend.o crtn.o)

MEMORY
{
	rom	:	ORIGIN = 0x0, LENGTH = 0x10000
	header	:	ORIGIN = 0x00010000, LENGTH = 0x100
	ram	:	ORIGIN = 0x00010100, LENGTH = 0xcf00
	regs	:	ORIGIN = 0x0001d000, LENGTH = 0x3000
}

SECTIONS
{
	/* code */
	.boot : { *(.boot) } > ram
	.text :
	{
		. = ALIGN(4);
		_ftext = .;
		_ftext_rom = .;
		*(.text .stub .text.* .gnu.linkonce.t.*)
		*(.gnu.warning)
		KEEP (*(.init))
		KEEP (*(.fini))

		/* Exception handlers */
		*(.eh_frame_hdr)
		KEEP (*(.eh_frame))
		*(.gcc_except_table)

		/* Constructors and destructors */
		KEEP (*crtbegin*.o(.ctors))
		KEEP (*(EXCLUDE_FILE (*crtend*.o ) .ctors))
		KEEP (*(SORT(.ctors.*)))
		KEEP (*(.ctors))
		KEEP (*crtbegin*.o(.dtors))
		KEEP (*(EXCLUDE_FILE (*crtend*.o ) .dtors))
		KEEP (*(SORT(.dtors.*)))
		KEEP (*(.dtors))
		KEEP (*(.jcr))
		_etext = .;
	} > ram =0

	/* read-only data */
	.rodata :
	{
		. = ALIGN(4);
		_frodata = .;
		_frodata_rom = LOADADDR(.rodata);
		*(.rodata .rodata.* .gnu.linkonce.r.*) 
		*(.rodata1)
		_erodata = .;
	} > ram

	/* read/write data */
	.data :
	{
		. = ALIGN(4);
		_fdata = .;
		_fdata_rom = .;
		*(.data .data.* .gnu.linkonce.d.*)
		*(.data1)
		SORT(CONSTRUCTORS)
		_gp = ALIGN(16) + 0x7ff0;
		*(.sdata .sdata.* .gnu.linkonce.s.*)
		_edata = .;
	} > ram

	.sreg :
	{
		. = ABSOLUTE(0x9a4);
		thermal_params = .;
		LONG(0x3178); /* VPC */
		LONG(0x0000);
		LONG(0x3171); /* BAPM */
		LONG(0x0000);
		LONG(0x3172); /* BAPM */
		LONG(0x0000);
		LONG(0x7103); /* BAPM */
		LONG(0x0000); /* BAPM */
		LONG(0x7116); /* BAPM */
		LONG(0x0000); /* BAPM */
		LONG(0x317d); /* VPC */
		LONG(0x0000);
		LONG(0x7103); /* VPC */
		LONG(0x0000); /* VPC */
		LONG(0x712e);
		LONG(0x0000);
		LONG(0x710f); /* TDC/HTC */
		LONG(0x0000); /* TDC/HTC */
		LONG(0x7110); /* LPMx */
		LONG(0x0000); /* LPMx */
		LONG(0x7111); /* LPMx */
		LONG(0x0000); /* LPMx */
		LONG(0x7112); /* LPMx */
		LONG(0x0000); /* LPMx */
		LONG(0x7113); /* LPMx */
		LONG(0x0000); /* LPMx */
		LONG(0x715c); /* VPC/BAPM */
		LONG(0x0000); /* VPC/BAPM */
		LONG(0x715d); /* VPC */
		LONG(0x0000);
		LONG(0x7162); /* LOADLINE */
		LONG(0x0000); /* LOADLINE */
		LONG(0x7117); /* BAPM */
		LONG(0x0000); /* BAPM */
		LONG(0x7157);
		LONG(0x0000);
		LONG(0x7106); /* BAPM */
		LONG(0x0000); /* BAPM */
	} > regs =0

	/* bss */
	.bss :
	{
		. = ALIGN(4);
		_fbss = .;
		*(.dynsbss)
		*(.sbss .sbss.* .gnu.linkonce.sb.*)
		*(.scommon)
		*(.dynbss)
		*(.bss .bss.* .gnu.linkonce.b.*)
		*(COMMON)
		. = ALIGN(4);
		_ebss = .;
		_end = .;
		PROVIDE (end = .);
	} > ram

	/* first location in stack is highest address in ram */
	PROVIDE(_fstack = ORIGIN(ram) + LENGTH(ram) - 4);

	/* stabs debugging sections.  */
	.stab          0 : { *(.stab) }
	.stabstr       0 : { *(.stabstr) }
	.stab.excl     0 : { *(.stab.excl) }
	.stab.exclstr  0 : { *(.stab.exclstr) }
	.stab.index    0 : { *(.stab.index) }
	.stab.indexstr 0 : { *(.stab.indexstr) }
	.comment       0 : { *(.comment) }
}
