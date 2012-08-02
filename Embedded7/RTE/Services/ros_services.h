#ifndef  _ROS_SERVICES_H_
#define  _ROS_SERVICES_H_
/*
** File:     ros_services.h
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

extern int_t    bsStrnCmp (char const *s1,char const *s2,int_t n);
extern bsName_t bsObjectName (int_t id);
extern int_t    bsObjectByName (bsName_t str);


#ifdef __cplusplus
}
#endif
#endif

