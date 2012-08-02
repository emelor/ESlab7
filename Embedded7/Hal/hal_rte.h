#ifndef _HAL_RTE_H_
#define _HAL_RTE_H_
/*
** File:     hal_rte.h
**
** Contents: Rubus OS
**           RTE
**           HAL Definitions
**
** Copyright 1996-2010 Arcticus Systems AB
**           All Rights Reserved
**
*/

#ifdef __cplusplus
extern "C" {
#endif

/*=========================================================
  Defines
=========================================================*/
#define R_TYPE_TIME_RTE    uint32_t

#define R_RTE_MONITOR_TIME_GET halBsFreeRunTimerGet()


/*===============================================
  Externals
===============================================*/


/*===============================================
  Prototypes
===============================================*/
extern R_TYPE_TIME_RTE halBsFreeRunTimerGet (void);

#ifdef __cplusplus
}
#endif

#endif
