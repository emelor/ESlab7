/*
** File:     rte_log.c
**
** Contents: Rubus RCM
**           Rubus RTE 
**           Log Services
**
** Version:  1.0
**
** Copyright 1996-2011 Arcticus Systems AB, All Rights Reserved.
** The format and content in the File is protected by copyright.
** The File is furnished under a licence and may only be used in
** accordance with the terms of this licence.
*/

#ifndef _BS_LOG_H_
#include <basic/bs_log.h>
#endif

#ifndef _RTE_CONFIG_H_
#include <rte_config.h>
#endif

#ifndef _RTE_LOG_H_
#include <rte_log.h>
#endif

/*==========================================================
** rteLogInit()
==========================================================*/
int_t rteLogInit (void)

{
  rteMemReset(rteAttr.logIdArray,rteAttr.idEntries);
  return(R_OK);
}

/*==========================================================
** rteLogSet()
==========================================================*/
int_t rteLogSet (int_t id, uint_t flags)

{
  if ((id < 0) || (id >= rteAttr.idEntries)) {
    return(-R_ERROR_INVALID_PARAMETER);
  }

  if (!((bsLogCB.flags & _R_INIT) > 0)) {
    return(-R_ERROR_ACCESS_DENIED);
  }

  *(rteAttr.logIdArray + id) = (uint8_t)(flags & (R_LOG_OBJECT_ON | R_LOG_OBJECT_OFF));
  return(R_OK);
}

/*==========================================================
** rteLogSetAll()
==========================================================*/
void rteLogSetAll (uint_t flags)

{ bsLogIdArray_t *s;
  int_t            n;

  s = rteAttr.logIdArray;
  for(n = rteAttr.idEntries; n--; ) {
    *s++ = (uint8_t)(flags & (R_LOG_OBJECT_ON | R_LOG_OBJECT_OFF));
  }
}

/*==========================================================
** rteLogPut()
==========================================================*/
void rteLogPut (uint16_t id, uint16_t event)

{
  if (!((*(rteAttr.logIdArray + id) & R_LOG_OBJECT_ON) > 0) ) {
    return;
  }

  bsLogPutElm(id,event | RTE_LOG_EVENT_OBJECT);
}
