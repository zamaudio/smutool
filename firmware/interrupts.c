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

typedef void(*ISRCallback)(unsigned int, void *);

typedef struct ISREntry{
	ISRCallback Callback;
	void *Context;
} ISREntry_t;

static ISREntry_t ISREntryTable[32];

void MicoISRHandler(void){
	/*
	 * If an interrupt-handler exists for the relevant interrupt (as detected
	 * from ip and im cpu registers), then invoke the handler else disable the
	 * interrupt in the im.
	 */
	unsigned int ip, im, Mask, IntLevel;
	asm volatile ("rcsr %0,im":"=r"(im));

	/* Inform that we've entered main ISR */
	//OSIntEnter();

	/* Service all interrupts */
	do {
		/* read ip and calculate effective ip */
		asm volatile ("rcsr %0,ip":"=r"(ip));
		ip &= im;
		Mask = 0x1;
		IntLevel = 0;

		if( ip!=0 ){
		do {
			if(Mask & ip) {
				if(ISREntryTable[IntLevel].Callback != 0){
					(ISREntryTable[IntLevel].Callback)(IntLevel, ISREntryTable[IntLevel].Context);
					asm volatile ("wcsr ip, %0"::"r"(Mask));
					break;
				} else {
					asm volatile ("rcsr %0,im":"=r"(im));
					im &= ~Mask;
					asm volatile ("wcsr im, %0"::"r"(im));
					asm volatile ("wcsr ip, %0"::"r"(Mask));
					break;
				}
			}
			Mask <<= 0x1;
			++IntLevel;
		} while(1);

		} else {
			break;
		}

	} while(1);

	/* Inform that we're done with servicing interrupts */
	//OSIntExit();
	
	return;
}

