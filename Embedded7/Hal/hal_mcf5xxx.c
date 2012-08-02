/*
** FILE    : hal_mcf52xx.c
** CONTENTS: Rubus OS
**           Tutorial
**           Target MCF52xx
**           HAL functions
**
** Copyright 1996-2011 Arcticus Systems AB
**           All Rights Reserved
*/
 
#include <basic/bs_basic.h>
#include <green/g_thread.h>
#include "hal.h"
#include <ros_xhp.h>
#include <hal.h>

#ifdef _CALIBRATION
extern int_t  halCalInit (void);

#else
#include <hal_io.h>
#include <hal_xhp.h>
#endif

/*===============================================
  Externals
===============================================*/
extern uint_t  __SP_INIT;
extern uint_t  __SP_END;


/************************************************
 FUNCTION: halUserStackUsed()
 Count size of boot stack used.
*************************************************/
uint32_t halUserStackUsed(void)

{ uint_t     *cp;
  int_t       i;

  cp = &__SP_END;
  i  = (&__SP_INIT - &__SP_END);
  for (;i > 0; i--, cp++) {
    if (*(cp) != 0xaaaaaaaa)
      break;  
  }
  return((uint16_t)i * sizeof(uint_t));
}
 
/************************************************
 FUNCTION: halUserStackSize()
 Return size of boot stack.
*************************************************/
uint32_t halUserStackSize(void)

{ int_t tmp;
  tmp = (&__SP_INIT-&__SP_END);
  return((uint16_t)tmp*sizeof(int_t));
}
 
/************************************************
 halInit()
 Initiate the Base System
*************************************************/
int_t halInit(void)

{
  
  return(ioInit());
}
 
 /************************************************
 halStart()
*************************************************/
int_t halStart(void)

{
#ifdef _PROJECT_OS
#ifdef _CALIBRATION
  halCalInit();
  return (R_OK);
#else
#ifndef _NO_XHP
  return (xhpHandler_osInit());
#endif
#endif
#else
  return(R_OK);
#endif
}

/************************************************
 halDestroy()
 Destroy all devices.
*************************************************/
void halDestroy(void)

{
  greenIntrDisable();
  halBsTimerStop();
}

/************************************************
 halHalt()
 Forces the system into a infinite loop
*************************************************/
void halHalt(void)

{ uint32_t loop = 0;

  halDestroy();
  for (;;) {
    loop++;
  }
}

/************************************************
 halExit()
*************************************************/
void halExit(void)

{
  halBsTimerStop();
}

/************************************************
 halIoNotify()
 Notify program is running
*************************************************/
void halIoNotify (void)

{
}


