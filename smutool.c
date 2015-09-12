/* smutool  Dump SMU region on AMD systems
 * Copyright (C) 2015  Damien Zammit <damien@zamaudio.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 2 of the License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
 */

#include <stdio.h>
#include <inttypes.h>
#include <pci/pci.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/io.h>
#include <stdlib.h>
#include <unistd.h>

#define SIZE 0x40000

#define BYTESWAP16(x)                   \
    ((((x) >> 8) & 0x00FF) | (((x) << 8) & 0xFF00))

#define BYTESWAP32(x)                   \
    ((((x) >> 24) & 0x000000FF) | (((x) >> 8) & 0x0000FF00) | \
         (((x) << 8) & 0x00FF0000) | (((x) << 24) & 0xFF000000))

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
	

/*  lm32 instructions, load at 0x1ff80, read peek at 0x1ffa0
   1ff80:	78 01 ab cd 	mvhi r1,0xabcd
   1ff84:	38 21 ef aa 	ori r1,r1,0xefaa
   1ff88:	78 02 00 01 	mvhi r2,0x0001
   1ff8c:	38 42 ff a0 	ori r2,r2,0xffa0
   1ff90:	58 41 00 00 	sw (r2+0),r1
   1ff94:	e3 ff ea df 	bi 0x1ab10
*/
	// Fill peek location with 1s so we can tell if anything changed
	pci_write_long(nb, 0xb8, 0x1ffa0);
	pci_write_long(nb, 0xbc, 0x11223344);
	
	uint32_t peek;
	for (peek = 0; peek < SIZE; peek += 4) {
		//fprintf(stderr, "Injecting copy service...\n");
		uint16_t peeklo = peek & 0xffff;
		uint16_t peekhi = (peek >> 16) & 0xffff;
		pci_write_long(nb, 0xb8, 0x1ff80);
		//pci_write_byte(nb, 0xdc, 0xff);
		pci_write_long(nb, 0xbc, BYTESWAP32(0x78010000 | (peekhi)));
		pci_write_long(nb, 0xb8, 0x1ff84);
		pci_write_long(nb, 0xbc, BYTESWAP32(0x38210000 | (peeklo)));
		pci_write_long(nb, 0xb8, 0x1ff88);
		pci_write_long(nb, 0xbc, BYTESWAP32(0x78020001));
		pci_write_long(nb, 0xb8, 0x1ff8c);
		pci_write_long(nb, 0xbc, BYTESWAP32(0x3842ffa0));
		pci_write_long(nb, 0xb8, 0x1ff90);
		pci_write_long(nb, 0xbc, BYTESWAP32(0x58410000));
		pci_write_long(nb, 0xb8, 0x1ff94);
		pci_write_long(nb, 0xbc, BYTESWAP32(0xe3ffeadf)); // jmp
		//pci_write_long(nb, 0xbc, BYTESWAP32(0xc3a00000));  // ret
		
		//fprintf(stderr, "Replacing service request handler pointer...\n");
		// add new service request
		pci_write_long(nb, 0xb8, 0x1dbe0);
		pci_write_long(nb, 0xbc, 0x1ff80);
		
		//pci_write_byte(nb, 0xdc, 0x00);

		fprintf(stderr, "Trigger a dummy service request...\n");
		uint8_t ack = 0;
		//while ((ack & 0x4) == 0) {
			pci_write_long(nb, 0xb8, 0xe0003004);
			ack = pci_read_long(nb, 0xbc);
		//}
		pci_write_long(nb, 0xb8, 0xe0003000);
		ack = pci_read_long(nb, 0xbc);
		ack ^= 1;
		ack |= (41 << 1);
		pci_write_long(nb, 0xb8, 0xe0003000);
		pci_write_long(nb, 0xbc, ack);
		
		fprintf(stderr, "ack:%08x\n", ack);
		//do {
			pci_write_long(nb, 0xb8, 0xe0003004);
			ack = pci_read_long(nb, 0xbc);
		//} while ((ack & 0x2) == 0);
		//do {
			pci_write_long(nb, 0xb8, 0xe0003004);
			ack = pci_read_long(nb, 0xbc);
		//} while ((ack & 0x4) == 0);
		  
		//fprintf(stderr, "Peeking...\n");
		uint32_t roml;
		pci_write_long(nb, 0xb8, 0x1ffa0);
		roml = pci_read_long(nb, 0xbc);
		printf("%c%c%c%c",
			roml >> 24,
			roml >> 16,
			roml >> 8,
			roml);
	
	} // end loop

/*
	fprintf(stderr, "Reading SMU RAM...\n");
	uint32_t data[SIZE];
	for (i = 0; i < SIZE; i+=4) {
		pci_write_long(nb, 0xb8, i);
		data[i/4] = pci_read_long(nb, 0xbc);
		printf("%c%c%c%c",
			data[i/4] >> 24,
			data[i/4] >> 16,
			data[i/4] >> 8,
			data[i/4]);
	}
*/

	fprintf(stderr, "exiting\n");
	pci_cleanup(pacc);
	return 0;
}
