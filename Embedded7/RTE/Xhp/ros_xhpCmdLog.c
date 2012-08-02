/*
** File:     ros_xhpCmdLog.c
**
** Contents: Rubus OS
**           Rubus RTE 
**           XHP Protocol
**           Event Log Services.
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

#ifndef _BS_LOG_H_
#include <basic/bs_log.h>
#endif

#ifndef _ROS_XHP_H_
#include <ros_xhp.h>
#endif

#ifndef _ROS_XHPCMD_H_
#include <ros_xhpCmd.h>
#endif

/*=========================================================
  Externals
=========================================================*/

/*=========================================================
  xhpCmdLogSet()

=========================================================*/
int8_t xhpCmdLogSet (xhpCmdCB_t *cbx)

{ uint8_t flag;
  uint_t  nId;

  if (cbx->nRead != 3) {
    return(-XHP_ERROR_CMD_LENGTH);
  }

  flag = *cbx->pRead;
  cbx->pRead += 1;

  nId = bsStringToB16(cbx->pRead);
  cbx->pRead += 2;
  if (bsLogSet(nId,flag) == R_OK) {
    return(R_OK);
  }
  return(-XHP_ERROR_ID_NOT_FOUND);
}

/*=========================================================
  xhpCmdLogSetAll()

=========================================================*/
int8_t xhpCmdLogSetAll (xhpCmdCB_t *cbx)

{ uint8_t flag;

  if (cbx->nRead != 1) {
    return(-XHP_ERROR_CMD_LENGTH);
  }

  flag = *cbx->pRead;
  cbx->pRead += 1;

  bsLogSetAll(flag);
  return(R_OK);
}

/*=========================================================
  xhpCmdLogStart()

=========================================================*/
int8_t xhpCmdLogStart (xhpCmdCB_t *cbx)

{ uint_t flags = 0;

  if (cbx->nRead != 1) {
    return(-XHP_ERROR_CMD_LENGTH);
  }

  if (*cbx->pRead != 0) {
    flags = _R_OVERWRITE; 
  }

  switch (bsLogStart(flags)) {
    case -R_ERROR_INVALID_CONTROL_BLOCK:
          return(-XHP_ERROR_LOG_CORRUPT);

    case -R_ERROR_ACCESS_DENIED:
          return(-XHP_ERROR_LOG_NOT_INITIALISED);

    default:
          break;
  }

  return(R_OK);
}

/*=========================================================
  xhpCmdLogStop()

=========================================================*/
int8_t xhpCmdLogStop (xhpCmdCB_t *cbx)

{
  if (cbx->nRead != 0) {
    return(-XHP_ERROR_CMD_LENGTH);
  }

  switch (bsLogStop()) {
    case -R_ERROR_INVALID_CONTROL_BLOCK:
          return(-XHP_ERROR_LOG_CORRUPT);

    case -R_ERROR_ACCESS_DENIED:
          return(-XHP_ERROR_LOG_NOT_INITIALISED);

    default:
          break;
  }
  return(R_OK);
}

/*=========================================================
  xhpCmdLogRead()

=========================================================*/
int8_t xhpCmdLogRead (xhpCmdCB_t *cbx)

{ uint_t nElm;

  if (cbx->nRead != 0) {
    return(-XHP_ERROR_CMD_LENGTH);
  }

  switch (bsLogStatus(&nElm)) {
    case -R_ERROR_ACCESS_DENIED:
         return(-XHP_ERROR_LOG_IN_PROGRESS);

    case -R_ERROR_INVALID_CONTROL_BLOCK:
         return(-XHP_ERROR_LOG_CORRUPT);

    default:
         break;
  }

  *cbx->pWrite++ = sizeof(bsLogElm_t);
  cbx->nWrite += 1;

  cbx->pWrite = bsB32ToString(cbx->pWrite,(uint32_t)nElm);
  cbx->nWrite += sizeof(uint32_t);
  return(R_OK);
}

/*=========================================================
  xhpCmdLogReadNext()

=========================================================*/
int8_t xhpCmdLogReadNext (xhpCmdCB_t *cbx)

{ bsLogElm_t elm;
  uint16_t   nElm,n;

  if (cbx->nRead != 0) {
    return(-XHP_ERROR_CMD_LENGTH);
  }

  nElm = (uint16_t)(cbx->sizeWrite / sizeof(bsLogElm_t));
  cbx->pWrite = bsB16ToString(cbx->pWrite,nElm);
  cbx->nWrite += sizeof(uint16_t);
  for (n = 0; n < nElm; n++) {
    if (bsLogGet(&elm) != R_OK) {
      break; 
    }

    cbx->pWrite = bsB16ToString(cbx->pWrite,elm.index);
    cbx->nWrite += sizeof(uint16_t);

    cbx->pWrite = bsB16ToString(cbx->pWrite,elm.event);
    cbx->nWrite += sizeof(uint16_t);

    cbx->pWrite = bsB32ToString(cbx->pWrite,elm.time);
    cbx->nWrite += sizeof(uint32_t);
  }

  return(R_OK);
}
