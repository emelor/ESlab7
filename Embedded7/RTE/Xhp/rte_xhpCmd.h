#ifndef _RTE_XHPCMD_H_
#define _RTE_XHPCMD_H_
/*
** File:     rte_xhpCmd.h
**
** Contents: Rubus RCM
**           Rubus RTE 
**           XHP Protocol
**           RTE XHP Definitions
**
** Version:  1.0
**
** Copyright 1996-2011 Arcticus Systems AB, All Rights Reserved.
** The format and content in the File is protected by copyright.
** The File is furnished under a licence and may only be used in
** accordance with the terms of this licence.
*/

#ifndef _ROS_XHP_H_
#include <ros_xhp.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*=========================================================
  XHP Commands 
=========================================================*/
#define XHP_CMD_RTE_GETINFO             0x40

#define XHP_CMD_RTE_LOG_SET             0x41
#define XHP_CMD_RTE_LOG_SET_ALL         0x42
#define XHP_CMD_RTE_LOG_START           0x43
#define XHP_CMD_RTE_LOG_STOP            0x44
#define XHP_CMD_RTE_LOG_READ            0x45
#define XHP_CMD_RTE_LOG_READ_NEXT       0x46

#define XHP_CMD_RTE_GET_BEHAVIOUR       0x47
#define XHP_CMD_RTE_GET_PORT_DATA       0x48
#define XHP_CMD_RTE_GET_EXEC_STATE      0x49
#define XHP_CMD_RTE_GET_MONITOR_TIME    0x4A
#define XHP_CMD_RTE_GET_MONITOR_COND    0x4B

/*=========================================================
  Externals
=========================================================*/

/*=========================================================
  Prototypes
=========================================================*/
extern void   rteXhpProcessPackage (xhpCmdCB_t *cbx);

extern int8_t rteXhpCmdGetInfo (xhpCmdCB_t *cbx);
extern int8_t rteXhpCmdGetBehaviour (xhpCmdCB_t *cbx);
extern int8_t rteXhpCmdGetPortData (xhpCmdCB_t *cbx);
extern int8_t rteXhpCmdGetExecState (xhpCmdCB_t *cbx);
extern int8_t rteXhpCmdGetMonitorTime (xhpCmdCB_t *cbx);
extern int8_t rteXhpCmdGetMonitorCond (xhpCmdCB_t *cbx);

extern int8_t rteXhpCmdLogSet (xhpCmdCB_t *cbx);
extern int8_t rteXhpCmdLogSetAll (xhpCmdCB_t *cbx);
extern int8_t rteXhpCmdLogStop (xhpCmdCB_t *cbx);
extern int8_t rteXhpCmdLogStart (xhpCmdCB_t *cbx);
extern int8_t rteXhpCmdLogRead (xhpCmdCB_t *cbx);
extern int8_t rteXhpCmdLogReadNext (xhpCmdCB_t *cbx);

#ifdef __cplusplus
}
#endif


#endif
