/*
 * Disclaimer:
 *
 *   This source code is intended as a design reference
 *   which illustrates how these types of functions can be implemented.
 *   It is the user's responsibility to verify their design for
 *   consistency and functionality through the use of formal
 *   verification methods.  Lattice Semiconductor provides no warranty
 *   regarding the use or functionality of this code.
 *
 * --------------------------------------------------------------------
 *
 *                     Lattice Semiconductor Corporation
 *                     5555 NE Moore Court
 *                     Hillsboro, OR 97214
 *                     U.S.A
 *
 *                     TEL: 1-800-Lattice (USA and Canada)
 *                          408-826-6000 (other locations)
 *
 *                     web: http://www.latticesemi.com/
 *                     email: techsupport@latticesemi.com
 *
 * --------------------------------------------------------------------
 *
 *  Project:           LatticeMico32 
 *  File:              MicoSleepHelper.S
 *  Description:       C Source code implementation for MicoSleepHelper
 *                     called by MicoSleepMilliSecs and MicoSleepMicroSecs
 *
 *----------------------------------------------------------------------------
 *  Change History
 *
 * Vers  Date            Change
 * ---------------------------------------------------------------------------
 * 3.0   Mar-25-2008:   Sync'd version to 3.0 for MSB 7.1 release
 *
 * 1.1   Mar-19-2008:   Updated function implementation to correct for 
 *                      branch-prediction.  branch-prediction no longer
 *                      results in 5 cycles for 1 add and one taken-bne
 *                      hence breaking the function.  The inner loop
 *                      now approximates 11 cycles.
 *
 *----------------------------------------------------------------------------
 */
    .section .text
    .align 4
    .global	MicoSleepHelper
    .type	MicoSleepHelper, @function
MicoSleepHelper:
.LM1:
    or     r3, r0, r2
    /* .LM2 to .LM3 consists the inner loop;
     * because of branch prediction, be and bi
     * don't take the exact ticks specified in the
     * processor user guide; so to nullify their 
     * effect, add a bunch of addi (1-cycle)
     * to reduce the uncertainty (in lieu of 
     * simulating it in RTL)
     */
.LM2:
    be     r3, r0, .LM3
    addi   r3, r3,-1
    addi   r3, r3, 1
    addi   r3, r3,-1
    addi   r3, r3, 1
    addi   r3, r3,-1
    addi   r3, r3, 1
    addi   r3, r3,-1
    addi   r3, r3, 0
    bi     .LM2
.LM3:
    addi   r1, r1, -1
    bne    r1, r0, .LM1
.LM4:
    ret
    .size     MicoSleepHelper, .-MicoSleepHelper

