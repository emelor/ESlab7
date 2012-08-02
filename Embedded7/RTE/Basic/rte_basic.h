#ifndef _RTE_BASIC_H_
#define _RTE_BASIC_H_
/*
** File:     rte_basic.h
**
** Contents: Rubus RCM
**           Rubus RTE 
**           Basic Definitions
**
** Version:  1.0
**
** Copyright 1996-2011 Arcticus Systems AB, All Rights Reserved.
** The format and content in the File is protected by copyright.
** The File is furnished under a licence and may only be used in
** accordance with the terms of this licence.
*/

/*==========================================================
** Include files
==========================================================*/
#ifndef _BS_BASIC_H_
#include <basic/bs_basic.h>
#endif

#ifndef _R_THREAD_H_
#include <red/r_thread.h>
#endif

#ifndef _HAL_CFG_H_
#include <hal/hal_cfg.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*==========================================================
** Port Access Definitions
==========================================================*/
#define R_IP(port)                        (*(args->IP.rte_##port))
#define R_IP_A(type,port)                 ((type *)args->IP.rte_##port)
#define R_IP_C(port,element)              args->IP.rte_##port->element

#define R_OP(port)                        args->OP->rte_##port
#define R_OP_PTR(port)                    &args->OP->rte_##port
#define R_OP_C(port,element)              args->OP->rte_##port.element
#define R_OP_C_PTR(port,element)          &args->OP->rte_##port.element

#define R_SP(port)                        args->ST->rte_##port
#define R_SP_PTR(port)                    &args->ST->rte_##port
#define R_SP_C(port,element)              args->ST->rte_##port.element
#define R_SP_C_PTR(port,element)          &args->ST->rte_##port.element

#define R_PORT_IN(port)                   (*(args->IP.rte_##port))
#define R_PORT_IN_A(type,port)            ((type *)args->IP.rte_##port)
#define R_PORT_IN_C(port,element)         args->IP.rte_##port->element

#define R_PORT_OUT(port)                  args->OP->rte_##port
#define R_PORT_OUT_PTR(port)              &args->OP->rte_##port
#define R_PORT_OUT_C(port,element)        args->OP->rte_##port.element
#define R_PORT_OUT_C_PTR(port,element)    &args->OP->rte_##port.element

#define R_PORT_STATE(port)                args->ST->rte_##port
#define R_PORT_STATE_PTR(port)            &args->ST->rte_##port
#define R_PORT_STATE_C(port,element)      args->ST->rte_##port.element
#define R_PORT_STATE_C_PTR(port,element)  &args->ST->rte_##port.element

/*==========================================================
** Rubus CM Object Definitions
==========================================================*/
#define R_OBJECT_CM_BEHAVIOUR             0x1100u
#define R_OBJECT_CM_INTERFACE             0x1200u
#define R_OBJECT_CM_INSTANCE              0x1300u
#define R_OBJECT_CM_ARG_TABLE             0x1400u
#define R_OBJECT_CM_INTERRUPT             0x1500u

#define R_OBJECT_CM_MODE                  0x2100u
#define R_OBJECT_CM_MODE_TABLE            0x2200u

#define R_OBJECT_CM_TASK                  0x2400u
#define R_OBJECT_CM_TASK_IT               0x2401u
#define R_OBJECT_CM_TASK_ET               0x2402u
#define R_OBJECT_CM_TASK_TT               0x2403u

#define R_OBJECT_CM_PORT                  0x3100u
#define R_OBJECT_CM_PORT_IP               0x3101u
#define R_OBJECT_CM_PORT_OP               0x3102u
#define R_OBJECT_CM_PORT_ST               0x3103u

#define R_OBJECT_CM_DATA_FLOW_CTRL        0x4100u

#define R_OBJECT_CM_MONITOR               0x5100u
#define R_OBJECT_CM_MONITOR_START         0x5101u
#define R_OBJECT_CM_MONITOR_TIME          0x5102u
#define R_OBJECT_CM_MONITOR_CONDITIONAL   0x5103u

#define R_OBJECT_CM_TYPE_SET              0xFF00u /* Set of all Object Types */
#define R_OBJECT_CM_SUB_CLASS             0x00FFu /* Object sub class mask */

#define R_RTE_ERROR_SELECT                256
#define R_RTE_ERROR_SUPERVISE             257
#define R_RTE_ERROR_MONITOR               258

/*==========================================================
** Mode Request Command Type
==========================================================*/
typedef enum {
      R_MODE_NA = 0,
      R_MODE_IMMEDIATE = 1,
      R_MODE_FIRST_APPROPRIATE = 2,
      R_MODE_BEST_APPROPRIATE = 3
    } rteModeRequest_t;

/*==========================================================
** Mode Entry
==========================================================*/
typedef void (*rteModeTask_t) (void);
typedef void (*rteBehaviour_t) (void *args);

/*==========================================================
** Interrupt Attribute
==========================================================*/
typedef struct rteInterruptAttr_s {
      bsObject_t                object;
      uint16_t                  priority;
      uint16_t                  osServices;
      void const                *thread;
    } rteInterruptAttr_t;

typedef rteInterruptAttr_t const *rteInterruptId_t;

/*==========================================================
** Mode Attribute
==========================================================*/
typedef struct rteModeAttr_s {
      bsObject_t                object;
      uint_t                    modeIndex;
      redSchedAttr_t const      *redSchedule;
      rteModeTask_t const       *taskTable;
    } rteModeAttr_t;

typedef rteModeAttr_t const     *rteModeId_t;

/*==========================================================
** Mode Status Type
==========================================================*/
typedef struct rteModeStatus_s {
      uint_t                    flags;
      int_t                     remainingTicks;
      rteModeId_t               mode;
    } rteModeStatus_t;

/*==========================================================
** Prototypes
==========================================================*/
extern int_t rteInit (void);
extern void  rteDestroy (void);

extern int_t rteModeRequest (rteModeRequest_t command, rteModeId_t mode, int32_t timeout);
extern void  rteModeQuerry (rteModeStatus_t *modeStatus);

extern void  rteErrorIT (int_t code, bsObject_t const *object);
extern void  rteErrorET (int_t code, bsObject_t const *object);
extern void  rteErrorTT (int_t code, bsObject_t const *object);

#ifdef __cplusplus
}
#endif


#endif
