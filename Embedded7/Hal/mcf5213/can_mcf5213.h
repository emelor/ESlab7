#ifndef _CAN_MCF5213_H_
#define _CAN_MCF5213_H_
/*
** File:     can_mcf5213.h
**
** Contents: Rubus OS
**           Tutorial 
**           CAN Device
**           ColdFire FlexCAN Controller Definitions
**
** Copyright 1996-2011 Arcticus Systems AB
**           All Rights Reserved
**
*/

/*===============================================
  FlexCAN2 Module Configuration Register
===============================================*/
typedef struct {
  union {
    uint32_t  w;
    struct {
      uint16_t MDIS:1;
      uint16_t FRZ:1;
      uint16_t :1;
      uint16_t HALT:1;
      uint16_t NOTRDY:1;
      uint16_t :1;
      uint16_t SOFTRST:1;
      uint16_t FRZACK:1;
      uint16_t SUPV:1;
      uint16_t :1;
      uint16_t :1;
      uint16_t LPMACK:1;
      uint16_t :4;
      uint16_t MAXMB;
    } bf;
  };
}FlexCAN_MCR_t;

/*===============================================
 FlexCAN2 Control Register
===============================================*/
typedef struct {
  union {
    uint32_t  w;
    struct {
      uint16_t PRESDIV:8;
      uint16_t RJW:2;
      uint16_t PSEG1:3;
      uint16_t PSEG2:3;
      uint16_t BOFFMSK:1;
      uint16_t ERRMSK:1;
      uint16_t CLKSRC:1;
      uint16_t LPB:1;
      uint16_t :4;
      uint16_t SMP:1;
      uint16_t BOFFREC:1;
      uint16_t TSYN:1;
      uint16_t LBUF:1;
      uint16_t LOM:1;
      uint16_t PROPSEG:3;
    } bf;
  };
}FlexCAN_CTRL_t;

/*===============================================
 Error and Status Register
===============================================*/
typedef struct {
  union {
    uint32_t  w;
    struct {
      uint16_t :16;
      uint16_t BIT1ERR:1;
      uint16_t BIT0ERR:1;
      uint16_t ACKERR:1;
      uint16_t CRCERR:1;
      uint16_t FRMERR:1;
      uint16_t STFERR:1;
      uint16_t TXWRN:1;
      uint16_t RXWRN:1;
      uint16_t IDLE:1;
      uint16_t TXRX:1;
      uint16_t FLTCONF:2;
      uint16_t :1;
      uint16_t BOFFINT:1;
      uint16_t ERRINT:1;
      uint16_t :1;
    } bf;
  };
} FlexCAN_ERRSTAT_t;

/*===============================================
 ID Register
===============================================*/
typedef uint32_t FlexCAN_Id_t;

/*===============================================
  CAN Gloabal Node Register Definitions
===============================================*/
typedef struct canGlobalReg_s {
    FlexCAN_MCR_t      fcMCR;  
    FlexCAN_CTRL_t     fcCTRL;
    uint32_t              fcTIMER;
    uint32_t              res0;
    FlexCAN_Id_t       fcRXGMSK; 
    FlexCAN_Id_t       fcRX14MSK;
    FlexCAN_Id_t       fcRX15MSK; 
    uint32_t              fcERRCNT;
    FlexCAN_ERRSTAT_t  fcESTAT;    
    uint32_t              res1;
    uint32_t              fcIMASK;
    uint32_t              res2;    
    uint32_t              fcIFLAG;
  } FlexCAN_GlobalReg_t;

/*===============================================
 Message Buffer Registers
===============================================*/
typedef struct {
    uint16_t          :4;
    uint16_t          CODE:4;
    uint16_t          :1;
    uint16_t          SRR:1;
    uint16_t          IDE:1;
    uint16_t          RTR:1;
    uint16_t          LENGTH:4;
    uint16_t          TIMESTAMP:16;
  } FlexCAN_MsgCtrlReg_t;

/*===============================================
  CAN Message Extended Object Definitions
===============================================*/
typedef struct {
    FlexCAN_MsgCtrlReg_t CTRL;       
    FlexCAN_Id_t         id;         
    canMsgData_t         data;
  } FlexCAN_MsgObject_t;

/************************************************
  Address to CAN Chip register
************************************************/
#define CAN_NODE_P                  FlexCAN_GlobalReg_t volatile *
#define CAN_NODE_PTR(node)         (CAN_NODE_P) ((__IPSBAR + 0x1C0000) + (node << 6))
#define CAN_MSG_OBJ_P               FlexCAN_MsgObject_t volatile *
#define CAN_MSG_OBJ_PTR(node,obj)  (CAN_MSG_OBJ_P) ((__IPSBAR + 0x1C0080) + (node << 6) + (obj << 4))  

#define MCF_INTC_ICR_CAN(obj_nr)  (*(uint8_t *) (obj_nr + (uint8_t*)&MCF_INTC_ICR23))

/*===============================================
  Externals
===============================================*/

/*===============================================
  Prototypes
===============================================*/


#endif
