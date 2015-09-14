/* smutool  Tool for SMU
 * Copyright (C) 2015  Damien Zammit <damien@zamaudio.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * See <http://www.gnu.org/licenses/>. 
 */

#include <stdio.h>
#include <inttypes.h>
#include <pci/pci.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/io.h>
#include <stdlib.h>
#include <unistd.h>

#define SIZE 0x10000

int main(int argc, char* argv[])
{
	uint32_t fd_mem;
	struct pci_access *pacc;
	struct pci_dev *nb;
	if (iopl(3)) {
		perror("iopl");
		fprintf(stderr, "You need to be root\n");
		exit(1);
	}

        if ((fd_mem = open("/dev/mem", O_RDWR)) < 0) {
                perror("Can not open /dev/mem");
                exit(1);
        }

	pacc = pci_alloc();
	pacc->method = PCI_ACCESS_I386_TYPE1;
	pci_init(pacc);
	pci_scan_bus(pacc);
	nb = pci_get_dev(pacc, 0, 0, 0x0, 0);
	pci_fill_info(nb, PCI_FILL_IDENT | PCI_FILL_BASES | PCI_FILL_SIZES | PCI_FILL_CLASS);
	

/*  lm32 instructions, load at 0x1ff80, read peek at 0x1fff0
   1ff80:	37 9c ff f0 	addi sp,sp,-16
   1ff84:	5b 9b 00 08 	sw (sp+8),fp
   1ff88:	5b 9d 00 04 	sw (sp+4),ra
   1ff8c:	34 1b 00 10 	mvi fp,16
   1ff90:	b7 7c d8 00 	add fp,fp,sp
   1ff94:	78 01 ab cd 	mvhi r1,0xabcd
   1ff98:	38 21 ef 00 	ori r1,r1,0xef00
   1ff9c:	5b 61 00 00 	sw (fp+0),r1
   1ffa0:	78 01 00 01 	mvhi r1,0x1
   1ffa4:	38 21 ff f0 	ori r1,r1,0xfff0
   1ffa8:	5b 61 ff fc 	sw (fp+-4),r1
   1ffac:	2b 61 ff fc 	lw r1,(fp+-4)
   1ffb0:	2b 62 00 00 	lw r2,(fp+0)
   1ffb4:	28 42 00 00 	lw r2,(r2+0)
   1ffb8:	58 22 00 00 	sw (r1+0),r2
   1ffbc:	2b 9b 00 08 	lw fp,(sp+8)
   1ffc0:	2b 9d 00 04 	lw ra,(sp+4)
   1ffc4:	37 9c 00 10 	addi sp,sp,16
   1ffc8:	c3 a0 00 00 	ret
*/
	// Fill peek location with 1s so we can tell if anything changed
	pci_write_long(nb, 0xb8, 0x1fff0);
	pci_write_long(nb, 0xbc, 0x11223344);

	// Enable interrupts on SMU
	pci_write_long(nb, 0xb8, 0x1f380);
	pci_write_long(nb, 0xbc,
		pci_read_long(nb, 0xbc) & ~1);
	pci_write_long(nb, 0xb8, 0x1f380);
	pci_write_long(nb, 0xbc,
		pci_read_long(nb, 0xbc) | 1);
	
	uint32_t peek;
	for (peek = 0; peek < SIZE; peek += 4) {
		uint16_t peeklo = peek & 0xffff;
		uint16_t peekhi = (peek >> 16) & 0xffff;
		pci_write_long(nb, 0xb8, 0x1ff80);
		pci_write_long(nb, 0xbc, (0x379cfff0));
		pci_write_long(nb, 0xb8, 0x1ff84);
		pci_write_long(nb, 0xbc, (0x5b9b0008));
		pci_write_long(nb, 0xb8, 0x1ff88);
		pci_write_long(nb, 0xbc, (0x5b9d0004));
		pci_write_long(nb, 0xb8, 0x1ff8c);
		pci_write_long(nb, 0xbc, (0x341b0010));
		pci_write_long(nb, 0xb8, 0x1ff90);
		pci_write_long(nb, 0xbc, (0xb77cd800));
		pci_write_long(nb, 0xb8, 0x1ff94);
		pci_write_long(nb, 0xbc, (0x78010000 | (peekhi)));
		pci_write_long(nb, 0xb8, 0x1ff98);
		pci_write_long(nb, 0xbc, (0x38210000 | (peeklo)));
		pci_write_long(nb, 0xb8, 0x1ff9c);
		pci_write_long(nb, 0xbc, (0x5b610000));
		pci_write_long(nb, 0xb8, 0x1ffa0);
		pci_write_long(nb, 0xbc, (0x78010001));
		pci_write_long(nb, 0xb8, 0x1ffa4);
		pci_write_long(nb, 0xbc, (0x3821fff0));
		pci_write_long(nb, 0xb8, 0x1ffa8);
		pci_write_long(nb, 0xbc, (0x5b61fffc));
		pci_write_long(nb, 0xb8, 0x1ffac);
		pci_write_long(nb, 0xbc, (0x2b61fffc));
		pci_write_long(nb, 0xb8, 0x1ffb0);
		pci_write_long(nb, 0xbc, (0x2b620000));
		pci_write_long(nb, 0xb8, 0x1ffb4);
		pci_write_long(nb, 0xbc, (0x28420000));
		pci_write_long(nb, 0xb8, 0x1ffb8);
		pci_write_long(nb, 0xbc, (0x58220000));
		pci_write_long(nb, 0xb8, 0x1ffbc);
		pci_write_long(nb, 0xbc, (0x2b9b0008));
		pci_write_long(nb, 0xb8, 0x1ffc0);
		pci_write_long(nb, 0xbc, (0x2b9d0004));
		pci_write_long(nb, 0xb8, 0x1ffc4);
		pci_write_long(nb, 0xbc, (0x379c0010));
		pci_write_long(nb, 0xb8, 0x1ffc8);
		pci_write_long(nb, 0xbc, (0xc3a00000));  // ret
		
		// add new service request
		uint32_t addr;
		for (addr = 0x1dbe0; addr < 0x1dbec; addr+=4) {
			pci_write_long(nb, 0xb8, addr);
			pci_write_long(nb, 0xbc, 0x1ff80);
		}

		uint8_t ack = 0;
		while ((ack & 0x3) == 0) {  // 0x4
			pci_write_long(nb, 0xb8, 0xe0003004);
			ack = pci_read_long(nb, 0xbc);
		}
		pci_write_long(nb, 0xb8, 0xe0003000);
		ack = pci_read_long(nb, 0xbc);
		ack ^= 1;
		ack |= (106 << 1);
		pci_write_long(nb, 0xb8, 0xe0003000);
		pci_write_long(nb, 0xbc, ack);
		
		do {
			pci_write_long(nb, 0xb8, 0xe0003004);
			ack = pci_read_long(nb, 0xbc);
		} while ((ack & 0x1) == 0);
		
		do {
			pci_write_long(nb, 0xb8, 0xe0003004);
			ack = pci_read_long(nb, 0xbc);
		} while ((ack & 0x2) == 0);
		
		usleep(10000);
		uint32_t roml;
		pci_write_long(nb, 0xb8, 0x1fff0);
		roml = pci_read_long(nb, 0xbc);
		printf("%c%c%c%c",
			(roml >> 24) & 0xff,
			(roml >> 16) & 0xff,
			(roml >> 8) & 0xff,
			(roml & 0xff));
	
		fflush(stdout);
	} // end loop

	fprintf(stderr, "exiting\n");
	pci_cleanup(pacc);
	return 0;
}
