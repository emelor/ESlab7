#ifndef _ROS_XHP_H_
#define _ROS_XHP_H_
/*
** File:     ros_xhp.h
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
#define XHP_CMD_CONNECT                 0x10
#define XHP_CMD_DISCONNECT              0x11

#define XHP_CMD_TABLE_END               0x7F

#define XHP_CMD_POS_RESPOND             0xFE
#define XHP_CMD_NEG_RESPOND             0xFF

/*=========================================================
  Protocol States
=========================================================*/
#define XHP_STATE_IDLE                  0x00
#define XHP_STATE_CONNECTED             0x0F

/*=========================================================
  XHP Error Codes
=========================================================*/
#define XHP_ERROR_STATE                 1
#define XHP_ERROR_CMD_LENGTH            2
#define XHP_ERROR_ID_NOT_FOUND          3
#define XHP_ERROR_ID_TYPE               4
#define XHP_ERROR_VALUE                 5
#define XHP_ERROR_LENGTH                6
#define XHP_ERROR_CMD_UNKNOWN           7
#define XHP_ERROR_LOG_CORRUPT           8
#define XHP_ERROR_LOG_IN_PROGRESS       9
#define XHP_ERROR_LOG_NOT_INITIALISED   10

/*=========================================================
  XHP Header Type
=========================================================*/
typedef uint16_t                        xhpHeaderSize_t;
typedef uint8_t                         xhpHeaderCode_t;

/*=========================================================
  XHP Control Block Type
=========================================================*/
typedef struct {
    uint8_t                             state;
} xhpStateCB_t;

/*=========================================================
  XHP Control Block Type
=========================================================*/
typedef struct {
    uint8_t                            *pRead;
    uint8_t                            *pWrite;
    uint16_t                            flags;
    uint16_t                            nRead;
    uint16_t                            nWrite;
    uint16_t                            nFields;
    uint16_t                            sizeWrite;
} R_LOC_CB xhpCmdCB_t;

/*=========================================================
  XHP Object Attribute Type
=========================================================*/
typedef struct {
    uint8_t                            *ioBufferRead;
    int16_t                             sizeRead;
    uint8_t                            *ioBufferWrite;
    int16_t                             sizeWrite;
} xhpHandlerAttr_t;

/*=========================================================
  Command Table Type
=========================================================*/
typedef struct {
    uint8_t                             command;
    int8_t                             (*function)(xhpCmdCB_t *cbx);
} xhpCmdTable_t;

typedef int8_t (*xhpCmd_t)(xhpCmdCB_t *cbx);

/*=========================================================
  Externals
=========================================================*/
extern xhpCmdCB_t                       xhpCmdCB;
extern xhpStateCB_t                     xhpStateCB;
extern xhpHandlerAttr_t const           xhpHandlerAttr;

/*=========================================================
  Prototypes
=========================================================*/
extern int8_t    xhpInit (void);
extern int8_t    xhpHandler_osInit (void);
extern void      xhpProcessPackage (xhpCmdCB_t *cbx);

extern int8_t    xhpCmdCtrlConnect (xhpCmdCB_t *cbx);
extern int8_t    xhpCmdCtrlDisconnect (xhpCmdCB_t *cbx);

extern void      xhpCopyIdentifyer (xhpCmdCB_t *cbx, char_t const *sid);
extern void      xhpFormatId (xhpCmdCB_t *cbx);

/* User defined services */
extern int8_t    halXhpInit (void);
extern int8_t    halXhpDestroy (void);
extern int8_t    halXhpWrite (uint8_t *ioBuffer, uint16_t ioLng);
extern int8_t    halXhpRead (uint8_t **ioBuffer, uint16_t *ioLng);

#ifdef __cplusplus
}
#endif


#endif
