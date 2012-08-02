#ifndef  _RUBUSOS_CFG_H_
#define  _RUBUSOS_CFG_H_
/*
** File:     rubusOS_cfg.h
**
** Contents: Rubus OS
**           Generic Definitions.
**           Rubus VS Configuration
**
**           DO NOT EDIT!
**
** Version:  4-1
**
** Copyright 1996-2010 Arcticus Systems AB
**           All Rights Reserved
**
*/

#ifndef _BS_BASIC_H_
#include <basic/bs_basic.h>
#endif

#ifndef _R_THREAD_H_
#include <red/r_thread.h>
#endif

#ifndef _G_THREAD_H_
#include <green/g_thread.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*===============================================
  Basic User Attribute Type
===============================================*/
typedef struct {
          bsObject_t                  object;
        } bsUserAttr_t;

/*==========================================================
  bsIdNameTable
==========================================================*/
typedef struct {
          bsName_t                    name;
          int_t                       length;
        } bsIdNameElement_t;


/*===============================================
  Log Object array Type
===============================================*/
typedef uint8_t R_LOC_CB bsLogIdArray_t;

/*===============================================
  Basic Attribute Type
===============================================*/
typedef struct bsAttr_s
        { bsObject_t                  object;
          uint32_t                    timerBasicFrequency;
          uint32_t                    timerBasicResNSec;
          uint32_t                    timerExecResPSec;
          uint32_t                    timerGenericResPSec;
          uint_t                      basicTimerPriority;
          uint_t                      timeAdjBasic;
          int_t                       idEntries;
          bsLogIdArray_t             *logIdArray;
          bsObject_t const * const   *idTable;
          bsIdNameElement_t const    *nameTable;
          char_t const * const       *labelOS;
          char_t const * const       *labelCoder;
          char_t const * const       *labelDate;
          char_t const * const       *labelIdentifier;
        } bsAttr_t;

/*===============================================
  Green Kernel Attribute Type
===============================================*/
typedef struct 
        { bsObject_t                  object;
          uint_t                      ceilingPrio;
        } greenAttr_t;
  
/*===============================================
  Red Element Stack Frame
===============================================*/
typedef struct redFrameCB_s {
          uint_t                      deadline;
          redThreadId_t	              execThread;
        } redFrameCB_t;

/*===============================================
  Red Attribute
===============================================*/
typedef struct
        { bsObject_t                  object;
          int_t                       preemptionLevels;
          bsThread_t                  entry;
          int_t                       stackSize;
          bsStack_t                  *stack;
          redFrameCB_t R_LOC_VAR     *top;
          redFrameCB_t R_LOC_VAR     *bottom;
        } redAttr_t;

/*===============================================
  Red Dispatch Variables
===============================================*/
typedef struct redDispatchVar_s {
          uint16_t                    releaseTime;
          redFrameCB_t R_LOC_VAR     *stackFrame;
          void                      (*nextToRun)(void);
        } redDispatchVar_t;

/*===============================================
  Red Dispatch Defines
===============================================*/
#define R_RED_NEXT(entry,release)   { redDispatchVar.releaseTime = release; \
                                      redDispatchVar.nextToRun   = entry; }

#define R_RED_SET_DEADLINE(thread,dline) \
                                    { redDispatchVar.stackFrame->deadline   = dline; \
                                      redDispatchVar.stackFrame->execThread = thread; }

/*===============================================
  Blue Kernel Attribute Type
===============================================*/
typedef struct blueAttr_s 
        { bsObject_t              object;
          int_t                   stackSize;
          bsStack_t              *stack;
          uint_t                  timeAdjPreemption;
        } blueAttr_t;

/*===============================================
  Externals
===============================================*/
extern bsAttr_t const             bsAttr;
extern redDispatchVar_t R_LOC_VAR redDispatchVar;
extern blueAttr_t const           blueAttr;
extern redAttr_t const            redAttr;

/*===============================================
  Prototypes
===============================================*/
extern int_t  bsInit (void);
extern int_t  blueInit (void);
extern int_t  blueMsgInitAll (void);
extern int_t  blueMutexInitAll (void);
extern int_t  blueSemInitAll (void);
extern int_t  blueThreadInitAll (void);
extern int_t  bsMailboxInitAll (void);
extern int_t  bsPoolInitAll (void);
extern int_t  bsQueueInitAll (void);
extern void   greenEnter(void);
extern void   greenExit (void);


#ifdef __cplusplus
}
#endif
#endif

