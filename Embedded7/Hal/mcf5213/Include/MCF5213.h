/********************************************************************/
/* Coldfire C Header File
 *
 *     Date      : 2009/04/30
 *     Revision  : 0.96
 *
 *     Copyright : 1997 - 2009 Freescale Semiconductor, Inc. All Rights Reserved.
 *
 *     http      : www.freescale.com
 *     mail      : support@freescale.com
 */

#ifndef __MCF5213_H__
#define __MCF5213_H__


/********************************************************************/
/*
 * The basic data types
 */

typedef unsigned char           uint8;   /*  8 bits */
typedef unsigned short int      uint16;  /* 16 bits */
typedef unsigned long int       uint32;  /* 32 bits */

typedef signed char             int8;    /*  8 bits */
typedef signed short int        int16;   /* 16 bits */
typedef signed long int         int32;   /* 32 bits */

typedef volatile uint8          vuint8;  /*  8 bits */
typedef volatile uint16         vuint16; /* 16 bits */
typedef volatile uint32         vuint32; /* 32 bits */

#ifdef __cplusplus
extern "C" {
#endif

#pragma define_section system ".system" far_absolute RW

/***
 * MCF5213 Derivative Memory map definitions from linker command files:
 * __IPSBAR, __RAMBAR, __RAMBAR_SIZE, __FLASHBAR, __FLASHBAR_SIZE linker
 * symbols must be defined in the linker command file.
 */

extern __declspec(system)  uint8 __IPSBAR[];
extern __declspec(system)  uint8 __RAMBAR[];
extern __declspec(system)  uint8 __RAMBAR_SIZE[];
extern __declspec(system)  uint8 __FLASHBAR[];
extern __declspec(system)  uint8 __FLASHBAR_SIZE[];

#define IPSBAR_ADDRESS   (uint32)__IPSBAR
#define RAMBAR_ADDRESS   (uint32)__RAMBAR
#define RAMBAR_SIZE      (uint32)__RAMBAR_SIZE
#define FLASHBAR_ADDRESS (uint32)__FLASHBAR
#define FLASHBAR_SIZE    (uint32)__FLASHBAR_SIZE


#include "MCF5213_SCM.h"
#include "MCF5213_DMA.h"
#include "MCF5213_UART.h"
#include "MCF5213_I2C.h"
#include "MCF5213_QSPI.h"
#include "MCF5213_DTIM.h"
#include "MCF5213_INTC.h"
#include "MCF5213_GPIO.h"
#include "MCF5213_PAD.h"
#include "MCF5213_RCM.h"
#include "MCF5213_CCM.h"
#include "MCF5213_PMM.h"
#include "MCF5213_CLOCK.h"
#include "MCF5213_EPORT.h"
#include "MCF5213_PIT.h"
#include "MCF5213_ADC.h"
#include "MCF5213_GPTA.h"
#include "MCF5213_PWM.h"
#include "MCF5213_FlexCAN.h"
#include "MCF5213_CANMB.h"
#include "MCF5213_CFM.h"

#ifdef __cplusplus
}
#endif


#endif /* __MCF5213_H__ */
