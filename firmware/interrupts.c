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
#include "interrupts.h"

#define OFF 0
#define ON 1

static void halt(void)
{
	return;
}

static void set_phyln(int onoff)
{
/*
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

static void set_cascadepll(int onoff)
{
}

static void set_x16off(void)
{
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
}

static void config_lpmx(void)
{
}

static void config_htc(void)
{
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
	u32 pm1 = 0x80010000;
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

static void adjust_loadline()
{
}

static void reconfigure()
{
}

static void pciepllswitch()
{
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

