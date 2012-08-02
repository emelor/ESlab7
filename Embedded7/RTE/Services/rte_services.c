/*
** File:     rte_services.c
**
** Contents: Rubus RCM
**           Rubus RTE 
**           RTE User Services
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
** rteObjectName()
==========================================================*/
char_t const *rteObjectName (int_t id)

{
  if ((id < 0) || (id >= rteAttr.idEntries) || (rteAttr.nameTable == 0u)) {
    return("?");
  }

  return(rteAttr.nameTable[id].name);
}

/*==========================================================
** rteObjectByName()
==========================================================*/
int_t rteObjectByName (char_t const *str)

{ int_t i;

  if (str == 0u) {
    return(-R_ERROR_INVALID_PARAMETER);
  }

  if (rteAttr.nameTable == 0u) {
    return(-R_ERROR_ACCESS_DENIED);
  }

  for (i = 0; i < rteAttr.idEntries; i++) {
    if (rteStrnCmp(rteAttr.nameTable[i].name,str,rteAttr.nameTable[i].length) == 0) {
      return(i);
    }
  }

  return(R_ERROR);
}

/*==========================================================
** rteGetObject()
==========================================================*/
bsObject_t const *rteGetObject (int_t id)

{
  if ((id < 0) || (id >= rteAttr.idEntries)) {
    return(0u);
  }

  return(*(rteAttr.idTable + id));
}


/*==========================================================
** rteJiffiesToTvExec()
==========================================================*/
void rteJiffiesToTvExec (uint32_t jiffies, uint32_t *time)

{
  *time = rteAttr.timerResExecPSec * jiffies;
}

/*==========================================================
** rteTvToJiffiesExec()
==========================================================*/
uint32_t rteTvToJiffiesExec (uint32_t time)

{
  return(time/rteAttr.timerResExecPSec);
}

/*==========================================================
** rteJiffiesToTvGeneral()
==========================================================*/
void rteJiffiesToTvGeneral (uint32_t jiffies, uint32_t *time)

{
  *time = rteAttr.timerResGeneralPSec * jiffies;
}

/*==========================================================
** rteTvToJiffiesGeneral()
==========================================================*/
uint32_t rteTvToJiffiesGeneral (uint32_t time)

{
  return(time/rteAttr.timerResGeneralPSec);
}

/*==========================================================
** rteGetModeName()
==========================================================*/
char_t const *rteGetModeName (uint_t modeIndex)

{ rteModeAttr_t const *mode;
  char_t   const        *name;

  if (modeIndex > rteModeTable.modes) {
    return("?");
  }

  mode = rteModeTable.modeTable[modeIndex];
  name = rteObjectName(mode->object.index);
  return(name);
}
