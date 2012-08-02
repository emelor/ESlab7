#ifndef  _G_THREAD_H_
#define  _G_THREAD_H_
/*
** File:     g_thread.h
**
** Contents: Rubus OS
**           Basic Services
**           Green Definitions.
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
  Green Thread Control Block Type
===============================================*/
typedef struct
        { bsExecTime_t             execTime;
          uint_t                   counter;
        } R_LOC_CB greenThreadCB_t;

/*===============================================
  Green Thread Attribute Type
===============================================*/
typedef struct greenThreadAttr_s
        { bsObject_t               object;
          greenThreadCB_t         *cb;
          uint_t                   priority;
          uint_t                   adjustment;
          bsThread_t               entry;
          bsThreadArg_t            argument;
        } greenThreadAttr_t;

/*===============================================
  Basic Id Types
===============================================*/
typedef greenThreadAttr_t const *greenThreadId_t;

/*===============================================
  Externals
===============================================*/

/*===============================================
  Prototypes
===============================================*/
extern int_t greenInit (void);
extern void  greenError (int_t code, bsObject_t const * object);
extern void  greenIntrDisable (void);
extern void  greenIntrEnable  (void);
extern R_TYPE_GREEN_LEVEL greenIntrSuspend (void);
extern void               greenIntrResume  (R_TYPE_GREEN_LEVEL level);

#ifdef __cplusplus
}
#endif
#endif


