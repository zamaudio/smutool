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
	int ie, mask, im;

	int irq = 1;

	mask = 0x1 << irq; // << irq

	/* disable peripheral interrupts */
	asm volatile ("rcsr %0,ie":"=r"(ie));
	ie &= (~0x1);
	asm volatile ("wcsr ie, %0"::"r"(ie));

	ISREntryTable[irq].Callback = &smu_service_request;
	ISREntryTable[irq].Context = 0; //?

	/* enable mask in the im */
	asm volatile ("rcsr %0, im":"=r"(im));
	im |= mask;
	asm volatile ("wcsr im, %0"::"r"(im));

	/* enable interrupts */
	ie |= 0x1;
	asm volatile ("wcsr ie, %0"::"r"(ie));

	while (1) {
		mdelay(10);
		
		MicoISRHandler();
	}
}
