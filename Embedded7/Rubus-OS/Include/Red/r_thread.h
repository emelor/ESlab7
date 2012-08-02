#ifndef  _R_THREAD_H_
#define  _R_THREAD_H_
/*
** File:     r_thread.h
**
** Contents: Rubus OS
**           Red Kernel
**           Definitions.
**
** Version:  4.1
**
** Copyright 1996-2010 Arcticus Systems AB
**           All Rights Reserved
**
*/

#ifndef _BS_BASIC_H_
#include <basic/bs_basic.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*===============================================
  Red Thread Control Block Type
===============================================*/
typedef struct {
          bsExecTime_t           execTime;
        } R_LOC_CB redThreadCB_t;

/*===============================================
  Red Thread Attribute Type
===============================================*/
typedef struct redThreadAttr_s
        { bsObject_t             object;
          redThreadCB_t         *cb;
        } redThreadAttr_t;

/*===============================================
  Red Schedule Attribute Block
===============================================*/
typedef struct redSchedAttr_s
        { bsObject_t             object;
          uint16_t               period;
          uint16_t               releaseTime;
          void                 (*entry)(void);
        } redSchedAttr_t;

/*===============================================
  Red Id Types
===============================================*/
typedef redThreadAttr_t const   *redThreadId_t;
typedef redSchedAttr_t  const   *redScheduleId_t;

/*===============================================
  Red Kernel Status Type
===============================================*/
typedef struct {
          uint16_t               redTime;
          redScheduleId_t        schedule;
          redThreadId_t          thread;
          uint_t                 lcetKernelBasic;
          uint_t                 lcetKernelPreemption;
        } redStatus_t;

/*===============================================
  Externals
===============================================*/

/*===============================================
  Prototypes
===============================================*/
extern int_t  redInit (redScheduleId_t schedule);
extern int_t  redSetSchedule (redScheduleId_t schedule);
extern int_t  redSetScheduleImmediate (redScheduleId_t schedule);
extern void   redError (int_t code, bsObject_t const *object);
extern int_t  redStackUsed (int_t *stackUsed);
extern int_t  redStatus (redStatus_t *status);
extern redThreadId_t redSelf (void);
extern uint16_t      redGetTime (void);

#ifdef __cplusplus
}
#endif
#endif
