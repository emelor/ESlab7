#ifndef _ROS_XHPCMD_H_
#define _ROS_XHPCMD_H_
/*
** File:     ros_xhpCmd.h
**
** Contents: Rubus OS
**           Rubus RTE 
**           XHP Protocol
**
** Version:  1.0
**
** Copyright 1996-2011 Arcticus Systems AB, All Rights Reserved.
** The format and content in the File is protected by copyright.
** The File is furnished under a licence and may only be used in
** accordance with the terms of this licence.
*/

#ifdef __cplusplus
extern "C" {
#endif

/*=========================================================
  XHP Commands 
=========================================================*/
#define XHP_CMD_OS_GETINFO              0x20
#define XHP_CMD_OS_LOG_SET              0x21
#define XHP_CMD_OS_LOG_SET_ALL          0x22
#define XHP_CMD_OS_LOG_START            0x23
#define XHP_CMD_OS_LOG_STOP             0x24
#define XHP_CMD_OS_LOG_READ             0x25
#define XHP_CMD_OS_LOG_READ_NEXT        0x26

/*=========================================================
  Externals
=========================================================*/

/*=========================================================
  Prototypes
=========================================================*/
extern int8_t xhpCmdGetInfo (xhpCmdCB_t *cbx);
extern int8_t xhpCmdLogSet (xhpCmdCB_t *cbx);
extern int8_t xhpCmdLogSetAll (xhpCmdCB_t *cbx);
extern int8_t xhpCmdLogRead (xhpCmdCB_t *cbx);
extern int8_t xhpCmdLogReadNext (xhpCmdCB_t *cbx);
extern int8_t xhpCmdLogStart (xhpCmdCB_t *cbx);
extern int8_t xhpCmdLogStop (xhpCmdCB_t *cbx);

#ifdef __cplusplus
}
#endif


#endif
