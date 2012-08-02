#ifndef  _B_THREAD_H_
#define  _B_THREAD_H_
/*
** File:     b_thread.h
**
** Contents: Rubus OS
**           Blue Kernel
**           Blue Thread Management Definitions.
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
  Blue State Flags
===============================================*/
#define _R_STATE_DEAD                    0x00u /* Terminated or not initialised */
#define _R_STATE_BLOCKED                 0x10u /* Blocked waiting for signal */
#define _R_STATE_READY                   0x20u /* Ready for execution*/
#define _R_STATE_RUNNING                 0x40u /* Running */

/*===============================================
  Blue Thread Priorities
===============================================*/
#define R_THREAD_PRIO_MIN                0u
#define R_THREAD_PRIO_MAX                15u

/*===============================================
  Blue Thread Queued Activation limit 
===============================================*/
#define R_THREAD_ACTIVATION_MAX          255u

/*===============================================
  Signal Type
===============================================*/
typedef uint_t                           blueSigSet_t;

/*===============================================
  Double Link structure
===============================================*/
typedef struct blueLinkD_s
        { struct blueLinkD_s R_LOC_CB    *next;
          struct blueLinkD_s R_LOC_CB    *prev;
        } blueLinkD_t;

/*===============================================
  Single Link structure
===============================================*/
typedef struct blueLinkS_s
        { struct blueLinkS_s R_LOC_CB    *next;
        } blueLinkS_t;

/*===============================================
  Blue Control Block Header
===============================================*/
typedef struct blueCBHeader_s
        { blueLinkD_t                     link;
          bsObject_t const               *attr;
        } blueCBHeader_t;
 
/*===============================================
  State Type
===============================================*/
typedef struct 
        { uint8_t                         state;
          uint8_t                         preempted;
          uint8_t                         priority;
          uint8_t                         activationCnt;
        } blueThreadState_t;

/*===============================================
  Blue Thread Dynamic Type
===============================================*/
typedef struct blueThreadCB_s
        { blueCBHeader_t                  header;
          blueThreadState_t               state;
          int_t                           preemption;
          blueSigSet_t                    sigBlocked;
          blueSigSet_t                    sigPending;
          blueSigSet_t                    intPending;
          blueCBHeader_t R_LOC_CB        *blockedOn;
          blueLinkD_t                     blockLink;
          int32_t                         expirationTime;
          R_TYPE_STACK_PTR                stackPtr;
          bsExecTime_t                    execTime;
          R_TYPE_BLUE_THREAD_EXTENSION
          struct blueThreadCB_s R_LOC_CB *self;
        } R_LOC_CB blueThreadCB_t;

/*===============================================
  Blue Thread Attribute Type
===============================================*/
typedef struct blueThreadAttr_s
        { bsObject_t            object;
          blueThreadCB_t       *cb;
          uint8_t               priority;
          bsThread_t            entry;
          bsThreadArg_t         argument;
          int_t                 stackSize;
          bsStack_t            *stack;
          R_TYPE_BLUE_THREAD_EXTENSION
        } blueThreadAttr_t;

/*===============================================
  Thread Id Type
===============================================*/
typedef blueThreadAttr_t const *blueThreadId_t;

/*===============================================
  Prototypes
===============================================*/
extern void   blueError(int_t code, bsObject_t const *object);
extern int_t  blueCreate(blueThreadId_t thread);
extern int_t  blueExit(void);
extern int_t  blueYield(void);
extern void   bluePreemptionLock(void);
extern void   bluePreemptionUnlock(void);
extern int_t  blueClockGetTime(int32_t *tp);
extern int_t  blueStackUsed (int_t *stackUsed);
extern int_t  blueThreadStackUsed (blueThreadId_t thread, int_t *stackUsed);
extern blueThreadId_t blueSelf(void);

#ifdef __cplusplus
}
#endif
#endif
