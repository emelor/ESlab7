#ifndef _HAL_H_
#define _HAL_H_
/*
** File:     hal.h
**
** Contents: Rubus OS
**           Tutorial 
**           MCF52xx
**           HAL Definitions
**
** Copyright 1996-2011 Arcticus Systems AB
**           All Rights Reserved
**
*/


#ifdef _MCF5213
#include <hal_mcf5213.h>
#endif

#ifdef _MCF5282
#include <hal_mcf5282.h>
#endif

/*==============================================
  Simulator Idle definition
===============================================*/
#define  SIM_RED_IDLE         
#define  SIM_BLUE_IDLE        
#define  SIM_RED_LOOP         

/*===============================================
  BIT Macro
===============================================*/
#define R_BIT(bit) (1 << bit)


/*===============================================
  Prototypes
===============================================*/
extern int_t  halStartupStackUsed(void);

extern void   halExit (void);
extern int_t  halInit (void);
extern int_t  halStart (void);
extern void   halHalt (void);
extern void   halIoNotify (void);
extern void   halDestroy (void);

extern uint32_t halUserStackUsed(void);
extern uint32_t halUserStackSize(void);



#endif

