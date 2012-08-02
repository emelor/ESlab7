/*
** File:     ros_xhpHandler.c
**
** Contents: Rubus OS
**           Rubus RTE 
**           XHP Protocol
**           XHP Handler
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

#ifndef _ROS_XHP_H_
#include <ros_xhp.h>
#endif

#ifndef _HAL_XHP_H_
#include <hal_xhp.h>
#endif


extern void      xhpHandlerRx_entry (void);
extern void      xhpHandlerTx_entry (void);

/*=========================================================
  Variables
=========================================================*/
xhpCmdCB_t                      xhpCmdCB;

/*=========================================================
  xhpHandler_Init()

=========================================================*/
int8_t xhpHandler_osInit (void)

{
  if (xhpInit() == R_OK) {
    if (halXhpInit() == R_OK) {
      xhpCmdCB.flags = _R_READ;
      return(R_OK);
    }
  }
  return(R_ERROR);
}

/*=========================================================
  xhpHandlerRx_entry()

=========================================================*/
void xhpHandlerRx_entry (void)

{
  if (halXhpRead (&xhpCmdCB.pRead, &xhpCmdCB.nRead) != R_OK) {
    xhpCmdCB.flags = _R_READ; 
    return;
  }

  xhpCmdCB.flags    &= (uint16_t)~_R_READ; 
  xhpCmdCB.pRead    += sizeof(xhpHeaderSize_t); 
  xhpCmdCB.nRead     = (uint16_t)(xhpCmdCB.nRead - sizeof(xhpHeaderSize_t));
  xhpCmdCB.pWrite    = xhpHandlerAttr.ioBufferWrite + sizeof(xhpHeaderSize_t); 
  xhpCmdCB.nWrite    = 0;
  xhpCmdCB.nFields   = 0;
  xhpCmdCB.sizeWrite = XHP_BUFFER_SIZE_WRITE - sizeof(xhpHeaderSize_t); 
  xhpProcessPackage(&xhpCmdCB);
  xhpCmdCB.nWrite += (sizeof(xhpHeaderSize_t) +  sizeof(xhpHeaderCode_t));
  bsB16ToString(xhpHandlerAttr.ioBufferWrite,xhpCmdCB.nWrite);
  xhpCmdCB.nRead = 0;
  xhpCmdCB.flags = _R_READ; 
  halXhpWrite(xhpHandlerAttr.ioBufferWrite,xhpCmdCB.nWrite);
}

/*=========================================================
  xhpHandlerTx_entry()

=========================================================*/
void xhpHandlerTx_entry (void)
{
}
