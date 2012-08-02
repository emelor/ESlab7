/*
** File:     hal_env.h
**
** Contents: Rubus OS
**           HAL 
**           Target ColdFire
**           Environment Definitions.
**
** NOTE:     The defint_tions should not be changed by the user
**
** Copyright 1996-2010 Arcticus Systems AB
**           All Rights Reserved
**
*/

#ifndef  _HAL_ENV_H_
#define  _HAL_ENV_H_

#ifndef _HAL_CTYPES_H
#include <hal/hal_ctypes.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*===============================================
  Compiler Related Definitions
===============================================*/
#define R_LOC_CB
#define R_LOC_VAR               
#define R_LOC_FAR               
#define R_LOC_LOG               
#define R_LOC_HAL_FUNC

/*===============================================
  Define 64-bits support
===============================================*/
#define R_SUPPORT_64_BIT

/*===============================================
  int_terrupt Level Definitions
===============================================*/
#define R_TYPE_GREEN_LEVEL              uint32_t

/*===============================================
  Time Definitions
===============================================*/
#define R_TYPE_TIME_EXEC                uint32_t

/*===============================================
  Configuration Definitions
===============================================*/
#define R_TYPE_ENDIAN_BIG               0 
#define R_TYPE_ENDIAN_LITTLE            1 
#define R_TYPE_ENDIAN                   R_TYPE_ENDIAN_BIG
#define R_TYPE_STACK_PTR                uint32_t *
#define R_TYPE_BLUE_THREAD_EXTENSION

/*===============================================
  Prototypes
===============================================*/
 
#ifdef __cplusplus
}
#endif

#endif		/* End of header */

