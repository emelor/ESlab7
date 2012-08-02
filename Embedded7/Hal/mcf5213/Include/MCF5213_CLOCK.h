/********************************************************************/
/* Coldfire C Header File
 *
 *     Date      : 2009/04/30
 *     Revision  : 0.96
 *
 *     Copyright : 1997 - 2009 Freescale Semiconductor, Inc. All Rights Reserved.
 *
 *     http      : www.freescale.com
 *     mail      : support@freescale.com
 */

#ifndef __MCF5213_CLOCK_H__
#define __MCF5213_CLOCK_H__


/*********************************************************************
*
* Clock Module (CLOCK)
*
*********************************************************************/

/* Register read/write macros */
#define MCF_CLOCK_SYNCR                      (*(vuint16*)(0x40120000))
#define MCF_CLOCK_SYNSR                      (*(vuint8 *)(0x40120002))
#define MCF_CLOCK_LPDR                       (*(vuint8 *)(0x40120007))


/* Bit definitions and macros for MCF_CLOCK_SYNCR */
#define MCF_CLOCK_SYNCR_PLLEN                (0x1)
#define MCF_CLOCK_SYNCR_PLLMODE              (0x2)
#define MCF_CLOCK_SYNCR_CLKSRC               (0x4)
#define MCF_CLOCK_SYNCR_FWKUP                (0x20)
#define MCF_CLOCK_SYNCR_DISCLK               (0x40)
#define MCF_CLOCK_SYNCR_LOCEN                (0x80)
#define MCF_CLOCK_SYNCR_RFD(x)               (((x)&0x7)<<0x8)
#define MCF_CLOCK_SYNCR_LOCRE                (0x800)
#define MCF_CLOCK_SYNCR_MFD(x)               (((x)&0x7)<<0xC)
#define MCF_CLOCK_SYNCR_LOLRE                (0x8000)

/* Bit definitions and macros for MCF_CLOCK_SYNSR */
#define MCF_CLOCK_SYNSR_LOCS                 (0x4)
#define MCF_CLOCK_SYNSR_LOCK                 (0x8)
#define MCF_CLOCK_SYNSR_LOCKS                (0x10)
#define MCF_CLOCK_SYNSR_CRYOSC               (0x20)
#define MCF_CLOCK_SYNSR_OCOSC                (0x40)
#define MCF_CLOCK_SYNSR_EXTOSC               (0x80)

/* Bit definitions and macros for MCF_CLOCK_LPDR */
#define MCF_CLOCK_LPDR_LPD(x)                (((x)&0xF)<<0)


#endif /* __MCF5213_CLOCK_H__ */
