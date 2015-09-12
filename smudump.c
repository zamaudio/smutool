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
	
	fprintf(stderr, "Reading SMU RAM...\n");
	uint32_t data[SIZE], i;
	for (i = 0; i < SIZE; i+=4) {
		pci_write_long(nb, 0xb8, i);
		data[i/4] = pci_read_long(nb, 0xbc);
		printf("%c%c%c%c",
			data[i/4] >> 24,
			data[i/4] >> 16,
			data[i/4] >> 8,
			data[i/4]);
	}

	fprintf(stderr, "exiting\n");
	pci_cleanup(pacc);
	return 0;
}
