#ifndef _CAN_TARGET_H_
#define _CAN_TARGET_H_
/*
** File:     can_target.h
**
** Contents: Rubus OS
**           CAN Device
**           Target Specific Definitions
**
** Copyright 1996-2005 Arctic6s Systems AB
**           All Rights Reserved
**
*/

/*===============================================
  CAN Device Defines 
===============================================*/
#define CAN_NODE_A              0
#define CAN_NODE_B              1
#define CAN_NODE_C              2

/*===============================================
  HP Defines
===============================================*/
#define CAN_XHP_NODE            CAN_NODE_A
#define CAN_RUBUS_OBJECT_READ   0
#define CAN_RUBUS_OBJECT_WRITE  1

/*===============================================
  CAN Device
===============================================*/
#define CAN_MAX_MSG_OBJ          15
#define CAN_MAX_NODE             CAN_NODE_A

/*===============================================
  CAN Message Codes
===============================================*/
#define CAN_CODE_RX_NOT_ACTIVE   0x00
#define CAN_CODE_RX_BUSY         0x01
#define CAN_CODE_RX_FULL         0x02
#define CAN_CODE_RX_EMPTY        0x04
#define CAN_CODE_RX_OVERRUN      0x06
#define CAN_CODE_TX_NOT_ACTIVE   0x08
#define CAN_CODE_TX_ONCE         0x0C

/*===============================================
  CAN Baudrate Type
===============================================*/
typedef struct {
	  uint8_t SAMP;
	  uint8_t RJW;
	  uint8_t PSEG1;
	  uint8_t PSEG2;
	  uint8_t DIV;
	  uint8_t PROPSEG; 
	} canBaud_t;

/*===============================================
  Externals
===============================================*/

/*===============================================
  Prototypes
===============================================*/
extern int_t  canDeviceInit (canUnit_t node, uint_t level, uint8_t maxNoObjects);
extern int_t  canInit (canUnit_t node, canBaud_t const *baud);
extern int_t  canDestroy (canUnit_t node);
extern int_t  canEnable (canUnit_t node);
extern int_t  canDisable (canUnit_t node);
extern int_t  canSetMask (canUnit_t node, canUnit_t object, uint32_t mask);
extern int_t  canSetIntrObj (canUnit_t node, canUnit_t object, uint_t level);

#endif
