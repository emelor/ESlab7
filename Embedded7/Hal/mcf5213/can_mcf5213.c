/*
** File:     can_mcf5213.c
**
** Contents: Rubus OS
**           Tutorial 
**           Target MFC5213
**           CAN I/O Services
**
** Copyright 1996-2011 Arcticus Systems AB
**           All Rights Reserved
**
*/
 
#include <basic/bs_basic.h>
#include <hal.h>
#include <can.h>
#include <can_target.h>
#include "hal_MCF5213.h"
#include <can_mcf5213.h>
#include "mcf5213_gpio.h"

/*===============================================
  Variables
===============================================*/

/********************************************************
  canObjectDisable()
  Disable all objects.
********************************************************/
static void canObjectDisable (canUnit_t node)

{ CAN_MSG_OBJ_P pObj;
  uint_t          i;

  for (i = 0; i < CAN_MAX_MSG_OBJ; i++) {
    pObj = CAN_MSG_OBJ_PTR(node,i);
    pObj->id = 0;   // Clear Substitute Remote Request
    pObj->CTRL.CODE = 0;
    MCF_INTC_ICR_CAN(i) = 0;
  }
}
 
/************************************************
  canDeviceInit()
  Initilisation of the CAN Device.
*************************************************/

int_t canDeviceInit (canUnit_t node, uint_t level, uint8_t maxNoObjects)

{ CAN_NODE_P    nP;
  FlexCAN_MCR_t mcr;
 
  if (node > CAN_MAX_NODE) 
    return(-R_ERROR_INVALID_PARAMETER);

  if ((maxNoObjects > CAN_MAX_MSG_OBJ))
    return(-R_ERROR_INVALID_PARAMETER);

  nP = CAN_NODE_PTR(node);
  mcr.w = nP->fcMCR.w;
  mcr.bf.FRZ    = 1;  //Frees mode
  mcr.bf.HALT   = 1;  //start initiation
  mcr.bf.MAXMB  = maxNoObjects;
  nP->fcMCR.w   = mcr.w;

  nP->fcRXGMSK  = 0;
  nP->fcRX14MSK = 0;
  nP->fcRX15MSK = 0;

  nP->fcIMASK  = 0;
  nP->fcIFLAG  = 0;
  nP->fcESTAT.w = 0;

  canObjectDisable(node);

  MCF_INTC_ICR_CAN(16) = (uint8_t)(MCF_INTC_ICR_IL(level) | MCF_INTC_ICR_IP(0)); //ERR_int_t
  MCF_INTC_ICR_CAN(17) = (uint8_t)(MCF_INTC_ICR_IL(level) | MCF_INTC_ICR_IP(1)); //BOFF_int_t


/* Pin assignments for port AS 
           Pin AS1 : FlexCAN receive data, CANRX 
           Pin AS0 : FlexCAN transmit data, CANTX 
*/
  MCF_GPIO_DDRAS = 0;
  MCF_GPIO_PASPAR = MCF_GPIO_PASPAR_PASPAR1(0x2) | MCF_GPIO_PASPAR_PASPAR0(0x2);

  MCF_INTC_IMRH &= ~(
		MCF_INTC_IPRH_INT32 |
		MCF_INTC_IPRH_INT33 |
		MCF_INTC_IPRH_INT34 |
		MCF_INTC_IPRH_INT35 |
		MCF_INTC_IPRH_INT36 |
		MCF_INTC_IPRH_INT37 |
		MCF_INTC_IPRH_INT38 |
		MCF_INTC_IPRH_INT39 |
		MCF_INTC_IPRH_INT40);  
  MCF_INTC_IMRL &= ~(
		MCF_INTC_IPRL_INT23 |
		MCF_INTC_IPRL_INT24 |
		MCF_INTC_IPRL_INT25 |
		MCF_INTC_IPRL_INT26 |
		MCF_INTC_IPRL_INT27 |
		MCF_INTC_IPRL_INT28 |
		MCF_INTC_IPRL_INT29 |
		MCF_INTC_IPRL_INT30 |
		MCF_INTC_IPRL_INT31); // Enable interrupts
  
  return(R_OK);
}


/************************************************
 canInit()
 Initiliate specified node.
*************************************************/

int_t canInit (canUnit_t node, canBaud_t const *baud)

{ CAN_NODE_P       nP;
  FlexCAN_CTRL_t   ctrl;

  if (node > CAN_MAX_NODE) 
    return(-R_ERROR_INVALID_PARAMETER);

  nP = CAN_NODE_PTR(node);
  nP->fcMCR.bf.HALT = 1;  //start initiation

  ctrl.w = nP->fcCTRL.w;
  ctrl.bf.PRESDIV = baud->DIV;
  ctrl.bf.RJW     = baud->RJW;
  ctrl.bf.PSEG1   = baud->PSEG1;
  ctrl.bf.PSEG2   = baud->PSEG2;
  ctrl.bf.SMP     = baud->SAMP;
  ctrl.bf.PROPSEG = baud->PROPSEG; 
  ctrl.bf.BOFFMSK = 1;
  ctrl.bf.ERRMSK  = 1;
  ctrl.bf.CLKSRC  = 1;
  nP->fcCTRL.w    = ctrl.w;

  return(R_OK);
}

/************************************************
 canDestroy()
 Destroy the specified CAN channel.
*************************************************/

int_t canDestroy (canUnit_t node)

{ CAN_NODE_P nP;

  if (node > CAN_MAX_NODE) 
    return(-R_ERROR_INVALID_PARAMETER);

  nP = CAN_NODE_PTR(node);
  nP->fcMCR.bf.HALT = 1;

  canObjectDisable(node);

  return(R_OK);
}

/***************************************************
  canEnable()
  Enable the device.
***************************************************/
int_t canEnable (canUnit_t node)

{ CAN_NODE_P nP;
  uint32_t  volatile dummy;

  if (node > CAN_MAX_NODE) 
    return(-R_ERROR_INVALID_PARAMETER);

  nP = CAN_NODE_PTR(node);
  nP->fcMCR.bf.MDIS = 0;
  nP->fcMCR.bf.FRZ  = 0;  
  nP->fcMCR.bf.HALT = 0;  //start to run
  dummy = nP->fcTIMER;    // A "read" unlocks all receive buffers
  return(R_OK);
}

/***************************************************
  canSetMask()
  Set receive mask register, objNr 14 and 15.
***************************************************/
int_t canSetMask (canUnit_t node, canUnit_t object, uint32_t mask)

{ CAN_NODE_P    nP;

  if (node > CAN_MAX_NODE) 
    return(-R_ERROR_INVALID_PARAMETER);

  nP   = CAN_NODE_PTR(node);

  if (nP->fcMCR.bf.HALT == 0) {
    return(-R_ERROR_OPERATION_INPROGRESS);  
  }  

  
  switch(object) {
      case 0:
        nP->fcRXGMSK  = mask;
        break;
      case 14:
        nP->fcRX14MSK = mask;
        break;
      case 15:
        nP->fcRX15MSK = mask;
        break;
      default:
        break;
  }
  return(R_OK);      
}

/************************************************
  canSetIntrObj()
  Set msg object interrupt level and enable it.
*************************************************/

int_t canSetIntrObj (canUnit_t node, canUnit_t object, uint_t level)

{ 

  if (node > CAN_MAX_NODE) 
    return(-R_ERROR_INVALID_PARAMETER);

  if (object > CAN_MAX_MSG_OBJ)
    return(-R_ERROR_INVALID_PARAMETER);

  MCF_INTC_ICR_CAN(object) = (uint8_t)(MCF_INTC_ICR_IL(level) | MCF_INTC_ICR_IP(0));
  
  return(R_OK);
}

/************************************************
  canConfigMsgObj ()
  Configure the message object. 
*************************************************/

int_t canConfigMsgObj (canUnit_t node, canUnit_t object, canMsgHeader_t *pMsg, uint_t flags)

{ CAN_MSG_OBJ_P pObj;
  CAN_NODE_P    nP;
  
  if (node > CAN_MAX_NODE)
    return(-R_ERROR_INVALID_PARAMETER);

  if (object > CAN_MAX_MSG_OBJ)
    return(-R_ERROR_INVALID_PARAMETER);

  nP   = CAN_NODE_PTR(node);
  pObj = CAN_MSG_OBJ_PTR(node,object);

  pObj->CTRL.CODE = CAN_CODE_RX_NOT_ACTIVE; // Deactivate
  pObj->CTRL.IDE  = 1; // Set ID Extended
  pObj->CTRL.RTR  = 0; // Data frame
  pObj->id        = pMsg->id.id32;

  if (flags & _R_WRITE) { // Tx-Obj
    pObj->CTRL.CODE = CAN_CODE_TX_NOT_ACTIVE; // Deactivate
  }
  else { 
    pObj->CTRL.CODE = CAN_CODE_RX_EMPTY; // Activate Receive  
  }

  if (flags & _R_APPEND) {
    nP->fcIMASK |= R_BIT( object);      // Enable interrupt	
  }
  else {
    nP->fcIMASK &= ~R_BIT(object);     // Disable interrupt
  }

  return(R_OK);
}

/************************************************
  canGetMsgObj () 
  Copy the contents of the selected message object. 
*************************************************/

int_t canGetMsgObj (canUnit_t node, canUnit_t object, canMsg_t *pMsg)

{ CAN_MSG_OBJ_P pObj;
  CAN_NODE_P    nP;
  uint16_t         code;
  uint32_t volatile dummy;

  if (node > CAN_MAX_NODE)
    return(-R_ERROR_INVALID_PARAMETER);

  if (object > CAN_MAX_MSG_OBJ)
    return(-R_ERROR_INVALID_PARAMETER);

  nP   = CAN_NODE_PTR(node);
  pObj = CAN_MSG_OBJ_PTR(node,object);

  if (nP->fcIFLAG & R_BIT(object)) {
    code = pObj->CTRL.CODE;
    if (code & CAN_CODE_RX_BUSY) {
      pMsg->header.status = CAN_MSG_DATA_INVALID; 
      return(-R_ERROR_EMPTY);
    }

    if ((code == CAN_CODE_RX_FULL) || (code == CAN_CODE_RX_OVERRUN))  {
      pMsg->header.id.id32   = pObj->id;
      pMsg->header.frameCounter  = pObj->CTRL.TIMESTAMP;
      pMsg->data.d32[0]   = pObj->data.d32[0];
      pMsg->data.d32[1]   = pObj->data.d32[1];
      pMsg->header.nBytes = (uint8_t)(pObj->CTRL.LENGTH);
      pMsg->header.status = CAN_MSG_DATA_NEW; 
      if (code == CAN_CODE_RX_OVERRUN) {
         pMsg->header.status |= CAN_MSG_DATA_LOST; 
      }
      pObj->CTRL.CODE = CAN_CODE_RX_EMPTY; // empty buffer
      nP->fcIFLAG |= R_BIT(object);
      dummy = nP->fcTIMER;           // A "read" unlocks all receive buffers
      return(R_OK);
    }
  }
  pMsg->header.status = CAN_MSG_DATA_INVALID; 
  return(-R_ERROR_EMPTY);
}


/************************************************
  canTransmitMsgObj () 
  Sets up the message object and send it.
*************************************************/

int_t canTransmitMsgObj (canUnit_t node, canUnit_t object, canMsg_t *pMsg, uint_t flags)

{ CAN_MSG_OBJ_P pObj;
  CAN_NODE_P    nP;

  if (node > CAN_MAX_NODE)
    return(-R_ERROR_INVALID_PARAMETER);

  if (object > CAN_MAX_MSG_OBJ)
    return(-R_ERROR_INVALID_PARAMETER);

  nP = CAN_NODE_PTR(node);
  pObj = CAN_MSG_OBJ_PTR(node,object);

  pObj->CTRL.CODE   = CAN_CODE_TX_NOT_ACTIVE; // Deactivate transmit object
  pObj->CTRL.LENGTH = pMsg->header.nBytes; 
  pObj->CTRL.IDE    = 1; // Set ID Extended
  pObj->CTRL.RTR    = 0; // Data frame
  pObj->id      = pMsg->header.id.id32;
  pObj->data.d32[0] = pMsg->data.d32[0];
  pObj->data.d32[1] = pMsg->data.d32[1];

  if (flags & _R_APPEND) {
    nP->fcIMASK |= R_BIT( object);      // Enable interrupt	
  }
  else {
    nP->fcIMASK &= ~R_BIT(object);     // Disable interrupt
  }
  pObj->CTRL.CODE = CAN_CODE_TX_ONCE; // Send frame once

  return(R_OK);
}

/************************************************
  canTransmitMsgStatus () 
  Check message object transmit status.
*************************************************/

int_t canTransmitMsgStatus (canUnit_t node, canUnit_t object)

{ CAN_MSG_OBJ_P pObj;
  CAN_NODE_P    nP;

  if (node > CAN_MAX_NODE)
    return(-R_ERROR_INVALID_PARAMETER);

  if (object > CAN_MAX_MSG_OBJ)
    return(-R_ERROR_INVALID_PARAMETER);

  nP   = CAN_NODE_PTR(node);
  pObj = CAN_MSG_OBJ_PTR(node,object);

  if (nP->fcIFLAG & R_BIT(object)) {
    if (pObj->CTRL.CODE == CAN_CODE_TX_NOT_ACTIVE) {
      nP->fcIFLAG &= ~R_BIT(object);
      return(R_OK);
    }
  }
  else {
    if (pObj->CTRL.CODE == CAN_CODE_TX_NOT_ACTIVE) {
      return(R_OK);
    }
  }
  return(-R_ERROR_OPERATION_INPROGRESS);
}

