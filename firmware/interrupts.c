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

void SMUServiceRequest(unsigned int level, void *ctx)
{
	int requestid;
	REG_WRITE(0xe0003004, 1);
	requestid = REG_READ(0xe0003000);
	requestid &= 0x1fffe;
	
	switch(requestid) {
	case SMC_MSG_HALT:
		break;
	case SMC_MSG_PHY_LN_OFF:
		break;
	case SMC_MSG_PHY_LN_ON:
		break;
	case SMC_MSG_DDI_PHY_OFF:
		break;
	case SMC_MSG_DDI_PHY_ON:
		break;
	case SMC_MSG_CASCADE_PLL_OFF:
		break;
	case SMC_MSG_CASCADE_PLL_ON:
		break;
	case SMC_MSG_PWR_OFF_x16:
		break;
	case SMC_MSG_CONFIG_LCLK_DPM:
		break;
	case SMC_MSG_FLUSH_DATA_CACHE:
		break;
	case SMC_MSG_FLUSH_INSTRUCTION_CACHE:
		break;
	case SMC_MSG_CONFIG_VPC_ACCUMULATOR:
		break;
	case SMC_MSG_CONFIG_BAPM:
		break;
	case SMC_MSG_CONFIG_TDC_LIMIT:
		break;
	case SMC_MSG_CONFIG_LPMx:
		break;
	case SMC_MSG_CONFIG_HTC_LIMIT:
		break;
	case SMC_MSG_CONFIG_THERMAL_CNTL:
		break;
	case SMC_MSG_CONFIG_VOLTAGE_CNTL:
		break;
	case SMC_MSG_CONFIG_TDP_CNTL:
		break;
	case SMC_MSG_EN_PM_CNTL:
		break;
	case SMC_MSG_DIS_PM_CNTL:
		break;
	case SMC_MSG_CONFIG_NBDPM:
		break;
	case SMC_MSG_CONFIG_LOADLINE:
		break;
	case SMC_MSG_ADJUST_LOADLINE:
		break;
	case SMC_MSG_RECONFIGURE:
		break;
	case SMC_MSG_PCIE_PLLSWITCH:
		break;
	case SMC_MSG_ENABLE_BAPM:
		break;
	case SMC_MSG_DISABLE_BAPM:
		break;
	default:
		break;
	}
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

