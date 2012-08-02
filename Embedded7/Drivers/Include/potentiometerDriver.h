/**************************
	UNDER DEVELOPMENT
***************************/

#ifndef POTENTIOMETERDRIVER_H
#define POTENTIOMETERDRIVER_H

//****************************************************************************
// @Function      int potentiometer_initialise(int interruptLevel, int interruptPriority)
//
//----------------------------------------------------------------------------
// @Description   This function initializes the potentiometer.
//		if the interruptLevel > 7 || interruptLevel < 1, then return 0
//		if the interruptPriority > 7 || interruptLevel < 0, then return 0
//****************************************************************************
int potentiometer_initialise(int interruptLevel, int interruptPriority);

//****************************************************************************
// @Function      void potentiometer_start(void)
//
//----------------------------------------------------------------------------
// @Description   This function starts the potentiometer loop reading
//
//****************************************************************************
void potentiometer_start(void);

//****************************************************************************
// @Function      void potentiometer_stop(void)
//
//----------------------------------------------------------------------------
// @Description   This function stops the potentiometer loop reading
//
//****************************************************************************
void potentiometer_stop(void);

//****************************************************************************
// @Function      int potentiometer_read(void)
//
//----------------------------------------------------------------------------
// @Description   This function initializes the LEDs.
//	Read the latest read potentiometer value.
//****************************************************************************
int potentiometer_read(void);

#endif