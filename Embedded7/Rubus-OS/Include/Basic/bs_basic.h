#ifndef  _BS_BASIC_H_
#define  _BS_BASIC_H_
/*
** File:     bs_basic.h
**
** Contents: Rubus OS
**           Basic Services
**           Basic Definitions.
**
** Version:  4.1
**
** Copyright 1996-2010 Arcticus Systems AB
**           All Rights Reserved
**
*/

#ifndef _HAL_ENV_H_
#include <hal/hal_env.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*===============================================
  Return Codes
===============================================*/
#define R_OK                                      0
#define R_ERROR                                   (-1)

/*==============================================
 Booleas Defines 
===============================================*/
#define R_TRUE                                    1
#define R_FALSE                                   0

/*===============================================
  Error Codes
===============================================*/
#define R_ERROR_ACCESS_DENIED                     2
#define R_ERROR_INVALID_ATTRIBUTE                 3
#define R_ERROR_INVALID_PARAMETER                 4
#define R_ERROR_INVALID_CONTROL_BLOCK             5
#define R_ERROR_OBJECT_DOES_NOT_EXIST             6
#define R_ERROR_OPERATION_INPROGRESS              7
#define R_ERROR_OPERATION_TIMEOUT                 8
#define R_ERROR_NOT_PERMITTED                     9
#define R_ERROR_SIZE                              10
#define R_ERROR_EMPTY                             11
#define R_ERROR_FULL                              12
#define R_ERROR_BUSY                              13
#define R_ERROR_CHECKSUM                          14
#define R_ERROR_IO                                15

/*===============================================
  Error Codes, Internal Errors
===============================================*/
#define R_ERROR_STACK_INCONSISTENT                128 /* Stack is corrupt */
#define R_ERROR_DEADLINE_OVERRUN                  129 /* Deadline overrun */
#define R_ERROR_EXECUTION_TIME                    130 /* Execution time overflow or underflow */
#define R_ERROR_PREEMPTION_OVERFLOW               131 /* Red preemption overflow */  
#define R_ERROR_FREQUENCY_OVERFLOW                132 /* Interrupt frequency overflow */
#define R_ERROR_PRIORITY                          134 /* Priority out of range */
#define R_ERROR_CORRUPT_RQ                        135 /* Ready Queue Corrupt */
#define R_ERROR_CORRUPT_IRQ                       136 /* Interrupt Queue Corrupt */

/*===============================================
  Open Flags
===============================================*/
#define _R_READ                         0x0001u                  /* Read only file */
#define _R_WRITE                        0x0002u                  /* Write only file */
#define _R_RDWR                         (_R_READ|_R_WRITE)      /* Read/write flag */
#define _R_APPEND                       0x0004u                  /* Append to file */
#define _R_BLOCKED                      0x0020u                  /* Blocked */
#define _R_EOF                          0x0100u                  /* EOF indicator */
#define _R_IN                           0x0200u                  /* Data is incoming */
#define _R_OUT                          0x0400u                  /* Data is outgoing */
#define _R_REWIND                       0x0800u                  /* Rewind */
#define _R_BUSY                         0x1000u                  /* Busy */
#define _R_OVERWRITE                    0x2000u                  /* Overwriting semantics */
#define _R_INIT                         0x4000u                  /* Initiate and open */
#define _R_RESET                        0x8000u                  /* Reset memory */

/*============================================
  Object Types
============================================*/
#define R_OBJECT_BASIC                  0x0100u /* Basic Object */
#define R_OBJECT_BASIC_LOG              0x0110u /* Basic Log Object */
#define R_OBJECT_BASIC_QUEUE            0x0120u /* Basic Queue Object */
#define R_OBJECT_BASIC_POOL             0x0130u /* Basic Memory Pool Object */
#define R_OBJECT_BASIC_MAILBOX          0x0140u /* Basic Mailbox Object */
#define R_OBJECT_BASIC_USER             0x0150u /* Basic User Defined Object */

#define R_OBJECT_GREEN                  0x0200u /* Green Object */
#define R_OBJECT_GREEN_THREAD           0x0210u /* Green Thread Object */

#define R_OBJECT_RED                    0x0400u /* Red Object */
#define R_OBJECT_RED_SCHEDULE           0x0410u /* Red Schedule Object */
#define R_OBJECT_RED_THREAD             0x0420u /* Red Thread Base Object */

#define R_OBJECT_BLUE                   0x0800u /* Blue Object */
#define R_OBJECT_BLUE_THREAD            0x0810u /* Blue Thread Object */
#define R_OBJECT_BLUE_MUTEX             0x0830u /* Blue Mutex Object */
#define R_OBJECT_BLUE_MSG               0x0840u /* Blue Message Queue Object */
#define R_OBJECT_BLUE_SEM               0x0850u /* Blue Semaphore Object */

#define R_OBJECT_TYPE_SET               0xFFF0u /* Set of all Object Types */
#define R_OBJECT_SUB_CLASS              0x000Fu /* Object sub class mask */

/*===============================================
  Object Type Sub Classes
===============================================*/
#define _R_THREAD_TYPE_STACK             0x0001u /* Blue Thread, Event Triggered, Individual Stack */
#define _R_THREAD_TYPE_NO_STACK          0x000Cu /* Blue Thread, Event Triggered, Shared Stack */

/*============================================
  Kernel Mode Types
============================================*/
#define R_MODE_BLUE                     0u
#define R_MODE_RED                      1u
#define R_MODE_GREEN                    2u

/*===============================================
  Time Definitions 
  Time Supervised Services
===============================================*/
#define R_TIME_WAIT_INFINITY         ((void *)0u)
#define R_TIME_NO_WAIT                 0u

/*===============================================
  Nano Seconds 10**9
===============================================*/
#define R_BASIC_NSEC                   1000000000Lu

/*===============================================
  Object Identifier Type
===============================================*/
typedef char_t const           *bsName_t;

/*============================================
  Double Link structure
============================================*/
typedef struct bsLinkD_s
        { struct bsLinkD_s     *next;
          struct bsLinkD_s     *prev;
        } bsLinkD_t;

/*============================================
  Object Structure
============================================*/
typedef struct bsObject_s
        { int16_t               index;
          uint16_t              type;
          uint_t                flags;
        } bsObject_t;

/*===============================================
  Time Structure
===============================================*/
typedef struct bsPosixTime_s {
          uint32_t              tvSec;
          int32_t               tvNsec;
        } bsPosixTime_t;

/*===============================================
  Basic Execution Time Type
===============================================*/
typedef struct bsExecTime_s {  
          R_TYPE_TIME_EXEC      temp;
          R_TYPE_TIME_EXEC      bcet;
          R_TYPE_TIME_EXEC      wcet;
          R_TYPE_TIME_EXEC      acet;
        } bsExecTime_t;

/*===============================================
  Basic Services Status Type
===============================================*/
typedef struct {
          uint_t                execMode;
          uint_t                preemptionLevel;
          uint_t                lcetBasicTimer;
        } bsStatus_t;

/*===============================================
  Stack Structure
===============================================*/
typedef struct bsStack_s
        { int_t                 nUnits;
          uint_t               *TOS;
          struct bsStack_s    **BOS;
          struct bsStack_s     *self;
        } bsStack_t;

/*===============================================
  Basic Thread Type
===============================================*/
typedef void  *bsThreadArg_t;
typedef void (*bsThread_t)(void *args);

/*===============================================
  Externals
===============================================*/

/*===============================================
  Prototypes
===============================================*/
extern int_t    bsRubusInit (void);
extern void     bsRubusStart (void);

extern void     bsStatus (bsStatus_t *status);

extern void     bsClockSetTime (uint32_t *tp);
extern void     bsClockGetTime (uint32_t *tp);
extern int_t    bsResourceNext (uint_t type, bsObject_t const **object);
extern uint32_t bsTvToJiffies (bsPosixTime_t const *value);
extern void     bsJiffiesToTv (uint32_t jiffies, bsPosixTime_t *value);

extern uint8_t  *bsB8ToString(uint8_t *str, uint8_t data);
extern uint8_t  *bsB16ToString(uint8_t *str, uint16_t data);
extern uint8_t  *bsB32ToString(uint8_t *str, uint32_t data);
extern uint16_t  bsStringToB16(uint8_t *str);
extern uint32_t  bsStringToB32(uint8_t *str);

#ifdef R_SUPPORT_64_BIT
extern uint8_t  *bsB64ToString(uint8_t *str, uint64_t data);
extern uint64_t  bsStringToB64(uint8_t *str);
#endif

/* User defined services */
extern void     halBsTimerDisable (void);
extern void     halBsTimerEnable (void);
extern void     halBsTimerReload (void);
extern void     halBsTimerStart (void);
extern void     halBsTimerStop (void);

extern R_TYPE_TIME_EXEC halBsExecTimeGet(void);
extern void             halBsExecTimeResume (R_TYPE_TIME_EXEC value, uint_t adjust);
extern R_TYPE_TIME_EXEC halBsExecTimeStart (void);
extern R_TYPE_TIME_EXEC halBsExecTimeStop  (R_TYPE_TIME_EXEC value, uint_t adjust);
extern uint32_t         halBsFreeRunTimerGet (void);


#ifdef __cplusplus
}
#endif
#endif

