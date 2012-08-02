/*
** File:     hal_mcf5213_sysinit.c
**
** Contents: Rubus OS
**           Tutorial 
**           Target MCF5213
**           Reset configuration of the M5213EVB
**
** Copyright 1996-2011 Arcticus Systems AB
**           All Rights Reserved
**
*/



#include "hal_mcf5213.h"
#include "mcf5213_gpio.h"
#include "mcf5213_eport.h"
#include "MCF5213_CLOCK.h"

extern unsigned long _interruptVector[];


/********************************************************************/
/* Initialize the PLL
 * 
 * Parameters:
 *  fref    PLL reference clock frequency in KHz
 *  fsys    Desired PLL output frequency in KHz
 *  flags   Operating parameters
 *
 * Return Value:
 *  The resulting output system frequency
 */
int clock_pll (int fref, int fsys, int flags)
{
    int syncr, mfd_max, mfd_min, rfd_max;
    int i, temp, fout, mfd, rfd, done;
    
    /* Check for the disable flag */
    if (flags & PLL_DISABLE)
    {
        MCF_CLOCK_SYNCR &= ~MCF_CLOCK_SYNCR_PLLEN;
        return fref;
    }
    
    /* Check bounds of reference clock */
    if((fref >= MAX_FREF) || (fref <= MIN_FREF))
        return fref;
        
    if (fsys == 0)
    {
        /* Return current PLL output */
        if ((MCF_CLOCK_SYNCR & MCF_CLOCK_SYNCR_CLKSRC) &&
            (MCF_CLOCK_SYNCR & MCF_CLOCK_SYNCR_PLLEN))
        {
            mfd = (MCF_CLOCK_SYNCR & 0x7000) >> 12;
            mfd = MIN_MFD + (mfd * 2);
            rfd = (MCF_CLOCK_SYNCR & 0x0700) >> 8;
            rfd = 1 << rfd;
            return (fref * mfd / rfd);
        }
        else
            return fref;            
    }
    
    /* Check bounds of requested system clock */
    if (fsys > MAX_FSYS)
        fsys = MAX_FSYS;

    /* Determine maximum possible multiplier (must be even) */
    mfd_max = MAX_FVCO / fref;
    mfd_max &= ~1;
    if (mfd_max > MAX_MFD)
        mfd_max = MAX_MFD;
    
    /* Determine maximum possible output based on max multiplier */
    fout = fref * mfd_max;

    /* Determine target output based on fsys and max possible */ 
    if (fout > fsys)
        fout = fsys;
    
    /* Determine the minimum multiplier */
    for (mfd_min = mfd_max; 
         mfd_min > MIN_MFD && fout < (fref * mfd_min); 
         mfd_min-=2);
         
    /* Set preliminary divider maximum */         
    rfd_max = MAX_RFD;

    /*
     * Loop across the valid MFD and RFD settings starting with
     * the max MFD and min RFD and find the closest match less-than
     * or equal-to the desired output frequency
     */
    done = FALSE;
    for (mfd = mfd_max; mfd >= mfd_min; mfd-=2)
    {
        for (rfd = MIN_RFD; rfd < rfd_max; rfd <<= 1)
        {
            temp = fref * mfd / rfd;
            
            if (fout == temp)
            {
                /* exact match */
                done = TRUE;
                break;
            }
            if (fout > temp)
            {
                /* new upper bound for the rfd */
                rfd_max = rfd;
                /* is this the nearest match? */
                if ((rfd != 1) && ((fout - temp) < (fref / (rfd>>1))))
                    done = TRUE;
                break;
            }
        }
        if (done)
            break;
     }
    if (!done)
    {
        /* 
         * Fell out of loop before finding an exact match or getting 
         * as close as possible. Adjust mfd to nearest match.
         */
        mfd += 2;
    }
    
    fout = fref * mfd / rfd;

    /* Encode MFD and RFD settings */
    mfd = (mfd - MIN_MFD) / 2;
    for (i = 0; rfd > MIN_RFD; rfd >>= 1, i++) {};
    rfd = i;

    /*
     * Temp fix for PLL bug
     */
    (*(vuint8 *)(&__IPSBAR[0x120006])) |= 0x04;

    /* 
     * Initialize the PLL to generate the new system clock frequency 
     * A higher divider is used first with the desired MFD.  Once 
     * locked, the desired RFD is applied
     */
    syncr = MCF_CLOCK_SYNCR & ~(0x7700);
    temp = (MCF_CLOCK_SYNCR & 0x7000) >> 12;
    MCF_CLOCK_SYNCR = syncr 
        | MCF_CLOCK_SYNCR_RFD(rfd + 1)
        | MCF_CLOCK_SYNCR_MFD(temp)
        | MCF_CLOCK_SYNCR_PLLEN;
    MCF_CLOCK_SYNCR = syncr 
        | MCF_CLOCK_SYNCR_RFD(rfd + 1)
        | MCF_CLOCK_SYNCR_MFD(mfd)
        | MCF_CLOCK_SYNCR_PLLEN;
        
   	/* Wait for the PLL to lock */	
	while (!(MCF_CLOCK_SYNSR & MCF_CLOCK_SYNSR_LOCK)) {};

    /* Finish off the initialization */
    MCF_CLOCK_SYNCR = syncr
        | MCF_CLOCK_SYNCR_RFD(rfd)
        | MCF_CLOCK_SYNCR_MFD(mfd)
        | MCF_CLOCK_SYNCR_CLKSRC
        | MCF_CLOCK_SYNCR_PLLEN;

    return fout;
}

/********************************************************************/
/*
 * Initialize the Low Power Divider circuit
 * 
 * Parameters:
 *  div     Desired system frequency divider
 *
 * Return Value:
 *  The divider value applied
 *  -1 if divider was out of valid bounds
 */
int clock_lpd (int div)
{
    int i, j;

    /* Check bounds of divider */
    if ((div < MIN_LPD) || (div > MAX_LPD))
        return (1 << (MCF_CLOCK_LPDR & 0x0F));

    /* Round divider down to nearest power of two */
    for (i = 0, j = div; j != 1; j >>= 1, i++) 
    {};
    
    /* Apply the divider to the system clock */
    MCF_CLOCK_LPDR = MCF_CLOCK_LPDR_LPD(i);

    return (1 << i);
}

/********************************************************************/

/* Actual system clock frequency */
//int sys_clk_khz = SYS_CLK_KHZ;

/********************************************************************/


void mcf5213_pll_init(void) {
    /* Initialize the PLL */
    clock_pll(REF_CLK_KHZ, SYS_CLK_KHZ, 0) / clock_lpd(1);
}


/********************************************************************/

/* Enables the proper GPIO pins for UART output */

/********************************************************************/

#define TERMINAL_PORT (0)

void mcf5213_gpio_uart_init(void) {

    /* Enable the proper UART pins */
    switch (TERMINAL_PORT)
    {
        case 2:
            MCF_GPIO_PUCPAR = 0
                | MCF_GPIO_PUCPAR_URXD2_URXD2
                | MCF_GPIO_PUCPAR_UTXD2_UTXD2;
            break;
        case 1:
            MCF_GPIO_PUBPAR = 0
                | MCF_GPIO_PUBPAR_URXD1_URXD1
                | MCF_GPIO_PUBPAR_UTXD1_UTXD1;
            break;
        case 0:
        default:
            MCF_GPIO_PUAPAR = 0
                | MCF_GPIO_PUAPAR_URXD0_URXD0
                | MCF_GPIO_PUAPAR_UTXD0_UTXD0;
    }

}


/********************************************************************/
/* Allow interrupts                                                 */
/********************************************************************/
void mcf5213_allow_interrupts(void) 
{
    /* 
     * Allow interrupts from ABORT, SW1, and SW2 (IRQ[4,5,7]) 
     */
     
    /* Enable IRQ signals on the port */
    MCF_GPIO_PNQPAR = 0
        | MCF_GPIO_PNQPAR_IRQ4_IRQ4
        | MCF_GPIO_PNQPAR_IRQ5_IRQ5
        | MCF_GPIO_PNQPAR_IRQ7_IRQ7;
    
    /* Set EPORT to look for rising edges */
    MCF_EPORT_EPPAR = 0
        | MCF_EPORT_EPPAR_EPPA4_RISING
        | MCF_EPORT_EPPAR_EPPA5_RISING
        | MCF_EPORT_EPPAR_EPPA7_RISING;
        
    /* Clear any currently triggered events on the EPORT */
    MCF_EPORT_EPIER = 0
        | MCF_EPORT_EPIER_EPIE4
        | MCF_EPORT_EPIER_EPIE5
        | MCF_EPORT_EPIER_EPIE7;
        
    /* Enable interrupts in the interrupt controller */
    MCF_INTC_IMRL &= ~(0
        | MCF_INTC_IMRL_INT_MASK4 
        | MCF_INTC_IMRL_INT_MASK5 
        | MCF_INTC_IMRL_INT_MASK7 
        | MCF_INTC_IMRL_MASKALL);
}

/********************************************************************/
/* Watchdog Initialization                                             */
/********************************************************************/

void 
mcf5213_wtm_init(void)
{
}

/********************************************************************
 * MCF5xxx ASM utility functions
 */
//__declspec(register_abi) asm void mcf5xxx_wr_vbr (uint32 vbr)
//
// { /* Set VBR */
//    movec vbr,VBR
//    nop
//	rts	
//}	

/********************************************************************/
/* Stand Alone initialization                                       */
/********************************************************************/

void mcf5213_init(void)
{
	//copy interrupt vector table from ROM to RAM if FLASH target is used
	//TODO: use linker symbols instead of hardcoded addresses
	if ((uint32)_interruptVector == 0)
	{
		int n;
		int*  interruptVectorRom = (int*) 0x00000000;
		int*  interruptVectorRam = (int*) 0x20000000;
		for (n = 0; n<256; n++)
			interruptVectorRam[n] = interruptVectorRom[n];
		mcf5xxx_wr_vbr((uint32)interruptVectorRam);
	}
	else	
		mcf5xxx_wr_vbr((uint32)_interruptVector);	
	mcf5213_wtm_init();
	mcf5213_pll_init();
	mcf5213_gpio_uart_init();
	

}

