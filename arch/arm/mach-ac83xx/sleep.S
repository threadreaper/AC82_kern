/* linux/arch/arm/mach-ac83xx/sleep.S
 *
 * Copyright 2008 Openmoko, Inc.
 * Copyright 2008 Simtec Electronics
 *	Ben Dooks <ben@simtec.co.uk>
 *	http://armlinux.simtec.co.uk/
 *
 * ac83xx CPU sleep code
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
*/

#include <linux/linkage.h>
#include <asm/assembler.h>
#include <mach/ac83xx_basic.h>
#define CR_MMU                  (1 << 0)

	.text

/*-------------------------------------------------------------------------------
 *
 *  Function:  OALEnterSleepMode
 *
 *      LEAF_ENTRY OALEnterSleepMode
 */
ENTRY(enter_sleep_mode_coreon)
     dsb
     wfi
     BX      lr
ENTRY(enter_sleep_mode_coreoff)     
     MRC     p15, 0, r3, c1, c0, 0       //Read CP15 control register
     BIC     r3, r3, #CR_MMU
     ldr     r2,=0xF4000020


     mov     r0,r0                       //quickboot param
     
     
     MCR     p15, 0, r3, c1, c0, 0       //Write back control register
     mov     pc,r2
     nop
     nop
     nop
     nop

ENTRY(quickboot_resume)
     MRC     p15, 0, r0, c1, c0, 0       //Read CP15 control register
     orr     r0, r0, #CR_MMU
     ldr     r1,=resume_mmu_on
     MCR     p15, 0, r0, c1, c0, 0       //Write back control register
     mov     pc,r1
     nop
     nop
     nop
     nop

resume_mmu_on:
     bx  lr

