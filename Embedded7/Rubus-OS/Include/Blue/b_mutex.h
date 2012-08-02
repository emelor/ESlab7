#ifndef  _B_MUTEX_H_
#define  _B_MUTEX_H_
/*
** File:     b_mutex.h
**
** Contents: Rubus OS
**           Blue Kernel
**           Mutex Definitions.
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
  Mutex Dynamic Type
===============================================*/
typedef struct blueMutexCB_s
        { blueCBHeader_t                  header;
          uint_t                          flags;
          uint8_t                         prio;
          blueThreadCB_t                *owner;
          struct blueMutexCB_s R_LOC_CB *self;
        } R_LOC_CB blueMutexCB_t;

/*===============================================
  Mutex Attribute Type
===============================================*/
typedef struct blueMutexAttr_s
        { bsObject_t       object;
          blueMutexCB_t   *cb;
          uint8_t          ceilingPrio;
        } blueMutexAttr_t;

/*===============================================
  Mutex Id Type
===============================================*/
typedef blueMutexAttr_t const *blueMutexId_t;

/*===============================================
  Prototypes
===============================================*/
extern int_t  blueMutexInit (blueMutexId_t mutex);
extern int_t  blueMutexDestroy (blueMutexId_t mutex);
extern int_t  blueMutexTryLock (blueMutexId_t mutex);
extern int_t  blueMutexTimedLock (blueMutexId_t mutex, int32_t *timeout);
extern int_t  blueMutexUnlock (blueMutexId_t mutex);


#ifdef __cplusplus
}
#endif
#endif

