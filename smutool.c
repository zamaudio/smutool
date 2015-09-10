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
#include <sys/io.h>
#include <stdlib.h>
#include "mmap.h"

#define SIZE 0x40000

extern int fd_mem;

void dumpmem(uint8_t *phys, uint32_t size)
{
	uint32_t i;
	fprintf(stderr, "Dumping memory:\n");
	for (i = 0; i < size; i++) {
		printf("%02X",*((uint8_t *) (phys + i)));
	}
	printf("\n");
}

void dumpmemfile(uint8_t *phys, uint32_t size)
{
	FILE *fp = fopen("dump.bin", "w");
	uint32_t i;
	for (i = 0; i < size; i++) {
		fprintf(fp, "%c", *((uint8_t *) (phys + i)));
	}
	fclose(fp);
}

int main(void)
{
	uint32_t i;
	uint32_t smu_phys;
	volatile uint8_t *smu;
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
	
	smu_phys = pci_read_long(nb, 0xb8) & ~1;
	smu = map_physical(smu_phys, SIZE);
	fprintf(stderr, "SMU at 0x%08" PRIx32 "\n", (uint32_t)smu_phys);

	uint32_t data[SIZE];
	for (i = 0; i < SIZE; i+=4) {
		pci_write_long(nb, 0xb8, i);
		data[i/4] = pci_read_long(nb, 0xbc);
		printf("%c%c%c%c", data[i/4], data[i/4+1], data[i/4+2], data[i/4+3]);
	}

	fprintf(stderr, "exiting\n");
	pci_cleanup(pacc);
	munmap((void*)smu, SIZE);
	return 0;
}
