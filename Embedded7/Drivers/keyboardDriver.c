//****************************************************************************
// This file contains the implementation of the Keyboard-driver
// By: Jad El-khoury
// Copyright: 2006
//****************************************************************************

#include "keyboardDriver.h"
#include "support_common.h"

void keyboard_initialise() {
	//The keyboard is configured to run on Port NQ!
	//NQ[3...6] is the input data.
	//NQ[7] is the keyboard status

	// Enable the NQ[3...7] ports as GPIO, 
	//by settting MCF_GPIO_PNQPAR[3...7] to 0
	MCF_GPIO_PNQPAR &= 0b00000111;

	// Enable the NQ[3...7] ports as digital inputs
	MCF_GPIO_DDRNQ &=     
				~MCF_GPIO_DDRNQ_DDRNQ3 
				& ~MCF_GPIO_DDRNQ_DDRNQ4
				& ~MCF_GPIO_DDRNQ_DDRNQ5
				& ~MCF_GPIO_DDRNQ_DDRNQ6
				& ~MCF_GPIO_DDRNQ_DDRNQ7;
}

int keyboard_get_status(void) {
	// Read the port NQ[7]! return 1 if a key is pressed, otherwise 0.
	return ((MCF_GPIO_SETNQ & MCF_GPIO_SETNQ_SETNQ7) >> 7);
}

char keyboard_get_char(void) {
	//The character '!' indicates that an error occured. 
	//Most likely, since no keyboard button was pressed.
	int data;
	char c = ' ';

	if (!keyboard_get_status()) {
		return '!';	
	}
	data = ((MCF_GPIO_SETNQ & 0b01111000) >> 3);
	switch (data) {
		case 0x0000: c = '1'; break;
		case 0x0001: c = '2'; break;
		case 0x0002: c = '3'; break;
		case 0x0003: c = '!'; break;
		case 0x0004: c = '4'; break;
		case 0x0005: c = '5'; break;
		case 0x0006: c = '6'; break;
		case 0x0007: c = '!'; break;
		case 0x0008: c = '7'; break;
		case 0x0009: c = '8'; break;
		case 0x000A: c = '9'; break;
		case 0x000B: c = '!'; break;
		case 0x000C: c = '*'; break;
		case 0x000D: c = '0'; break;
		case 0x000E: c = '#'; break;
		case 0x000F: c = '!'; break;
	}
	return c;
}
