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

void MicoISRHandler(void);
void smu_service_request(unsigned int, void*);
