/*
** File:     rte_xhpCmd.c
**
** Contents: Rubus RCM
**           Rubus RTE 
**           XHP Protocol
**           RTE XHP Command handler
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

#ifndef _RTE_CONFIG_H_
#include <rte_config.h>
#endif

#ifndef _RTE_SERVICES_H_
#include <rte_services.h>
#endif

#ifndef _RTE_XHPCMD_H_
#include <rte_xhpCmd.h>
#endif

#ifndef _ROS_XHPCMD_H_
#include <ros_xhpCmd.h>
#endif

/*=========================================================
  Externals
=========================================================*/
extern int8_t xhpParseCommand (xhpCmdTable_t const *pCmd, uint8_t command,xhpCmdCB_t *cbx);
extern xhpCmdTable_t const * const xhpCmdTableCtrlPtr;

/*=========================================================
  XHP RTE Command Table
=========================================================*/
xhpCmdTable_t const xhpCmdTableRte[] = {

  {XHP_CMD_DISCONNECT,&xhpCmdCtrlDisconnect },
  {XHP_CMD_RTE_GETINFO,&rteXhpCmdGetInfo },

  {XHP_CMD_RTE_GET_BEHAVIOUR,&rteXhpCmdGetBehaviour },
  {XHP_CMD_RTE_GET_PORT_DATA,&rteXhpCmdGetPortData },
  {XHP_CMD_RTE_GET_EXEC_STATE,&rteXhpCmdGetExecState },
  {XHP_CMD_RTE_GET_MONITOR_TIME,&rteXhpCmdGetMonitorTime },
  {XHP_CMD_RTE_GET_MONITOR_COND,&rteXhpCmdGetMonitorCond },

  {XHP_CMD_RTE_LOG_SET,&rteXhpCmdLogSet },
  {XHP_CMD_RTE_LOG_SET_ALL,&rteXhpCmdLogSetAll },

  {XHP_CMD_RTE_LOG_START,&xhpCmdLogStart },
  {XHP_CMD_RTE_LOG_STOP,&xhpCmdLogStop },
  {XHP_CMD_RTE_LOG_READ,&xhpCmdLogRead },
  {XHP_CMD_RTE_LOG_READ_NEXT,&xhpCmdLogReadNext },

  {XHP_CMD_TABLE_END,0u}
};

xhpCmdTable_t const * const xhpCmdTableRtePtr = &xhpCmdTableRte[0];

/*=========================================================
  rteXhpCmdGetInfo()

=========================================================*/
int8_t rteXhpCmdGetInfo (xhpCmdCB_t *cbx)

{
  if (cbx->nRead != 0) {
    return(-XHP_ERROR_CMD_LENGTH);
  }

  xhpCopyIdentifyer(cbx,*rteAttr.labelCoder);
  xhpCopyIdentifyer(cbx,*rteAttr.labelIdentifier);
  xhpCopyIdentifyer(cbx,*rteAttr.labelDate);
  return(R_OK);
}

/*=========================================================
  rteXhpProcessPackage()

=========================================================*/
void rteXhpProcessPackage (xhpCmdCB_t *cbx)

{ uint8_t *pCode;
  uint8_t  pid;
  int8_t   code;

  pCode = cbx->pWrite;
  cbx->pWrite += sizeof(xhpHeaderCode_t); 
  cbx->nWrite  = sizeof(xhpHeaderCode_t); 

  pid = *cbx->pRead++;
  cbx->nRead  -= sizeof(xhpHeaderCode_t); 

  switch (xhpStateCB.state) {
    case XHP_STATE_IDLE:
         code = xhpParseCommand(xhpCmdTableCtrlPtr,pid,cbx);
         break;

    case XHP_STATE_CONNECTED:
         code = xhpParseCommand(xhpCmdTableRte,pid,cbx);
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

/*=========================================================
  xhpPortEvalScalar()

=========================================================*/
static int8_t xhpPortEvalScalar (xhpCmdCB_t *cbx, rtePort_t const *port)

{ uint8_t  *mp = port->accessAddr;
  uint16_t  lng;
  uint16_t  ltmp;

  lng = port->data.dataSize;
  if ((lng  >= 0x7fff) ||
      (cbx->nFields >= 0x7fff)) {
    return(-XHP_ERROR_LENGTH);
  }

  ltmp = cbx->nWrite + lng + 2;
  if (ltmp > cbx->sizeWrite) {
    return(-XHP_ERROR_LENGTH);
  }

  cbx->pWrite = bsB16ToString(cbx->pWrite,lng);
  cbx->nWrite += 2;
  switch (lng) {
    case 1:
         cbx->pWrite = bsB8ToString(cbx->pWrite,*mp);
         cbx->nWrite += 1;
         break;

    case 2:
         cbx->pWrite = bsB16ToString(cbx->pWrite,*(uint16_t *)mp);
         cbx->nWrite += 2;
         break;

    case 4:
         cbx->pWrite = bsB32ToString(cbx->pWrite,*(uint32_t *)mp);
         cbx->nWrite += 4;
         break;

#ifdef R_SUPPORT_64_BIT
    case 8:
         cbx->pWrite = bsB64ToString(cbx->pWrite,*(uint64_t *)mp);
         cbx->nWrite += 8;
         break;
#endif

    default:
         return(-XHP_ERROR_LENGTH);
  }

  cbx->nFields++;
  return(R_OK);
}

/*=========================================================
  xhpPortEvalComplex()

=========================================================*/
static int8_t xhpPortEvalComplex (xhpCmdCB_t *cbx, rtePort_t const *port, uint16_t dimension)

{ rtePort_t const *pp;
  rtePort_t const *pi;
  uint16_t         i;
  int8_t           code = R_OK;

  for (i = 0; ((i < dimension) && (code == R_OK)); i++) {
    pp = &port[i];
    pi = pp->link;
    switch (pp->data.dataType) {
      case R_PORT_ARRAY:
      case R_PORT_COMPOSITE:
           code = xhpPortEvalComplex(cbx,pi,pp->data.dataSize);
           break;

      default:
           code = xhpPortEvalScalar(cbx,pp);
           break;
    }
  }

  return(code);
}

/*=========================================================
  xhpPortEval()

=========================================================*/
static void xhpPortEval (xhpCmdCB_t *cbx,rtePortTable_t const *pInst)

{ uint8_t  *hp;
  uint16_t  n;
  int8_t    code;

  hp = cbx->pWrite;
  cbx->pWrite += 2;
  cbx->nWrite += 2;
  switch (pInst->dataType) {
    case R_PORT_ARRAY:
    case R_PORT_COMPOSITE:
         code = xhpPortEvalComplex(cbx,pInst->link,pInst->dimension);
         break;

    default:
         code = xhpPortEvalScalar(cbx,pInst->link);
         break;
  }

  n = cbx->nFields;
  if (code == -XHP_ERROR_LENGTH) {
    n |= 0x8000u;  /* Indicate truncated data */
  }

  bsB16ToString(hp,n);
}

/*=========================================================
  rteXhpCmdGetBehaviour()

=========================================================*/
int8_t rteXhpCmdGetBehaviour (xhpCmdCB_t *cbx)

{ rteSwcBehaviour_t const *obj;
  rteTimeCB_t             *cb;
  uint16_t                 id;
 
  if (cbx->nRead != 2) {
    return(-XHP_ERROR_CMD_LENGTH);
  }

  id = bsStringToB16(cbx->pRead);
  obj = (rteSwcBehaviour_t const *)rteGetObject(id);
  if (obj == 0u) {
    return(-XHP_ERROR_ID_NOT_FOUND);
  }

  if (obj->object.type != R_OBJECT_CM_BEHAVIOUR) {
    return(-XHP_ERROR_ID_TYPE);
  }

  cb = obj->cb;
  cbx->pWrite = bsB32ToString(cbx->pWrite,(uint32_t)cb->bcet);
  cbx->nWrite += sizeof(uint32_t);

  cbx->pWrite = bsB32ToString(cbx->pWrite,(uint32_t)cb->wcet);
  cbx->nWrite += sizeof(uint32_t);

  cbx->pWrite = bsB32ToString(cbx->pWrite,(uint32_t)cb->acet);
  cbx->nWrite += sizeof(uint32_t);

  cbx->pWrite = bsB32ToString(cbx->pWrite,(uint32_t)cb->vCntBcet);
  cbx->nWrite += sizeof(uint32_t);

  cbx->pWrite = bsB32ToString(cbx->pWrite,(uint32_t)cb->vCntWcet);
  cbx->nWrite += sizeof(uint32_t);
  return(R_OK);
}

/*=========================================================
  rteXhpCmdGetMonitorTime()

=========================================================*/
int8_t rteXhpCmdGetMonitorTime (xhpCmdCB_t *cbx)

{ rteMonitorTimeAttr_t const *obj;
  rteMonitorTimeCB_t         *cb;
  uint16_t                    id;
 
  if (cbx->nRead != 2) {
    return(-XHP_ERROR_CMD_LENGTH);
  }

  id = bsStringToB16(cbx->pRead);
  obj = (rteMonitorTimeAttr_t const *)rteGetObject(id);
  if (obj == 0u) {
    return(-XHP_ERROR_ID_NOT_FOUND);
  }

  if (obj->object.type != R_OBJECT_CM_MONITOR_TIME) {
    return(-XHP_ERROR_ID_TYPE);
  }

  cb = obj->cb;
  cbx->pWrite = bsB32ToString(cbx->pWrite,(uint32_t)obj->start->cb->value);
  cbx->nWrite += sizeof(uint32_t);

  cbx->pWrite = bsB32ToString(cbx->pWrite,(uint32_t)cb->bcet);
  cbx->nWrite += sizeof(uint32_t);

  cbx->pWrite = bsB32ToString(cbx->pWrite,(uint32_t)cb->wcet);
  cbx->nWrite += sizeof(uint32_t);

  cbx->pWrite = bsB32ToString(cbx->pWrite,(uint32_t)cb->acet);
  cbx->nWrite += sizeof(uint32_t);
  
  return(R_OK);
}

/*=========================================================
  rteXhpCmdGetMonitorCond()

=========================================================*/
int8_t rteXhpCmdGetMonitorCond (xhpCmdCB_t *cbx)

{ rteMonitorCondAttr_t const *obj;
  rteMonitorCondTimeCB_t     *cb;
  uint16_t                    id;
 
  if (cbx->nRead != 2) {
    return(-XHP_ERROR_CMD_LENGTH);
  }

  id = bsStringToB16(cbx->pRead);
  obj = (rteMonitorCondAttr_t const *)rteGetObject(id);
  if (obj == 0u) {
    return(-XHP_ERROR_ID_NOT_FOUND);
  }

  if (obj->object.type != R_OBJECT_CM_MONITOR_CONDITIONAL) {
    return(-XHP_ERROR_ID_TYPE);
  }

  cb = obj->cb;
  cbx->pWrite = bsB32ToString(cbx->pWrite,(uint32_t)obj->start->cb->value);
  cbx->nWrite += sizeof(uint32_t);

  cbx->pWrite = bsB32ToString(cbx->pWrite,(uint32_t)cb->diff);
  cbx->nWrite += sizeof(uint32_t);

  cbx->pWrite = bsB32ToString(cbx->pWrite,(uint32_t)cb->vCnt);
  cbx->nWrite += sizeof(uint32_t);
  return(R_OK);
}

/*=========================================================
  rteXhpCmdGetPortData()

=========================================================*/
int8_t rteXhpCmdGetPortData (xhpCmdCB_t *cbx)

{ rteSwcInterfaceAttr_t const *swcInterface;
  rteSwcInstanceAttr_t const  *swcInstance;
  rtePortTable_t const        *pInst;
  rteSwcPortAttr_t const      *pAttr;
  uint16_t                     id;
  uint16_t                     pid;
  uint8_t                      pType;
  uint_t                       i;
 
  if (cbx->nRead != 5) {
    return(-XHP_ERROR_CMD_LENGTH);
  }

  id = bsStringToB16(cbx->pRead);
  cbx->pRead += 2;
  swcInstance = (rteSwcInstanceAttr_t const *)rteGetObject(id);
  if (swcInstance == 0u) {
    return(-XHP_ERROR_ID_NOT_FOUND);
  }

  if ((swcInstance->object.type & R_OBJECT_CM_TYPE_SET) != R_OBJECT_CM_INSTANCE) {
    return(-XHP_ERROR_ID_TYPE);
  }

  pid = bsStringToB16(cbx->pRead);
  cbx->pRead += 2;

  pType = *cbx->pRead;
  swcInterface = swcInstance->swcInterface;
  pInst = swcInstance->portTable;
  pAttr = swcInterface->portAttrTable;
  if (pAttr && pInst) {
    for (i = 0; i < swcInterface->noOfPorts;i++) {
      if ((pid == pAttr->portIndex) && 
          (pType == (pAttr->portType & R_OBJECT_CM_SUB_CLASS))) {
        xhpPortEval(cbx,pInst);
        return(R_OK);
      }

      pAttr++;
      pInst++;
    }
  }

  return(-XHP_ERROR_ID_NOT_FOUND);
}

/*=========================================================
  rteXhpCmdExecState()

=========================================================*/
int8_t rteXhpCmdGetExecState (xhpCmdCB_t *cbx)

{ rteModeStatus_t modeStatus;
 
  if (cbx->nRead != 0) {
    return(-XHP_ERROR_CMD_LENGTH);
  }

  rteModeQuerry(&modeStatus);
  cbx->pWrite = bsB16ToString(cbx->pWrite,(uint16_t)modeStatus.mode->modeIndex);
  cbx->nWrite += sizeof(uint16_t);

  cbx->pWrite = bsB16ToString(cbx->pWrite,(uint16_t)modeStatus.remainingTicks);
  cbx->nWrite += sizeof(uint16_t);
  return(R_OK);
}
