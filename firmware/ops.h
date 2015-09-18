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

#ifndef _OPS_H
#define _OPS_H

inline int __mulsi3 (int a, int b)
{
	int c;
	asm ("mul %0, %1, %2"
		:"=r"(c)
		:"r"(a),"r"(b)
		:
		);
	return c;
}

inline int __lshrsi3 (int a, int b)
{
	int c;
	asm ("sr %0, %1, %2"
		:"=r"(c)
		:"r"(a),"r"(b)
		:
		);
	return c;
}

inline int __lshlsi3 (int a, int b)
{
	int c;
	asm ("sl %0, %1, %2"
		:"=r"(c)
		:"r"(a),"r"(b)
		:
		);
	return c;
}

inline int __ashrsi3 (int a, int b)
{
	int c;
	asm ("sr %0, %1, %2"
		:"=r"(c)
		:"r"(a),"r"(b)
		:
		);
	return c;
}

inline int __ashlsi3 (int a, int b)
{
	int c;
	asm ("sl %0, %1, %2"
		:"=r"(c)
		:"r"(a),"r"(b)
		:
		);
	return c;
}

inline unsigned int __udivsi3 (unsigned int a, unsigned int b)
{
	unsigned int c;
	asm ("divu %0, %1, %2"
		:"=r"(c)
		:"r"(a),"r"(b)
		:
		);
	return c;
}

inline int __divsi3 (int a, int b)
{
	unsigned int c;
	asm ("divu %0, %1, %2"
		:"=r"(c)
		:"r"(a),"r"(b)
		:
		);
	return c;
}
#endif
