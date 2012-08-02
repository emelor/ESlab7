#ifndef _HAL_MCF5213_H_
#define _HAL_MCF5213_H_
/*
** File:     hal_MCF5213.h
**
** Contents: Rubus OS
**           Tutorial 
**           Target MCF5213
**           HAL Definitions
**
** Copyright 1996-2011 Arcticus Systems AB
**           All Rights Reserved
**
*/

#include "mcf5xxx.h"
#include <mcf5213_intc.h>

/********************************************************************/
/* 
 * PLL min/max specifications
 */
#define MAX_FVCO    80000   /* KHz */
#define MAX_FSYS    80000   /* KHz */
#define MAX_FREF    10000   /* KHz */
#define MIN_FREF    2000    /* KHz */
#define MAX_MFD     18      /* Multiplier (not encoded) */
#define MIN_MFD     4       /* Multiplier (not encoded) */
#define MAX_RFD     128     /* Divider (not encoded) */
#define MIN_RFD     1       /* Divider (not encoded) */

/*
 * Low Power Divider specifications
 */
#define MIN_LPD     (1 << 0)    /* Divider (not encoded) */
#define MAX_LPD     (1 << 15)   /* Divider (not encoded) */

/* 
 * Operating Parameters
 * Pass to clock_pll() the 'flags' argument
 */
#define PLL_DISABLE   (0x0001)
#define PLL_CLKSRC    (0x0004)
#define PLL_FWKUP     (0x0020)
#define PLL_DISCLK    (0x0040)
#define PLL_LOCEN     (0x0080)
#define PLL_LOCRE     (0x0800)
#define PLL_LOLRE     (0x8000)
#define PLL_ALLFLAGS  (0x88E4)


/*===============================================
  1000 k baud rate
===============================================*/
#define CAN_BAUD_SAMP      0 
#define CAN_BAUD_RJW       1 
#define CAN_BAUD_PSEG1     1 
#define CAN_BAUD_PSEG2     1 
#define CAN_BAUD_PRESDIV   4 
#define CAN_BAUD_PROPSEG   2 


/*===============================================
  System Bus Clock Info 
===============================================*/
#define	SYSTEM_CLOCK		64	    /* system bus frequency in MHz */
#define SYSTEM_PERIOD		15.625	/* system bus period in ns */

#define REF_CLK_MHZ         (8)
#define REF_CLK_KHZ         (8000)
#define SYS_CLK_MHZ         (80)
#define SYS_CLK_KHZ         (80000)

extern int sys_clk_khz;
extern int sys_clk_mhz;

/*===============================================
  Memory map definitions 
===============================================*/
extern uint8 __IPSBAR[];
extern uint8 __SRAM[];
extern uint8 __SRAM_SIZE[];
extern uint8 __FLASH[];
extern uint8 __FLASH_SIZE[];



#endif
