#ifndef _RTE_CONFIG_H_
#define _RTE_CONFIG_H_
/*
** File:     rte_config.h
**
** Contents: Rubus RCM
**           Rubus RTE 
**           RTE Configuration
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
#ifndef _B_THREAD_H_
#include <blue/b_thread.h>
#endif

#ifndef  _RUBUSOS_CFG_H_
#include <rubusOS_cfg.h>
#endif

#ifndef _RTE_BASIC_H_
#include <rte_basic.h>
#endif

#ifndef _RTE_LOG_H_
#include <rte_log.h>
#endif

#ifndef _HAL_RTE_H_
#include <hal_rte.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*==========================================================
** Null size
==========================================================*/
#define R_NULL_SIZE                     0

/*==========================================================
** Mode Task Entry Access Definitions
==========================================================*/
#define R_MODE_TASK_ACCESS(index)       rteModeVar.modeExec->taskTable[(index)]()

/*==========================================================
** Time Measurement Definitions
==========================================================*/
#define R_RTE_EXEC_TIME_WCET(cb)        ((cb).wcet)
#define R_RTE_EXEC_TIME_BCET(cb)        ((cb).bcet)
#define R_RTE_EXEC_TIME_ACET(cb)        ((cb).acet)
#define R_RTE_EXEC_TIME_BCET_CNT(cb)    ((cb).vCntBcet)
#define R_RTE_EXEC_TIME_WCET_CNT(cb)    ((cb).vCntWcet)

/*==========================================================
** Monitor Flags
==========================================================*/
#define _RTE_IDLE                       0x0001u
#define _RTE_RUNNING                    0X0002u

/*==========================================================
** Flow control test
==========================================================*/
#define R_DATA_FLOW_NORMAL              0
#define R_DATA_FLOW_FORCED              1

/*==========================================================
** RTE Port Definitions
==========================================================*/
#define R_PORT_SIZE_08                  sizeof(uint8_t)
#define R_PORT_SIZE_16                  sizeof(uint16_t)
#define R_PORT_SIZE_32                  sizeof(uint32_t)
#define R_PORT_UNSIGN                   0
#define R_PORT_SIGN                     1

/*==========================================================
** RTE Port Types
==========================================================*/
typedef enum {
      R_PORT_UNDEF     = 00u,
      R_PORT_SCALAR    = 01u,
      R_PORT_PRIMITIVE = 02u,
      R_PORT_COMPOSITE = 03u,
      R_PORT_ENUM      = 04u,
      R_PORT_ARRAY     = 05u
    } rtePortType_t;

typedef struct {
      uint8_t                       dataType;
      uint8_t                       dataSigned;
      uint16_t                      dataSize;
    } rtePortData_t;

typedef struct rtePort_s {
      rtePortData_t                 data;
      char_t const                 *name;
      char_t const                 *typeName;
      struct rtePort_s const       *link;
      void                         *accessAddr;
    } rtePort_t;

typedef struct  {
      uint8_t                       dataType;
      uint16_t                      dimension;
      rtePort_t const              *link;
    } rtePortTable_t;

typedef struct {
      uint16_t                      portType;
      uint16_t                      portIndex;
      char_t const                 *name;
      char_t const                 *typeName;
    } rteSwcPortAttr_t;

/*==========================================================
** Behaviour Time Measurment Control Block
==========================================================*/
typedef struct {
      R_TYPE_TIME_EXEC              temp;
      R_TYPE_TIME_EXEC              bcet;
      R_TYPE_TIME_EXEC              wcet;
      R_TYPE_TIME_EXEC              acet;
      uint_t                        vCntBcet;
      uint_t                        vCntWcet;
    } rteTimeCB_t;

typedef struct {
      uint_t                        bcet;
      uint_t                        wcet;
    } rteExecTimeSet_t;

/*==========================================================
** Interface RTE-Object
==========================================================*/
typedef struct {
      bsObject_t                    object;
      rteTimeCB_t R_LOC_CB         *cb;
      rteBehaviour_t                behaviour;
      char_t const                 *runTimeProfileName;
      rteExecTimeSet_t              timingSet;
    } rteSwcBehaviour_t;

typedef struct {
      bsObject_t                    object;
      uint16_t                      noOfPorts;
      rteSwcPortAttr_t const       *portAttrTable;
    } rteSwcInterfaceAttr_t;

/*==========================================================
** Instance RTE-Object
==========================================================*/
typedef struct {
      bsObject_t                    object;
      uint_t                        modeIndex;
      rteSwcBehaviour_t const      *behaviour;
      rteSwcInterfaceAttr_t const  *swcInterface;
      void  const * const           argument;
      rtePortTable_t const         *portTable;
    } rteSwcInstanceAttr_t;

/*==========================================================
** Monitor Start Control Block
==========================================================*/
typedef struct {
      R_TYPE_TIME_RTE               value;
} rteMonitorStartCB_t;

/*==========================================================
** Monitor Start RTE-Object
==========================================================*/
typedef struct {
      bsObject_t                    object;
      rteMonitorStartCB_t R_LOC_CB  *cb;
    } rteMonitorStartAttr_t;

/*==========================================================
** Monitor Time Control Block
==========================================================*/
typedef struct {
      R_TYPE_TIME_RTE               temp;
      R_TYPE_TIME_RTE               bcet;
      R_TYPE_TIME_RTE               wcet;
      R_TYPE_TIME_RTE               acet;
} rteMonitorTimeCB_t;

/*==========================================================
** Monitor Time RTE-Object
==========================================================*/
typedef struct {
      bsObject_t                    object;
      rteMonitorTimeCB_t R_LOC_CB  *cb;
      rteMonitorStartAttr_t const  *start;
    } rteMonitorTimeAttr_t;

/*==========================================================
** Monitor Conditional Control Block
==========================================================*/
typedef struct {
      R_TYPE_TIME_RTE               diff;
      uint_t                        vCnt;
} rteMonitorCondTimeCB_t;

/*==========================================================
** Monitor Conditional RTE-Object
==========================================================*/
typedef struct {
      bsObject_t                        object;
      R_TYPE_TIME_RTE                   tvCondition;
      rteMonitorCondTimeCB_t R_LOC_CB  *cb;
      rteMonitorStartAttr_t const      *start;
    } rteMonitorCondAttr_t;

/*==========================================================
** Data Flow Control
==========================================================*/
typedef struct {
      void const                   **portAddr;
    } rteDataFlowPorts_t;

/*==========================================================
** Data Flow Control RTE-Object
==========================================================*/
typedef struct {
      bsObject_t                    object;
      uint8_t                      *ctrlAttr;
      uint_t                        entries;
      rteDataFlowPorts_t const     *portTable;
    } rteDataFlow_t;

/*==========================================================
** Task Attribute Type
==========================================================*/
typedef struct {
      rteSwcInstanceAttr_t const   *swcInstance;
    } rteTaskEntry_t;

/*==========================================================
** Task RTE-Object
==========================================================*/
typedef struct {
      bsObject_t                    object;
      uint_t                        modeIndex;
      uint_t                        entries;
      void const                   *thread;
      rteTaskEntry_t const         *entryTable;
    } rteTaskAttr_t;

/*==========================================================
** Mode Information
==========================================================*/
typedef struct  {
      bsObject_t                    object;
      uint_t                        modes;
      rteModeAttr_t const         **modeTable;
    } rteModeTable_t;

/*==========================================================
** Mode Management
==========================================================*/
typedef struct rteModeVar_s {
      uint_t                        flags;
      rteModeRequest_t              command;
      rteModeAttr_t const          *modeExec;
      rteModeAttr_t const          *modeNext;
      int32_t                       timeout;
    } rteModeVar_t;

/*==========================================================
** RTE Information
==========================================================*/
typedef struct {
      uint32_t                      timerResExecPSec;
      uint32_t                      timerResGeneralPSec;
      int_t                         idEntries;
      bsLogIdArray_t               *logIdArray;
      bsObject_t const *const      *idTable;
      bsIdNameElement_t const      *nameTable;
      char_t const * const         *labelCoder;
      char_t const * const         *labelDate;
      char_t const * const         *labelIdentifier;
    } rteAttr_t;

/*==========================================================
** Externals
==========================================================*/
extern rteModeVar_t                 rteModeVar;
extern void                         rteModeEnd (void);
extern blueThreadAttr_t const       blueModeManager;
extern redSchedAttr_t   const       redModeTransitionSchedule;
extern rteAttr_t const              rteAttr;
extern rteModeTable_t const         rteModeTable;

/*==========================================================
** Function prototypes
==========================================================*/
extern void   rteBehaviourInit (void);
extern void   rteMonitorInit (void);
extern int_t  rteModeInit (rteModeId_t mode);

extern void   rteModeEntryUndefinedTT (void);
extern void   rteModeEntryUndefinedET (void);
extern void   rteModeEntryUndefinedIT (void);

extern int_t  rteStrnCmp (char_t const *s1, char_t const *s2, int_t n);
extern void   rteMemCopy (register uint8_t *s, register uint8_t *ct, register int_t n);
extern void   rteMemReset (register uint8_t R_LOC_CB *s, register int_t n );
extern bsObject_t const *rteGetObject (int_t id);
extern int_t             rteGetObjectNext (uint_t type, bsObject_t const **object);


#ifdef __cplusplus
}
#endif


#endif
