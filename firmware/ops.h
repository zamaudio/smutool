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

extern int __mulsi3 (int a, int b);
extern int __lshrsi3 (int a, int b);
extern int __lshlsi3 (int a, int b);
extern int __ashrsi3 (int a, int b);
extern int __ashlsi3 (int a, int b);

extern int __mulsi3 (int a, int b)
{
	return a * b;
}

extern int __lshrsi3 (int a, int b)
{
	return a >> b;
}

extern int __lshlsi3 (int a, int b)
{
	return a << b;
}

extern int __ashrsi3 (int a, int b)
{
	return a >> b;
}

extern int __ashlsi3 (int a, int b)
{
	return a << b;
}
#endif
