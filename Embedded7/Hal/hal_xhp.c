/*
** File:     hal_xhp.c
**
** Contents: Rubus OS
**           XHP Protocol
**           HAL Services
**
** Copyright 1996-2011 Arcticus Systems AB
**           All Rights Reserved
*/

#include <basic/bs_basic.h>
#include <hal.h>
#include "hal_MCF5213.h"
#include <can.h>

#include <ros_xhp.h>
#include <hal_xhp.h>

#ifdef _PROJECT_OS
#include <blue/b_signal.h>
#include <r_ex_b.h>
#include <r_ex_g.h>
#else
#include <rRte_Interface.h>
#endif

void canBsHpPut (uint8_t *data, uint8_t nBytes);

#ifdef _PROJECT_OS
void comXhpRx_handler (void);
void comXhpTx_handler (void);
#endif

/*===============================================
  HP Defines
===============================================*/
#define CAN_RUBUS_ID_RX                 0x18000100
#define CAN_RUBUS_ID_TX                 0x18000101

/*=========================================================
  XHP Control Block Type
=========================================================*/
typedef struct {
          vuint16_t    flags;
          uint16_t     ioSize;
          uint8_t     *pIo;
          uint16_t     nIo;
        } R_LOC_CB comHandlerCB_t;

/*=========================================================
  Variables
=========================================================*/
uint8_t                         xhpBufferRead[XHP_BUFFER_SIZE_READ + 1];
uint8_t                         xhpBufferWrite[XHP_BUFFER_SIZE_WRITE + 1];

comHandlerCB_t                  comHandlerRxCB;
comHandlerCB_t                  comHandlerTxCB;

canMsg_t canMsgRx;
canMsg_t canMsgTx;

/*=========================================================
  Constants
=========================================================*/
xhpHandlerAttr_t const xhpHandlerAttr = {
  &xhpBufferRead[0],
  XHP_BUFFER_SIZE_READ,
  &xhpBufferWrite[0],
  XHP_BUFFER_SIZE_WRITE,
};

uint32_t const canMaskGlobal = {0x1fffffff};

canBaud_t const canBaud = {
  CAN_BAUD_SAMP,
  CAN_BAUD_RJW,
  CAN_BAUD_PSEG1,
  CAN_BAUD_PSEG2,
  CAN_BAUD_PRESDIV,
  CAN_BAUD_PROPSEG,
};

/***********************************************
  halXhpInit()
***********************************************/
int8_t halXhpInit (void)

{
  comHandlerRxCB.flags    = _R_READ;
  comHandlerRxCB.ioSize   = xhpHandlerAttr.sizeRead;
  comHandlerRxCB.pIo      = xhpHandlerAttr.ioBufferRead;
  comHandlerRxCB.nIo      = 0;

  comHandlerTxCB.flags    = 0;
  comHandlerTxCB.ioSize   = xhpHandlerAttr.sizeWrite;
  comHandlerTxCB.pIo      = xhpHandlerAttr.ioBufferWrite;
  comHandlerTxCB.nIo      = 0;
 
  canMsgRx.header.id.id32 = CAN_RUBUS_ID_RX;
  canMsgRx.header.nBytes = 8;
  canMsgTx.header.id.id32 = CAN_RUBUS_ID_TX;

#ifdef _PROJECT_OS
  canDeviceInit (CAN_XHP_NODE,comXhpTx.priority,2);
#else
  canDeviceInit (CAN_XHP_NODE,RTE_IT_Int_IrqTx.priority,2);
#endif
  canInit (CAN_XHP_NODE, &canBaud);

  canSetMask (CAN_XHP_NODE, 0, canMaskGlobal);
  canConfigMsgObj(CAN_XHP_NODE,CAN_RUBUS_OBJECT_READ,&canMsgRx.header,(_R_READ | _R_APPEND));

#ifdef _PROJECT_OS
  canSetIntrObj(CAN_XHP_NODE,CAN_RUBUS_OBJECT_READ,comXhpRx.priority);
  canSetIntrObj(CAN_XHP_NODE,CAN_RUBUS_OBJECT_WRITE,comXhpTx.priority);
#else
  canSetIntrObj(CAN_XHP_NODE,CAN_RUBUS_OBJECT_READ,RTE_IT_Int_IrqRx.priority);
  canSetIntrObj(CAN_XHP_NODE,CAN_RUBUS_OBJECT_WRITE,RTE_IT_Int_IrqTx.priority);
#endif
  canEnable (CAN_XHP_NODE);
  return(R_OK);
} 

/***********************************************
  halXhpDestroy()
***********************************************/
int8_t halXhpDestroy (void)

{
  return((int8_t)canDestroy(CAN_XHP_NODE));
}

/***************************************************
 FUNCTION: canBsHpPut()
 Transmit a CAN message 
***************************************************/
void canBsHpPut (uint8_t *data, uint8_t nBytes)

{ uint8_t      i;

  canMsgTx.header.nBytes = nBytes;
  for (i = 0; i < nBytes; i++) {
    canMsgTx.data.d8[i] = *data++;
  }
  canTransmitMsgObj(CAN_XHP_NODE,CAN_RUBUS_OBJECT_WRITE, &canMsgTx, _R_APPEND);
}

/***********************************************
  halXhpWrite()
***********************************************/
int8_t halXhpWrite (uint8_t *ioBuffer, uint16_t ioLng)

{ uint16_t  n;
  uint8_t  *p;

  comHandlerRxCB.flags = _R_READ;

  if (ioLng == 0) {
    return(R_ERROR);
    }

  comHandlerTxCB.pIo = ioBuffer;
  comHandlerTxCB.nIo = ioLng;
  n = 8;
  if (ioLng <= n) {
    n = ioLng;
  }

  comHandlerTxCB.flags |= _R_OUT;
  p = comHandlerTxCB.pIo;
  comHandlerTxCB.pIo += n;
  comHandlerTxCB.nIo -= n;
  canBsHpPut(p,(uint8_t)n);

  return(R_OK);
  }

/***********************************************
  halXhpRead()
***********************************************/
int8_t halXhpRead (uint8_t **ioBuffer, uint16_t *ioLng)

{
  if ((comHandlerRxCB.flags & _R_READ) && (comHandlerRxCB.nIo > 0)) {
    *ioBuffer = xhpHandlerAttr.ioBufferRead; 
    *ioLng    = comHandlerRxCB.nIo;
    comHandlerRxCB.flags &= (uint16_t)~_R_READ; 
    comHandlerRxCB.pIo  = xhpHandlerAttr.ioBufferRead;
    comHandlerRxCB.nIo  = 0;
  return(R_OK);
}

  comHandlerRxCB.flags = 0; 
  comHandlerRxCB.pIo   = xhpHandlerAttr.ioBufferRead;
  comHandlerRxCB.nIo   = 0;
  comHandlerRxCB.flags = _R_READ; 
  return(-R_ERROR_EMPTY);
}

/***********************************************
  comXhpRx_handler()
***********************************************/
#ifdef _PROJECT_OS
void comXhpRx_handler (void)
#else
void   comXhpRx_handler (rte_comXhpRx_iArgs_t const *args)
#endif

{ uint16_t  n;
  uint16_t  i;
  uint16_t  lng;

  canGetMsgObj(CAN_XHP_NODE,CAN_RUBUS_OBJECT_READ, &canMsgRx);
  if (canMsgRx.header.status != CAN_MSG_DATA_NEW) {
    return;
  }

  n = canMsgRx.header.nBytes;
  if ((comHandlerRxCB.nIo + n) > comHandlerRxCB.ioSize) {
    comHandlerRxCB.pIo   = xhpHandlerAttr.ioBufferRead;
    comHandlerRxCB.nIo   = 0;
    comHandlerRxCB.flags &= (uint16_t)~_R_IN;
    return;
  }

  comHandlerRxCB.flags   |= _R_IN;
  if ((comHandlerRxCB.flags & _R_READ) != 0) {
    for (i = 0; i < n; i++) {
      *comHandlerRxCB.pIo++ = canMsgRx.data.d8[i];
    }

    comHandlerRxCB.nIo += n;
    lng = bsStringToB16(xhpHandlerAttr.ioBufferRead);
    if (comHandlerRxCB.nIo >= lng) {
        comHandlerRxCB.flags   &= (uint16_t)~_R_IN;
#ifdef _PROJECT_OS
        blueActivate(&xhpHandlerRx);
#else
        R_PORT_OUT(OD_msgLng) = lng;   
        R_PORT_OUT(OT_C) = R_TRUE;
#endif
    }
  }
}

/***********************************************
  comXhpTx_handler()
***********************************************/
#ifdef _PROJECT_OS
void comXhpTx_handler (void)
#else
void   comXhpTx_handler (rte_comXhpTx_iArgs_t const *args)
#endif

{ uint16_t  n;
  uint8_t  *p;


  if ((comHandlerTxCB.flags & _R_OUT) != 0) {
    if (comHandlerTxCB.nIo == 0) {
      comHandlerTxCB.flags = 0;
#ifdef _PROJECT_OS
      blueActivate(&xhpHandlerTx);
#else
      R_PORT_OUT(OD_msgLng) = 0;   
      R_PORT_OUT(OT_C) = R_TRUE;
#endif
      return;
    }

    if ((comHandlerTxCB.nIo / 8) > 0) {
      n = 8;
    }
    else {
      n = (uint16_t)(comHandlerTxCB.nIo % 8u);
    }

    if (n > 0) {
      p = comHandlerTxCB.pIo;
      comHandlerTxCB.pIo += n;
      comHandlerTxCB.nIo -= n;
      canBsHpPut(p,(uint8_t)n);
    }
  }
}

