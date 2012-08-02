/*
** File:     can_mcf5213_isr.c
**
** Contents: Rubus OS
**           Tutorial 
**           CAN Device
**           FlexCan Services
**
** Copyright 1996-2011 Arcticus Systems AB
**           All Rights Reserved
**
*/

#include <basic/bs_basic.h>
#include <hal.h>
#include <can.h>
#include <can_mcf5213.h>

#ifdef _PROJECT_OS
#include <r_ex_g.h>
#else
#include <rRte_Interface.h>
#endif

void canISR_Msg0(void);
void canISR_Msg1(void);

/********************************************************
  CAN Interrupt Service
********************************************************/

__declspec(interrupt)
void canISR_Msg0(void)
{
#ifdef _PROJECT_OS
  comXhpRx.entry(comXhpRx.argument);
#else
  RTE_IT_ENTRY_Int_IrqRx(0);
#endif
}  

/********************************************************
  CAN Interrupt Service
********************************************************/
__declspec(interrupt)
void canISR_Msg1(void)
{
#ifdef _PROJECT_OS
  comXhpTx.entry(comXhpTx.argument);
#else
  RTE_IT_ENTRY_Int_IrqTx(0);
#endif
}  

