#ifndef  _HAL_CFG_H_
#define  _HAL_CFG_H_
/*
** File:     hal_cfg.h
**
** Contents: Rubus OS
**           HAL 
**           Target ColdFire
**           Configuration Definitions.
**
** Copyright 1996-2010 Arcticus Systems AB
**           All Rights Reserved
**
*/

#ifdef __cplusplus
extern "C" {
#endif

/*===============================================
  Configuration
===============================================*/
#define R_EXEC_TIME_START(tv)                { (tv) = halBsExecTimeStart(); }
#define R_EXEC_TIME_STOP(tv,tvStart,adjust)  { (tv) = halBsExecTimeStop((tvStart),(adjust)); }
#define R_FREE_RUN_TIME_GET                    halBsFreeRunTimerGet()

#define R_RED_KERNEL_EXIT                      halBsTimerEnable()
#define R_RED_KERNEL_ENTER                     halBsTimerDisable()

/*===============================================
  Prototypes
===============================================*/

#ifdef __cplusplus
}
#endif

#endif                /* End of header */
