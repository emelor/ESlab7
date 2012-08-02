/*
** File:     ros_xhpCmdCtrl.c
**
** Contents: Rubus OS
**           Rubus RTE 
**           XHP Protocol
**           Command handler for basic commands
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

#ifndef  _RUBUSOS_CFG_H_
#include <rubusOS_cfg.h>
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
extern xhpCmdTable_t const * const xhpCmdTableRtosPtr;

extern int8_t xhpCmdCtrlConnect (xhpCmdCB_t *cbx);
extern int8_t xhpCmdCtrlDisconnect (xhpCmdCB_t *cbx);
extern int8_t xhpCmdGetInfo (xhpCmdCB_t *cbx);
extern int8_t xhpParseCommand (xhpCmdTable_t const *pCmd, uint8_t command,xhpCmdCB_t *cbx);

/*=========================================================
  Command Table
=========================================================*/
xhpCmdTable_t const xhpCmdTableCtrl[] = {
  {XHP_CMD_CONNECT,&xhpCmdCtrlConnect },
  {XHP_CMD_TABLE_END,0u}
};

xhpCmdTable_t const * const xhpCmdTableCtrlPtr = &xhpCmdTableCtrl[0];

xhpCmdTable_t const xhpCmdTableOs[] = {
  {XHP_CMD_DISCONNECT,&xhpCmdCtrlDisconnect },
  {XHP_CMD_OS_GETINFO,&xhpCmdGetInfo },
  {XHP_CMD_OS_LOG_READ,&xhpCmdLogRead },
  {XHP_CMD_OS_LOG_READ_NEXT,&xhpCmdLogReadNext },
  {XHP_CMD_OS_LOG_SET_ALL,&xhpCmdLogSetAll },
  {XHP_CMD_OS_LOG_SET,&xhpCmdLogSet },
  {XHP_CMD_OS_LOG_START,&xhpCmdLogStart },
  {XHP_CMD_OS_LOG_STOP,&xhpCmdLogStop },
  {XHP_CMD_TABLE_END,0u}
};

xhpCmdTable_t const * const xhpCmdTableOsPtr = &xhpCmdTableOs[0];

/*=========================================================
  Variables
=========================================================*/
xhpStateCB_t       xhpStateCB;

/*=========================================================
  xhpCopyIdentifyer()
=========================================================*/
void xhpCopyIdentifyer (xhpCmdCB_t *cbx, char_t const *sid)

{ uint8_t       i = 0;
  char_t const  *sp;

  sp = sid;
  while ((*sid++ != 0x00) && (i < 255)) {
    i++;
  } 

  if (cbx->sizeWrite >= (cbx->nWrite + i + 1)) {
    *cbx->pWrite++ = i;
    cbx->nWrite += (i + 1);
    for (;i > 0; i--) {
      *cbx->pWrite++ = *sp++;
    } 
  }
}

/*=========================================================
  xhpInit()

=========================================================*/
int8_t xhpInit (void)

{
  xhpStateCB.state = XHP_STATE_IDLE;
  return(R_OK);
}

/*=========================================================
  xhpCmdCtrlConnect()

=========================================================*/
int8_t xhpCmdCtrlConnect (xhpCmdCB_t *cbx)

{
  if (cbx->nRead != 0) {
    return(-XHP_ERROR_CMD_LENGTH);
  }

  xhpStateCB.state = XHP_STATE_CONNECTED;
  cbx->pWrite = bsB16ToString(cbx->pWrite,0);
  *cbx->pWrite++ = sizeof(uint_t);
  cbx->pWrite = bsB16ToString(cbx->pWrite,xhpHandlerAttr.sizeRead);
  cbx->pWrite = bsB16ToString(cbx->pWrite,xhpHandlerAttr.sizeWrite);
  cbx->nWrite = (2 + 1 + 2 + 2);
  return(R_OK);
}

/*=========================================================
  xhpCmdCtrlDisconnect()

=========================================================*/
int8_t xhpCmdCtrlDisconnect (xhpCmdCB_t *cbx)

{
  if (cbx->nRead != 0) {
    return(-XHP_ERROR_CMD_LENGTH);
  }

  xhpStateCB.state = XHP_STATE_IDLE;
  return(R_OK);
}

/*=========================================================
  xhpCmdGetInfo()

=========================================================*/
int8_t xhpCmdGetInfo (xhpCmdCB_t *cbx)

{
  if (cbx->nRead != 0) {
    return(-XHP_ERROR_CMD_LENGTH);
  }

  xhpCopyIdentifyer(cbx,*bsAttr.labelCoder);
  xhpCopyIdentifyer(cbx,*bsAttr.labelIdentifier);
  xhpCopyIdentifyer(cbx,*bsAttr.labelDate);
  return(R_OK);
}

/*=========================================================
  xhpParseCommand()

=========================================================*/
int8_t xhpParseCommand (xhpCmdTable_t const *pCmd, uint8_t command,xhpCmdCB_t *cbx)

{ xhpCmd_t cfp;
  
  for (; (pCmd->command != XHP_CMD_TABLE_END); pCmd++) {
    if (pCmd->command == command) {
      cfp = (xhpCmd_t)pCmd->function;
      return(cfp(cbx));
    }
  }

  return(-XHP_ERROR_CMD_UNKNOWN);
}

/*=========================================================
  xhpProcessPackage()

=========================================================*/
void xhpProcessPackage (xhpCmdCB_t *cbx)

{ uint8_t  pid;
  int8_t   code;
  uint8_t *pCode;

  pCode = cbx->pWrite;
  cbx->pWrite += sizeof(xhpHeaderCode_t); 
  cbx->nWrite  = sizeof(xhpHeaderCode_t); 

  pid   = *cbx->pRead++;
  cbx->nRead  -= sizeof(xhpHeaderCode_t); 
  switch (xhpStateCB.state) {
    case XHP_STATE_IDLE:
         code = xhpParseCommand(xhpCmdTableCtrlPtr,pid,cbx);
         break;

    case XHP_STATE_CONNECTED:
         code = xhpParseCommand(xhpCmdTableOsPtr,pid,cbx);
         break;

    default:
         code = -XHP_ERROR_STATE;
         break;
  }

/* Prepare for respond */
  if (code >= 0) {
    *pCode = XHP_CMD_POS_RESPOND; 
  }
  else {
    *pCode++ = XHP_CMD_NEG_RESPOND; 
    *pCode   = code; 
    cbx->nWrite += 1; 
  }
}
