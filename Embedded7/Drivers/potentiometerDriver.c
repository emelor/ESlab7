/**************************
	UNDER DEVELOPMENT
***************************/

//****************************************************************************
// This file contains the implementation of the potentiometer-driver
// By: Jad El-khoury
// Copyright: 2006
//****************************************************************************

#include "potentiometerDriver.h"
#include "support_common.h"
#include <stdio.h>
#include "interruptRoutines.h"

//IS THIS THE CORRECT WAY TO LIMIT THIS GLOBAL VARIALBE TO THIS FILE?
static int potentimeterValue;

__declspec(interrupt) void potentiometer_handler(void) {
	potentimeterValue = (MCF_ADC_ADRSLT(0))>>3;
	//printf("Data:%d\n\r", potentimeterValue);	
	//fflush(stdout);
    MCF_ADC_ADSTAT = MCF_ADC_ADSTAT_EOSI0;
}

//****************************************************************************
// @Function      int potentiometer_initialise(int interruptLevel, int interruptPriority)
//
//----------------------------------------------------------------------------
// @Description   This function initializes the potentiometer.
//		if the interruptLevel > 7 || interruptLevel < 1, then return 0
//		if the interruptPriority > 7 || interruptLevel < 0, then return 0
//****************************************************************************
int potentiometer_initialise(int interruptLevel, int interruptPriority)
{
	//The potentiometer is configured to run on Pin AN[0]!

	if ((interruptLevel>7) || (interruptLevel<1) || (interruptPriority>7) || (interruptPriority<0)) 
	{
		return 0;
	}
	
	potentimeterValue = 0;
	
    /* set pin An[0] function to ADC */
	MCF_GPIO_PANPAR |= 0b00000001;

	//Set SYNC0=0
	MCF_ADC_CTRL1 &= ~MCF_ADC_CTRL1_SYNC0;
	//Set STOP0=0
	MCF_ADC_CTRL1 &= ~MCF_ADC_CTRL1_STOP0;
	//Set the scan to "loop sequential"
	MCF_ADC_CTRL1 = ((MCF_ADC_CTRL1 >>3)<<3) | MCF_ADC_CTRL1_SMODE(0b010);
	
	//Enable an interrupt upon completion of a scan
	MCF_ADC_CTRL1   |= MCF_ADC_CTRL1_EOSIE0;

	/* set to 4 MHZ the sampling according to table*/
    MCF_ADC_CTRL2   = MCF_ADC_CTRL2_DIV(9);

	/* Set the sampling order for the channels.
	We only want to scan pin AN[0] at SAMPLE0*/
    MCF_ADC_ADLST1	= MCF_ADC_ADLST1_SAMPLE0(0);
    				  
    /* Only enable SAMPLE0 defined in MCF_ADC_ADLST1*/
    MCF_ADC_ADSDIS  = 0b11111110;
    
    /* set the power-up delay in ADC */
    MCF_ADC_POWER   = 0x00D0; //Delay in the POWER Reg by reset

    /* wait until module is powered-up */
    while(MCF_ADC_POWER & MCF_ADC_POWER_PSTS0);
    
	//Setup the interrupt registers for ADC
	MCF_INTC_IMRH &= ~ MCF_INTC_IMRH_INT_MASK49;
	MCF_INTC_ICR(49) = MCF_INTC_ICR_IP(interruptPriority) | MCF_INTC_ICR_IL(interruptLevel);
    mcf5xxx_set_handler(64 + 49, potentiometer_handler);
//	mcf5xxx_irq_enable();
    
    return 1;
}


//****************************************************************************
// @Function      void potentiometer_start(void)
//
//----------------------------------------------------------------------------
// @Description   This function starts the potentiometer loop reading
//
//****************************************************************************
void potentiometer_start(void)
{
	//Clear the STOP0 bit first
	MCF_ADC_CTRL1 &= ~MCF_ADC_CTRL1_STOP0;
	//Then, start the ADC
	MCF_ADC_CTRL1 |= MCF_ADC_CTRL1_START0;
	return;
}

//****************************************************************************
// @Function      void potentiometer_stop(void)
//
//----------------------------------------------------------------------------
// @Description   This function stops the potentiometer loop reading
//
//****************************************************************************
void potentiometer_stop(void)
{
	//Stop the ADC
	MCF_ADC_CTRL1 |= MCF_ADC_CTRL1_STOP0;
	return;
}


//****************************************************************************
// @Function      int potentiometer_read(void)
//
//----------------------------------------------------------------------------
// @Description   This function initializes the LEDs.
//	Read the latest read potentiometer value.
//****************************************************************************
int potentiometer_read(void)
{
	return potentimeterValue;
}

