/*
** File:     rte_xhpCmdLog.c
**
** Contents: Rubus RCM
**           Rubus RTE 
**           XHP Protocol
**           RTE XHP Event Log Services.
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

#ifndef _RTE_LOG_H_
#include <rte_log.h>
#endif

#ifndef _RTE_XHPCMD_H_
#include <rte_xhpCmd.h>
#endif

/*=========================================================
  Externals
=========================================================*/

/*=========================================================
  rteXhpCmdLogSet()

=========================================================*/
int8_t rteXhpCmdLogSet (xhpCmdCB_t *cbx)

{ uint8_t flag;
  uint_t  nId;

  if (cbx->nRead != 3) {
    return(-XHP_ERROR_CMD_LENGTH);
  }

  flag = *cbx->pRead;
  cbx->pRead += 1;

  nId = bsStringToB16(cbx->pRead);
  cbx->pRead += sizeof(uint16_t);
  rteLogSet(nId,flag);
  return(R_OK);
}

/*=========================================================
  rteXhpCmdLogSetAll()

=========================================================*/
int8_t rteXhpCmdLogSetAll (xhpCmdCB_t *cbx)

{ uint8_t flag;

  if (cbx->nRead != 1) {
    return(-XHP_ERROR_CMD_LENGTH);
  }

  flag = *cbx->pRead;
  cbx->pRead += 1;

  rteLogSetAll(flag);
  return(R_OK);
}


