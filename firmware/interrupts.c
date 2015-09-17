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
#include "ops.h"
#include "interrupts.h"

#define OFF 0
#define ON 1

static void halt(void)
{
	return;
}

/*
static void x17bdc()
{
	
}
*/

static void set_phyln(int onoff)
{
/*
	// off
	r2 = read(0x1f39c)
	r1 = r2 & 3
	r3 = r2 & 8
	if (r1 == 0)
		goto x1a9a0
	if (r3 != 0)
		goto x1a9a0
	r11 = sp+16
	r1 = r11
	call 17bdc
	r2 = read(0x1f39c)
	r1 = r11
	call 1916c
x1a9a0:
	r1 = read(0x1f39c)
	r1 = r1 >> 2
	r1 &= 1
	r1 = (r1 == 0)
	if (r1 != 0)
		goto x1a9c8
	call 17cf0
	r1 = read(0x1f39c)
	r1 &= 0x10
	if (r1 != 0)
		goto x1a9c8
	call 1a200
x1a9c8:
	return;
*/
}

static void set_ddiphy(int onoff)
{
}


static void adjust_loadline()
{
}

static void x1a200(void)
{
	u32 r1, r2, r3, r4;
	u32 r11, r12, r13, r14;
	
	r14 = 0;
	r1 = 0x1f6c4;
	r2 = read32(r1);
	r13 = 0x01318010;
	r11 = 0x1f688;
	r1 = 0xff0000;
	r1 = r2 & r1;
	if (r1 == 0)
		goto end;
	r1 = 0xff00ffff;
	r1 = r2 & r1;
	if (r1 != 0)
		goto end;
	r12 = r1;
try0:
	r1 = 0x01318010 + r12;
	
	r2 = 0x80080000;
	write32(r2+160, r1);
	r1 = read32(r2+164);

	write32(r11, r1);
	r12 = r12 + 1;
	r1 = (r12 > 7);
	r11 = r11 + 4;
	if (r1 == 0)
		goto try0;
	r1 = 0x02010011;
	r11 = 0x1f6a8;

	r2 = 0x80080000;
	write32(r2+160, r1);
	r1 = read32(r2+164);

	write32(r11, r1);
	r1 = 0x01110012;
	r11 = 0x1df78;

	r2 = 0x80080000;
	write32(r2+160, r1);
	r1 = read32(r2+164);

	write32(r11, r1);
	r1 = 0x01110013;

	r2 = 0x80080000;
	write32(r2+160, r1);
	r1 = read32(r2+164);

	write32(r11+4, r1);
	r1 = 0x02110012;

	r2 = 0x80080000;
	write32(r2+160, r1);
	r1 = read32(r2+164);
	
	write32(r11+8, r1);
	r1 = 0x02110013;

	r2 = 0x80080000;
	write32(r2+160, r1);
	r1 = read32(r2+164);

	write32(r11+12, r1);
	
	r1 = 0x03210009;
	r2 = 0x81000000;

	r3 = 0x80080000;
	write32(r3+160, r1);
	r1 = read32(r3+164) | r2;
	write32(r3+164, r1);

	r1 = 0x0321000a;
	r2 = 0x81000000;

	r3 = 0x80080000;
	write32(r3+160, r1);
	r1 = read32(r3+164) | r2;
	write32(r3+164, r1);
	
	r1 = 0x01318011;
	r2 = 0x100;

	r3 = 0x80080000;
	write32(r3+160, r1);
	r1 = read32(r3+164) | r2;
	write32(r3+164, r1);
	
	r1 = 0x01328014;
	r2 = 0x20000000;
	r3 = 0xf0000000;
	
	r4 = 0x80080000;
	write32(r4+160, r1);
	r1 = read32(r4+164);
	r3 = ~r3;
	r1 &= r3;
	r1 |= r2;
	write32(r4+164, r1);
	
	r1 = 0x01308014;
	r2 = 0x10000000;
	r3 = 0xf0000000;
	
	r4 = 0x80080000;
	write32(r4+160, r1);
	r1 = read32(r4+164);
	r3 = ~r3;
	r1 &= r3;
	r1 |= r2;
	write32(r4+164, r1);

	r1 = 0x01308014;
	r2 = 0x10000000;
	r3 = 0xf0000000;

	r4 = 0x80080000;
	write32(r4+160, r1);
	r1 = read32(r4+164);
	r3 = ~r3;
	r1 &= r3;
	r1 |= r2;
	write32(r4+164, r1);
	
	r1 = 0x01110010;
	r2 = 0xfffe;
	
	r3 = 0x80080000;
	write32(r3+160, r1);
	r1 = read32(r3+164);
	r1 = r1 & r2;
	write32(r3+164, r1);

	r1 = 0x01328014;
	r2 = 0x30000000;
	r3 = 0xf0000000;

	r4 = 0x80080000;
	write32(r4+160, r1);
	r1 = read32(r4+164);
	r3 = ~r3;
	r1 &= r3;
	r1 |= r2;
	write32(r4+164, r1);
	
	r1 = 0x01328071;
	r2 = 1;

	r3 = 0x80080000;
	write32(r3+160, r1);
	r1 = read32(r3+164);
back:
	r1 = r2 & r1;
	if (r1 != r2)
		goto back;

	r1 = 0x64;
	r2 = read32(0xe0002028);
	r11 = r2 & 0x7f;
	
// 1b2d0
	r2 = 0xe0003020;
	r2 = read32(r2);
	r2 = r2 * 100;
	r2 = r2 << 8;
	r3 = r2 / r1;
	r1 = r3 >> 8;
	r2 = r3 >> 6;
	r4 = r1 + 64;
	r2 = r2 & 0xff;
	r1 = 0x1fff;
	if (r1 >= r3)
		goto skip3;
	r2 = r4 & 0xff;
	goto x1b324;
skip3:
	r1 = r3 + r3;
	r1 = r1 - 0x2000;
	r4 = r1 >> 8;
	r1 = 0xfff;
	if (r1 >= r3)
		goto x1b324;
	r1 = r4 + 0x40;
	r2 = r1 & 0xff;
x1b324:
	r1 = (r2 > 7);
	if (r1 != 0)
		goto skip4;
	r2 = 8;
skip4:
	r1 = r2 & 0xff;

	r4 = r1 & 0xff;
	r1 = 0xff;
	if (r4 == 0)
		goto skip0;
	r2 = 0xe000205c;
back2:
	r1 = read32(r2);
	r1 &= 1;
	if (r1 == 0)
		goto back2;
	r1 = 0xe0002058;
	r3 = 0xe000205c;
	write32(r1, r4);
back3:
	r1 = read32(r3);
	r1 ^= 1;
	r2 = r1 & 1;
	r1 = (r2 == 0);
	if (r1 == 0)
		goto back3;
	r1 = r2;
skip0:

	r4 = 0xe0000000;
	r3 = r4;
	r3 = r3 | 0xc;
	r1 = read32(r3);
	r1 = r1 | 0x4;
	r2 = 0xe0300000;
	write32(r3, r1);

	r1 = 0x5ff;
	write32(r2+12, r1);
x1a3fc:
	r1 = read32(r2+516);
	r1 = r1 & 0x400;
	if (r1 != 0)
		goto x1a3fc;
	
	r3 = r4;
	r3 |= 0xc;
	r2 = read32(r3);
	r1 = r11;
	r14 = r14 | 0xffff;
	r2 = r2 | 0x3;
	write32(r3, r2);

	r4 = r1 & 0xff;
	r1 = 0xff;
	if (r4 == 0)
		goto skip1;
	r2 = 0xe000205c;
back4:
	r1 = read32(r2);
	r1 &= 1;
	if (r1 == 0)
		goto back4;
	r1 = 0xe0002058;
	r3 = 0xe000205c;
	write32(r1, r4);
back5:
	r1 = read32(r3);
	r1 ^= 1;
	r2 = r1 & 1;
	r1 = (r2 == 0);
	if (r1 == 0)
		goto back5;
	r1 = r2;
skip1:

	r2 = 0x1f604;
	r1 = read32(r2);
	r3 = 0xfffd;
	r1 = r1 & r3;
	write32(r2, r1);

	adjust_loadline();

	r2 = 0x1f6c4;
	r1 = read32(r2);
	r1 = r1 & r14;
	write32(r2, r1);
end:
	return;
}

static void x196e0(void)
{
	u32 r1, r2, r3, r4;
	u32 r11, r12, r13, r14, r15, r16;

	r12 = 0x1f6c4;
	r2 = read32(r12);
	r1 = 0x00ff0000;
	r13 = 0x1df78;
	r1 = r2 & r1;
	if (r1 != 0)
		goto end;
	r14 = 0xff000000;
	r1 = r14 | 0xffff;
	r1 = r2 & r1;
	if (r1 == 0)
		goto end;
	r2 = 0x1f604;
	r1 = read32(r2);
	r1 |= 2;
	write32(r2, r1);
	adjust_loadline();
	r1 = 0xe0300000;
	r2 = 0x6ff;
	write32(r1+12, r2);
	r2 = r1;
	
	while ((read32(r2+516) & 0x400) == 0);
	r3 = 0xe0300000;
	while ((read32(r3+516) & 0x80000) == 0);

	r16 = 0xe0000000;
	r11 = r16;
	r11 |= 0xc;
	r4 = read32(r11);
	r2 = 0xfffb;
	r1 = 0x01328014;
	r4 = r4 & r2;
	r2 = 0x20000000;
	r3 = 0xf0000000;
	write32(r11, r4);
	r4 = 0x80080000;
	write32(r4+160, r1);
	r1 = read32(r4+164);
	r3 = ~r3;
	r1 &= r3;
	r1 |= r2;
	write32(r4+164, r1);

	r1 = read32(r11);
	r15 = 0xfffe;
	r2 = 0x1f3a0;
	r1 = r1 & r15;
	write32(r11, r1);
	
	r2 = read32(r2);
	r1 = 0x0131fff0;
	r3 = 0x80080000;
	write32(r3+160, r1);
	write32(r3+164, r2);

	r2 = read32(r13);
	r1 = 0x01110012;
	r3 = 0x80080000;
	write32(r3+160, r1);
	write32(r3+164, r2);

	r2 = read32(r13+4);
	r1 = 0x01110013;
	r3 = 0x80080000;
	write32(r3+160, r1);
	write32(r3+164, r2);
	
	r2 = read32(r13+8);
	r1 = 0x02110012;
	r3 = 0x80080000;
	write32(r3+160, r1);
	write32(r3+164, r2);

	r2 = read32(r13+12);
	r1 = 0x02110013;
	r3 = 0x80080000;
	write32(r3+160, r1);
	write32(r3+164, r2);

	r1 = 0x01318040;
	r2 = 1;
	r3 = 0x80080000;
	write32(r3+160, r1);
	write32(r3+164, r2);

	r1 = 0x01318041;
	r2 = 1;
	r3 = 0x80080000;
	write32(r3+160, r1);
	write32(r3+164, r2);

	r1 = 0x01318042;
	r2 = 1;
	r3 = 0x80080000;
	write32(r3+160, r1);
	write32(r3+164, r2);

	r1 = 0x01318043;
	r2 = 1;
	r3 = 0x80080000;
	write32(r3+160, r1);
	write32(r3+164, r2);

	r2 = read8(r12+61);
	r3 = read8(r12+69);
	r1 = 0x01110002;
	r2 |= r3;
	r2 = ~r2;
	r2 = r2 & 0xff;
	r3 = 0x80080000;
	write32(r3+160, r1);
	r1 = read32(r3+164) | r2;
	write32(r3+164, r1);

	r1 = read8(r12+61);
	r13 = 0;
	if (r1 != 0)
		goto skip0;
	r1 = read8(r12+69);
	if (r1 == 0)
		goto skip1;
skip0:
	r1 = 0x01110010;
	r2 = 1;
	r3 = 0x80080000;
	write32(r3+160, r1);
	r1 = read32(r3+164) | r2;
	write32(r3+164, r1);
	goto x198d8;

skip1:
	r1 = 0x01110002;
	r2 = 0xff;
	r1 |= 2;
	r3 = 0x80080000;
	write32(r3+160, r1);
	r1 = read32(r3+164) | r2;
	write32(r3+164, r1);
	
	r1 = 0x01318070;
	r2 = r15;
	r13 = 1;
	r3 = 0x80080000;
	write32(r3+160, r1);
	r1 = read32(r3+164);
	r1 &= r2;
	write32(r3+164, r1);

x198d8:
	r2 = read8(r12+62);
	r3 = read8(r12+70);
	r1 = 0x02110002;
	r2 |= r3;
	r2 = ~r2;
	r2 &= 0xff;
	r3 = 0x80080000;
	write32(r3+160, r1);
	r1 = read32(r3+164) | r2;
	write32(r3+164, r1);

	r1 = read8(r12+62);
	if (r1 != 0)
		goto x1991c;
	r11 = read8(r12+70);
	if (r11 != 0)
		goto x1991c;
	
	r1 = 0x01318074;
	r2 = 0xfffe;
	r3 = 0x80080000;
	write32(r3+160, r1);
	r1 = read32(r3+164);
	r1 &= r2;
	write32(r3+164, r1);

	goto x19934;

x1991c:
	r1 = 0x02110010;
	r11 = (r13 == 0);
	r2 = 1;
	r3 = 0x80080000;
	write32(r3+160, r1);
	r1 = read32(r3+164) | r2;
	write32(r3+164, r1);

	if (r11 != 0)
		goto x19944;
x19934:
	r1 = 0x01318062;
	r2 = 0xa000;
	r3 = 0x80080000;
	write32(r3+160, r1);
	r1 = read32(r3+164) | r2;
	write32(r3+164, r1);

x19944:
	r1 = 0x01328014;
	r3 = 0xf0000000;
	r2 = 0;
	r4 = 0x80080000;
	write32(r4+160, r1);
	r1 = read32(r4+164);
	r3 = ~r3;
	r1 &= r3;
	r1 |= r2;
	write32(r4+164, r1);

	r1 = 0x01308014;
	r3 = 0xf0000000;
	r2 = 0;
	r4 = 0x80080000;
	write32(r4+160, r1);
	r1 = read32(r4+164);
	r3 = ~r3;
	r1 &= r3;
	r1 |= r2;
	write32(r4+164, r1);

	r2 = r16;
	r2 |= 0xc;
	r3 = read32(r2);
	r4 = 0xfffd;
	r1 = 0x01318060;
	r3 &= r4;
	write32(r2, r3);
	r2 = 4;
	r3 = 0x80080000;
	write32(r3+160, r1);
x17040:
	r1 = read32(r3+164);
	r1 = r2 & r1;
	if (r1 != r2)
		goto x17040;

	if (r11 != 0)
		goto x199b4;
	r1 = 0x01318062;
	r2 = 0xffff5fff;
	r3 = 0x80080000;
	write32(r3+160, r1);
	r1 = read32(r3+164);
	r1 &= r2;
	write32(r3+164, r1);

x199b4:
	r1 = 0x03110011;
	r2 = 0x300;
	r3 = 0x80080000;
	write32(r3+160, r1);
	write32(r3+164, r2);

	r1 = 0x01318023;
	r2 = 0;
	r3 = 0x80080000;
	write32(r3+160, r1);
	write32(r3+164, r2);

	r3 = 0x1f6c4;
	r2 = read32(r3);
	r14 = r14 | 0xffff;
	r1 = 0x10000;
	r2 = r2 & r14;
	r2 |= r1;
	write32(r3, r2);

end:
	return;
}

static void set_cascadepll(int onoff)
{
	u32 r1, r2, r3, r4;

	switch (onoff) {
	case ON:
		r1 = 0x1f47c;
		r2 = 0x1f6c4;
		r3 = read8(r1+3);
		r4 = 0x1f39c;
		r1 = (r3 != 1);
		if (r1 != 0)
			goto end;
		write8(r2, r3);
		r1 = read32(r4);
		r1 &= 0x10;
		if (r1 != 0)
			goto end;
		x196e0();
		break;
	default:
	case OFF:
		r1 = 0x1f47c;
		r1 = read8(r1+3);
		r2 = 0x1f6c4;
		r3 = 0x1f39c;
		r4 = 0;
		if (r1 != 0)
			goto end;
		write8(r2, 0);
		r1 = read32(r3);
		r1 &= 0x10;
		if (r1 != 0)
			goto end;
		x1a200();
		break;
	}
end:
	return;
}

static void x18b20(void)
{
	u32 r1, r2, r3, r4, r5, r6, r7, r8, r9;
	u32 r10, r11, r12, r13, r14, r15, r16, ra;
	
	r3 = 0x1dff4;
	r1 = read32(r3+28);
	r2 = 0x1f850;
	if (r1 >= 0)
		goto skip;
	r2 = r3;
skip:
	r1 = r2;
	r12 = r1;

	r1 = 0x1dd94;
	r8 = 0x1f610;
	r11 = 0x1f438;
	r13 = r8;
	r2 = read8(r8);
	r3 = read8(r11);
	r15 = 0x1f43c;
	r14 = 0x1f6bc;
	r16 = r1;
	r9 = 0;
	if (r3 == r9)
		goto x18bc4;
	r4 = read32(r12+20);
	r1 = r4 >> (u16)8;
	r8 = r4 & 0xff;
	r7 = r1 & 0xff;
retry1:
	r5 = r3 & 1;
	r1 = r2 & 1;
	r2 >>= 1;
	r6 = r3 >> 1;
	r4 = r8*r5;
	r1 = (r1 == 0);
	r2 = r2 & 0xff;
	r3 = r6 & 0xff;
	if (r1 == 0)
		goto x18bbc;
	r4 = r7*r5;
x18bbc:
	r9 = r9 + r4;
	if (r3 != 0)
		goto retry1;
x18bc4:
	r8 = 0x1f614;
	r11 = r11 + 1;
	r7 = 2;
x18bd4:
	r1 = r11 + r7;
	r2 = r8 + r7;
	r3 = read8(r1);
	r2 = read8(r2);
	if (r3 == 0)
		goto x18c28;
	r4 = read32(r12+28);
	r1 = r4 >> 8;
	ra = r4 & 0xff;
	r10 = r1 & 0xff;
x18bf8:
	r5 = r3 & 1;
	r1 = r2 & 1;
	r4 = ra * r5;
	r1 = (r1 == 0);
	r2 = r2 & 0xff;
	r3 = r6 & 0xff;
	if (r1 == 0)
		goto x18c20;
	r4 = r10 * r5;
x18c20:
	r9 = r9 + r4;
	if (r3 != 0)
		goto x18bf8;
x18c28:
	r7 = r7 + 1;
	r1 = (r7 > 3);
	if (r1 == 0)
		goto x18bd4;
	r8 = 0x1f610;
	r7 = 0;
x18c40:
	r1 = r11 + r7;
	r2 = r14 + r7;
	r3 = read8(r1);
	r2 = read8(r2);
	r5 = 0;
	if (r3 == r5)
		goto x18cc4;
	r10 = r8 + r7;
x18c5c:
	r1 = r2 & 1;
	r6 = r3 >> 1;
	r13 = r2 >> 1;
	r1 = (r1 == 0);
	r3 = r3 & 1;
	ra = r5 + 1;
	if (r1 != 0)
		goto x18c84;
	r2 = read8(r10+4);
	r4 = read32(r12+28);
	goto x18c8c;
x18c84:
	r2 = read8(r10+1);
	r4 = read32(r12+20);
x18c8c:
	r2 = r2 >> r5;
	r1 = r4 & 0xff;
	r5 = r1 * r3;
	r2 |= 1;
	r2 = (r2 == 0);
	r1 = r4 >> 8;
	r1 = r1 & 0xff;
	if (r2 == 0)
		goto x18cb0;
	r5 = r1 * r3;
x18cb0:
	r9 = r9 + r5;
	r3 = r6 & 0xff;
	r2 = r13 & 0xff;
	r5 = ra;
	if (r3 != 0)
		goto x18c5c;
x18cc4:
	r7 = r7 + 1;
	r1 = (r7 > 1);
	if (r1 == 0)
		goto x18c40;
	r1 = r9 * 131;
	r9 = r1 >> 11;
	write16(r15+2, r9);
	write16(r16+60, r9);
	return;
}

static void set_x16off(void)
{
	if ((read32(0x1f39c) & 0x10) != 0)
		goto skip;
	x1a200();
	x18b20();
skip:
	return;
}

static void config_lclkdpm(void)
{
}

static void flush_datacache(void)
{
	asm volatile (
		"addi r1, r0, 1\n\t"
		"wcsr DCC, r1\n\t"
		"nop\n\t"
		"nop\n\t"
		"nop\n\t"
		"nop\n\t"
	);
}

static void flush_instcache(void)
{
	asm volatile (
		"addi r1, r0, 1\n\t"
		"wcsr ICC, r1\n\t"
		"nop\n\t"
		"nop\n\t"
		"nop\n\t"
		"nop\n\t"
	);
}

static void config_vpc(void)
{
}

static void config_bapm(void)
{
}

static void config_tdc(void)
{
	u32 r1, r2;

	r2 = read32(0x1f428) & 4;
	if (r2 == 0)
		goto skip;
	write8(0x1dcf4, read8(0x1f638+3));
	write8(read32(0x1d8f0), read8(0x1f638+3));
	write32(0x1f634, 0);
	write32(0x1f624, 0);

	r1 = read32(0xe0400000 + (read32(0x1d9a4+64) << 2));
	r1 |= 1;
	write32(0x1d9a4+68, r1);
	goto end;
skip:
	write8(0x1dcf4, 0);
	write8(read32(0x1df80), 0);
	write8(0x1d950, 0);
end:
	return;
}

static void config_lpmx(void)
{
}

static void config_htc(void)
{
	u32 r1, r2, r3, r4, r11, r12, r13;

	r4 = 0x1d9a4;
	r1 = 0x1f428;
	r1 = read32(r1);
	r11 = r1 & 0x10;
	r2 = 0x1f638;
	r3 = 0x1f624;
	r13 = 0x1dcf4;
	r12 = 0x1d8f0;
	if (r11 == 0)
		goto skip1;

	r1 = read8(r2+2);
	write8(r13+9, r1);
	r1 = read32(r12);
	r2 = read8(r2+2);
	write8(r1+9, r2);
	r1 = 0;
	write32(r3, r1);
	goto end;
skip1:
	r2 = read32(r4+68);
	r1 = read32(r4+64);
	r3 = 0xfff1;
	r2 = r2 & r3;
	write32(r4+68, r2);

	r1 = r1 << 2;
	r3 = 0xe0400000;
	r1 = r1 + r3;
	write32(r1, r2);

	r12 = 0x1d8f0;
	r1 = read32(r12);
	write8(r13+9, r11);
	write8(r1+9, r11);
end:
	return;
}

static void config_thermal(void)
{
}

static void config_voltage(void)
{
}

static void config_tdp(void)
{
}

static void set_pm(int onoff)
{
	u32 pm2 = 0x80010084;
	u32 pm3 = 0x80010800;
	u32 pm4 = 0x1dbdc;

	switch(onoff) {
	default:
	case OFF:
		write8(pm3, 0);
		write32(pm2, read32(pm2) | 1);
		write32(pm4, read32(pm4) & 0xfffe);
		break;
	case ON:
		write32(pm3+12, 1);
		write32(pm3+16, read32(0x1f468));
		write32(pm3+8, 1);
		write8(pm3+1, 1);
		write8(pm3, 1);
		write32(pm2, read32(pm2) | 1);
		write32(pm4, read32(pm4) | 1);
		break;
	}
	return;
}

static void config_nbdpm()
{
	return;
}

static void config_loadline()
{
}

static void reconfigure()
{
}

static void x1c300(u32 r1)
{
	u32 reg, r3;

	reg = 0x800108d8;
	write8(reg, 1);
	write8(reg+1, 1);
retry:
	r3 = read32(reg+32);
	if (r3 >= r1)
		goto found;
	goto retry;
found:
	write8(reg, 0);
	return;
}

static void pciepllswitch()
{
	u32 r1, reg;

	reg = 0xe0003014;
	r1 = (read32(0x1f630) & 0xff) * 100;
	write32(reg, read32(reg) | 2);

	x1c300(r1);

	write32(reg, read32(reg) & 0xfffd);
}

static void set_bapm(int onoff)
{
}

void SMUServiceRequest(unsigned int level, void *ctx)
{
	int requestid;
	write32(0xe0003004, 1);
	requestid = read32(0xe0003000);
	requestid &= 0x1fffe;
	requestid >>= 1;

	switch(requestid) {
	case SMC_MSG_HALT:
		halt();
		break;
	case SMC_MSG_PHY_LN_OFF:
		set_phyln(OFF);
		break;
	case SMC_MSG_PHY_LN_ON:
		set_phyln(ON);
		break;
	case SMC_MSG_DDI_PHY_OFF:
		set_ddiphy(OFF);
		break;
	case SMC_MSG_DDI_PHY_ON:
		set_ddiphy(ON);
		break;
	case SMC_MSG_CASCADE_PLL_OFF:
		set_cascadepll(OFF);
		break;
	case SMC_MSG_CASCADE_PLL_ON:
		set_cascadepll(ON);
		break;
	case SMC_MSG_PWR_OFF_x16:
		set_x16off();
		break;
	case SMC_MSG_CONFIG_LCLK_DPM:
		config_lclkdpm();
		break;
	case SMC_MSG_FLUSH_DATA_CACHE:
		flush_datacache();
		break;
	case SMC_MSG_FLUSH_INSTRUCTION_CACHE:
		flush_instcache();
		break;
	case SMC_MSG_CONFIG_VPC_ACCUMULATOR:
		config_vpc();
		break;
	case SMC_MSG_CONFIG_BAPM:
		config_bapm();
		break;
	case SMC_MSG_CONFIG_TDC_LIMIT:
		config_tdc();
		break;
	case SMC_MSG_CONFIG_LPMx:
		config_lpmx();
		break;
	case SMC_MSG_CONFIG_HTC_LIMIT:
		config_htc();
		break;
	case SMC_MSG_CONFIG_THERMAL_CNTL:
		config_thermal();
		break;
	case SMC_MSG_CONFIG_VOLTAGE_CNTL:
		config_voltage();
		break;
	case SMC_MSG_CONFIG_TDP_CNTL:
		config_tdp();
		break;
	case SMC_MSG_EN_PM_CNTL:
		set_pm(ON);
		break;
	case SMC_MSG_DIS_PM_CNTL:
		set_pm(OFF);
		break;
	case SMC_MSG_CONFIG_NBDPM:
		config_nbdpm();
		break;
	case SMC_MSG_CONFIG_LOADLINE:
		config_loadline();
		break;
	case SMC_MSG_ADJUST_LOADLINE:
		adjust_loadline();
		break;
	case SMC_MSG_RECONFIGURE:
		reconfigure();
		break;
	case SMC_MSG_PCIE_PLLSWITCH:
		pciepllswitch();
		break;
	case SMC_MSG_ENABLE_BAPM:
		set_bapm(ON);
		break;
	case SMC_MSG_DISABLE_BAPM:
		set_bapm(OFF);
		break;
	default:
		break;
	}

	write32(0xe0003004, 3);
}

void MicoISRHandler(void)
{
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
			Mask = Mask << 0x1;
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

