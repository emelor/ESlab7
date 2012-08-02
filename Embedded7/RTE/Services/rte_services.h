#ifndef  _RTS_SERVICES_H_
#define  _RTS_SERVICES_H_
/*
** File:     rte_services.h
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

#ifndef _BS_BASIC_H_
#include <basic/bs_basic.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif


/*===============================================
  Externals
===============================================*/

/*===============================================
  Prototypes
===============================================*/
extern char_t const     *rteGetModeName (uint_t modeIndex);
extern char_t const     *rteObjectName (int_t id);
extern int_t             rteObjectByName (char_t const *str);


#ifdef __cplusplus
}
#endif
#endif

