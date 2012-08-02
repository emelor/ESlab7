#ifndef KEYBOARDDRIVER_H
#define KEYBOARDDRIVER_H

//IMPORTANT: This keyboard is configured to run on Port NQ! 
//The 4 switches (Reset, Abort, sw1 & sw2) on the evaluation board 
//are also configured to use some pins of this port, namely NQ[4,5,7].
//(See the evbDriver.h header file.)
//It is hence not possible to use both the keyboard and the switches simultaneously.

//This function initialises the keyboard.
void keyboard_initialise();

//This function gets the status of the keyboard.
//Return 1 if a key is pressed, otherwise 0.
int keyboard_get_status(void);

//This function tries to read the pressed button from the keyboard.
//It returns the character corresponding to the pressed button.
//The character '!' indicates that an error occured, 
//most likely, since no keyboard button was pressed. (!keyboard_get_status())
char keyboard_get_char(void);

#endif
