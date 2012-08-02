/*
** File:     ros_status.c
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

#ifndef  _ROS_STATUS_H_
#include <ros_status.h>
#endif

#ifndef _RUBUSOS_CFG_H_
#include <rubusOS_cfg.h>
#endif

/************************************************
 FUNCTION: bsMailboxStatus()
 Return information of the specified Message Mailbox
*************************************************/
int_t bsMailboxStatus(bsMailboxId_t mailbox, bsMailboxStatus_t *status)

{ bsMailboxCB_t R_LOC_CB *cb;
  R_TYPE_GREEN_LEVEL      gil;
  
  if (mailbox->object.type != R_OBJECT_BASIC_MAILBOX) {
    return(-R_ERROR_INVALID_ATTRIBUTE);
  }

  cb = mailbox->cb;
  gil = greenIntrSuspend();
  status->flags   = cb->flags;
  status->current = cb->current;
  status->peek    = cb->peek;
  greenIntrResume(gil);
  if (cb != cb->self) {
    return(-R_ERROR_INVALID_CONTROL_BLOCK);
  }

  return(R_OK);
}
/************************************************
 FUNCTION: bsPoolStatus()
 Return information of the specified Message Queue
*************************************************/
int_t bsPoolStatus(bsPoolId_t pool, bsPoolStatus_t *status)

{ bsPoolCB_t R_LOC_CB *cb;
  R_TYPE_GREEN_LEVEL   gil;

  if (pool->object.type != R_OBJECT_BASIC_POOL) {
    return(-R_ERROR_INVALID_ATTRIBUTE);
  }

  cb = pool->cb;
  gil = greenIntrSuspend();
  status->flags   = cb->flags;
  status->current = cb->current;
  status->peek    = cb->peek;
  greenIntrResume(gil);
  if (cb != cb->self) {
    return(-R_ERROR_INVALID_CONTROL_BLOCK);
  }

  return(R_OK);
}

/************************************************
 FUNCTION: bsQueueStatus()
 Return information of the specified queue.
*************************************************/
int_t bsQueueStatus (bsQueueId_t queue, bsQueueStatus_t *status)

{ bsQueueCB_t R_LOC_CB *cb;
  R_TYPE_GREEN_LEVEL   gil;

  if (queue->object.type != R_OBJECT_BASIC_QUEUE) {
    return(-R_ERROR_INVALID_ATTRIBUTE);
  }

  gil = greenIntrSuspend();
  cb = queue->cb;
  status->current = cb->current;
  status->peek    = cb->peek;
  status->flags   = cb->flags;
  greenIntrResume(gil);
  if (cb != cb->self) {
    return(-R_ERROR_INVALID_CONTROL_BLOCK);
  }

  return(R_OK);
}

/************************************************
 FUNCTION: blueMsgStatus()
 Return information of the specified Message Queue
*************************************************/
int_t blueMsgStatus(blueMsgId_t msg, blueMsgStatus_t *status)

{ blueMsgCB_t *cb;

  if (msg->object.type != R_OBJECT_BLUE_MSG) {
    return(-R_ERROR_INVALID_ATTRIBUTE);
  }

  cb = msg->cb;
  bluePreemptionLock();
  status->flags   = cb->flags;
  status->current = cb->current;
  status->peek    = cb->peek;
  bluePreemptionUnlock();
  if (cb != cb->self) {
    return(-R_ERROR_INVALID_CONTROL_BLOCK);
  }

  return(R_OK);
}

/************************************************
 FUNCTION: blueMutexStatus()
 Return information of the specified mutex.
*************************************************/
int_t blueMutexStatus(blueMutexId_t mutex, blueMutexStatus_t *status)

{ blueMutexCB_t *cb;

  if (mutex->object.type != R_OBJECT_BLUE_MUTEX) {
    return(-R_ERROR_INVALID_ATTRIBUTE);
  }

  cb = mutex->cb;
  bluePreemptionLock();
  status->flags = cb->flags;
  if (cb->owner != 0) {
    status->owner = cb->owner->header.attr->index;
  }
  else {
    status->owner = -1;
  }

  bluePreemptionUnlock();
  if (cb != cb->self) {
    return(-R_ERROR_INVALID_CONTROL_BLOCK);
  }

  return(R_OK);
}

/************************************************
 blueSemStatus()
 Return information of the specified semaphore
*************************************************/
int_t blueSemStatus(blueSemId_t sem, blueSemStatus_t *status)

{ blueSemCB_t *cb;

  if (sem->object.type != R_OBJECT_BLUE_SEM) {
    return(-R_ERROR_INVALID_ATTRIBUTE);
  }

  cb = sem->cb;
  bluePreemptionLock();
  status->flags = cb->flags;
  status->value = 0 - (cb->value);
  bluePreemptionUnlock();
  if (cb != cb->self) {
    return(-R_ERROR_INVALID_CONTROL_BLOCK);
  }

  return(R_OK);
}

/************************************************
 FUNCTION: blueFindResource()
 Find the resource the thread is blocked on
*************************************************/
static int_t blueFindResource (blueThreadCB_t *cb)

{
  if ((cb->sigBlocked & R_SIGNAL_RESOURCE) != 0) {
    if ((cb->blockedOn) != 0) {
      return(cb->blockedOn->attr->index);
    }
  }

  return(R_ERROR);
}

/************************************************
 FUNCTION: blueThreadStatus()
 Return information of the specified Blue Thread
*************************************************/
int_t blueThreadStatus(blueThreadId_t thread, blueThreadStatus_t *status)

{ blueThreadCB_t *cb;
 
  if ((thread->object.type & R_OBJECT_TYPE_SET) != R_OBJECT_BLUE_THREAD) {
    return(-R_ERROR_INVALID_ATTRIBUTE);
  }

  cb = thread->cb;
  bluePreemptionLock();
  status->state       = (uint8_t)cb->state.state;
  status->priority    = (uint8_t)cb->state.priority;
  status->blockedOn   = (int16_t)blueFindResource(cb);
  status->sigBlocked  = cb->sigBlocked;
  status->sigPending  = cb->sigPending;
  status->preemption  = cb->preemption;
  status->timeout     = cb->expirationTime;
  bluePreemptionUnlock();
  if (cb != cb->self) {
    return(-R_ERROR_INVALID_CONTROL_BLOCK);
  }

  return(R_OK);
}

