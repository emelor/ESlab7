#ifndef _CAN_H_
#define _CAN_H_
/*
** File:     can.h
**
** Contents: Rubus OS
**           Tutorial 
**           CAN Device
**           Generic Definitions
**
** Copyright 1996-2005 Arcticus Systems AB
**           All Rights Reserved
**
*/

/*===============================================
  Can Message Defines 
===============================================*/
#define CAN_MSG_DATA_NEW        0x01  
#define CAN_MSG_DATA_LOST       0x10  
#define CAN_MSG_DATA_INVALID    -1  

#define CAN_MSG_STD_ID          0x00  
#define CAN_MSG_EXT_ID          0x04  


/*===============================================
  CAN Id Type
===============================================*/
typedef union {
	  uint8_t     id8[4];
	  uint16_t    id16[2];
	  uint32_t     id32;
	} canMsgId_t;

/*===============================================
  CAN Message Header Type
===============================================*/
typedef struct {
	  int8_t        status;    /* Can message status */
	  uint8_t       nBytes;    /* Length of CAN message */
	  uint8_t       control;   /* Msg Control */
	  uint8_t       control_1; /* */
	  uint_t        frameCounter; /* Frame Counter or Time Stamp */
	  canMsgId_t  id;        /* ID */
	  canMsgId_t  arbMask;   /* Arbritation Mask */
	} canMsgHeader_t;

/*===============================================
  CAN Data Type
===============================================*/
typedef union {
	  uint8_t     d8[8];
	  uint16_t    d16[4];
	  uint32_t     d32[2];
	} canMsgData_t;

/*===============================================
  CAN Message Type
===============================================*/
typedef struct {
	  canMsgHeader_t 	header;        
	  canMsgData_t   	data;         
	} canMsg_t;

/*===============================================
  CAN Unit Type
===============================================*/
typedef uint_t canUnit_t;  

/*===============================================
  CAN Object Attribute Type
===============================================*/
typedef struct {
      canUnit_t   node;     /* Node */
      canUnit_t   msgObj;   /* Msg object number */
      canUnit_t   control;  /* Msg control */
    } canObject_t;
 
/*===============================================
  Externals
===============================================*/

/*===============================================
  Prototypes
===============================================*/
extern int_t  canGetMsgObj (canUnit_t node, canUnit_t obj, canMsg_t *pMsg);
extern int_t  canConfigMsgObj (canUnit_t node, canUnit_t obj, canMsgHeader_t *pMsg, uint_t flags);
extern int_t  canTransmitMsgObj (canUnit_t node, canUnit_t obj, canMsg_t *pMsg, uint_t flags);
extern int_t  canTransmitMsgStatus (canUnit_t node, canUnit_t obj);

/*===============================================
  Target Specific
===============================================*/

#include <can_target.h>

#endif
