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

/* Not used */
//#define SMC_MSG_FIRMWARE_AUTH              0

#define SMC_MSG_HALT                       1
#define SMC_MSG_PHY_LN_OFF                 2
#define SMC_MSG_PHY_LN_ON                  3
#define SMC_MSG_DDI_PHY_OFF                4
#define SMC_MSG_DDI_PHY_ON                 5
#define SMC_MSG_CASCADE_PLL_OFF            6
#define SMC_MSG_CASCADE_PLL_ON             7
#define SMC_MSG_PWR_OFF_x16                8
#define SMC_MSG_CONFIG_LCLK_DPM            9
#define SMC_MSG_FLUSH_DATA_CACHE           10
#define SMC_MSG_FLUSH_INSTRUCTION_CACHE    11
#define SMC_MSG_CONFIG_VPC_ACCUMULATOR     12
#define SMC_MSG_CONFIG_BAPM                13
#define SMC_MSG_CONFIG_TDC_LIMIT           14
#define SMC_MSG_CONFIG_LPMx                15
#define SMC_MSG_CONFIG_HTC_LIMIT           16
#define SMC_MSG_CONFIG_THERMAL_CNTL        17
#define SMC_MSG_CONFIG_VOLTAGE_CNTL        18
#define SMC_MSG_CONFIG_TDP_CNTL            19
#define SMC_MSG_EN_PM_CNTL                 20
#define SMC_MSG_DIS_PM_CNTL                21
#define SMC_MSG_CONFIG_NBDPM               22
#define SMC_MSG_CONFIG_LOADLINE            23
#define SMC_MSG_ADJUST_LOADLINE            24
#define SMC_MSG_RECONFIGURE                25
#define SMC_MSG_PCIE_PLLSWITCH             27
#define SMC_MSG_ENABLE_BAPM                32
#define SMC_MSG_DISABLE_BAPM               33

#define MICO32_CPU_CLOCK_MHZ (25000000)
#define MICO_SLEEP_MICROSEC  (MICO32_CPU_CLOCK_MHZ/11000000)
#define MICO_SLEEP_MILLISEC  (MICO32_CPU_CLOCK_MHZ/11000)

#define REG_WRITE(addr, val) (*((volatile unsigned int *)(addr)) = val)

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
