/*
** File:     rte_config.c
**
** Contents: Rubus RCM
**           Rubus RTE 
**           RTE Configuration
**
** Version:  1.0
**
** Copyright 1996-2011 Arcticus Systems AB, All Rights Reserved.
** The format and content in the File is protected by copyright.
** The File is furnished under a licence and may only be used in
** accordance with the terms of this licence.
*/

/*==========================================================
** Include files
==========================================================*/
#ifndef _RTE_CONFIG_H_
#include <rte_config.h>
#endif

/*==========================================================
** rteMemCopy()
==========================================================*/
void rteMemCopy (register uint8_t *s, register uint8_t *ct, register int_t n)

{
  for( ; n > 0; n-- ) {
     *s++ = *ct++;
  }
}

/*==========================================================
** rteMemReset()
==========================================================*/
void rteMemReset (register uint8_t R_LOC_CB *s, register int_t n )

{
  for( ; n > 0; n-- ) {
    *s++ = 0x00;
  }
}

/*==========================================================
** rteStrnCmp()
==========================================================*/
int_t rteStrnCmp (char_t const *s1,char_t const *s2, int_t n)

{ char_t c1, c2;

  while( n-- > 0) {
    c2 = *s2++;
    c1 = *s1++;
    if( c1 != c2) {
      return(c1 - c2);
    }
    if ( c1 == 0 ) {
      break;
    }
  }
  return(0);
}

/*==========================================================
** rteGetObjects()
==========================================================*/
static int_t rteGetObjects (uint_t type, uint_t mask, int_t *id)

{ int_t      i;
  bsObject_t const *object;

  i = *id + 1;
  if ((i < 0) || (i >= rteAttr.idEntries)) {
    return(-R_ERROR_INVALID_PARAMETER);
  }

  for (; i < rteAttr.idEntries; i++) {
    object = rteAttr.idTable[i];
    if (type == (object->type | mask)) {
       *id = i;
       return(R_OK);
    }
  }

  return(-R_ERROR_EMPTY);
}

/*==========================================================
** rteGetObjectNext()
==========================================================*/
int_t rteGetObjectNext (uint_t type, bsObject_t const **object)

{ int_t  i;
  uint_t mask;

  mask = (type & R_OBJECT_CM_SUB_CLASS);
  if ((*object) == 0) {
    i = -1;
  }
  else {
    if (((*object)->type | mask) != type) {
      return(-R_ERROR_INVALID_ATTRIBUTE);
    }
    i = (*object)->index;
  }

  if ((rteGetObjects (type, mask, &i)) != R_OK) {
    return(-R_ERROR_EMPTY);
  }

  *object = *(rteAttr.idTable + i);
  return(R_OK);
}

/*==========================================================
** rteBehaviourInit()
==========================================================*/
void rteBehaviourInit (void)

{ rteSwcBehaviour_t const *behaviour = 0u;
  rteTimeCB_t R_LOC_CB    *cb;

  while (rteGetObjectNext (R_OBJECT_CM_BEHAVIOUR,(bsObject_t const **)&behaviour) == R_OK) {
    cb = behaviour->cb;
    rteMemReset((uint8_t R_LOC_CB*)cb, sizeof(rteTimeCB_t));
    cb->bcet = (uint_t)-1;
  }
}

/*==========================================================
** rteMonitorInit()
==========================================================*/
void rteMonitorInit (void)

{ rteMonitorCondAttr_t const      *monCond = 0u;
  rteMonitorTimeAttr_t const      *monTime = 0u;
  rteMonitorCondTimeCB_t R_LOC_CB *cbCond;
  rteMonitorTimeCB_t R_LOC_CB     *cbTime;

  while (rteGetObjectNext ((R_OBJECT_CM_MONITOR_CONDITIONAL),(bsObject_t const **)&monCond) == R_OK) {
    if (monCond->object.type == R_OBJECT_CM_MONITOR_CONDITIONAL) {
      cbCond = monCond->cb;
      rteMemReset((uint8_t R_LOC_CB*)cbCond, sizeof(rteMonitorCondTimeCB_t));
    }
  }

  while (rteGetObjectNext ((R_OBJECT_CM_MONITOR_TIME),(bsObject_t const **)&monTime) == R_OK) {
    if (monTime->object.type == R_OBJECT_CM_MONITOR_TIME) {
      cbTime = monTime->cb;
      rteMemReset((uint8_t R_LOC_CB*)cbTime, sizeof(rteMonitorTimeCB_t));
      cbTime->bcet = (uint_t)-1;
    }
  }
}
