#ifndef ENCODERDRIVER_H
#define ENCODERDRIVER_H

/**********************************************************************************
This driver handles the two encoders provided in the test rig for the course 4F1908.
The encoders differ in their resolution.
This driver however only deals with the pulses received and 
does not try to compensate for the different resolutions.
***********************************************************************************/

//Initialise the encoders
void encoders_initialise();

//Returns the encoder counter value.
long int encoder1_read(void);
long int encoder2_read(void);

//Resets the encoder counter value.
void encoder1_reset();
void encoder2_reset();

#endif