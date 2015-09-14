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

extern void MicoSleepHelper(int tick, int clock);

void mdelay(int ms)
{
	MicoSleepHelper(ms, MICO_SLEEP_MILLISEC);
}

void udelay(int us)
{
	MicoSleepHelper(us, MICO_SLEEP_MICROSEC);
}

extern void main(void);

void bootblock(void)
{
//	REG_WRITE(0x80000020, 305441741);
	main();
}

void main() {
	int a;
start:
	a = 1;
	goto start;
}
