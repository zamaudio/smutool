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

#ifndef _SMU_H
#define _SMU_H

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

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

#define write8(addr, val) (*((volatile u8 *)(addr))) = (val)
#define read8(addr) (*((volatile u8 *)(addr)))
#define write16(addr, val) (*((volatile u16 *)(addr))) = (val)
#define read16(addr) (*((volatile u16 *)(addr)))
#define write32(addr, val) (*((volatile u32 *)(addr))) = (val)
#define read32(addr) (*((volatile u32 *)(addr)))

#define INTACK 1
#define INTDONE 2

/// x1F200
typedef union {
  struct {
    u32                                               StateValid:1 ;
    u32                                             Reserved_7_1:7 ;
    u32                                              LclkDivider:8 ;
    u32                                                      VID:8 ;
    u32                                   LowVoltageReqThreshold:8 ;
  } Field;
  u32 Value;
} x1F200_t;

/// x1F208
typedef union {
  struct {
    u32                                             HysteresisUp:8 ;
    u32                                           HysteresisDown:8 ;
    u32                                         ResidencyCounter:16;
  } Field;
  u32 Value;
} x1F208_t;

/// x1F210
typedef union {
  struct {
    u32                                        ActivityThreshold:8 ;
    u32                                            Reserved_31_8:24;
  } Field;
  u32 Value;
} x1F210_t;

/// x1F220
typedef union {
  struct {
    u32                                               StateValid:1 ;
    u32                                             Reserved_7_1:7 ;
    u32                                              LclkDivider:8 ;
    u32                                                      VID:8 ;
    u32                                   LowVoltageReqThreshold:8 ;
  } Field;
  u32 Value;
} x1F220_t;

/// x1F228
typedef union {
  struct {
    u32                                             HysteresisUp:8 ;
    u32                                           HysteresisDown:8 ;
    u32                                         ResidencyCounter:16;
  } Field;
  u32 Value;
} x1F228_t;

/// x1F230
typedef union {
  struct {
    u32                                        ActivityThreshold:8 ;
    u32                                            Reserved_31_8:24;
  } Field;
  u32 Value;
} x1F230_t;

/// x1F240
typedef union {
  struct {
    u32                                               StateValid:1 ;
    u32                                             Reserved_7_1:7 ;
    u32                                              LclkDivider:8 ;
    u32                                                      VID:8 ;
    u32                                   LowVoltageReqThreshold:8 ;
  } Field;
  u32 Value;
} x1F240_t;

/// x1F248
typedef union {
  struct {
    u32                                             HysteresisUp:8 ;
    u32                                           HysteresisDown:8 ;
    u32                                         ResidencyCounter:16;
  } Field;
  u32 Value;
} x1F248_t;

/// x1F250
typedef union {
  struct {
    u32                                        ActivityThreshold:8 ;
    u32                                            Reserved_31_8:24;
  } Field;
  u32 Value;
} x1F250_t;

/// x1F260
typedef union {
  struct {
    u32                                               StateValid:1 ;
    u32                                             Reserved_7_1:7 ;
    u32                                              LclkDivider:8 ;
    u32                                                      VID:8 ;
    u32                                   LowVoltageReqThreshold:8 ;
  } Field;
  u32 Value;
} x1F260_t;

/// x1F268
typedef union {
  struct {
    u32                                             HysteresisUp:8 ;
    u32                                           HysteresisDown:8 ;
    u32                                         ResidencyCounter:16;
  } Field;
  u32 Value;
} x1F268_t;

/// x1F270
typedef union {
  struct {
    u32                                        ActivityThreshold:8 ;
    u32                                            Reserved_31_8:24;
  } Field;
  u32 Value;
} x1F270_t;

/// x1F280
typedef union {
  struct {
    u32                                               StateValid:1 ;
    u32                                             Reserved_7_1:7 ;
    u32                                              LclkDivider:8 ;
    u32                                                      VID:8 ;
    u32                                   LowVoltageReqThreshold:8 ;
  } Field;
  u32 Value;
} x1F280_t;

/// x1F288
typedef union {
  struct {
    u32                                             HysteresisUp:8 ;
    u32                                           HysteresisDown:8 ;
    u32                                         ResidencyCounter:16;
  } Field;
  u32 Value;
} x1F288_t;

/// x1F290
typedef union {
  struct {
    u32                                        ActivityThreshold:8 ;
    u32                                            Reserved_31_8:24;
  } Field;
  u32 Value;
} x1F290_t;

/// x1F2A0
typedef union {
  struct {
    u32                                               StateValid:1 ;
    u32                                             Reserved_7_1:7 ;
    u32                                              LclkDivider:8 ;
    u32                                                      VID:8 ;
    u32                                   LowVoltageReqThreshold:8 ;
  } Field;
  u32 Value;
} x1F2A0_t;

/// x1F2A8
typedef union {
  struct {
    u32                                             HysteresisUp:8 ;
    u32                                           HysteresisDown:8 ;
    u32                                         ResidencyCounter:16;
  } Field;
  u32 Value;
} x1F2A8_t;

/// x1F2B0
typedef union {
  struct {
    u32                                        ActivityThreshold:8 ;
    u32                                            Reserved_31_8:24;
  } Field;
  u32 Value;
} x1F2B0_t;

/// x1F2C0
typedef union {
  struct {
    u32                                               StateValid:1 ;
    u32                                             Reserved_7_1:7 ;
    u32                                              LclkDivider:8 ;
    u32                                                      VID:8 ;
    u32                                   LowVoltageReqThreshold:8 ;
  } Field;
  u32 Value;
} x1F2C0_t;

/// x1F2C8
typedef union {
  struct {
    u32                                             HysteresisUp:8 ;
    u32                                           HysteresisDown:8 ;
    u32                                         ResidencyCounter:16;
  } Field;
  u32 Value;
} x1F2C8_t;

/// x1F2D0
typedef union {
  struct {
    u32                                        ActivityThreshold:8 ;
    u32                                            Reserved_31_8:24;
  } Field;
  u32 Value;
} x1F2D0_t;

/// x1F2E0
typedef union {
  struct {
    u32                                               StateValid:1 ;
    u32                                             Reserved_7_1:7 ;
    u32                                              LclkDivider:8 ;
    u32                                                      VID:8 ;
    u32                                   LowVoltageReqThreshold:8 ;
  } Field;
  u32 Value;
} x1F2E0_t;

/// x1F2E8
typedef union {
  struct {
    u32                                             HysteresisUp:8 ;
    u32                                           HysteresisDown:8 ;
    u32                                         ResidencyCounter:16;
  } Field;
  u32 Value;
} x1F2E8_t;

/// x1F2F0
typedef union {
  struct {
    u32                                        ActivityThreshold:8 ;
    u32                                            Reserved_31_8:24;
  } Field;
  u32 Value;
} x1F2F0_t;

/// x1F300
typedef union {
  struct {
    u32                                                LclkDpmEn:1 ;
    u32                                             Reserved_7_1:7 ;
    u32                                              LclkDpmType:1 ;
    u32                                            Reserved_15_9:7 ;
    u32                                         LclkDpmBootState:8 ;
    u32                                             VoltageChgEn:1 ;
    u32                                           Reserved_31_25:7 ;
  } Field;
  u32 Value;
} x1F300_t;

/// x1F308
typedef union {
  struct {
    u32                                  LclkThermalThrottlingEn:1 ;
    u32                                             Reserved_7_1:7 ;
    u32                                           TemperatureSel:1 ;
    u32                                            Reserved_15_9:7 ;
    u32                                               LclkTtMode:3 ;
    u32                                           :13;
  } Field;
  u32 Value;
} x1F308_t;

/// x1F30C
typedef union {
  struct {
    u32                                             LowThreshold:16;
    u32                                            HighThreshold:16;
  } Field;
  u32 Value;
} x1F30C_t;

/// x1F380
typedef union {
  struct {
    u32                                        InterruptsEnabled:1 ;
    u32                                            Reserved_23_1:23;
    u32                                                TestCount:8 ;
  } Field;
  u32 Value;
} x1F380_t;

/// x1F384
typedef union {
  struct {
    u32                                              FirmwareVid:8 ;
    u32                                            Reserved_31_8:24;
  } Field;
  u32 Value;
} x1F384_t;

/// x1F388
typedef union {
  struct {
    u32                                                  CsrAddr:6 ;
    u32                                                   TcenId:4 ;
    u32                                           Reserved_31_10:22;
  } Field;
  u32 Value;
} x1F388_t;

/// x1F39C
typedef union {
  struct {
    u32                                                       Rx:1 ;
    u32                                                       Tx:1 ;
    u32                                                     Core:1 ;
    u32                                                  SkipPhy:1 ;
    u32                                                 SkipCore:1 ;
    u32                                            Reserved_15_5:11;
    u32                                              LowerLaneID:8 ;
    u32                                              UpperLaneID:8 ;
  } Field;
  u32 Value;
} x1F39C_t;

/// x1F3D8
typedef union {
  struct {
    u32                                            LoadLineTrim3:8 ;
    u32                                            LoadLineTrim2:8 ;
    u32                                            LoadLineTrim1:8 ;
    u32                                            LoadLineTrim0:8 ;
  } Field;
  u32 Value;
} x1F3D8_t;

/// x1F3DC
typedef union {
  struct {
    u32                                            LoadLineTrim7:8 ;
    u32                                            LoadLineTrim6:8 ;
    u32                                            LoadLineTrim5:8 ;
    u32                                            LoadLineTrim4:8 ;
  } Field;
  u32 Value;
} x1F3DC_t;

/// x1F3F8
typedef union {
  struct {
    u32                                       SviInitLoadLineVdd:8 ;
    u32                                     SviInitLoadLineVddNB:8 ;
    u32                                          SviTrimValueVdd:8 ;
    u32                                        SviTrimValueVddNB:8 ;
  } Field;
  u32 Value;
} x1F3F8_t;

/// x1F3FC
typedef union {
  struct {
    u32                                           SviVidStepBase:16;
    u32                                               SviVidStep:16;
  } Field;
  u32 Value;
} x1F3FC_t;

/// x1F400
typedef union {
  struct {
    u32                                     SviLoadLineOffsetVdd:8 ;
    u32                                   SviLoadLineOffsetVddNB:8 ;
    u32                                                PstateMax:8 ;
    u32                                           Reserved_31_24:8 ;
  } Field;
  u32 Value;
} x1F400_t;

/// x1F404
typedef union {
  struct {
    u32                                          LoadLineOffset3:8 ;
    u32                                          LoadLineOffset2:8 ;
    u32                                          LoadLineOffset1:8 ;
    u32                                          LoadLineOffset0:8 ;
  } Field;
  u32 Value;
} x1F404_t;

/// x1F428
typedef union {
  struct {
    u32                                    EnableVpcAccumulators:1 ;
    u32                                               EnableBapm:1 ;
    u32                                           EnableTdcLimit:1 ;
    u32                                               EnableLpmx:1 ;
    u32               field_4:1;
    u32                                              EnableNbDpm:1 ;
    u32                                           EnableLoadline:1 ;
    u32                                            Reserved_15_7:9 ;
    u32                                       :1 ;
    u32                                                  :1 ;
    u32                                                 :1 ;
    u32                                 line180        :1 ;
    u32                                           Reserved_23_20:4 ;
    u32                                        PstateAllCpusIdle:3 ;
    u32                                      NbPstateAllCpusIdle:1 ;
    u32                                        BapmCoeffOverride:1 ;
    u32                                                  SviMode:1 ;
    u32                                           Reserved_31_30:2 ;
  } Field;
  u32 Value;
} x1F428_t;

/// x1F460
typedef union {
  struct {
    u32                                                  LclkDpm:8 ;
    u32                                              ThermalCntl:8 ;
    u32                                              VoltageCntl:8 ;
    u32                                                 Loadline:8 ;
  } Field;
  u32 Value;
} x1F460_t;

/// x1F464
typedef union {
  struct {
    u32                                                  SclkDpm:8 ;
    u32                                         StaticSimdPgCntl:8 ;
    u32                                            DynSimdPgCntl:8 ;
    u32                                                  TdpCntl:8 ;
  } Field;
  u32 Value;
} x1F464_t;

/// x1F468
typedef union {
  struct {
    u32                                              TimerPeriod:32;
  } Field;
  u32 Value;
} x1F468_t;

/// x1F46C
typedef union {
  struct {
    u32                                                VpcPeriod:16;
    u32                                               BapmPeriod:8 ;
    u32                                               LpmxPeriod:8 ;
  } Field;
  u32 Value;
} x1F46C_t;

/// x1F5F8
typedef union {
  struct {
    u32                                             Dpm0PgNbPsLo:2 ;
    u32                                             Dpm0PgNbPsHi:2 ;
    u32                                               DpmXNbPsLo:2 ;
    u32                                               DpmXNbPsHi:2 ;
    u32                                               Hysteresis:8 ;
    u32                                                   SkipPG:1 ;
    u32                                                 SkipDPM0:1 ;
    u32                                           Reserved_21_18:4 ;
    u32                                             EnableNbPsi1:1 ;
    u32                                      EnableDpmPstatePoll:1 ;
    u32                                           Reserved_31_24:8 ;
  } Field;
  u32 Value;
} x1F5F8_t;

/// x1F5FC
typedef union {
  struct {
    u32                                         ChangeInProgress:1 ;
    u32                                        CurrentPstatePair:1 ;
    u32                                             Reserved_7_2:6 ;
    u32                                                  PSI1Sts:1 ;
    u32                                            Reserved_31_9:23;
  } Field;
  u32 Value;
} x1F5FC_t;

/// x1F610
typedef union {
  struct {
    u32                                                 RESERVED:8 ;
    u32                                                     GFXH:8 ;
    u32                                                     GFXL:8 ;
    u32                                                    GPPSB:8 ;
  } Field;
  u32 Value;
} x1F610_t;

/// x1F628
typedef union {
  struct {
    u32                                             Reserved_15_0:16;
    u32                                      HtcActivePstateLimit:8;
    u32                                            Reserved_31_24:8;
  } Field;
  u32 Value;
} x1F628_t;

/// x1F62C
typedef union {
  struct {
    u32                                                      Idd:16;
    u32                                                    Iddnb:16;
  } Field;
  u32 Value;
} x1F62C_t;

/// x1F630
typedef union {
  struct {
    u32                                              RECONF_WAIT:8;
    u32                                           RECONF_WRAPPER:8;
    u32                                                Reserved:16;
  } Field;
  u32 Value;
} x1F630_t;

/// x1F638
typedef union {
  struct {
    u32                                                TdcPeriod:8 ;
    u32                                                HtcPeriod:8 ;
    u32                                              NbdpmPeriod:8 ;
    u32                                        PginterlockPeriod:8 ;
  } Field;
  u32 Value;
} x1F638_t;

/// x1F6E4
typedef union {
  struct {
    u32                                             DdrVoltFloor:8 ;
    u32                                         BapmDdrVoltFloor:8 ;
    u32                                                 Reserved:16;
  } Field;
  u32 Value;
} x1F6E4_t;

/// x1F6B4
typedef union {
  struct {
    u32                                                 TjOffset:8 ;
    u32                                                 Reserved:24;
  } Field;
  u32 Value;
} x1F6B4_t;

/// x1F840
typedef union {
  struct {
    u32                                              IddspikeOCP:16;
    u32                                            IddNbspikeOCP:16;
  } Field;
  u32 Value;
} x1F840_t;

/// x1F844
typedef union {
  struct {
    u32                                                   CsrAddr:6;
    u32                                                    TcenId:4;
    u32                                           Reserved_31_10:22;
  } Field;
  u32 Value;
} x1F844_t;

/// x1F848
typedef union {
  struct {
    u32                                                   CsrAddr:6;
    u32                                                    TcenId:4;
    u32                                           Reserved_31_10:22;
  } Field;
  u32 Value;
} x1F848_t;

/// x1F84C
typedef union {
  struct {
    u32                                                   CsrAddr:6;
    u32                                                    TcenId:4;
    u32                                           Reserved_31_10:22;
  } Field;
  u32 Value;
} x1F84C_t;

/// x1F870
typedef union {
  struct {
    u32                                           AmbientTempBase:8;
    u32                                          BAPMTI_TjOffset_2:8;
    u32                                          BAPMTI_TjOffset_1:8;
    u32                                          BAPMTI_TjOffset_0:8;
  } Field;
  u32 Value;
} x1F870_t;

/// x1F878
typedef union {
  struct {
    u32                                                FUSE_DATA:32;
  } Field;
  u32 Value;
} x1F878_t;

/// x1F87C
typedef union {
  struct {
    u32                                         LL_PCIE_LoadStep:16;
    u32                                     LL_VddNbLoadStepBase:16;
  } Field;
  u32 Value;
} x1F87C_t;

/// x1F880
typedef union {
  struct {
    u32                                          LL_VCE_LoadStep:16;
    u32                                          LL_UVD_LoadStep:16;
  } Field;
  u32 Value;
} x1F880_t;

/// x1F884
typedef union {
  struct {
    u32                                         LL_DCE2_LoadStep:16;
    u32                                          LL_DCE_LoadStep:16;
  } Field;
  u32 Value;
} x1F884_t;

/// x1F888
typedef union {
  struct {
    u32                                                 VddNbTdp:16;
    u32                                          LL_GPU_LoadStep:16;
  } Field;
  u32 Value;
} x1F888_t;

/// x1F88C
typedef union {
  struct {
    u32                                                  NbVid_3:8 ;
    u32                                                  NbVid_2:8 ;
    u32                                                  NbVid_1:8 ;
    u32                                                  NbVid_0:8 ;
  } Field;
  u32 Value;
} x1F88C_t;

/// x1F890
typedef union {
  struct {
    u32                                                 CpuVid_3:8 ;
    u32                                                 CpuVid_2:8 ;
    u32                                                 CpuVid_1:8 ;
    u32                                                 CpuVid_0:8 ;
  } Field;
  u32 Value;
} x1F890_t;

/// x1F894
typedef union {
  struct {
    u32                                                 CpuVid_7:8 ;
    u32                                                 CpuVid_6:8 ;
    u32                                                 CpuVid_5:8 ;
    u32                                                 CpuVid_4:8 ;
  } Field;
  u32 Value;
} x1F894_t;

/// x1F8D4
typedef union {
  struct {
    u32                                           BapmPstateVid_3:8;
    u32                                           BapmPstateVid_2:8;
    u32                                           BapmPstateVid_1:8;
    u32                                           BapmPstateVid_0:8;
  } Field;
  u32 Value;
} x1F8D4_t;

/// x1F8D8
typedef union {
  struct {
    u32                                           BapmPstateVid_7:8;
    u32                                           BapmPstateVid_6:8;
    u32                                           BapmPstateVid_5:8;
    u32                                           BapmPstateVid_4:8;
  } Field;
  u32 Value;
} x1F8D8_t;

/// x1F8DC
typedef union {
  struct {
    u32                                                  SClkVid3:8;
    u32                                                  SClkVid2:8;
    u32                                                  SClkVid1:8;
    u32                                                  SClkVid0:8;
  } Field;
  u32 Value;
} x1F8DC_t;

/// x1F8E0
typedef union {
  struct {
    u32                                             BapmSclkVid_2:8;
    u32                                             BapmSclkVid_1:8;
    u32                                             BapmSclkVid_0:8;
    u32                                              DdrVoltFloor:8;
  } Field;
  u32 Value;
} x1F8E0_t;

/// x1F8E4
typedef union {
  struct {
    u32                                               BapmNbVid_1:8;
    u32                                               BapmNbVid_0:8;
    u32                                          BapmDdrVoltFloor:8;
    u32                                             BapmSclkVid_3:8;
  } Field;
  u32 Value;
} x1F8E4_t;

/// x1F8E8
typedef union {
  struct {
    u32                                            Reserved_15_0:16;
    u32                                              BapmNbVid_3:8;
    u32                                              BapmNbVid_2:8;
  } Field;
  u32 Value;
} x1F8E8_t;

/// x1F85C
typedef union {
  struct {
    u32                                                    VCETdp:20;
    u32                                                    spare8:1;
    u32                                               TdpAgeValue:3;
    u32                                                TdpAgeRate:8;
  } Field;
  u32 Value;
} x1F85C_t;

/// x1F860
typedef union {
  struct {
    u32                                           BAPMTI_TjHyst_1:8;
    u32                                            BAPMTI_TjMax_1:8;
    u32                                           BAPMTI_TjHyst_0:8;
    u32                                            BAPMTI_TjMax_0:8;
  } Field;
  u32 Value;
} x1F860_t;

/// x1F864
typedef union {
  struct {
    u32                                            PCIe2PhyOffset:8;
    u32                                            PCIe1PhyOffset:8;
    u32                                          BAPMTI_GpuTjHyst:8;
    u32                                           BAPMTI_GpuTjMax:8;
  } Field;
  u32 Value;
} x1F864_t;

/// x1F86C
typedef union {
  struct {
    u32                                             Reserved_22_0:23;
    u32                                               BapmLhtcCap:1;
    u32                                            Reserved_31_24:8;
  } Field;
  u32 Value;
} x1F86C_t;

/// x1FE00
typedef union {
  struct {
    u32                                                     Data:32;
  } Field;
  u32 Value;
} x1FE00_t;


///////////////////////////////////////
// Hardware registers

/// xE0000004
typedef union {
  struct {
    u32                                      RCU_TST_jpc_rep_req:1 ;
    u32                                     RCU_TST_jpc_rep_done:1 ;
    u32                                             drv_rst_mode:1 ;
    u32                              SMU_DC_efuse_status_invalid:1 ;
    u32                                                 Reserved:1 ;
    u32                                TST_RCU_jpc_DtmSMSCntDone:1 ;
    u32                                                TP_Tester:1 ;
    u32                                            boot_seq_done:1 ;
    u32                                     sclk_deep_sleep_exit:1 ;
    u32                                         BREAK_PT1_ACTIVE:1 ;
    u32                                         BREAK_PT2_ACTIVE:1 ;
    u32                                                 FCH_HALT:1 ;
    u32                                   FCH_LOCKDOWN_WRITE_DIS:1 ;
    u32                                     RCU_GIO_fch_lockdown:1 ;
    u32                                            Reserved14_23:10;
    u32                                           lm32_irq31_sel:2 ;
    u32                                            Reserved26_31:6 ;
  } Field;
  u32 Value;
} xE0000004_t;

/// xE0000120
typedef union {
  struct {
    u32                                           ActivityCntRst:1 ;
    u32                                             PeriodCntRst:1 ;
    u32                                             Reserved_2_2:1 ;
    u32                                               BusyCntSel:2 ;
    u32                                             Reserved_7_5:3 ;
    u32                                                 EnBifCnt:1 ;
    u32                                               EnOrbUsCnt:1 ;
    u32                                               EnOrbDsCnt:1 ;
    u32                                           Reserved_31_11:21;
  } Field;
  u32 Value;
} xE0000120_t;

/// xE0001008
typedef union {
  struct {
    u32                                                 SClkVid0:8 ;
    u32                                                 SClkVid1:8 ;
    u32                                                 SClkVid2:8 ;
    u32                                                 SClkVid3:8 ;
  } Field;
  u32 Value;
} xE0001008_t;


// SERVICE REQUESTS

/// xE0003000
typedef union {
  struct {
    u32                                                IntToggle:1 ;
    u32                                             ServiceIndex:16;
    u32                                           Reserved_31_17:15;
  } Field;
  u32 Value;
} xE0003000_t;

/// xE0003004
typedef union {
  struct {
    u32                                                   IntAck:1 ;
    u32                                                  IntDone:1 ;
    u32                                            Reserved_31_2:30;
  } Field;
  u32 Value;
} xE0003004_t;

/// xE0003024
typedef union {
  struct {
    u32                                            SMU_SCRATCH_A:32;
  } Field;
  u32 Value;
} xE0003024_t;

/// xE0003034
typedef union {
  struct {
    u32                                           PmAllcpusincc6:1 ;
    u32                                                   PmNbps:1 ;
    u32                                         PmCommitselfrefr:2 ;
    u32                                         PmPreselfrefresh:1 ;
    u32                                            PmReqnbpstate:1 ;
    u32                                             Reserved_8_6:3 ;
    u32                                                   NbNbps:1 ;
    u32                                         NbCommitselfrefr:2 ;
    u32                                         NbPreselfrefresh:1 ;
    u32                                            NbReqnbpstate:1 ;
    u32                                                   McNbps:1 ;
    u32                                      GmconCommitselfrefr:2 ;
    u32                                      GmconPreselfrefresh:1 ;
    u32                                         GmconReqnbpstate:1 ;
    u32                                                   SysIso:1 ;
    u32                                                    CpIso:1 ;
    u32                                                   Dc0Iso:1 ;
    u32                                                   Dc1Iso:1 ;
    u32                                                   DciIso:1 ;
    u32                                                 DcipgIso:1 ;
    u32                                                   DdiIso:1 ;
    u32                                                   GmcIso:1 ;
    u32                                           Reserved_27_27:1 ;
    u32                                                 GmcPmSel:2 ;
    u32                                                  CpPmSel:2 ;
  } Field;
  u32 Value;
} xE0003034_t;

/// xE0003048
typedef union {
  struct {
    u32                                                    Fracv:12;
    u32                                                     Intv:7 ;
    u32                                           Reserved_31_19:13;
  } Field;
  u32 Value;
} xE0003048_t;

/// xE0003088
typedef union {
  struct {
    u32                                              SmuAuthDone:1 ;
    u32                                              SmuAuthPass:1 ;
    u32                                            Reserved_31_2:30;
  } Field;
  u32 Value;
} xE0003088_t;

/// xE00030A4
typedef union {
  struct {
    u32                                            Reserved_15_0:16;
    u32                                         SmuProtectedMode:1 ;
    u32                                           Reserved_31_17:15;
  } Field;
  u32 Value;
} xE00030A4_t;

/// xE0104040
typedef union {
  struct {
    u32                                             Reserved_6_0:7;
    u32                                                DeviceID:16 ;
    u32                                           Reserved_31_23:9;
  } Field;
  u32 Value;
} xE0104040_t;

/// xE0104168
typedef union {
  struct {
    u32                                            GnbLPML15_5_0:6 ;
    u32                                           MemClkVid0_7_0:8 ;
    u32                                           MemClkVid1_7_0:8 ;
    u32                                           MemClkVid2_7_0:8 ;
    u32                                           MemClkVid3_1_0:2 ;
  } Field;
  u32 Value;
} xE0104168_t;

/// xE010416C
typedef union {
  struct {
    u32                                           MemClkVid3_7_2:6 ;
    u32                                           MemClkVid4_7_0:8 ;
    u32                                           MemClkVid5_7_0:8 ;
    u32                                           MemClkVid6_7_0:8 ;
    u32                                           MemClkVid7_1_0:2 ;
  } Field;
  u32 Value;
} xE010416C_t;

/// xE0104170
typedef union {
  struct {
    u32                                           MemClkVid7_7_2:6 ;
    u32                                           MemClkVid8_7_0:8 ;
    u32                                      AmbientTempBase_7_0:8 ;
    u32                                          SMU_SPARE31_9_0:10;
  } Field;
  u32 Value;
} xE0104170_t;

/// xE0300000
typedef union {
  struct {
    u32                                                  FsmAddr:8 ;
    u32                                                PowerDown:1 ;
    u32                                                  PowerUp:1 ;
    u32                                                 P1Select:1 ;
    u32                                                 P2Select:1 ;
    u32                                                  WriteOp:1 ;
    u32                                                   ReadOp:1 ;
    u32                                           Reserved_27_14:14;
    u32                                                  RegAddr:4 ;
  } Field;
  u32 Value;
} xE0300000_t;

/// xE0300004
typedef union {
  struct {
    u32                                              Write_value:32;
  } Field;
  u32 Value;
} xE0300004_t;

/// xE0300008
typedef union {
  struct {
    u32                                                ReadValue:24;
    u32                                                ReadValid:1 ;
    u32                                           Reserved_31_25:7 ;
  } Field;
  u32 Value;
} xE0300008_t;

/// xE030000C
typedef union {
  struct {
    u32                                                  FsmAddr:8 ;
    u32                                                PowerDown:1 ;
    u32                                                  PowerUp:1 ;
    u32                                                 P1Select:1 ;
    u32                                                 P2Select:1 ;
    u32                                                  WriteOp:1 ;
    u32                                                   ReadOp:1 ;
    u32                                           Reserved_27_14:14;
    u32                                                  RegAddr:4 ;
  } Field;
  u32 Value;
} xE030000C_t;

/// xE0300010
typedef union {
  struct {
    u32                                              Write_value:32;
  } Field;
  u32 Value;
} xE0300010_t;

/// xE0300018
typedef union {
  struct {
    u32                                                  FsmAddr:8 ;
    u32                                                PowerDown:1 ;
    u32                                                  PowerUp:1 ;
    u32                                                 P1Select:1 ;
    u32                                                 P2Select:1 ;
    u32                                                  WriteOp:1 ;
    u32                                                   ReadOp:1 ;
    u32                                           Reserved_27_14:14;
    u32                                                  RegAddr:4 ;
  } Field;
  u32 Value;
} xE0300018_t;

/// xE030001C
typedef union {
  struct {
    u32                                              Write_value:32;
  } Field;
  u32 Value;
} xE030001C_t;

/// xE0300024
typedef union {
  struct {
    u32                                                  FsmAddr:8 ;
    u32                                                PowerDown:1 ;
    u32                                                  PowerUp:1 ;
    u32                                                 P1Select:1 ;
    u32                                                 P2Select:1 ;
    u32                                                  WriteOp:1 ;
    u32                                                   ReadOp:1 ;
    u32                                           Reserved_27_14:14;
    u32                                                  RegAddr:4 ;
  } Field;
  u32 Value;
} xE0300024_t;

/// xE0300028
typedef union {
  struct {
    u32                                              Write_value:32;
  } Field;
  u32 Value;
} xE0300028_t;

/// xE0300030
typedef union {
  struct {
    u32                                                  FsmAddr:8 ;
    u32                                                PowerDown:1 ;
    u32                                                  PowerUp:1 ;
    u32                                                 P1Select:1 ;
    u32                                                 P2Select:1 ;
    u32                                                  WriteOp:1 ;
    u32                                                   ReadOp:1 ;
    u32                                           Reserved_27_14:14;
    u32                                                  RegAddr:4 ;
  } Field;
  u32 Value;
} xE0300030_t;

/// xE0300034
typedef union {
  struct {
    u32                                              Write_value:32;
  } Field;
  u32 Value;
} xE0300034_t;

/// xE030003C
typedef union {
  struct {
    u32                                                  FsmAddr:8 ;
    u32                                                PowerDown:1 ;
    u32                                                  PowerUp:1 ;
    u32                                                 P1Select:1 ;
    u32                                                 P2Select:1 ;
    u32                                                  WriteOp:1 ;
    u32                                                   ReadOp:1 ;
    u32                                           Reserved_27_14:14;
    u32                                                  RegAddr:4 ;
  } Field;
  u32 Value;
} xE030003C_t;

/// xE0300040
typedef union {
  struct {
    u32                                              Write_value:32;
  } Field;
  u32 Value;
} xE0300040_t;

/// xE0300054
typedef union {
  struct {
    u32                                                  FsmAddr:8 ;
    u32                                                PowerDown:1 ;
    u32                                                  PowerUp:1 ;
    u32                                                 P1Select:1 ;
    u32                                                 P2Select:1 ;
    u32                                                  WriteOp:1 ;
    u32                                                   ReadOp:1 ;
    u32                                           Reserved_27_14:14;
    u32                                                  RegAddr:4 ;
  } Field;
  u32 Value;
} xE0300054_t;

/// xE0300058
typedef union {
  struct {
    u32                                               WriteValue:32;
  } Field;
  u32 Value;
} xE0300058_t;

/// xE0300070
typedef union {
  struct {
    u32                                                  FsmAddr:8 ;
    u32                                                PowerDown:1 ;
    u32                                                  PowerUp:1 ;
    u32                                                 P1Select:1 ;
    u32                                                 P2Select:1 ;
    u32                                                  WriteOp:1 ;
    u32                                                   ReadOp:1 ;
    u32                                           Reserved_27_14:14;
    u32                                                  RegAddr:4 ;
  } Field;
  u32 Value;
} xE0300070_t;

/// xE0300074
typedef union {
  struct {
    u32                                               WriteValue:32;
  } Field;
  u32 Value;
} xE0300074_t;

/// xE030008C
typedef union {
  struct {
    u32                                                  FsmAddr:8 ;
    u32                                                PowerDown:1 ;
    u32                                                  PowerUp:1 ;
    u32                                                 P1Select:1 ;
    u32                                                 P2Select:1 ;
    u32                                                  WriteOp:1 ;
    u32                                                   ReadOp:1 ;
    u32                                           Reserved_27_14:14;
    u32                                                  RegAddr:4 ;
  } Field;
  u32 Value;
} xE030008C_t;

/// xE0300090
typedef union {
  struct {
    u32                                               WriteValue:32;
  } Field;
  u32 Value;
} xE0300090_t;

/// xE03000A8
typedef union {
  struct {
    u32                                                  FsmAddr:8 ;
    u32                                                PowerDown:1 ;
    u32                                                  PowerUp:1 ;
    u32                                                 P1Select:1 ;
    u32                                                 P2Select:1 ;
    u32                                                  WriteOp:1 ;
    u32                                                   ReadOp:1 ;
    u32                                           Reserved_27_14:14;
    u32                                                  RegAddr:4 ;
  } Field;
  u32 Value;
} xE03000A8_t;

/// xE03000AC
typedef union {
  struct {
    u32                                               WriteValue:32;
  } Field;
  u32 Value;
} xE03000AC_t;

/// xE03000C4
typedef union {
  struct {
    u32                                                  FsmAddr:8 ;
    u32                                                PowerDown:1 ;
    u32                                                  PowerUp:1 ;
    u32                                                 P1Select:1 ;
    u32                                                 P2Select:1 ;
    u32                                                  WriteOp:1 ;
    u32                                                   ReadOp:1 ;
    u32                                           Reserved_27_14:14;
    u32                                                  RegAddr:4 ;
  } Field;
  u32 Value;
} xE03000C4_t;

/// xE03000C8
typedef union {
  struct {
    u32                                               WriteValue:32;
  } Field;
  u32 Value;
} xE03000C8_t;

/// xE03000E0
typedef union {
  struct {
    u32                                                  FsmAddr:8 ;
    u32                                                PowerDown:1 ;
    u32                                                  PowerUp:1 ;
    u32                                                 P1Select:1 ;
    u32                                                 P2Select:1 ;
    u32                                                  WriteOp:1 ;
    u32                                                   ReadOp:1 ;
    u32                                           Reserved_27_14:14;
    u32                                                  RegAddr:4 ;
  } Field;
  u32 Value;
} xE03000E0_t;

/// xE03000E4
typedef union {
  struct {
    u32                                               WriteValue:32;
  } Field;
  u32 Value;
} xE03000E4_t;

/// xE03000FC
typedef union {
  struct {
    u32                                                  FsmAddr:8 ;
    u32                                                PowerDown:1 ;
    u32                                                  PowerUp:1 ;
    u32                                                 P1Select:1 ;
    u32                                                 P2Select:1 ;
    u32                                                  WriteOp:1 ;
    u32                                                   ReadOp:1 ;
    u32                                           Reserved_27_14:14;
    u32                                                  RegAddr:4 ;
  } Field;
  u32 Value;
} xE03000FC_t;

/// xE0300100
typedef union {
  struct {
    u32                                               WriteValue:32;
  } Field;
  u32 Value;
} xE0300100_t;

/// xE0300200
typedef union {
  struct {
    u32                                             Reserved_9_0:10;
    u32                                                   P1IsoN:1 ;
    u32                                           Reserved_31_11:21;
  } Field;
  u32 Value;
} xE0300200_t;

/// xE0300208
typedef union {
  struct {
    u32                                             Reserved_9_0:10;
    u32                                                   P1IsoN:1 ;
    u32                                           Reserved_12_11:2 ;
    u32                                                :1 ;
    u32                                           Reserved_31_14:18;
  } Field;
  u32 Value;
} xE0300208_t;

/// xE030020C
typedef union {
  struct {
    u32                                             Reserved_9_0:10;
    u32                                                   P1IsoN:1 ;
    u32                                           Reserved_31_11:21;
  } Field;
  u32 Value;
} xE030020C_t;

/// xE0300210
typedef union {
  struct {
    u32                                             Reserved_9_0:10;
    u32                                                   P1IsoN:1 ;
    u32                                           Reserved_12_11:2 ;
    u32                                                :1 ;
    u32                                           Reserved_31_14:18;
  } Field;
  u32 Value;
} xE0300210_t;

/// xE0300218
typedef union {
  struct {
    u32                                             Reserved_9_0:10;
    u32                                                   P1IsoN:1 ;
    u32                                           Reserved_31_11:21;
  } Field;
  u32 Value;
} xE0300218_t;

/// xE03002DC
typedef union {
  struct {
    u32                                        DC2_PGFSM_CONTROL:1 ;
    u32                                                 Reserved:31;
  } Field;
  u32 Value;
} xE03002DC_t;

/// xE03002E4
typedef union {
  struct {
    u32                                            SmuCb0PsoDaug:1 ;
    u32                                            SmuCb1PsoDaug:1 ;
    u32                                            SmuDb0PsoDaug:1 ;
    u32                                            SmuDb1PsoDaug:1 ;
    u32                                             SmuPaPsoDaug:1 ;
    u32                                            SmuSpmPsoDaug:1 ;
    u32                                            SmuSpsPsoDaug:1 ;
    u32                                            SmuSqbPsoDaug:1 ;
    u32                                            SmuSxmPsoDaug:1 ;
    u32                                           SmuSxs0PsoDaug:1 ;
    u32                                           SmuSxs1PsoDaug:1 ;
    u32                                            SmuXbrPsoDaug:1 ;
    u32                                            SmuGdsPsoDaug:1 ;
    u32                                            SmuVgtPsoDaug:1 ;
    u32                                            SmuSqaPsoDaug:1 ;
    u32                                            SmuSqcPsoDaug:1 ;
    u32                                             SmuTcPsoDaug:1 ;
    u32                                             SmuScPsoDaug:1 ;
    u32                                           Reserved_31_18:14;
  } Field;
  u32 Value;
} xE03002E4_t;

/// xE03002F0
typedef union {
  struct {
    u32                                           SmuTatd0P1IsoN:1 ;
    u32                                           SmuSp000P1IsoN:1 ;
    u32                                           SmuSp002P1IsoN:1 ;
    u32                                            SmuLds0P1IsoN:1 ;
    u32                                            SmuTcp0P1IsoN:1 ;
    u32                                           SmuTatd1P1IsoN:1 ;
    u32                                           SmuSp010P1IsoN:1 ;
    u32                                           SmuSp012P1IsoN:1 ;
    u32                                            SmuLds1P1IsoN:1 ;
    u32                                            SmuTcp1P1IsoN:1 ;
    u32                                           SmuTatd2P1IsoN:1 ;
    u32                                           SmuSp020P1IsoN:1 ;
    u32                                           SmuSp022P1IsoN:1 ;
    u32                                            SmuLds2P1IsoN:1 ;
    u32                                            SmuTcp2P1IsoN:1 ;
    u32                                           SmuTatd3P1IsoN:1 ;
    u32                                           SmuSp030P1IsoN:1 ;
    u32                                           SmuSp032P1IsoN:1 ;
    u32                                            SmuLds3P1IsoN:1 ;
    u32                                            SmuTcp3P1IsoN:1 ;
    u32                                           SmuTatd4P1IsoN:1 ;
    u32                                           SmuSp040P1IsoN:1 ;
    u32                                           SmuSp042P1IsoN:1 ;
    u32                                            SmuLds4P1IsoN:1 ;
    u32                                            SmuTcp4P1IsoN:1 ;
    u32                                           SmuTatd5P1IsoN:1 ;
    u32                                           SmuSp050P1IsoN:1 ;
    u32                                           SmuSp052P1IsoN:1 ;
    u32                                            SmuLds5P1IsoN:1 ;
    u32                                            SmuTcp5P1IsoN:1 ;
    u32                                           Reserved_31_30:2 ;
  } Field;
  u32 Value;
} xE03002F0_t;

/// xE03002F4
typedef union {
  struct {
    u32                                               SmuCb0IsoN:1 ;
    u32                                               SmuCb1IsoN:1 ;
    u32                                               SmuDb0IsoN:1 ;
    u32                                               SmuDb1IsoN:1 ;
    u32                                                SmuPaIsoN:1 ;
    u32                                               SmuSpmIsoN:1 ;
    u32                                               SmuSpsIsoN:1 ;
    u32                                               SmuSqbIsoN:1 ;
    u32                                               SmuSxmIsoN:1 ;
    u32                                              SmuSxs0IsoN:1 ;
    u32                                              SmuSxs1IsoN:1 ;
    u32                                               SmuXbrIsoN:1 ;
    u32                                               SmuGdsIsoN:1 ;
    u32                                               SmuVgtIsoN:1 ;
    u32                                               SmuSqaIsoN:1 ;
    u32                                               SmuSqcIsoN:1 ;
    u32                                                SmuTcIsoN:1 ;
    u32                                                SmuScIsoN:1 ;
    u32                                           Reserved_31_18:14;
  } Field;
  u32 Value;
} xE03002F4_t;

/// xE03002F8
typedef union {
  struct {
    u32                                           SmuTatd0P2IsoN:1 ;
    u32                                           SmuSp000P2IsoN:1 ;
    u32                                           SmuSp002P2IsoN:1 ;
    u32                                            SmuLds0P2IsoN:1 ;
    u32                                            SmuTcp0P2IsoN:1 ;
    u32                                           SmuTatd1P2IsoN:1 ;
    u32                                           SmuSp010P2IsoN:1 ;
    u32                                           SmuSp012P2IsoN:1 ;
    u32                                            SmuLds1P2IsoN:1 ;
    u32                                            SmuTcp1P2IsoN:1 ;
    u32                                           SmuTatd2P2IsoN:1 ;
    u32                                           SmuSp020P2IsoN:1 ;
    u32                                           SmuSp022P2IsoN:1 ;
    u32                                            SmuLds2P2IsoN:1 ;
    u32                                            SmuTcp2P2IsoN:1 ;
    u32                                           SmuTatd3P2IsoN:1 ;
    u32                                           SmuSp030P2IsoN:1 ;
    u32                                           SmuSp032P2IsoN:1 ;
    u32                                            SmuLds3P2IsoN:1 ;
    u32                                            SmuTcp3P2IsoN:1 ;
    u32                                           SmuTatd4P2IsoN:1 ;
    u32                                           SmuSp040P2IsoN:1 ;
    u32                                           SmuSp042P2IsoN:1 ;
    u32                                            SmuLds4P2IsoN:1 ;
    u32                                            SmuTcp4P2IsoN:1 ;
    u32                                           SmuTatd5P2IsoN:1 ;
    u32                                           SmuSp050P2IsoN:1 ;
    u32                                           SmuSp052P2IsoN:1 ;
    u32                                            SmuLds5P2IsoN:1 ;
    u32                                            SmuTcp5P2IsoN:1 ;
    u32                                           Reserved_31_30:2 ;
  } Field;
  u32 Value;
} xE03002F8_t;

/// xE03002FC
typedef union {
  struct {
    u32                                        SmuTatd0P2PsoDaug:1 ;
    u32                                        SmuSp000P2PsoDaug:1 ;
    u32                                        SmuSp002P2PsoDaug:1 ;
    u32                                         SmuLds0P2PsoDaug:1 ;
    u32                                         SmuTcp0P2PsoDaug:1 ;
    u32                                        SmuTatd1P2PsoDaug:1 ;
    u32                                        SmuSp010P2PsoDaug:1 ;
    u32                                        SmuSp012P2PsoDaug:1 ;
    u32                                         SmuLds1P2PsoDaug:1 ;
    u32                                         SmuTcp1P2PsoDaug:1 ;
    u32                                        SmuTatd2P2PsoDaug:1 ;
    u32                                        SmuSp020P2PsoDaug:1 ;
    u32                                        SmuSp022P2PsoDaug:1 ;
    u32                                         SmuLds2P2PsoDaug:1 ;
    u32                                         SmuTcp2P2PsoDaug:1 ;
    u32                                        SmuTatd3P2PsoDaug:1 ;
    u32                                        SmuSp030P2PsoDaug:1 ;
    u32                                        SmuSp032P2PsoDaug:1 ;
    u32                                         SmuLds3P2PsoDaug:1 ;
    u32                                         SmuTcp3P2PsoDaug:1 ;
    u32                                        SmuTatd4P2PsoDaug:1 ;
    u32                                        SmuSp040P2PsoDaug:1 ;
    u32                                        SmuSp042P2PsoDaug:1 ;
    u32                                         SmuLds4P2PsoDaug:1 ;
    u32                                         SmuTcp4P2PsoDaug:1 ;
    u32                                        SmuTatd5P2PsoDaug:1 ;
    u32                                        SmuSp050P2PsoDaug:1 ;
    u32                                        SmuSp052P2PsoDaug:1 ;
    u32                                         SmuLds5P2PsoDaug:1 ;
    u32                                         SmuTcp5P2PsoDaug:1 ;
    u32                                           Reserved_31_30:2 ;
  } Field;
  u32 Value;
} xE03002FC_t;

/// xE0300320
typedef union {
  struct {
    u32                                          PgdPgfsmClockEn:1 ;
    u32                                        IommuPgfsmClockEn:1 ;
    u32                                            Reserved_31_2:30;
  } Field;
  u32 Value;
} xE0300320_t;

/// xE0300324
typedef union {
  struct {
    u32                                          VcePgfsmClockEn:1 ;
    u32                                          UvdPgfsmClockEn:1 ;
    u32                                          Dc2PgfsmClockEn:1 ;
    u32                                            Reserved_31_3:29;
  } Field;
  u32 Value;
} xE0300324_t;

/// xFF000000
typedef union {
  struct {
    u32                                              GckFuseProg:1 ;
    u32                                   MainPllOpFreqIdStartup:6 ;
    u32                                       MainPllOpFreqIdMax:6 ;
    u32                                            MainPllRefAdj:5 ;
    u32                                           PllMiscFuseCtl:4 ;
    u32                                           Reserved_31_22:10;
  } Field;
  u32 Value;
} xFF000000_t;

/// xE010703C
typedef union {
  struct {
    u32                                             Reserved_2_0:3 ;
    u32                                               NbPstateHi:2 ;
    u32                                               NbPstateLo:2 ;
    u32                                            Reserved_31_7:25;
  } Field;
  u32 Value;
} xE010703C_t;

/// xE01040A8
typedef union {
  struct {
    u32                                             Reserved0_14:15;
    u32                                           SviLoadLineVdd:7 ;
    u32                                         SviLoadLineVddNb:7 ;
    u32                                            Reserved29_31:3 ;
  } Field;
  u32 Value;
} xE01040A8_t;

/// xE0104158
typedef union {
  struct {
    u32                                              Reserved0_9:10;
    u32                                                 EClkDid0:7 ;
    u32                                                 EClkDid1:7 ;
    u32                                                 EClkDid2:7 ;
    u32                                            Reserved31_31:1 ;
  } Field;
  u32 Value;
} xE0104158_t;

/// xE010415B
typedef union {
  struct {
    u32                                              Reserved0_6:7 ;
    u32                                                 EClkDid3:7 ;
    u32                                            Reserved14_31:18;
  } Field;
  u32 Value;
} xE010415B_t;

/// xE0104184
typedef union {
  struct {
    u32                                       SviLoadLineTrimVdd:3 ;
    u32                                     SviLoadLineTrimVddNb:3 ;
    u32                                     SviLoadLineOffsetVdd:2 ;
    u32                                   SviLoadLineOffsetVddNb:2 ;
    u32                                                 VCEFlag0:8 ;
    u32                                                 VCEFlag1:8 ;
    u32                                            Reserved26_31:6 ;
  } Field;
  u32 Value;
} xE0104184_t;

/// xE0104187
typedef union {
  struct {
    u32                                              Reserved0_1:2 ;
    u32                                                 VCEFlag2:8 ;
    u32                                            Reserved10_31:22;
  } Field;
  u32 Value;
} xE0104187_t;

/// xE0104188
typedef union {
  struct {
    u32                                              Reserved0_1:2 ;
    u32                                                 VCEFlag3:8 ;
    u32                                              ReqSclkSel0:3 ;
    u32                                              ReqSclkSel1:3 ;
    u32                                              ReqSclkSel2:3 ;
    u32                                              ReqSclkSel3:3 ;
    u32                                                  VCEMclk:4 ;
    u32                                          LhtcPstateLimit:3 ;
    u32                                         BapmMeasuredTemp:1 ;
    u32                                              BapmDisable:1 ;
    u32                                            Reserved31_31:1 ;
  } Field;
  u32 Value;
} xE0104188_t;

/// xE0106020
typedef union {
  struct {
    u32                                             Reserved0_24:25;
    u32                                    PowerplayDClkVClkSel0:2 ;
    u32                                    PowerplayDClkVClkSel1:2 ;
    u32                                    PowerplayDClkVClkSel2:2 ;
    u32                                            Reserved31_31:1 ;
  } Field;
  u32 Value;
} xE0106020_t;

/// xE0106023
typedef union {
  struct {
    u32                                              Reserved0_6:7 ;
    u32                                    PowerplayDClkVClkSel3:2 ;
    u32                                             Reserved9_31:23;
  } Field;
  u32 Value;
} xE0106023_t;

/// xE0106024
typedef union {
  struct {
    u32                                              Reserved0_0:1 ;
    u32                                    PowerplayDClkVClkSel4:2 ;
    u32                                    PowerplayDClkVClkSel5:2 ;
    u32                                             Reserved5_31:27;
  } Field;
  u32 Value;
} xE0106024_t;

/// xE010705C
typedef union {
  struct {
    u32                                             Reserved0_17:18;
    u32                                        PowerplayTableRev:4 ;
    u32                                             SClkThermDid:7 ;
    u32                                              PcieGen2Vid:2 ;
    u32                                            Reserved31_31:1 ;
  } Field;
  u32 Value;
} xE010705C_t;

/// xE010705F
typedef union {
  struct {
    u32                                              Reserved0_6:7 ;
    u32                                              SClkDpmVid0:2 ;
    u32                                             Reserved9_31:23;
  } Field;
  u32 Value;
} xE010705F_t;

/// xE0107060
typedef union {
  struct {
    u32                                              Reserved0_0:1 ;
    u32                                              SClkDpmVid1:2 ;
    u32                                              SClkDpmVid2:2 ;
    u32                                              SClkDpmVid3:2 ;
    u32                                              SClkDpmVid4:2 ;
    u32                                              SClkDpmDid0:7 ;
    u32                                              SClkDpmDid1:7 ;
    u32                                              SClkDpmDid2:7 ;
    u32                                            Reserved30_31:2 ;
  } Field;
  u32 Value;
} xE0107060_t;

/// xE0107063
typedef union {
  struct {
    u32                                              Reserved0_5:6 ;
    u32                                              SClkDpmDid3:7 ;
    u32                                            Reserved13_31:19;
  } Field;
  u32 Value;
} xE0107063_t;

/// xE0107064
typedef union {
  struct {
    u32                                              Reserved0_4:5 ;
    u32                                              SClkDpmDid4:7 ;
    u32                                            Reserved12_31:20;
  } Field;
  u32 Value;
} xE0107064_t;

/// xE0107067
typedef union {
  struct {
    u32                                              Reserved0_3:4 ;
    u32                                              DispClkDid0:7 ;
    u32                                            Reserved11_31:21;
  } Field;
  u32 Value;
} xE0107067_t;

/// xE0107068
typedef union {
  struct {
    u32                                              Reserved0_2:3 ;
    u32                                              DispClkDid1:7 ;
    u32                                              DispClkDid2:7 ;
    u32                                              DispClkDid3:7 ;
    u32                                              LClkDpmDid0:7 ;
    u32                                            Reserved31_31:1 ;
  } Field;
  u32 Value;
} xE0107068_t;

/// xE010706B
typedef union {
  struct {
    u32                                              Reserved0_6:7 ;
    u32                                              LClkDpmDid1:7 ;
    u32                                            Reserved14_31:18;
  } Field;
  u32 Value;
} xE010706B_t;

/// xE010706C
typedef union {
  struct {
    u32                                              Reserved0_5:6 ;
    u32                                              LClkDpmDid2:7 ;
    u32                                              LClkDpmDid3:7 ;
    u32                                             LClkDpmValid:4 ;
    u32                                                 DClkDid0:7 ;
    u32                                            Reserved31_31:1 ;
  } Field;
  u32 Value;
} xE010706C_t;

/// xE010706F
typedef union {
  struct {
    u32                                              Reserved0_6:7 ;
    u32                                                 DClkDid1:7 ;
    u32                                            Reserved14_31:18;
  } Field;
  u32 Value;
} xE010706F_t;

/// xE0107070
typedef union {
  struct {
    u32                                              Reserved0_5:6 ;
    u32                                                 DClkDid2:7 ;
    u32                                                 DClkDid3:7 ;
    u32                                                 VClkDid0:7 ;
    u32                                            Reserved27_31:5 ;
  } Field;
  u32 Value;
} xE0107070_t;

/// xE0107073
typedef union {
  struct {
    u32                                              Reserved0_2:3 ;
    u32                                                 VClkDid1:7 ;
    u32                                            Reserved10_31:22;
  } Field;
  u32 Value;
} xE0107073_t;

/// xE0107074
typedef union {
  struct {
    u32                                              Reserved0_1:2 ;
    u32                                                 VClkDid2:7 ;
    u32                                                 VClkDid3:7 ;
    u32                                   PowerplaySclkDpmValid0:5 ;
    u32                                   PowerplaySclkDpmValid1:5 ;
    u32                                   PowerplaySclkDpmValid2:5 ;
    u32                                            Reserved31_31:1 ;
  } Field;
  u32 Value;
} xE0107074_t;

/// xE0107077
typedef union {
  struct {
    u32                                              Reserved0_6:7 ;
    u32                                   PowerplaySclkDpmValid3:5 ;
    u32                                            Reserved12_31:20;
  } Field;
  u32 Value;
} xE0107077_t;

/// xE0107078
typedef union {
  struct {
    u32                                              Reserved0_3:4 ;
    u32                                   PowerplaySclkDpmValid4:5 ;
    u32                                   PowerplaySclkDpmValid5:5 ;
    u32                                    PowerplayPolicyLabel0:2 ;
    u32                                    PowerplayPolicyLabel1:2 ;
    u32                                    PowerplayPolicyLabel2:2 ;
    u32                                    PowerplayPolicyLabel3:2 ;
    u32                                    PowerplayPolicyLabel4:2 ;
    u32                                    PowerplayPolicyLabel5:2 ;
    u32                                            Reserved26_31:6 ;
  } Field;
  u32 Value;
} xE0107078_t;

/// xE010707B
typedef union {
  struct {
    u32                                              Reserved0_1:2 ;
    u32                                      PowerplayStateFlag0:7 ;
    u32                                             Reserved9_31:23;
  } Field;
  u32 Value;
} xE010707B_t;

/// xE010707C
typedef union {
  struct {
    u32                                              Reserved0_0:1 ;
    u32                                      PowerplayStateFlag1:7 ;
    u32                                      PowerplayStateFlag2:7 ;
    u32                                      PowerplayStateFlag3:7 ;
    u32                                      PowerplayStateFlag4:7 ;
    u32                                            Reserved29_31:3 ;
  } Field;
  u32 Value;
} xE010707C_t;

/// xE010707F
typedef union {
  struct {
    u32                                              Reserved0_4:5 ;
    u32                                      PowerplayStateFlag5:7 ;
    u32                                            Reserved12_31:20;
  } Field;
  u32 Value;
} xE010707F_t;

#endif
