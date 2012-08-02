#ifndef  _B_SEM_H_
#define  _B_SEM_H_
/*
** File:     b_sem.h
**
** Contents: Rubus OS
**           Blue Kernel
**           Semaphore Definitions.
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

#ifndef _B_THREAD_H_
#include <blue/b_thread.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*===============================================
  Semaphore Definitions
===============================================*/
#define R_BLUE_SEM_VALUE_LOCKED         1
#define R_BLUE_SEM_VALUE_FREE           0
#define R_BLUE_SEM_VALUE_MAX            1

/*===============================================
  Semaphore Control Block Type
===============================================*/
typedef struct blueSemCB_s
        { blueCBHeader_t                  header;
          uint_t                          flags;
          int_t                           value;
          struct blueSemCB_s R_LOC_CB   *self;
        } R_LOC_CB blueSemCB_t;
 
/*===============================================
  Semaphore Attribute Type
===============================================*/
typedef struct blueSemAttr_s
        { bsObject_t       object;
          blueSemCB_t     *cb;
          uint_t           value;
        } blueSemAttr_t;

/*===============================================
  Semaphore Id Type
===============================================*/
typedef blueSemAttr_t const *blueSemId_t;

/*===============================================
  Prototypes
===============================================*/
extern int_t  blueSemInit (blueSemId_t sem, uint_t value);
extern int_t  blueSemDestroy (blueSemId_t sem);
extern int_t  blueSemTryLock (blueSemId_t sem);
extern int_t  blueSemTimedLock (blueSemId_t sem, int32_t *timeout);
extern int_t  blueSemUnlock (blueSemId_t sem);

#ifdef __cplusplus
}
#endif
#endif

