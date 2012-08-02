/*
** File:     can_mcf5213_i.c
**
** Contents: Rubus OS
**           Tutorial 
**           Target Motorola FLEXCAN
**           CAN I/O Services
**
** Copyright 1996-2011 Arcticus Systems AB
**           All Rights Reserved
**
*/

#include <basic/bs_basic.h>
#include <green/g_thread.h>
#include <hal.h>
#include <hal_mcf5213.h>
#include <can.h>
#include <can_mcf5213.h>

#ifdef _PROJECT_OS
extern void comXhpRx_entry (void);
extern void comXhpTx_entry (void);
extern void comXhpRx_handler (void);
extern void comXhpTx_handler (void);
#else
#include <rRte_Interface.h>
extern void comXhpRx_handler (rte_comXhpRx_iArgs_t const *args);
extern void comXhpTx_handler (rte_comXhpTx_iArgs_t const *args);
#endif

/********************************************************
  CAN Interrupt Handler
********************************************************/
#ifdef _PROJECT_OS
void comXhpRx_entry (void)
#else
void comXhpRx_entry (rte_comXhpRx_iArgs_t const *args)
#endif

{ 
  greenIntrDisable();
#ifdef _PROJECT_OS
  comXhpRx_handler();
#else
    comXhpRx_entry(args);
#endif
}  

/********************************************************
  CAN Interrupt Handler
********************************************************/
#ifdef _PROJECT_OS
void comXhpTx_entry (void)
#else
void comXhpTx_entry (rte_comXhpTx_iArgs_t const *args)
#endif

{ CAN_NODE_P    nP;
  uint32_t      flags;
  
  greenIntrDisable();
  nP = CAN_NODE_PTR(CAN_NODE_A);
  flags = nP->fcIFLAG;
  nP->fcIFLAG |= R_BIT(1);
#ifdef _PROJECT_OS
    comXhpTx_handler();
#else
    comXhpTx_entry(args);
#endif
}  
