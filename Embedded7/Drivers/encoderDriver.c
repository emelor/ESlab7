//****************************************************************************
// This file contains the implementation of the encoder-driver
// By: Jad El-khoury
// Copyright: 2006
//****************************************************************************

#include "encoderDriver.h"
#include "support_common.h"
#include <stdio.h>
#include "interruptRoutines.h"

static int ed_direction1; 
static int ed_direction2; 
static long int ed_lastCounter1;
static long int ed_lastCounter2;

__declspec(interrupt) void direction1_handler(void) {
	long int counter;

	//Read and reset the counter ASAP, so that it can start counting in the right direction
	counter = (long int) MCF_DTIM_DTCN(2);	//Read the encoder counter

	MCF_DTIM_DTCN(2) = 0;		//Reset the encorder counter

	//Update the lastCounter so that it contains the correct encoder counter
	//Toggle the direction since we know we had a direction change.
	ed_lastCounter1 = ed_lastCounter1 + ed_direction1*counter;
	ed_direction1 = -1*ed_direction1;

	//printf("Direction1 has changed:%i\n", ed_direction1);	
	//fflush(stdout);

	MCF_DTIM_DTER(3) |= MCF_DTIM_DTER_CAP;
}

__declspec(interrupt) void direction2_handler(void) {
	long int counter;

	//Read and reset the counter ASAP, so that it can start counting in the right direction
	counter = (long int) MCF_DTIM_DTCN(0);	//Read the encoder counter

	MCF_DTIM_DTCN(0) = 0;		//Reset the encorder counter

	//Update the lastCounter so that it contains the correct encoder counter
	//Toggle the direction since we know we had a direction change.
	ed_lastCounter2 = ed_lastCounter2 + ed_direction2*counter;
	ed_direction2 = -1*ed_direction2;

//	printf("Direction2 has changed:%i\n", ed_direction2);	
//	fflush(stdout);

	MCF_DTIM_DTER(1) |= MCF_DTIM_DTER_CAP;
}


void encoders_initialise()
{
//WHAT PRIORITY TO RUN THE INTERRUPTS ON????
	//The encoders are configured to run on Ports TC[0] & TC[2]!
	//The directions are configured to run on Ports PTC[1] & PTC[3]
	//Motor1 uses TC[2] & TC[3]
	//Motor2 uses TC[0] & TC[1]

	//First, set the pins TC[1] & TC[3] pins as GPIO to read what the state of this pins are.
	//This is then used to set the initial value of the direction variable.
    MCF_GPIO_PTCPAR &= 
    				  ~MCF_GPIO_PTCPAR_DTIN1_GPIO 
    				& ~MCF_GPIO_PTCPAR_DTIN3_GPIO; 
    MCF_GPIO_DDRTC &= ~MCF_GPIO_DDRTC_DDRTC1 & ~MCF_GPIO_DDRTC_DDRTC3;
    
    //Read the encoder1 direction
    if (((MCF_GPIO_SETTC & MCF_GPIO_SETTC_SETTC3) >> 3))
    	ed_direction1 = 1;
    else
    	ed_direction1 = -1;
 
    //Read the encoder2 direction
    if (((MCF_GPIO_SETTC & MCF_GPIO_SETTC_SETTC1) >> 1))
    	ed_direction2 = 1;
    else
    	ed_direction2 = -1;
    
    ed_lastCounter1 = 0;
    ed_lastCounter2 = 0;

    // Enable the encoders pins TC[0] & TC[2] as TIN
    // Enable the directions pins TC[1] & TC[3] as TIN
    MCF_GPIO_PTCPAR = 0
    				| MCF_GPIO_PTCPAR_DTIN0_DTIN0
    				| MCF_GPIO_PTCPAR_DTIN1_DTIN1 
    				| MCF_GPIO_PTCPAR_DTIN2_DTIN2
    				| MCF_GPIO_PTCPAR_DTIN3_DTIN3; 

	//For the encoders, set the timers' input clock source to be DTIN[0] & DTIN[2] pin
	MCF_DTIM_DTMR(0) = 	
		MCF_DTIM_DTMR_PS(0x00)
		| MCF_DTIM_DTMR_CE_RISE	
		| MCF_DTIM_DTMR_CLK_DTIN
		| MCF_DTIM_DTMR_RST;
	MCF_DTIM_DTMR(2) = 	
		MCF_DTIM_DTMR_PS(0x00)
		| MCF_DTIM_DTMR_CE_RISE	
		| MCF_DTIM_DTMR_CLK_DTIN
		| MCF_DTIM_DTMR_RST;
		
	//For the directions, set the timers' input clock source to be the system clock.
	//Set the Capture Edge pin (CE) to capture on any edge. 
	//This will trigger an event whenever the direction changes.
	//The DTIN[1] & DTIN[3] pins will be used to capture the clock source.
	//This will trigger an interrupt that we will use to detect a direction change.
	MCF_DTIM_DTMR(1) = 	
		MCF_DTIM_DTMR_PS(0x00)
		| MCF_DTIM_DTMR_CE_ANY	
		| MCF_DTIM_DTMR_CLK_DIV1
		| MCF_DTIM_DTMR_RST;
	MCF_DTIM_DTMR(3) = 	
		MCF_DTIM_DTMR_PS(0x00)
		| MCF_DTIM_DTMR_CE_ANY	
		| MCF_DTIM_DTMR_CLK_DIV1
		| MCF_DTIM_DTMR_RST;
		
	//Setup the interrupt registers for DTIN[1] & DTIN[3]
	MCF_INTC_IMRL &= ~MCF_INTC_IMRL_MASKALL
						& ~MCF_INTC_IMRL_INT_MASK20 
						& ~MCF_INTC_IMRL_INT_MASK22;
	MCF_INTC_ICR(20) = MCF_INTC_ICR_IP(4) | MCF_INTC_ICR_IL(4);
	MCF_INTC_ICR(22) = MCF_INTC_ICR_IP(4) | MCF_INTC_ICR_IL(4);
    mcf5xxx_set_handler(64 + 22, direction1_handler);
    mcf5xxx_set_handler(64 + 20, direction2_handler);
//	mcf5xxx_irq_enable();
}

long int encoder1_read(void)
{
	return ed_lastCounter1 + ed_direction1*MCF_DTIM_DTCN(2);
}
long int encoder2_read(void)
{
	return ed_lastCounter2 + (long int)ed_direction2*MCF_DTIM_DTCN(0);
}

void encoder1_reset()
{
	MCF_DTIM_DTCN(2)=0;
	ed_lastCounter1 = 0;
}
void encoder2_reset()
{
	MCF_DTIM_DTCN(0)=0;
	ed_lastCounter2 = 0;
}


int encoder1_direction(void)
{
	return ed_direction1;
}
int encoder2_direction(void)
{
	return ed_direction2;
}

