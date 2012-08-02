/*
** File:     rte_modeCtrl.c
**
** Contents: Rubus RCM
**           Rubus RTE 
**           Mode Control Definitions
**
** Version:  1.0
**
** Copyright 1996-2011 Arcticus Systems AB, All Rights Reserved.
** The format and content in the File is protected by copyright.
** The File is furnished under a licence and may only be used in
** accordance with the terms of this licence.
*/

#ifndef _RUBUSOS_CFG_H_
#include <rubusOS_cfg.h>
#endif

#ifndef _B_SIGNAL_H_
#include <blue/b_signal.h>
#endif

#ifndef _RTE_CONFIG_H_
#include <rte_config.h>
#endif

/*==========================================================
** Variables
==========================================================*/
rteModeVar_t rteModeVar;

/*==========================================================
** rteModeEndOfSchedule()
==========================================================*/
void rteModeEndOfSchedule (void)

{
  if (rteModeVar.flags == _R_INIT) {
    rteModeVar.flags |= _R_BUSY;
    /* Synchronization with ET triggered */
    rteModeVar.flags = 0;
  }
}

/*==========================================================
** rteModeRequest()
==========================================================*/
int_t rteModeRequest (rteModeRequest_t command, rteModeId_t mode, int32_t timeout)

{ int_t rcode = R_OK;

  if (mode->object.type != R_OBJECT_CM_MODE) {
    return(-R_ERROR_INVALID_ATTRIBUTE);
  }

  if (!((command == R_MODE_IMMEDIATE) ||
        (command == R_MODE_FIRST_APPROPRIATE) ||
        (command == R_MODE_BEST_APPROPRIATE))) {
    return(-R_ERROR_INVALID_PARAMETER);
  }

  R_RED_KERNEL_ENTER;
  rteModeVar.flags    = _R_INIT;
  rteModeVar.command  = command;
  rteModeVar.modeNext = mode;
  rteModeVar.timeout  = timeout;
  switch (command) {
    case R_MODE_IMMEDIATE:
         rteModeVar.flags    = 0;
         rteModeVar.modeExec = mode;
         rteModeVar.modeNext = 0;
         rcode = redSetScheduleImmediate(mode->redSchedule);
         break;

    case R_MODE_FIRST_APPROPRIATE:
    case R_MODE_BEST_APPROPRIATE:
         rteModeVar.modeExec = mode;
         rteModeVar.modeNext = 0;
         rcode = redSetSchedule(rteModeVar.modeExec->redSchedule);
         break;

    default:
         break;
  }

  R_RED_KERNEL_EXIT;
  return(rcode);
}

/*==========================================================
** rteModeRequest()
==========================================================*/
void rteModeQuerry (rteModeStatus_t *modeStatus)

{ redStatus_t     rstatus;

  R_RED_KERNEL_ENTER;
  redStatus(&rstatus);
  modeStatus->remainingTicks = rstatus.schedule->period - rstatus.redTime; 
  modeStatus->mode  = rteModeVar.modeExec;
  modeStatus->flags = rteModeVar.flags; 
  R_RED_KERNEL_EXIT;
}

/*==========================================================
** bsModeInit()
==========================================================*/
int_t rteModeInit(rteModeId_t mode)

{

  if (mode->object.type != R_OBJECT_CM_MODE) {
    return(-R_ERROR_INVALID_ATTRIBUTE);
  }

  rteModeVar.modeExec = mode;
  rteModeVar.modeNext = 0;
  rteModeVar.command  = R_MODE_NA;
  return(R_OK);
}

/*==========================================================
** TT Task Undefined for current mode
==========================================================*/
void rteModeEntryUndefinedTT (void)

{
  rteErrorTT(R_ERROR_OBJECT_DOES_NOT_EXIST,&rteModeVar.modeExec->object);
}

/*==========================================================
** ET Task Undefined for current mode
==========================================================*/
void rteModeEntryUndefinedET (void)

{
  rteErrorET(R_ERROR_OBJECT_DOES_NOT_EXIST,&rteModeVar.modeExec->object);
}

/*==========================================================
** IT Task Undefined for current mode
==========================================================*/
void rteModeEntryUndefinedIT (void)

{
  rteErrorIT(R_ERROR_OBJECT_DOES_NOT_EXIST,&rteModeVar.modeExec->object);
}

