//****************************************************************************
// This file contains the implementation of the LED-driver
// By: Jad El-khoury
// Copyright: 2006
//****************************************************************************

#include "LEDDriver.h"
#include "support_common.h"


void leds_initialise() {
	//The LEDs are configured to run on Ports UB and UC.
	
    // Enable the UB and UC ports as GPIO
    MCF_GPIO_PORTUB = 0
        | MCF_GPIO_PUBPAR_UCTS1_GPIO
        | MCF_GPIO_PUBPAR_URTS1_GPIO
        | MCF_GPIO_PUBPAR_URXD1_GPIO
        | MCF_GPIO_PUBPAR_UTXD1_GPIO;
    MCF_GPIO_PUCPAR = 0
        | MCF_GPIO_PUCPAR_UCTS2_GPIO
        | MCF_GPIO_PUCPAR_URTS2_GPIO
        | MCF_GPIO_PUCPAR_URXD2_GPIO
        | MCF_GPIO_PUCPAR_UTXD2_GPIO;

    //Set the UB and UC ports as digital outputs
    MCF_GPIO_DDRUB = 0
        | MCF_GPIO_DDRUB_DDRUB3
        | MCF_GPIO_DDRUB_DDRUB2
        | MCF_GPIO_DDRUB_DDRUB1
        | MCF_GPIO_DDRUB_DDRUB0;
    MCF_GPIO_DDRUC = 0
        | MCF_GPIO_DDRUC_DDRUC3
        | MCF_GPIO_DDRUC_DDRUC2
        | MCF_GPIO_DDRUC_DDRUC1
        | MCF_GPIO_DDRUC_DDRUC0;

    //Set output values to 0
    leds_output(0);
}

void leds_output(int number) {
	//Only the lowest byte (8 bits) of the number parameter are considered.
    MCF_GPIO_PORTUB = number;
    MCF_GPIO_PORTUC = number>>4;
}

void leds_turnON(int LEDNumber) {
	//LEDNumber ranges from 0 to 7!
	switch(LEDNumber) {
		case 0: MCF_GPIO_PORTUB |= 0b0001; break;
		case 1: MCF_GPIO_PORTUB |= 0b0010; break;
		case 2: MCF_GPIO_PORTUB |= 0b0100; break;
		case 3: MCF_GPIO_PORTUB |= 0b1000; break;
		case 4: MCF_GPIO_PORTUC |= 0b0001; break;
		case 5: MCF_GPIO_PORTUC |= 0b0010; break;
		case 6: MCF_GPIO_PORTUC |= 0b0100; break;
		case 7: MCF_GPIO_PORTUC |= 0b1000; break;
		default: break;
	}
}

void leds_turnOFF(int LEDNumber) {
	//LEDNumber ranges from 0 to 7!
	switch(LEDNumber) {
		case 0: MCF_GPIO_PORTUB &= 0b1110; break;
		case 1: MCF_GPIO_PORTUB &= 0b1101; break;
		case 2: MCF_GPIO_PORTUB &= 0b1011; break;
		case 3: MCF_GPIO_PORTUB &= 0b0111; break;
		case 4: MCF_GPIO_PORTUC &= 0b1110; break;
		case 5: MCF_GPIO_PORTUC &= 0b1101; break;
		case 6: MCF_GPIO_PORTUC &= 0b1011; break;
		case 7: MCF_GPIO_PORTUC &= 0b0111; break;
		default: break;
	}
}
