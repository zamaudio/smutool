/* Free/Libre SMU firmware
 * Copyright (C) 2015  Damien Zammit <damien@zamaudio.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *-
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * See <http://www.gnu.org/licenses/>.-
 */

#include "smu.h"
#include "delay.h"
#include "servicereq.h"

void main(void)
{
	int i;
	int ie;
	int e3;
	int toggle = 0;

	/* disable interrupts */
	asm volatile ("rcsr %0,ie":"=r"(ie));
	ie &= (~0x1);
	asm volatile ("wcsr ie, %0"::"r"(ie));

	for (i = 0; i < 32; i++) {
		ISREntryTable[i].Callback = 0;
		ISREntryTable[i].Context = 0;
	}

	/* clear all pending interrupts */
	asm volatile ("wcsr ip, %0"::"r"(0xffffffff));
	
	/* tell x86 that interrupts are ready */
	write32(0xe0003004, INTACK | INTDONE);
	write32(0x1f380, 1);
	
	toggle = read32(0xe0003000) & 1;

	while (1) {
		e3 = read32(0xe0003000);
		if (toggle != (e3 & 1)) {
			write32(0xe0003004, INTACK);
			smu_service_request(e3);
			write32(0xe0003004, INTACK | INTDONE);
		}

		toggle = read32(0xe0003000) & 1;
		mdelay(30);
	}
}
