/*
** File:     ros_services.c
**
** Contents: Rubus OS
**           Rubus RTE 
**           Rubus OS SServices 
**
** Version:  1.0
**
** Copyright 1996-2011 Arcticus Systems AB, All Rights Reserved.
** The format and content in the File is protected by copyright.
** The File is furnished under a licence and may only be used in
** accordance with the terms of this licence.
*/

#ifndef  _ROS_SERVICES_H_
#include <ros_services.h>
#endif

#ifndef _RUBUSOS_CFG_H_
#include <rubusOS_cfg.h>
#endif

/************************************************
 FUNCTION: bsStrnCmp()
 Compare two strings
*************************************************/
int_t bsStrnCmp (char_t const *s1, char_t const *s2, int_t n)

{
  while( n-- ) {
    if( *s1 != *s2) {
      return(*s1 - *s2);
    }
    if ( *s1 == 0 ) {
      break;
    }
    s2++;
    s1++;
  }
  return(0);
}

/************************************************
 FUNCTION: bsObjectName()
 Find the name of the specified object id
*************************************************/
bsName_t bsObjectName (int_t id)

{
  if ((id < 0) || (id >= bsAttr.idEntries) || (bsAttr.nameTable == 0u)) {
     return(0u);
  }
  return(bsAttr.nameTable[id].name);
}

/************************************************
 FUNCTION: bsObjectByName()
 Find the object id of the specified named object
*************************************************/
int_t bsObjectByName (bsName_t str)

{ int_t i;

  if (str == 0u) { 
    return(-R_ERROR_INVALID_PARAMETER);
  }

  if (bsAttr.nameTable == 0u) {
    return(-R_ERROR_ACCESS_DENIED);
  }

  for (i = 0; i < bsAttr.idEntries; i++) {
    if (!bsStrnCmp(bsAttr.nameTable[i].name,str,bsAttr.nameTable[i].length)) {
      return(i);
    }
  }

  return(R_ERROR);
}

