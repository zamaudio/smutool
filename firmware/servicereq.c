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
#include "servicereq.h"

#define OFF 0
#define ON 1

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

static u32 x16e90(u32 rr1)
{
	u32 r1, r2, r3, r4, r5, r6;

	r2 = 0x1f850;
	r5 = rr1;
	r6 = r2 + 0x2c;
	r4 = 0;
	r3 = 1;
x16ea8:
	r2 = r3 + r3;
	r1 = r5 >> r3;
	r2 = r2 + r6;
	r2 = read16(r2);
	r1 &= 1;
	r1 ^= 1;
	r2 = r2 * r1;
	r3++;
	r1 = (r3 > 6);
	r4 += r2;
	if (r1 == 0)
		goto x16ea8;
	return r4;
}

static void x1b65c(u32 rr1)
{
	u32 r1, r2, r3, r4, r5, r6;
	u32 r11, r12, r13;
	r13 = rr1 & 0xff;
	r1 = 0x1d9a4;
	
	r11 = 0x1d989;
	r4 = rr1;
	r1 = read8(r11+10);
	if (r1 == r13)
		goto end;
	r5 = 0xe000;
	r2 = r5 | 0x21b4;
x1b698:
	r1 = read32(r2);
	r1 ^= 1;
	r12 = r1 & 1;
	r1 = (r12 == 0);
	if (r1 == 0)
		goto x1b698;
	
	r1 = read8(r11+8);
	r2 = 0xe00021b0;
	r1 = r1 + r13;
	r1 <<= 1;
	r1 |= 1;
	write32(r2, r1);
	r1 = read8(r11+3);
	r1 = (r1 != 1);
	if (r1 != 0)
		goto x1b6f8;
	r2 = read32(r4+124);
	r3 = 0xfffc;
	r1 = read32(r4+120);
	r2 &= r3;
	r2 |= 1;
	write32(r4+124, r2);
	r1 <<= 2;
	r3 = 0xe0400000;
	r1 += r3;
	write32(r1, r2);

	write8(r11+3, r12);
	goto x1b77c;

x1b6f8:
	r6 = 0x80010000;
	r2 = r6;
	r1 = 1;
	r2 |= 0x08d8;
	write8(r2+1, r1);
	write8(r2, r1);
	r1 = r5;
	r1 |= 0x21b4;
	r1 = read32(r1);
x1b71c:
	r1 &= 1;
	if (r1 != 0)
		goto x1b76c;
	r1 = r6;
	r1 |= 0x08d8;
	r2 = read32(r1+32);
	r3 = r5;
	r3 |= 0x21b4;
	r1 = 0x1869f;
	if (r1 >= r2)
		goto x1b764;
	r2 = read32(r4+124);
	r1 = read32(r4+120);
	r2 |= 3;
	write32(r4+124, r2);
	r1 <<= 2;
	r3 = 0xe0400000;
	r1 += r3;
	write32(r1, r2);

	r1 = 1;
	write8(r11+3, r1);
	goto x1b76c;
x1b764:
	r1 = read32(r3);
	goto x1b71c;
x1b76c:
	r1 = 0x800108d8;
	r2 = 0;
	write8(r1, r2);
x1b77c:
	r1 = read8(r11+3);
	if (r1 != 0)
		goto end;
	write8(r11+10, r13);
end:
	return;
}

static void adjust_loadline()
{
	u32 r1, r2, r3, r4;
	u32 r11, r12, r13;
	r1 = 0x1f850;
	r4 = read8(r1+140);
	r11 = 0x1d989;
	r1 = read8(r11+7);
	r2 = 0x1f600;
	r3 = 0x1f604;
	r13 = 0x7e;
	r12 = 0x10000;
	if (r1 == 0)
		goto x16f34;
	r2 = read32(r2);
	r1 = read32(r3);
	r13 = r2 | r1;
x16f34:
	r1 = read8(r11+8);
	if (r1 != r4)
		goto x16f64;
	r2 = read8(r11+9);
	r1 = r13;
	if (r2 != r4)
		goto x16f64;
	r1 = x16e90(r1);

	r1 = r1 & 0xff;
	x1b65c(r1);
	
	r1 = 0x1f608;
	write32(r1, r13);
	goto end;
x16f64:
	r2 = read8(r11+9);
	r1 = r13;
	r3 = 0;
	if (r2 != r4)
		goto x16f88;
	r1 = x16e90(r1);

	write8(r11+10, r1);
	r12 |= 0xf608;
	write32(r12, r13);
	goto end;
x16f88:
	write8(r11+10, r3);
	r12 |= 0xf608;
	r1 = 0x7e;
	write32(r12, r1);
end:
	return;
}

static void x18b20(void)
{
	u32 r1, r2, r3, r4, r5, r6, r7, r8, r9;
	u32 r10, r11, r12, r13, r14, r15, r16, ra;
	
	r6 = 0; // compiler
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

static void halt(void)
{
	return;
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

static void x17bdc(u32 r1, u32 r2)
{
	u32 r3, r4, r5, r6, r7, r8, r9, r10;
	u32 r11, r12, r13;

	r5 = r2 >> 16;
	r11 = r2 >> 24;
	r9 = r2;
	r12 = 0x1f6c8;
	r2 = -r11;
	r13 = r1;
	r5 &= 0xff;
	r2 = r2 + 7;
	r7 = 8;
	r6 = 0;
x17c18:
	r8 = r6 << 3;
	r10 = 0xff;
	r1 = r5 - r8;
	r4 = r10 << r1;
	r3 = r13 + r6;
	r6++;
	r1 = (r6 > 4);
	if (r5 >= r7)
		goto x17c5c;
	write8(r3, r4);
	write8(r3+5, r4);
	r5 = r8 + 8;
	if (r11 >= r7)
		goto x17c5c;
	r1 = r10 >> r2;
	r1 = r4 & r1;
	write8(r3+5, r1);
	write8(r3, r1);
	goto x17c68;

x17c5c:
	r7 = r7 + 8;
	r2 = r2 + 8;
	if (r1 == 0)
		goto x17c18;
	
x17c68:
	r8 = r9 >> 1;
	r6 = 0;
x17c70:
	r3 = r13 + r6;
	r5 = r9 & 1;
	r1 = read8(r3);
	r7 = (r5 == 0);
	if (r1 == 0)
		goto x17cd0;
	r2 = r12 + r6;
	r4 = ~r1;
	if (r7 != 0)
		goto x17ca0;
	r1 = read8(r2);
	r1 = r4 & r1;
	write8(r2, r1);
	goto x17ca4;

x17ca0:
	write8(r3, r5);
x17ca4:
	r2 = r8 & 1;
	r1 = (r2 == 0);
	r4 = r12 + r6;
	if (r1 != 0)
		goto x17ccc;
	r1 = read8(r3+5);
	r2 = read8(r4+8);
	r1 = ~r1;
	r1 &= r2;
	write8(r4+8, r1);
	goto x17cd0;
x17ccc:
	write8(r3+5, r2);
x17cd0:
	r6++;
	r1 = (r6 > 4);
	if (r1 == 0)
		goto x17c70;
	return;
}

static void x1916c(u32 r1, u32 r2)
{
	u32 r3, r4, r5, r6, r7, r8, r9, r10;
	u32 r11, r12, r13, r14, r15, r16, r17, r18, r19, r20;
	u32 r21, r22, r23, r24, r25, fp;
	
	r18 = r1;
	r22 = 0x1f6c8;
	r1 = 0;
	r23 = 0x1f3c4;
	fp = 0x1f438;
	r21 = 0x1f710;
	r20 = 0x1f718;
	r24 = r2;
	r14 = r1;
	r16 = r22;
	r13 = r18;
x1920c:
	r1 = read8(r13);
	r17 = 0;
	r25 = r17;
	if (r1 != r17)
		goto x19224;
	r1 = read8(r13+5);
	if (r1 == r17)
		goto x19448;
x19224:
	r1 = read8(r16+56);
	r1 = (r1 != 0xff);
	if (r1 != 0)
		goto x192f8;
	r1 = read8(r16+64);
	r1 = (r1 != 0xff);
	if (r1 != 0)
		goto x192f8;
	r19 = 0x10000;
	r15 = r14 << 2;
	r1 = r19 | 0xd844;
	r1 = r15 + r1;
	r12 = read32(r1);
	r11 = 0x1df88;
	r1 = r12 + 11;
	r2 = 0x80080000;
	write32(r2+160, r1);
	r1 = read32(r2+164);

	r11 = r15 + r11;
	write32(r11, r1);
	r1 = r12 + 12;
	r2 = 0x80080000;
	write32(r2+160, r1);
	r1 = read32(r2+164);

	r2 = (r14 > 2);
	write32(r11+20, r1);
	if (r2 != 0)
		goto x192ac;
	r11 = 0x1dfb0;
	r1 = r12 + 0x400f;
	r2 = 0x80080000;
	write32(r2+160, r1);
	r1 = read32(r2+164);

	r11 = r15 + r11;
	write32(r11, r1);
	r1 = r12 + 0x400a;
	r2 = 0x80080000;
	write32(r2+160, r1);
	r1 = read32(r2+164);

	r2 = 0xfffd;
	r1 &= r2;
	write32(r11+20, r1);
x192ac:
	r12 = r17;
x192b0:
	r1 = 0x1d844;
	r1 = r15 + r1;
	r1 = read32(r1);
	r3 = r12 << 7;
	r2 = 0x1df50;
	r11 = r14 << 3;
	r1 = r1 + r3;
	r11 = r11 + r2;
	r1 = r1 + 0x6005;
	r2 = 0x80080000;
	write32(r2+160, r1);
	r1 = read32(r2+164);

	r11 = r11 + r12;
	r1 >>= 24;
	r12 = r12 + 1;
	r2 = (r12 > (u32)7);
	write8(r11, r1);
	if (r2 == 0)
		goto x192b0;
x192f8:
	r1 = read8(r16);
	r2 = read8(r16+8);
	r5 = r21 + r14;
	r6 = r20 + r14;
	r1 |= r2;
	r1 &= 0xff;
	r7 = r24 & 1;
	if (r1 == 0)
		goto x19374;
	r2 = read8(r5);
	r3 = 1;
	r1 = read8(r13);
	r2 = r3 << r2;
	r4 = read8(r13+5);
	r2 = ~r2;
	r2 &= r1;
	write8(r13, r2);
	r1 = read8(r6);
	r1 = r3 << r1;
	r1 = ~r1;
	r2 &= r1;
	write8(r13, r2);
	r1 = read8(r5);
	r1 = r3 << r1;
	r1 = ~r1;
	r1 &= r4;
	write8(r13+5, r1);
	r2 = read8(r6);
	r3 <<= r2;
	r1 &= r3;
	goto x193d4;

x19374:
	r2 = r18 + r14; // arg?
	r1 = 1;
	write8(r2-20, r1);
	r1 = read8(r5);
	r3 = 1;
	r2 = read8(r13);
	r1 = r3 << r1;
	r4 = read8(r13+5);
	r1 |= r2;
	write8(r13, r1);
	r2 = read8(r6);
	r17 = r3;
	r25 = r3;
	r2 = r3 << r2;
	r1 |= r2;
	write8(r13, r1);
	r1 = read8(r5);
	r1 = r3 << r1;
	r1 |= r4;
	write8(r13+5, r1);
	r2 = read8(r6);
	r3 = r3 << r2;
	r1 |= r3;
x193d4:
	write8(r13+5, r1);
	r1 = r7 | r25;
	r1 = (r1 == 0);
	if (r1 != 0)
		goto x1940c;
	r3 = read8(r13);
	r2 = read8(r16+56);
	r1 = r24 + r14; // arg?
	r2 = r3 & r2;
	r2 = r2 & 0xff;
	r4 = 1;
	if (r3 == r2)
		goto x19408;
	r4 = read8(r1);

x19408:
	write8(r1, r4);
x1940c:
	r1 = r24 >> 1;
	r1 &= 1;
	r1 |= r17;
	r1 = (r1 == 0);
	if (r1 == 0)
		goto x19448;
	r3 = read8(r13+5);
	r2 = read8(r16+64);
	r1 = r24 + r14; // arg?
	r2 = r3 & r2;
	r2 &= 0xff;
	r4 = 1;
	if (r3 == r2)
		goto x19444;
	r4 = read8(r1);

x19444:
	write8(r1, r4);
x19448:
	r14 += 1;
	r1 = (r14 > 4);
	r13 += 1;
	r16 += 1;
	if (r1 == 0)
		goto x1920c;
	
	r14 = 0;
	r11 = r24; // arg?
	r10 = r24; // arg?
	r3 = r23;
x1946c:
	r4 = r18 + r14;
	r5 = r22 + r14;
	r1 = r11 + r14;
	r1 = read8(r1);
	r9 = (r14 > 4);
	r7 = r4;
	r8 = r5;
	if (r1 == 0)
		goto x194b8;
	r2 = read8(r4);
	r1 = read8(r3);
	r1 |= r2;
	write8(r3, r1);
	r1 = read8(r4);
	r2 = read8(r5+56);
	r1 = ~r1;
	r1 &= r2;
	write8(r5+56, r1);
x194b8:
	r1 = read8(r6);
	if (r1 == 0)
		goto x194e4;
	r2 = read8(r7+5);
	r1 = read8(r3+2);
	r1 |= r2;
	write8(r3+2, r1);
	r1 = read8(r7+5);
	r2 = read8(r8+64);
	r1 = ~r1;
	r1 &= r2;
	write8(r8+64, r1);

x194e4:
	r3 = r3 + 4;
	if (r9 == 0)
		goto x1946c;

//x19564
	r1 = 2000;
	r14 = 0;
	x1c300(r1);
	r13 = r18;
	r15 = r23;
	r16 = r14;
x1957c:
	r1 = 0x1d830;
	r12 = r22 + r14;
	r5 = read8(r13);
	r6 = read8(r13+5);
	r7 = r16 + r1;
	r3 = read8(r12);
	r2 = read8(r12+8);
	r1 = r17 + r14;
	r4 = r18 + r14;
	r1 = read8(r1);
	r4 = read8(r4);
	r3 &= r5;
	r2 &= r6;
	r3 ^= r5;
	r2 ^= r6;
	r2 |= r3;
	r1 |= r4;
	r2 &= 0xff;
	r1 &= 0xff;
	if (r1 == 0)
		goto x19678;
	r11 = read32(r7);
	r1 = r11 | 2;
	r3 = 0x80080000;
	write32(r3+160, r1);
	r1 = read32(r3+164);
	r1 |= r2;
	write32(r3+164, r1);

	r1 = read8(r12+56);
	if (r1 != 0)
		goto x19600;
	r3 = 0x80080000;
	write32(r3+160, r1);
	r1 = read32(r3+164);
	r1 &= r2;
	write32(r3+164, r1);

x19600:
	r1 = 0x1d844;
	r5 = r16 + r1;
	r1 = r17 + r14;
	r1 = read8(r1);
	r3 = r16 + r23;
	r4 = r18 + r14;
	if (r1 == 0)
		goto x19630;
	r2 = read8(r13+5);
	r1 = read8(r3+3);
	r1 |= r2;
	write8(r3+3, r1);
x19630:
	r1 = read8(r4);
	if (r1 == 0)
		goto x19648;
	r1 = read8(r15+1);
	r2 = read8(r13);
	r1 |= r2;
	write8(r15+1, r1);
x19648:
	r1 = read32(r5);
	r2 = read32(r15);
	r1 |= 0x12;
	r3 = 0x80080000;
	write32(r3+160, r1);
	write32(r3+164, r2);

	r1 = read8(r15+3);
	r2 = read8(r15+1);
	r4 = fp + r14;
	r3 = read8(r4);
	r1 &= r2;
	r1 = ~r1;
	r1 &= r3;
	write8(r4, r1);
x19678:
	r14++;
	r1 = (r14 > 4);
	r13++;
	r16 += 4;
	r15 += 4;
	if (r1 == 0)
		goto x1957c;
	x18b20();

	return;
}

static void x17e94(u32 r1)
{
	u32 r2, r3;
	u32 r11, r12, r13, r14, r15, r16, r17, r18, r19, r20;
	r19 = 0;
	r20 = r1;
	r17 = r19;
x17ed0:
	r1 = r20 + r19;
	r1 = read8(r1);
	if (r1 == 0)
		goto x180ac;
	r18 = 0x00010000;
	r1 = 0xe0001000;
	r2 = r18;
	r2 = r2 | 0xdfd8;
	r12 = read32(r2);
	r1 = read32(r1);
	r2 = 0x00010000;
	r12 |= 9;
	r1 &= 0x4000;
	if (r1 == 0)
		goto x17f3c;
	r2 |= 0xd844;
	r1 = r17 + r2;
	r11 = read32(r1);
	r12 |= 0x10;
	r2 = r12;
	r1 = r11 + 0x11;
	r3 = 0x80080000;
	write32(r3+160, r1);
	write32(r3+164, r2);

	r1 = r11 + 1;
	r2 = 0x200;
	r3 = 0x80080000;
	write32(r3+160, r1);
	write32(r3+164, r2);

	r1 = r11 + 2;
	r2 = 0x200;
	goto x17f50;

x17f3c:
	r2 |= 0xd844;
	r1 = r17 + r2;
	r1 = read32(r1);
	r2 = r12;
	r1 = r1 + 0x11;
x17f50:
	r3 = 0x80080000;
	write32(r3+160, r1);
	write32(r3+164, r2);

	r16 = 0x00010000;
	r1 = r16;
	r1 |= 0xd844;
	r1 = r17 + r1;
	r11 = read32(r1);
	r2 = r12 | 0x20;
	r15 = 0;
	r1 = r11 + 0x11;
	r3 = 0x80080000;
	write32(r3+160, r1);
	write32(r3+164, r2);

	r1 = r11 + 1;
	r2 = 0x621f;
	r3 = 0x80080000;
	write32(r3+160, r1);
	write32(r3+164, r2);

	r1 = r11 + 2;
	r2 = 0x621f;
	r3 = 0x80080000;
	write32(r3+160, r1);
	write32(r3+164, r2);

x17f90:
	r1 = r15 << 2;
	r2 = r16;
	r2 |= 0xd844;
	r1 = r1 + r2;
	r1 = read32(r1);
	r2 = 0;
	r15++;
	r1 = r1 + 13;
	r3 = 0x80080000;
	write32(r3+160, r1);
	write32(r3+164, r2);

	r1 = (r15 > 4);
	if (r1 == 0)
		goto x17f90;
	r15 = 0;
x17fc0:
	r1 = r15 << 2;
	r11 = r16;
	r11 |= 0xd844;
	r1 += r11;
	r1 = read32(r1);
	r12 = 0x8000;
	r2 = 0;
	r1 += r12;
	r3 = 0x80080000;
	write32(r3+160, r1);
	write32(r3+164, r2);

	r15++;
	r1 = (r15 > 4);
	if (r1 == 0)
		goto x17fc0;
	r1 = r17 + r11;
	r11 = read32(r1);
	r2 = 8;
	r18 |= 0xdfd8;
	r12 = r11 + r12;
	r1 = r12;
	r3 = 0x80080000;
	write32(r3+160, r1);
	write32(r3+164, r2);

	r1 = 3000;
	x1c300(r1);

	r1 = r12;
	r2 = 0;
	r3 = 0x80080000;
	write32(r3+160, r1);
	write32(r3+164, r2);

	r14 = r11 + 1;
	r1 = r14;
	r2 = 0x200;
	r3 = 0x80080000;
	write32(r3+160, r1);
	write32(r3+164, r2);

	r13 = r11 + 2;
	r1 = r13;
	r2 = 0x200;
	r3 = 0x80080000;
	write32(r3+160, r1);
	write32(r3+164, r2);

	r1 = r12;
	r2 = 8;
	r3 = 0x80080000;
	write32(r3+160, r1);
	write32(r3+164, r2);

	r2 = read32(r18);
	r1 = r11 + 0x11;
	r15 = 0;
	r3 = 0x80080000;
	write32(r3+160, r1);
	write32(r3+164, r2);

	r1 = r14;
	r2 = r15;
	r3 = 0x80080000;
	write32(r3+160, r1);
	write32(r3+164, r2);

	r1 = r13;
	r2 = r15;
	r3 = 0x80080000;
	write32(r3+160, r1);
	write32(r3+164, r2);

	r1 = r12;
	r2 = r15;
	r3 = 0x80080000;
	write32(r3+160, r1);
	write32(r3+164, r2);

x18080:
	r1 = r15 << 2;
	r2 = r16;
	r2 |= 0xd844;
	r1 += r2;
	r2 = 1;
	r15 += r2;
	r1 += 13;
	r3 = 0x80080000;
	write32(r3+160, r1);
	write32(r3+164, r2);

	r1 = (r15 > 4);
	if (r1 == 0)
		goto x18080;

x180ac:
	r19++;
	r1 = (r19 > 4);
	r17 += 4;
	if (r1 == 0)
		goto x17ed0;

	return;
}

static void x18d04(u32 rr1, u32 rr2, u32 rr3)
{
	u32 r1, r2, r3, r4, r5, r6, r7, r8, r9, r10;
	u32 r11, r12, r13, r14, r15, r16, r17, r18, r19, r20, r21;
	r15 = rr1;
	r16 = 0x00010000;
	r1 = 0;
	r16 |= 0xf3c4;
	r20 = 0x1f438;
	r12 = 0x1f6c8;
	r19 = 0x1f710;
	r18 = 0x1f718;
	r13 = r1;
	r21 = rr2;
	r11 = r15;
	r17 = r1;
	r14 = r16;
x18d8c:
	r5 = read8(r11);
	r8 = 0;
	r10 = r8;
	if (r5 != r8)
		goto x18da4;
	r1 = read8(r11+5);
	if (r1 == r8)
		goto x18f68;
x18da4:
	r1 = read8(r12+56);
	r2 = read8(r12+64);
	r7 = read8(r11+5);
	r4 = r19 + r13;
	r1 |= r2;
	r1 &= 0xff;
	r6 = r18 + r13;
	r9 = r21 & 1;
	if (r1 == 0)
		goto x18e1c;

	r2 = read8(r4);
	r3 = 1;
	r2 = r3 << r2;
	r2 = ~r2;
	r2 &= r5;
	write8(r11, r2);
	r1 = read8(r6);
	r1 = r3 << r1;
	r1 = ~r1;
	r2 &= r1;
	write8(r11, r2);
	r1 = read8(r4);
	r1 = r3 << r1;
	r1 = ~r1;
	r1 &= r7;
	write8(r11+5, r1);
	r2 = read8(r6);
	r3 <<= r2;
	r3 = ~r3;
	r1 &= r3;
	goto x18e64;

x18e1c:
	r2 = read8(r4);
	r3 = 1;
	r8 = r3;
	r2 = r3 << r2;
	r10 = r3;
	r2 |= r5;
	write8(r11, r2);
	r1 = read8(r6);
	r1 = r3 << r1;
	r2 |= r1;
	write8(r11, r2);
	r1 = read8(r4);
	r1 = r3 << r1;
	r1 |= r7;
	write8(r11+5, r1);
	r2 = read8(r6);
	r3 <<= r2;
	r1 |= r3;
x18e64:
	write8(r11+5, r1);
	r1 = r9 | r10;
	r1 = (r1 == 0);
	if (r1 == 0)
		goto x18e9c;
	
	r1 = read8(r12+56);
	r3 = read8(r11);
	r2 = r15; // arg?
	r1 = ~r1;
	r2 = r2 + r13;
	r1 = r1 & r3;
	r4 = 1;
	if (r1 == r3)
		goto x18e98;
	r4 = read8(r2);
x18e98:
	write8(r2, r4);
x18e9c:
	r1 = r21 >> 1;
	r1 &= 1;
	r1 |= r8;
	r1 = (r1 == 0);
	if (r1 != 0)
		goto x18ed8;
	r1 = read8(r12+64);
	r3 = read8(r11+5);
	r2 = rr3; // arg?
	r1 = ~r1;
	r2 += r13;
	r1 &= r3;
	r4 = 1;
	if (r1 == r3)
		goto x18ed4;
	r4 = read8(r2);
x18ed4:
	write8(r2, r4);
x18ed8:
	r1 = rr1; // arg?
	r4 = r1 + r13;
	r1 = read8(r4);
	if (r1 == 0)
		goto x18efc;
	r1 = read8(r11);
	r2 = read8(r14);
	r1 = ~r1;
	r1 &= r2;
	write8(r14+1, r1);
x18efc:
	r1 = rr3; // arg?
	r3 = r1 + r13;
	r1 = read8(r3);
	if (r1 == 0)
		goto x18f20;
	r1 = read8(r11+5);
	r2 = read8(r14+3);
	r1 = ~r1;
	r1 &= r2;
	write8(r14+3, r1);
x18f20:
	r1 = read8(r3);
	if (r1 != 0)
		goto x18f30;
	r1 = read8(r4);
	if (r1 == 0)
		goto x18f68;
x18f30:
	r1 = 0x1d844;
	r1 = r17 + r1;
	r1 = read32(r1);
	r2 = read32(r14);
	r1 |= 0x12;
	r3 = 0x80080000;
	write32(r3+160, r1);
	write32(r3+164, r2);

	r4 = r20 + r13;
	r1 = read8(r11);
	r2 = read8(r11+5);
	r3 = read8(r4);
	r1 |= r2;
	r1 |= r3;
	write8(r4, r1);
x18f68:
	r13++;
	r1 = (r13 > 4);
	r12++;
	r14 += 4;
	r17 += 4;
	r11++;
	if (r1 == 0)
		goto x18d8c;

	r1 = 500;
	r13 = 0;
	x1c300(r1);

	r11 = r16;
	r12 = r13;
x18f98:
	r1 = 0x1d844;
	r14 = rr3; // arg?
	r6 = r12 + r1;
	r3 = r14 + r13;
	r16 = rr1; // arg?
	r1 = read8(r3);
	r2 = r15 + r13;
	r4 = r16 + r13;
	r5 = r2;
	r13++;
	r12 += 4;
	if (r1 == 0)
		goto x18fe0;
	r1 = read8(r2+5);
	r2 = read8(r11+2);
	r1 = ~r1;
	r1 &= r2;
	write8(r11+2, r1);
x18fe0:
	r1 = read8(r4);
	if (r1 == 0)
		goto x18ffc;
	r1 = read8(r5);
	r2 = read8(r11);
	r1 = ~r1;
	r1 &= r2;
	write8(r11, r1);
x18ffc:
	r1 = read8(r3);
	if (r1 != 0)
		goto x1900c;
	r1 = read8(r4);
	if (r1 == 0)
		goto x1901c;
x1900c:
	r1 = read32(r6);
	r2 = read32(r11);
	r1 |= 0x12;
	r3 = 0x80080000;
	write32(r3+160, r1);
	write32(r3+164, r2);

x1901c:
	r1 = (r13 > 4);
	r11 += 4;
	if (r1 == 0)
		goto x18f98;
	
	r13 = 0;
x1902c:
	r1 = r14 + r13;
	r1 = read8(r1);
	if (r1 == 0)
		goto x190a0;
	
	r12 = 0;
x1903c:
	r1 = r15 + r13;
	r2 = read8(r1+5);
	r5 = r13 << 2;
	r3 = 0x1df50;
	r1 = 0x1d844;
	r2 >>= r12;
	r4 = r13 << 3;
	r1 = r5 & r1;
	r4 &= r3;
	r5 = r12 << 7;
	r2 &= 1;
	r4 += r12;
	r2 = (r2 == 0);
	r12++;
	if (r2 == 0)
		goto x19098;
	
	r1 = read32(r1);
	r2 = read8(r4);
	r1 = r1 + r5;
	r2 = r2 << 24;
	r1 = r1 + 0x6005;
	r3 = 0x80080000;
	write32(r3+160, r1);
	write32(r3+164, r2);
x19098:
	r1 = (r12 > 7);
	if (r1 == 0)
		goto x1903c;
x190a0:
	r13++;
	r1 = (r13 > 4);
	if (r1 == 0)
		goto x1902c;
	r13 = 0;
x190b0:
	r1 = r16 + r13;
	r1 = read8(r1);
	if (r1 == 0)
		goto x19124;
	
	r12 = 0;
x190c0:
	r3 = r13 << 2;
	r1 = 0x1d844;
	r11 = r3 + r1;
	r1 = 0x1dfb0;
	r14 = r3 + r1;
	r2 = r15 + r13;
	r1 = read8(r2);
	r3 = r12 << 7;
	r1 >>= r12;
	r1 &= 1;
	r1 = (r1 == 0);
	r12++;
	if (r1 != 0)
		goto x1911c;
	
	r11 = read32(r11);
	r2 = read32(r14);
	r11 = r11 + r3;
	r1 = r11 + 0x400f;
	r3 = 0x80080000;
	write32(r3+160, r1);
	write32(r3+164, r2);

	r2 = read32(r14+20);
	r1 = r11 + 0x400a;
	r3 = 0x80080000;
	write32(r3+160, r1);
	write32(r3+164, r2);

x1911c:
	r1 = (r12 > 7);
	if (r1 == 0)
		goto x190c0;

x19124:
	r13++;
	r1 = (r13 > 2);
	if (r1 == 0)
		goto x190b0;
	
	x18b20();
	return;
}

static void x18490(u32 rr1, u32 rr2)
{
	
}

static void x180f0(u32 rr1, u32 rr2)
{
	u32 r1, r2, r3, r4, r5, r6, r7, r8, r9;
	u32 r11, r12, r13, r14, r15, r16, r17, r18, r19, r20;
	r4 = rr2 >> 1;
	r3 = 0;
	r18 = 0x1f6c8;
	r16 = rr1;
	r4 &= 1;
	r13 = r3;
	r9 = rr2 & 1;
x18158:
	r7 = r16 + r13;
	r1 = read8(r7);
	r8 = 0;
	r3 = r8;
	if (r1 != r8)
		goto x18174;
	r1 = read8(r7+5);
	if (r1 == r8)
		goto x1820c;
x18174:
	r6 = r18 + r13;
	r1 = read8(r6+56);
	r2 = read8(r6+64);
	r1 |= r2;
	r1 &= 0xff;
	if (r1 != 0)
		goto x181a4;
	r1 = rr1; // arg?
	r2 = r1 + r13;
	r1 = 1;
	r8 = r1;
	write8(r2-4, r1);
	r3 = r1;
x181a4:
	r1 = r9 | r3;
	r1 = (r1 == 0);
	if (r1 == 0)
		goto x181d8;
	r1 = read8(r6+56);
	r3 = read8(r7);
	r2 = 0; // sp+48
	r1 = ~r1;
	r2 = r2 + r13;
	r1 = r1 + r3;
	r5 = 1;
	if (r1 == r3)
		goto x181d4;
	r5 = read8(r2);
x181d4:
	write8(r2, r5);
x181d8:
	r1 = r4 | r8;
	r1 = (r1 == 0);
	if (r1 == 0)
		goto x1820c;
	r1 = read8(r6+64);
	r3 = read8(r7+5);
	r2 = 0; // sp+56
	r1 = ~r1;
	r2 = r2 + r13;
	r1 = r1 & r3;
	r5 = 1;
	if (r1 == r3)
		goto x18208;
	r5 = read8(r2);
x18208:
	write8(r2, r5);
x1820c:
	r13++;
	r1 = (r13 > 4);
	if (r1 == 0)
		goto x18158;
	
	r17 = 0x1f3c0;
	r13 = 0;
	r15 = r16;
x18228:
	r20 = 0; // sp+56
	r1 = r20 + r13;
	r1 = read8(r1);
	if (r1 == 0)
		goto x1824c;
	r1 = r18 + r13;
	r2 = read8(r1+64);
	r3 = read8(r15+5);
	r2 |= r3;
	write8(r1+64, r2);
x1824c:
	r19 = 0; // sp+48
	r1 = r19 + r13;
	r1 = read8(r1);
	if (r1 == 0)
		goto x1834c;
	if (r13 != 0)
		goto x182d0;

	r12 = 0x1f3b0;
	r11 = r13;
x1826c:
	r2 = read8(r16);
	r14 = r11 << 7;
	r1 = 0x01204011;
	r2 >>= r11;
	r2 &= 1;
	r2 = (r2 == 0);
	r1 = r14 + r1;
	if (r2 != 0)
		goto x182c0;
	r2 = read32(r12);
	r3 = 0x80080000;
	write32(r3+160, r1);
	write32(r3+164, r2);


	r1 = 0x01204010;
	r1 = r14 + r1;
	r12 = r12 + 4;
	r2 = 2;
	if (r2 >= r11)
		goto x182b8;
	r12 = 0x1f3a4;
x182b8:
	r2 = read32(r17);
	r3 = 0x80080000;
	write32(r3+160, r1);
	write32(r3+164, r2);

x182c0:
	r11++;
	r1 = (r11 > 7);
	if (r1 == 0)
		goto x1826c;
	goto x1834c;

x182d0:
	r1 = r13 - 1;
	r1 = (r1 > 1);
	if (r1 != 0)
		goto x1834c;
	r12 = 0x1f3ac;
	r2 = (r13 != 1);
	if (r2 == 0)
		goto x182f4;
	r12 = 0x1f3a8;
x182f4:
	r1 = 0x01214010;
	if (r2 == 0)
		goto x18308;
	r1 = 0x02214010;
x18308:
	r11 = r1;
	r14 = 0;
x18310:
	r2 = read8(r15);
	r1 = r11 + 1;
	r2 >>= r14;
	r2 &= 1;
	r2 = (r2 == 0);
	r14++;
	if (r2 != 0)
		goto x18340;
	r2 = read32(r12);
	r3 = 0x80080000;
	write32(r3+160, r1);
	write32(r3+164, r2);

	r2 = read32(r17);
	r1 = r11;
	r3 = 0x80080000;
	write32(r3+160, r1);
	write32(r3+164, r2);

x18340:
	r1 = (r14 > 7);
	r11 += 0x80;
	if (r1 == 0)
		goto x18310;
x1834c:
	r1 = r19 + r13;
	r1 = read8(r1);
	if (r1 != 0)
		goto x18364;
	r1 = r20 + r13;
	r1 = read8(r1);
	if (r1 == 0)
		goto x183dc;
x18364:
	r1 = 0x1d830;
	r12 = r13 << 2;
	r3 = read8(r15+5);
	r2 = read8(r15);
	r1 = r12 + r1;
	r11 = read32(r1);
	r2 |= r3;
	r2 &= 0xff;
	r2 = ~r2;
	r1 = r11 | 2;
	r3 = 0x80080000;
	write32(r3+160, r1);
	r1 = read32(r3+164);
	r1 &= r2;
	write32(r3+164, r1);

	r2 = 1;
	r1 = r11 | 0x10;
	r3 = 0x80080000;
	write32(r3+160, r1);
	r1 = read32(r3+164);
	r1 |= r2;
	write32(r3+164, r1);


	r2 = rr1; // sp+68;
	r1 = r2 + r13;
	r1 = read8(r1-4);
	if (r1 == 0)
		goto x183dc;
	r1 = 0x1d81c;
	r1 = r12 + r1;
	r2 = read32(r1);
	r3 = (r13 != 2);
	r1 = 0x8070;
	r1 = r2 + r1;
	if (r3 != 0)
		goto x183d4;
	r1 = r1 + 4;
x183d4:
	r2 = 1;
	r3 = 0x80080000;
	write32(r3+160, r1);
	r1 = read32(r3+164);
	r1 |= r2;
	write32(r3+164, r1);

x183dc:
	r13++;
	r1 = (r13 > 4);
	r15++;
	if (r1 == 0)
		goto x18228;
	
	return;
}

static void set_ddiphy(int onoff)
{
	
}

static void set_phyln(int onoff)
{
	u32 r1, r2, r3, r4, r5, r6, r7, r8, r9, r10, r11, r12, r13, r14, r15, r16;
	u32 r11a, r12a, r13a;

	switch (onoff) {
	default:
	case OFF:
		r2 = read32(0x1f39c);
		r1 = r2 & 3;
		r3 = r2 & 8;
		if (r1 == 0)
			goto x1a9a0;
		if (r3 != 0)
			goto x1a9a0;
		r11 = 0;
		r1 = r11;
		x17bdc(r1, r2);
		
		r2 = read32(0x1f39c);
		r1 = r11;
		x1916c(r1, r2);
x1a9a0:
		r1 = read32(0x1f39c);
		r1 = r1 >> 2;
		r1 &= 1;
		r1 = (r1 == 0);
		if (r1 != 0)
			goto end;
		r2 =  0x1f6c4;
		r3 = read8(r2+61);
		r1 = read8(r2+62);
		r5 = read8(r2+69);
		r4 = read8(r2+70);
		r1 |= r4;
		r1 <<= 8;
		r3 |= r5;
		r1 |= r3;
		write16(r2+2, r1);

		r1 = read32(0x1f39c);
		r1 &= 0x10;
		if (r1 != 0)
			goto end;
		x1a200();
		break;
	case ON:
		r15 = 0x10000;
		r1 = r15;
		r1 |= 0xf6c4;
		r2 = read32(r1);
		r14 = 0x00ff0000;
		r13 = 0x00010000;
		r1 = 0;
		r1 = r14;
		r13 = r13 | 0xf39c;
		r2 &= r1;
		r3 = read32(r13);
		r2 >>= 16;
		r1 = r3 & 7;
		r16 = r2 & 0xff;
		if (r1 == 0)
			goto x1a0e4;
		r2 = r3 >> 16;
		r1 = r3 >> 24;
		r2 &= 0xff;
//x17d20
		r6 = 0x00ffffff;
		r8 = r6 << r2;
		r3 = r1;
		r7 = 0x1f6c4;
		r1 = (r1 > 0x7);
		r2 = (r2 > 0x17);
		r5 = 0;
		r4 = 0x17;
		if (r1 != r5)
			goto x17d50;
		r5 = 1;
x17d50:
		r1 = r2 | r2;
		r1 = (r1 == 0);
		if (r1 == 0)
			goto x17d84;
		if (r4 >= r3)
			goto x17d64;
		r3 = r4;
x17d64:
		r1 = r4 - r3;
		r1 = r6 >> r1;
		r2 = read32(r7);
		r1 &= r8;
		r1 >>= 8;
		r1 &= 0xffff;
		r2 |= r1;
		write32(r7, r2);

x17d84:
		r1 = read32(r13);
		r1 &= 0x10;
		if (r1 != 0)
			goto x1a0e4;
		x196e0();

x1a0e4:
		r2 = read32(r13);
		r1 = r2 & 3;
		if (r1 == 0)
			goto x1a168;
		r1 = 0x01318014;
		r2 = 0x80080000;
		write32(r2+160, r1);
		r1 = read32(r2+164);

		r11 = r1;
		r1 = 0x01318014;
		r2 = 0xffc3;
		r2 = r11 & r2;
		r3 = 0x80080000;
		write32(r3+160, r1);
		write32(r3+164, r2);

		r2 = read32(r13);
		r12 = 0; // sp+32
		r1 = r12;
		r11a = r11;
		r12a = r12;
		r13a = r13;

		r5 = r2 >> 16;
		r11 = r2 >> 24;
		r9 = r2;
		r12 = 0x1f6c8;
		r2 = -r11;
		r13 = r1;
		r5 &= 0xff;
		r2 = r2 + 7;
		r7 = 8;
		r6 = 0;
x17dc4:
		r8 = r6 << 3;
		r10 = 0xff;
		r1 = r5 - r8;
		r4 = r10 << r1;
		r3 = r13 + r6;
		r6++;
		r1 = (r6 > 4);
		if (r5 >= r7)
			goto x17e08;
		write8(r3, r4);
		write8(r3+5, r4);
		r5 = r8 + 8;
		if (r11 >= r7)
			goto x17e08;
		r1 = r10 >> r2;
		r1 = r4 & r1;
		write8(r3+5, r1);
		write8(r3, r1);
		goto x17e14;

x17e08:
		r7 = r7 + 8;
		r2 = r2 + 8;
		if (r1 == 0)
			goto x17dc4;
x17e14:
		r7 = r9 >> 1;
		r6 = 0;
x17e1c:
		r3 = r13 + r6;
		r1 = r9 & 1;
		r5 = read8(r3);
		r4 = (r1 == 0);
		if (r5 == 0)
			goto x17e74;
		r2 = r12 + r6;
		if (r4 != 0)
			goto x17e48;
		r1 = read8(r2);
		r1 |= r5;
		write8(r2, r1);
		goto x17e4c;
x17e48:
		write8(r3, r1);
x17e4c:
		r2 = r7 & 1;
		r1 = (r2 == 0);
		r4 = r12 + r6;
		if (r1 != 0)
			goto x17e70;
		r2 = read8(r3+5);
		r1 = read8(r4+8);
		r1 |= r2;
		write8(r4+8, r1);
		goto x17e74;
x17e70:
		write8(r3+5, r2);
x17e74:
		r6++;
		r1 = (r6 > 4);
		if (r1 == 0)
			goto x17e1c;

		r11 = r11a;
		r12 = r12a;
		r13 = r13a;

		r2 = read32(r13);
		r1 = r12;
		x18d04(r1, r2, r3);

		r2 = read32(r13);
		r1 = r12;
		x180f0(r1, r2);

		r2 = read32(r13);
		r1 = r12;
		x18490(r1, r2);

		r1 = r12;
		x17e94(r1);

		r1 = 0x01318014;
		r2 = r11;
		r3 = 0x80080000;
		write32(r3+160, r1);
		write32(r3+164, r2);

x1a168:
		r1 = read32(r13);
		r1 &= 0x10;
		if (r1 != 0)
			goto end;
		r13 = 0x01318010;
		r12 = 0x1f688;
		if (r16 != 0)
			goto end;
		r15 = 0x1f6c4;
		r1 = read32(r15);
		r1 = r1 & r14;
		r1 >>= 16;
		r1 = (r1 != 1);
		if (r1 != 0)
			goto end;
		r11 = r16;
x1a1a8:
		r2 = read32(r12);
		r1 = r13 + r11;
		r11++;
		r3 = 0x80080000;
		write32(r3+160, r1);
		write32(r3+164, r2);

		r1 = (r11 > 7);
		r12 += 4;
		if (r1 == 0)
			goto x1a1a8;
		r1 = 0x1f6a8;
		r2 = read32(r1);
		r1 = 0x02010011;
		r3 = 0x80080000;
		write32(r3+160, r1);
		write32(r3+164, r2);
		break;
	}
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


static void set_x16off(void)
{
	if ((read32(0x1f39c) & 0x10) != 0)
		goto end;
	x1a200();
	x18b20();
end:
	return;
}

static u32 x11cb0(u32 rr1, u32 rr2)
{
	u32 r1, r2, r3, r4, r5;
	u32 r11, r12, r13, r14, r15;
	r15 = rr1;
	r1 = read32(rr1);
	r11 = 0x1d8ac;
	r3 = read32(r11+56);
	r1 <<= 5;
	r14 = 0x1d989;
	r1 = r1 + r3;
	r1 = read8(r1+3);
	r13 = rr2 & 0xff;
	r12 = 0;
	r2 = 0xff;
	if (r1 == r12)
		goto x11d74;
	write32(r11+24, r12);
	write32(r11+28, r12);
	write32(r11+32, r12);
	write8(r11+5, r12);
	write8(r11+3, r13);
	write8(r11+12, r12);
	return r1;

	r3 = 0xe0000124;
	r1 = (r13 != 1);
	if (r1 != r12)
		goto x11d34;
	write32(r3, r12);
x11d34:
	r12 = read32(r15);
	r2 = read32(r11+56);
	r3 = read8(r14+8);
	r1 = r12 << 5;
	r1 = r1 + r2;
	r1 = read8(r1+1);
	r1 &= 0xff;
	write8(r14+1, r1);
	if (r1 >= r3)
		goto x11d68;
	r3 = read8(r14+5);
	r2 = 1;
	if (r3 == 0)
		goto x11d68;
	//x1b5c4();
	r12 = 0x1d989;
	r3 = read8(r12+11);
	r11 = r1 & 0xff;
	r13 = r2 & 0xff;
	if (r1 >= r3)
		goto x1b5f4;
	r11 = r3;
x1b5f4:
	r2 = 0xe00021b4;
x1b5fc:
	r1 = read32(r2);
	r1 = r1 & 1;
	if (r1 == 0)
		goto x1b5fc;
	write8(r12+9, r11);
	adjust_loadline();
	r1 = read8(r12+10);
	r2 = 0xe00021b0;
	r1 = r11 + r1;
	r1 <<= 1;
	r3 = 0xe00021b4;
	r1 |= r13;
	write32(r2, r1);
x1b634:
	r1 = read32(r3);
	r1 &= 1;
	if (r1 == 0)
		goto x1b634;
	write8(r12+8, r11);

x11d68:
	r1 = r12;
	
	r11 = 0x1d8ac;
	r2 = read32(r11+56);
	r3 = r1 << 5;
	r12 = 0x1f304;
	r2 = r2 & r3;
	write32(r11+52, r2);
	write32(r11+20, r1);
	write8(r12+2, r1);
	r1 = read32(r11+52);
	r1 = read8(r1+2);
	r1 &= 0xff;
	
	r12 = r1 & 0xff;
	r1 = r12;
	r11 = 0x10000;
	
	r4 = r1 & 0xff;
	r1 = 0xff;
	if (r4 == 0)
		goto x1b2cc;
	r2 = 0xe000205c;
x1b294:
	r1 = read32(r2);
	r1 = r1 & 1;
	if (r1 == 0)
		goto x1b294;
	r1 = 0xe0002058;
	r3 = 0xe000205c;
	write32(r1, r4);
x1b2b4:
	r1 = read32(r3);
	r1 ^= 1;
	r2 = r1 & 1;
	r1 = (r2 == 0);
	if (r1 == 0)
		goto x1b2b4;
	r1 = r2;
x1b2cc:

	r11 |= 0xd8ac;
	r1 = 1;
	write8(r11+4, r12);
	
	r1 = read32(r11+20);
	write8(r12+3, r1);
	r1 = read32(r11+20);
	r2 = read32(r11+56);
	r3 = r5 << 5;
	write32(r11+16, r1);
	r2 = r2 & r3;
	write32(r11+48, r2);
	r1 <<= 2;
	r2 = 0x1f900;
	r1 = r1 + r2;
	r1 = read32(r1+64);
	write32(r2+12, r1);

	r3 = read32(r11+48);
	r2 = 0;
	r1 = r2;
	write16(r3+8, r2);

	r2 = 0;
x11d74:
	r1 = r2;
	return r1;
}

static void config_lclkdpm(void)
{
	u32 r1, r2, r3, r4, r5, r6, r7;
	u32 r11, r12, r13, r14;

	r1 = 0x1d8f0;
	r1 = read32(r1);
	r14 = r1;
	r1 = 0x1dcf4;
	r5 = 0x1f300;
	r3 = read8(r5+3);
	r13 = r1;
	r7 = 0xff000000;
	r6 = 0xe0000124;
	r12 = 0x1f460;
	r4 = 0x1d989;
	r11 = 0x1d8ac;
	r2 = 0;

	if (r3 != r2)
		goto x11e1c;
	write8(r4+5, r3);
	write8(r11, r3);
	write8(r13+3, r3);
	write8(r14+3, r3);
	write32(r6, r3);
	write8(r11+5, r3);
	goto x11e64;
x11e1c:
	r3 = read8(r5+1);
	//write32(sp+24, r3);
	r3 = read32(r5);
	r3 = r3 & r7;
	r3 >>= 24;
	write8(r4+5, r3);
	r1 = x11cb0(r1, r2);
	
	r3 = 0xe0000124;
	r2 = (r1 != 0xff);
	r4 = 1;
	if (r2 == 0)
		goto end;
	write8(r11, r4);
	r1 = read8(r12+3);
	r1 &= 0xff;
	write8(r13+3, r1);
	write8(r14+3, r1);
	write32(r3, r4);
x11e64:
	r1 = 0;
end:
	return;
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
	u32 r1, r2, r3, r11, r12;

	r1 = 0x1d8f0;
	r12 = r1;
	r1 = 0x1dcf4;
	r11 = 0x1f460;
	r2 = read8(r11+2);
	r3 = 0x1d998;
	r2 &= 0xff;
	write8(r1+5, r2);
	write8(r12+5, r2);
	r2 = 0;
	r1 = 0x1f308;
	write8(r3+8, r2);
	write8(r3+9, r2);
	write8(r1+1, r2);
	r2 = read8(r3+8);
	r1 = 0x1f108;
	write8(r1+1, r2);
	return;
}

static void config_voltage(void)
{
	u32 r1, r2, r3, r4;
	u32 r11, r12, r13;

	r1 = 0x1d8f0;
	r1 = read32(r1);
	r12 = r1;
	r11 = 0x1f460;
	r1 = 0x1dcf4;
	r3 = read8(r11+1);
	r2 = 1;
	r4 = 0x1f384;
	r3 &= 0xff;
	write8(r1+4, r3);
	write8(r12+4, r3);
	r3 = read8(r1+4);
	if (r3 == 0)
		goto x1b90c;
	r1 = read32(r4);
	goto x1b918;
x1b90c:
	r1 = read32(r4);
	r2 = r3;
x1b918:
	r1 &= 0xff;
	
	r12 = 0x1d989;
	r3 = read8(r12+11);
	r11 = r1 & 0xff;
	r13 = r2 & 0xff;
	if (r1 >= r3)
		goto x1b5f4;
	r11 = r3;
x1b5f4:
	r2 = 0xe00021b4;
x1b5fc:
	r1 = read32(r2);
	r1 = r1 & 1;
	if (r1 == 0)
		goto x1b5fc;
	write8(r12+9, r11);
	adjust_loadline();
	r1 = read8(r12+10);
	r2 = 0xe00021b0;
	r1 = r11 + r1;
	r1 <<= 1;
	r3 = 0xe00021b4;
	r1 |= r13;
	write32(r2, r1);
x1b634:
	r1 = read32(r3);
	r1 &= 1;
	if (r1 == 0)
		goto x1b634;

	write8(r12+8, r11);
	return;
}

static void config_tdp(void)
{
	u32 r1, r2, r3, r4, r5, r6;
	u32 r11, r12, r13, r14, r15, r16;

	//x1c5f4();
	r3 = 0x1dff4;
	r1 = read32(r3+28);
	r2 = 0x1f850;
	if (r1 >= 0)
		goto x1c610;
	r2 = r3;
x1c610:
	r1 = r2;

	r15 = r1;
	r1 = 0x1f428;
	r1 = read8(r1);
	r11 = 0x1f464;
	r1 >>= 5;
	r14 = 0x1f900;
	r1 &= 1;
	r1 ^= 1;
	r1 = -r1;
	r13 = r1 & 0x271;
	r1 = 0x1d8f0;
	r1 = read32(r1);
	r12 = r1;
	r1 = 0x1dcf4;
	r2 = read8(r11);
	r16 = 0x1f160;
	r2 &= 0xff;
	write8(r1+14, r2);
	write8(r12+14, r2);
	r1 = read8(r14+26);
	r13 = r13 + 0x271;
	if (r1 == 0)
		goto x12dac;
	r1 = read32(r15+76);
	r2 = 0x000fffff;
	r1 &= 0x3fff;
	write32(r14, r1);
	r1 = read32(r15);
	r5 = 0x1f850;
	r1 >>= 10;
	r1 &= r2;
	write32(r14+16, r1);
	r1 = read32(r15+12);
	r1 &= r2;
	write32(r14+20, r1);
	r2 = read32(r5+144);
	r1 = read32(r5+152);
	r2 >>= 16;
	r1 >>= 16;
	r2 &= 0xff;
	r1 &= 0xff;
	if (r2 >= r1)
		goto x12d30;
	r3 = read8(r5+153);
	goto x12d34;
x12d30:
	r3 = read8(r5+145);
x12d34:
	write8(r14+42, r3);
	r4 = read8(r5+150);
	r1 = read8(r5+148);
	if (r1 >= r4)
		goto x12d48;
	r4 = r1;
x12d48:
	r2 = r4 & 0xff;
	r3 &= 0xff;
	r2 = r2 * r13;
	r3 = r3 * r13;
	r1 = 100;
	r2 = r2 / r1;
	write8(r14+43, r4);
	r6 = r15 + 96;
	r4 = 0;
	r5 = r14 + 96;
	r3 = r3 / r1;
	r1 = 1550;
	r1 = r1 - r2;
	write16(r14+36, r1);
	r1 = 1520;
	r1 = r1 - r3;
	write16(r14+38, r1);
x12d8c:
	r1 = r6 + r4;
	r1 = read8(r1);
	r4++;
	r2 = (r4 > 0xf);
	r1 <<= 6;
	write32(r5, r1);
	if (r2 == 0)
		goto x12d8c;
x12dac:
	r1 = 0xe0002294;
	r3 = read32(r1);
	r2 = 0x1d938;
	r1 = 0xe0002298;
	r1 = read32(r1);
	r3 = r3 & 0xfff;
	r11 = 0x1dd18;
	r1 = r1 & 0x1ff;
	r1++;
	r3 = r3 * r1;
	write32(r2, r3);
	r1 = 0x1dd28;

	write32(r11, r1);
	r2 = 0;
	r1 = 0x1dd10;
	r6 = 0xe0000000;
	write8(r16+2, r2);
	r3 = r6;
	write32(r1+4, r2);
	r3 |= 0x228c;
	r4 = r2;
	r2 = read32(r3);
	r1 = 0xbfffffff;
	r2 &= r1;
	write32(r3, r2);
	r2 = read32(r3);
	r1 = 0x7fffffff;
	r2 &= r1;
	
	r5 = 0xe0500400;
	write32(r3, r2);
x12e44:
	r1 = r4 << 2;
	r2 = r1 + r14;
	r2 = read32(r2+160);
	r1 += r5;
	r4++;
	write32(r1, r2);
	r1 = (r4 > 0x60);
	if (r1 == 0)
		goto x12e44;
	r3 = r6;
	r3 = 0xe000228c;
	r2 = read32(r3);
	r1 = 0xffff7fff;
	r2 &= r1;

	//x128f4();
	r4 = 0xe000228c;
	r2 = read32(r4);
	r3 = 0xfffeffff;
	r1 = 0x10000;
	r2 &= r3;
	r2 |= r1;
	write32(r4, r2);
	r1 = read32(r4);
	r1 &= r3;
	write32(r4, r1);
	return;
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
	u32 r1, r2, r3;

	r1 = 0x1f428;
	r1 = read32(r1);
	r2 = 0x1d989;
	r3 = 1;
	r1 &= 0x40;
	if (r1 == 0)
		goto x12564;
	write8(r2+7, r3);
	goto end;
x12564:
	write8(r2+7, r1);
end:
	adjust_loadline();
	return;
}

static void reconfigure()
{
	u32 r1, r2, r3, r4, r11, r12, r13;

	r1 = 0x1f630;
	r1 = read32(r1);
	r1 = r1 & 0xff00;
	r11 = r1 >> 8;
	r1 = 3;
	if (r1 >= r11)
		goto x1aa10;
	goto end;
x1aa10:
	r1 = 0xe0002028;
	r2 = read32(r1);
	r1 = 0x64;
	r13 = r2 & 0x7f;
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

	//x1b280();
	r4 = r1 & 0xff;
	r1 = 0xff;
	if (r4 == 0)
		goto x1b2cc;
	r2 = 0xe000205c;
x1b294:
	r1 = read32(r2);
	r1 &= 1;
	if (r1 == 0)
		goto x1b294;
	r1 = 0xe0002058;
	r3 = 0xe000205c;
	write32(r1, r4);
x1b2b4:
	r1 = read32(r3);
	r1 ^= 1;
	r2 = r1 & 1;
	r1 = (r2 == 0);
	if (r1 == 0)
		goto x1b2b4;
	r1 = r2;
x1b2cc:

	if (r11 != 0)
		goto x1aa3c;
	r12 = 0x01308060;
	goto x1aa74;
x1aa3c:
	r1 = (r11 != 1);
	if (r1 != 0)
		goto x1aa50;
	r12 = 0x01318060;
	goto x1aa74;
x1aa50:
	r1 = (r11 != 2);
	if (r1 != 0)
		goto x1aa64;
	r12 = 0x01328060;
	goto x1aa74;
x1aa64:
	r1 = (r11 != 3);
	if (r1 != 0)
		goto x1aa74;
	r12 = 0x01338060;
x1aa74:
	r2 = 1;
	r1 = r12;
	r3 = 0x80080000;
	write32(r3+160, r1);
	r1 = read32(r3+164);
	r1 |= r2;
	write32(r3+164, r1);

	r1 = 1;
	r1 = r12;
	r3 = 0x80080000;
	write32(r3+160, r1);
x1705c:
	r1 = read32(r3+164);
	r1 = r2 & r1;
	if (r1 == r2)
		goto x1705c;

	r1 = r12;
	r2 = 4;
	r3 = 0x80080000;
	write32(r3+160, r1);
x17040:
	r1 = read32(r3+164);
	r1 = r2 & r1;
	if (r1 != r2)
		goto x17040;

	r1 = r13;
	//x1b280();
	r4 = r1 & 0xff;
	r1 = 0xff;
	if (r4 == 0)
		goto end;
	r2 = 0xe000205c;
x1b294_1:
	r1 = read32(r2);
	r1 &= 1;
	if (r1 == 0)
		goto x1b294_1;
	r1 = 0xe0002058;
	r3 = 0xe000205c;
	write32(r1, r4);
x1b2b4_1:
	r1 = read32(r3);
	r1 ^= 1;
	r2 = r1 & 1;
	r1 = (r2 == 0);
	if (r1 == 0)
		goto x1b2b4_1;
	r1 = r2;
end:
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

static void set_bapm(int onoff, u32 *bapmoff, u32 *bapmon)
{
	u32 r1, r2, r3, r4, r5, r6, r11, r12, r13;
	switch (onoff) {
	case ON:
		// disable interrupts (nah)
		r1 = 0x1d9a4;
		r11 = r1;
		r1 = 0x1dd8b;
		r1 = read8(r1);
		r12 = 0x1f160;
		r1 = (r1 != 1);
		if (r1 == 0)
			goto end;
		r1 = read32(r11+128);
		r13 = 0xfffe;
		r1 <<= 2;
		r2 = 0xe0400000;
		r1 += r2;
		r1 = read32(r1);
		
		r3 = r1;
		r1 = 0x1dd8a;
		write32(r11+132, r3);
		r2 = 0xfffc;
		r3 = r3 & r2;
		r1 &= 3;
		r3 |= r1;
		r1 = 0x1dd89;
		write32(r11+132, r3);
		r2 = read8(r1);
		r1 = 0xff7f;
		r2 &= 1;
		r3 &= r1;
		r2 <<= 7;
		r1 = read32(r1+128);
		r3 |= r2;
		r2 = r3;
		write32(r11+132, r3);
		r1 <<= 2;
		r3 = 0xe0400000;
		r1 += r3;
		write32(r1, r2);

		r1 = read32(r11+104);
		r1 <<= 2;
		r2 = 0xe0400000;
		r1 += r2;
		r1 = read32(r1);

		r2 = r1;
		r1 = 0x1dd88;
		write32(r11+108, r2);
		r3 = read8(r1);
		r1 = 0xf1ff;
		r3 &= 7;
		r3 <<= 9;
		r2 &= r1;
		r1 = read32(r11+104);
		r2 |= r3;
		write32(r11+108, r2);
		r1 <<= 2;
		r3 = 0xe0400000;
		r1 += r3;
		write32(r1, r2);

		r6 = 0x1f428;
		r1 = read32(r6);
		r5 = 0x1ddec;
		*bapmon = r1; // arg? sp
		r3 = read8(r5+3);
		r2 = 0xfffd;
		r4 = 0x1dd8c;
		r1 = ((*bapmon) >> 24) & 0xff;  // sp+23
		r3 &= 2;
		r1 &= r2;
		r1 |= r3;
		*bapmon = (*bapmon & ~0xff000000) | ((r1 & 0xff) << 24);
		r2 = read8(r5+3);
		r4 = read8(r4);
		r1 = ((*bapmon) >> 24) & 0xff;
		r2 &= 1;
		r1 &= r13;
		r1 |= r2;
		*bapmon = (*bapmon & ~0xff000000) | ((r1 & 0xff) << 24);
		r3 = read8(r5+3);
		r2 = 0xfff7;
		r1 = ((*bapmon) >> 24) & 0xff;
		r3 &= 8;
		r1 &= r2;
		r1 |= r3;
		*bapmon = (*bapmon & ~0xff000000) | ((r1 & 0xff) << 24);
		r3 = read8(r5+3);
		r2 = 0xfffb;
		r1 = ((*bapmon) >> 24) & 0xff;
		r3 &= 4;
		r1 &= r2;
		r1 |= r3;
		*bapmon = (*bapmon & ~0xff000000) | ((r1 & 0xff) << 24);
		if (r4 != 0)
			goto x14e24;
		r1 = ((*bapmon) >> 24) & 0xff;
		r2 = 0xffef;
		r1 &= r2;
		*bapmon = (*bapmon & ~0xff000000) | ((r1 & 0xff) << 24);
x14e24:
		r1 = *bapmon;
		r11 = 1;
		write32(r6, r1);

		config_htc();
		config_vpc();
		config_lpmx();
		config_tdc();
		config_tdp();
		config_bapm();

		r2 = 0x80010800;
		write8(r12+3, r11);
		r1 = read32(r2);
		r3 = 0x80010810;
		r1 &= r13;
		write32(r2, r1);
		r1 = read32(r2);
		r4 = 0x1d940;
		r1 |= 0x100;
		write32(r2, r1);
		r1 = read32(r3);
		r1 = read32(r4);
		write32(r3, r1);
		r1 = read32(r2);
		r1 &= r13;
		r1 |= r11;
		write32(r2, r1);
		r1 = 0x1d95c;

		write8(r1+8, r11);
		// enable interrupts (nah)
		break;
	case OFF:
		// disable interrupts (nah)
		r1 = 0x1d9a4;
		r12 = r1;
		r1 = 0x1dd8b;
		r1 = read8(r1);
		if (r1 == 0)
			goto end;
		r1 = read32(r12+128);
		r11 = 0xfffe;
		r1 <<= 2;
		r2 = 0xe0400000;
		r1 += r2;
		r1 = read32(r1);

		write32(r12+132, r1);
		r2 = 0x1dd8a;
		r1 &= 3;
		write8(r2, r1);
		r1 = read32(r12+132);
		r2 = 0x1dd89;
		r1 >>= 7;
		r1 &= 1;
		write8(r2, r1);
		r3 = read32(r12+132);
		r2 = 0xfffc;
		r1 = read32(r12+128);
		r3 &= r2;
		r2 = 0xff7f;
		r3 &= r2;
		r2 = r3;
		write32(r12+132, r3);
		r1 <<= 2;
		r3 = 0xe0400000;
		r1 += r3;
		write32(r1, r2);
		
		r1 = read32(r12+104);
		r1 <<= 2;
		r2 = 0xe0400000;
		r1 += r2;
		r1 = read32(r1);
		
		r3 = r1 >> 9;
		r2 = 0x1dd88;
		write32(r12+108, r1);
		r3 &= 7;
		write8(r2, r3);
		r3 = read32(r12+108);
		r1 = read32(r12+104);
		r2 = 0xfff1;
		r3 &= r2;
		r2 = r3;
		write32(r12+108, r3);
		r1 <<= 2;
		r3 = 0xe0400000;
		r1 += r3;
		write32(r1, r2);
		
		r3 = 0x1f428;
		r2 = read32(r3);
		r1 = 0x1ddec;
		*bapmoff = r2;
		r2 = *bapmoff;
		write32(r1, r2);
		r1 = ((*bapmoff) >> 24) & 0xff;
		r2 = 0xfffd;
		r1 &= r2;
		*bapmoff = (*bapmoff & ~0xff000000) | ((r1 & 0xff) << 24);
		
		r1 = ((*bapmoff) >> 24) & 0xff;
		r2 = 0xfff7;
		r1 &= r11;
		*bapmoff = (*bapmoff & ~0xff000000) | ((r1 & 0xff) << 24);
		r1 = ((*bapmoff) >> 24) & 0xff;
		r1 &= r2;
		*bapmoff = (*bapmoff & ~0xff000000) | ((r1 & 0xff) << 24);
		r1 = ((*bapmoff) >> 24) & 0xff;
		r2 = 0xfffb;
		r1 &= r2;
		*bapmoff = (*bapmoff & ~0xff000000) | ((r1 & 0xff) << 24);
		r1 = ((*bapmoff) >> 24) & 0xff;
		r1 |= 0x10;
		*bapmoff = (*bapmoff & ~0xff000000) | ((r1 & 0xff) << 24);
		r1 = *bapmoff;
		write32(r3, r1);

		config_htc();
		config_bapm();
		config_tdc();
		config_vpc();
		config_lpmx();
		
		//x12ea8
		r1 = 0x1dcf4;
		r5 = 0;
		r4 = 0xe000228c;
		write8(r1+14, r5);
		r3 = read32(r4);
		r1 = 0xbfffffff;
		r2 = 0x40000000;
		r3 &= r1;
		r3 |= r2;
		write32(r4, r3);
		r3 = read32(r4);
		r1 = 0x7fffffff;
		r2 = 0x80000000;
		r3 &= r1;
		r3 |= r2;
		write32(r4, r3);
		r2 = read32(r4);
		r1 = 0xffff7fff;
		r2 &= r1;
		write32(r4, r2);
		r1 = 0x1f160;
		write8(r1+2, r5);
		write8(r1+3, r5);

		r1 = 0x1f468;
		r2 = read32(r1);
		r3 = 0x80010800;
		r1 = 0x1d940;
		write32(r1, r2);
		r1 = read32(r3);
		r4 = 0x80010810;
		r1 &= r11;
		write32(r3, r1);
		r1 = read32(r3);
		r2 = 0x0007a120;
		r1 |= 0x100;
		write32(r3, r1);
		r1 = read32(r4);
		write32(r4, r2);
		r1 = read32(r3);
		r1 &= r11;
		r1 |= 1;
		write32(r3, r1);
		r1 = 0x1d95c;
		r2 = 0;
		write8(r1+8, r2);

		// enable interrupts (nah)
		break;
	}
end:
	return;
}

void smu_service_request(void)
{
	static u32 bapmoff = 0;
	static u32 bapmon = 0;
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
		set_bapm(ON, &bapmoff, &bapmon);
		break;
	case SMC_MSG_DISABLE_BAPM:
		set_bapm(OFF, &bapmoff, &bapmon);
		break;
	default:
		break;
	}

	write32(0xe0003004, 3);
}

void MicoISRHandler(void)
{
/*
	unsigned int ip, im, Mask, IntLevel;
	asm volatile ("rcsr %0,im":"=r"(im));

	//OSIntEnter();

	do {
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

	//OSIntExit();
*/	
	return;
}
