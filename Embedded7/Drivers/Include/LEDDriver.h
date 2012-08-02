#ifndef LEDDRIVER_H
#define LEDDRIVER_H

#include "LEDDriver.h"
//#include "support_common.h"

//This function initializes the LEDs.
void leds_initialise();

//Outputs the parameter 'number' to the LEDs.
//Only the lowest byte (8 bits) of the number parameter are considered.
void leds_output(int number);

//Turn ON the LED LEDNumber; where LEDNumber ranges from 0 to 7.
void leds_turnON(int LEDNumber);

//Turn ON the LED LEDNumber; where LEDNumber ranges from 0 to 7.
void leds_turnOFF(int LEDNumber);


    
#endif
