/*
** File:     rte_xhpHandler.c
**
** Contents: Rubus RCM
**           Rubus RTE 
**           XHP Protocol
**           RTE XHP Handler
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

#ifndef _RTE_XHPCMD_H_
#include <rte_xhpCmd.h>
#endif

#ifndef _HAL_XHP_H_
#include <hal_xhp.h>
#endif

#ifndef _RRTE_INTERFACE_H_
#include <rRte_Interface.h>
#endif

/*=========================================================
  Variables
=========================================================*/
xhpCmdCB_t                      xhpCmdCB;

/*=========================================================
  xhpHandler_Init()

=========================================================*/
void xhpHandler_Init (rte_xhpHandler_iArgs_t const *args)

{
  R_PORT_STATE(stateTxCompleted) = R_TRUE;
  xhpInit();
  halXhpInit();
}

/*=========================================================
  xhpHandlerRx_entry()

=========================================================*/
void xhpHandlerRx_entry (rte_xhpHandler_iArgs_t const *args)

{
  xhpCmdCB.pRead     = xhpHandlerAttr.ioBufferRead + sizeof(xhpHeaderSize_t); 
  xhpCmdCB.nRead     = R_PORT_IN(ID_msgLng) - (uint16_t)sizeof(xhpHeaderSize_t);
  xhpCmdCB.pWrite    = xhpHandlerAttr.ioBufferWrite + sizeof(xhpHeaderSize_t); 
  xhpCmdCB.nWrite    = 0;
  xhpCmdCB.nFields   = 0;
  xhpCmdCB.sizeWrite = XHP_BUFFER_SIZE_WRITE - sizeof(xhpHeaderSize_t); 
  if (xhpCmdCB.nRead >= 1) {
    rteXhpProcessPackage(&xhpCmdCB);
    xhpCmdCB.nWrite += (sizeof(xhpHeaderSize_t) +  sizeof(xhpHeaderCode_t));
    bsB16ToString(xhpHandlerAttr.ioBufferWrite,xhpCmdCB.nWrite);
    R_PORT_STATE(stateTxCompleted) = R_FALSE;
    halXhpWrite(xhpHandlerAttr.ioBufferWrite,xhpCmdCB.nWrite);
  }
}

/*=========================================================
  xhpHandlerTx_entry()

=========================================================*/
void xhpHandlerTx_entry (rte_xhpHandler_iArgs_t const *args)
{
  R_PORT_STATE(stateTxCompleted) = R_TRUE;
}
