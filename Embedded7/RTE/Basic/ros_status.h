#ifndef  _ROS_STATUS_H_
#define  _ROS_STATUS_H_
/*
** File:     ros_status.h
**
** Contents: Rubus OS
**           Rubus RTE 
**           Rubus OS Status 
**
** Version:  1.0
**
** Copyright 1996-2011 Arcticus Systems AB, All Rights Reserved.
** The format and content in the File is protected by copyright.
** The File is furnished under a licence and may only be used in
** accordance with the terms of this licence.
*/

#ifndef _BS_BASIC_H_
#include <basic/bs_basic.h>
#endif

#ifndef _BS_MBOX_H_
#include <basic/bs_mbox.h>
#endif

#ifndef _BS_POOL_H_
#include <basic/bs_pool.h>
#endif

#ifndef _BS_QUEUE_H_
#include <basic/bs_queue.h>
#endif

#ifndef _B_MUTEX_H_
#include <blue/b_mutex.h>
#endif

#ifndef _B_MSGQUEUE_H_
#include <blue/b_msgqueue.h>
#endif

#ifndef _B_SEM_H_
#include <blue/b_sem.h>
#endif

#ifndef _B_THREAD_H_
#include <blue/b_thread.h>
#endif

#ifndef _B_SIGNAL_H_
#include <blue/b_signal.h>
#endif

#ifndef _G_THREAD_H_
#include <green/g_thread.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*===============================================
  Mailbox Status Type
===============================================*/
typedef struct bsMailboxStatus_s {
          uint_t        flags;
          uint_t        current;
          uint_t        peek;
        } bsMailboxStatus_t;

/*===============================================
  Mememory Pool Status Type
===============================================*/
typedef struct bsPoolStatus_s {
          uint_t          flags;
          uint_t          current;
          uint_t          peek;
        } bsPoolStatus_t;

/*===============================================
  Queue Status Type
===============================================*/
typedef struct {
          uint_t              flags;
          uint_t              current;
          uint_t              peek;
        } bsQueueStatus_t;

/*===============================================
  Message Queue Status Type
===============================================*/
typedef struct {
          uint_t           flags;
          uint_t           current;
          uint_t           peek;
        } blueMsgStatus_t;

/*===============================================
  Mutex Status Type
===============================================*/
typedef struct {
          uint_t            flags;
          int_t             owner;
        } blueMutexStatus_t;

/*===============================================
  Semaphor Status Type
===============================================*/
typedef struct {
          uint_t            flags;
          int_t             value;
        } blueSemStatus_t;

/*===============================================
  Thread Status Type
===============================================*/
typedef struct blueThreadStatus_s { 
          uint8_t               state;        
          uint8_t               priority;  
          int16_t               blockedOn;  
          uint_t                sigBlocked;   
          uint_t                sigPending;    
          int_t                 preemption;
          uint32_t              timeout;       
        } blueThreadStatus_t;

/*===============================================
  Externals
===============================================*/

/*===============================================
  Prototypes
===============================================*/
extern int_t  bsMailboxStatus (bsMailboxId_t mailbox, bsMailboxStatus_t *status);
extern int_t  bsPoolStatus (bsPoolId_t pool, bsPoolStatus_t *status);
extern int_t  bsQueueStatus (bsQueueId_t queue, bsQueueStatus_t *status);
extern int_t  blueMsgStatus (blueMsgId_t msg, blueMsgStatus_t *status);
extern int_t  blueMutexStatus (blueMutexId_t mutex, blueMutexStatus_t *status);
extern int_t  blueSemStatus (blueSemId_t sem, blueSemStatus_t *status);
extern int_t  blueThreadStatus(blueThreadId_t thread, blueThreadStatus_t *status);

#ifdef __cplusplus
}
#endif
#endif

