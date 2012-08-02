/*
** FILE    : hal_timer.c
** CONTENTS: Rubus OS
**           Tutorial
**           Target MCF
**           HAL Timer Services
**
** Copyright 1996-2011 Arcticus Systems AB
**           All Rights Reserved
*/
 
#include <basic/bs_basic.h>
#include <blue/b_signal.h>
#include <r_ex_bs.h>

#include <hal.h>
#include <hal_mcf5213.h>

#include "mcf5213_pit.h"

typedef struct {
  union {
  	uint32_t u32;
  	uint16_t u16[2];
  } u;
} halTimerType_t;

/*===============================================
  Externals
===============================================*/
extern void halBsTimerIntrEntry (void);	
extern void rubusISR_Timer (void);

/*===============================================
  Variables
===============================================*/
vuint32_t      halTimerAdjustment;
halTimerType_t halTimerExt;
 
/************************************************
 halBsFreeRunTimerGet()
*************************************************/
uint32_t halBsFreeRunTimerGet (void)

{ uint16_t tvl;

  tvl = (uint16_t)~MCF_PIT1_PCNTR;
  return(tvl);
}

/************************************************
 halBsExecTimeStart()
*************************************************/
uint_t halBsExecTimeStart (void)

{ halTimerType_t tvu;
  
  tvu.u.u16[0] = halTimerExt.u.u16[0];
  tvu.u.u16[1] = (uint16_t)~MCF_PIT1_PCNTR;
  tvu.u.u32 = tvu.u.u32 - halTimerAdjustment;
  return(tvu.u.u32);
}

/************************************************
 halBsExecTimeStop()
*************************************************/
uint_t halBsExecTimeStop (uint_t value, uint_t adjust)

{ halTimerType_t tvu;
  uint_t         et;

  tvu.u.u16[0] = halTimerExt.u.u16[0];
  tvu.u.u16[1] = (uint16_t)~MCF_PIT1_PCNTR;

  tvu.u.u32 = tvu.u.u32 - value;
  et  = (tvu.u.u32 - halTimerAdjustment);
  halTimerAdjustment = (tvu.u.u32 + adjust);
  return(et);
}

/************************************************
 halBsExecTimeGet()
*************************************************/
uint_t halBsExecTimeGet (void)

{ 
  return(halTimerAdjustment);
}

/************************************************
 halBsExecTimeResume()
*************************************************/
void halBsExecTimeResume (uint_t value, uint_t adjust)

{ 
  halTimerAdjustment = value + adjust;
}

/************************************************
 halBsTimerStart()
*************************************************/
void halBsTimerStart(void)

{ uint32_t reload;
  uint8_t    prio;
  
  halTimerAdjustment = 0;
  halTimerExt.u.u32 = 0;

  reload = (bsAttr.timerBasicResNSec * SYSTEM_CLOCK) / (1 << (7 + 1));
  reload = reload / 1000;         /* Round up microsec*/

  prio = (uint8_t)bsAttr.basicTimerPriority;

  MCF_INTC_ICR55 = (uint8_t)(MCF_INTC_ICR_IL(prio) | MCF_INTC_ICR_IP(0)); // Set PIT0 interrupt level
  MCF_INTC_IMRH &= ~MCF_INTC_IMRH_INT_MASK55; // Enable the PIT0 interrupt
  MCF_INTC_IMRL &= ~MCF_INTC_IMRL_MASKALL; // Enable interrupts

  MCF_PIT0_PCSR = MCF_PIT_PCSR_PRE(7) | MCF_PIT_PCSR_RLD | MCF_PIT_PCSR_DBG  | MCF_PIT_PCSR_OVW;
  MCF_PIT0_PMR  = (uint16_t)reload;
  MCF_PIT0_PCSR &= ~MCF_PIT_PCSR_OVW;
  MCF_PIT0_PCSR |= MCF_PIT_PCSR_EN;

  MCF_PIT1_PCSR = MCF_PIT_PCSR_PRE(7) | MCF_PIT_PCSR_OVW;
  MCF_PIT1_PMR  = 0xffff;
  MCF_PIT1_PCSR |= MCF_PIT_PCSR_EN;

/*
  MCF_PIT2_PCSR = MCF_PIT_PCSR_PRE(7) | MCF_PIT_PCSR_OVW;
  MCF_PIT2_PMR  = 0xffff;
  MCF_PIT2_PCSR |= MCF_PIT_PCSR_EN;
*/

  halBsTimerEnable();

}

/************************************************
 halBsTimerStop()
*************************************************/
void halBsTimerStop(void)

{
  MCF_INTC_IMRH |= MCF_INTC_IMRH_INT_MASK55; // Disable the PIT0 interrupt
  MCF_PIT0_PCSR = 0;
}

/************************************************
 halBsTimerDisable()
*************************************************/
void  halBsTimerDisable(void)

{
  asm 
  {
    strldsr   #0x2700
    move.w    MCF_PIT0_PCSR,d0
    and.l     #~MCF_PIT_PCSR_PIE,d0
    move.w    d0,MCF_PIT0_PCSR
    move.l    (a7)+,d0
    move.w    d0,sr
  }

//   MCF_PIT0_PCSR &= ~MCF_PIT_PCSR_PIE;
}

/************************************************
 halBsTimerEnable()
*************************************************/
void  halBsTimerEnable(void)

{
  asm 
  {
    strldsr   #0x2700
    move.w    MCF_PIT0_PCSR,d0
    or.l      #MCF_PIT_PCSR_PIE,d0
    move.w    d0,MCF_PIT0_PCSR
    move.l    (a7)+,d0
    move.w    d0,sr
  }

//  MCF_PIT0_PCSR |= MCF_PIT_PCSR_PIE;
}


/************************************************
 rubusISR_Timer()
*************************************************/
__declspec(interrupt) void rubusISR_Timer (void)
{

// Clear PIT0 pending interrupt flag 
  MCF_PIT0_PCSR |= MCF_PIT_PCSR_PIF;
  
  if (halTimerExt.u.u16[1] < MCF_PIT1_PCNTR) {
    halTimerExt.u.u16[0]++;	
  }
  halTimerExt.u.u16[1] = MCF_PIT1_PCNTR;

  halBsTimerIntrEntry();	
}
