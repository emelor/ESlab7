/*
** File: C:\Documents and Settings\emeliehe\Desktop\ESlab7\Embedded7\r_ex_s.c
** Generated by XMLLauncher v3.9.1.77 x86 2011a
**
** Copyright 1995-2011 Arcticus Systems AB, All rights reserved.
** The format and content in the File is protected by copyright.
** The File is furnished under a licence and may only be used in
** accordance with the terms of this licence.
** Rubus� is a registered trademark to which Arcticus has all exclusive rights.
*/

/*==========================================================
** Include files
==========================================================*/
#include <basic/bs_basic.h>
#include <basic/bs_log.h>
#include <hal/hal_cfg.h>
#include <rubusOS_cfg.h>
#include "r_ex_bs.h"
#include "r_ex_r.h"
#include "r_ex_g.h"
#include "r_ex_b.h"


/*==========================================================
** greenAttr
==========================================================*/
greenAttr_t const greenAttr = {
  {2,R_OBJECT_GREEN,0},
  5u
};

/*==========================================================
** Green Thread comXhpRx
==========================================================*/
extern greenThreadCB_t comXhpRxCB;
extern void comXhpRxInternal(void);
greenThreadAttr_t const comXhpRx = {
  {3,R_OBJECT_GREEN_THREAD,0},
  &comXhpRxCB,
  4u,
  0,
  (bsThread_t)&comXhpRxInternal,
  0u
};

/*==========================================================
** Green Thread comXhpTx
==========================================================*/
extern greenThreadCB_t comXhpTxCB;
extern void comXhpTxInternal(void);
greenThreadAttr_t const comXhpTx = {
  {4,R_OBJECT_GREEN_THREAD,0},
  &comXhpTxCB,
  5u,
  0,
  (bsThread_t)&comXhpTxInternal,
  0u
};

/*==========================================================
** redAttr
==========================================================*/
extern struct {
  bsStack_t header;
  uint_t      stack[(1024u + sizeof(uint_t) - 1u) / sizeof(uint_t)];
} redStack;
extern redFrameCB_t R_LOC_VAR redStackFrame[4];
redAttr_t const redAttr = {
  {10,R_OBJECT_RED,0},
  2,
  0u,
  (1024u + sizeof(uint_t) - 1u) / sizeof(uint_t),
  (bsStack_t *)&redStack,
  &redStackFrame[0],
  &redStackFrame[3]
};

/*==========================================================
** Red Thread redStart
==========================================================*/
extern redThreadCB_t redStartCB;
redThreadAttr_t const redStart = {
  {11,R_OBJECT_RED_THREAD,0},
  &redStartCB
};

/*==========================================================
** Red Thread blinkyResched
==========================================================*/
extern redThreadCB_t blinkyReschedCB;
redThreadAttr_t const blinkyResched = {
  {12,R_OBJECT_RED_THREAD,0},
  &blinkyReschedCB
};

/*==========================================================
** Red Thread blinky0
==========================================================*/
extern redThreadCB_t blinky0CB;
redThreadAttr_t const blinky0 = {
  {13,R_OBJECT_RED_THREAD,0},
  &blinky0CB
};

/*==========================================================
** Red Thread blinky1
==========================================================*/
extern redThreadCB_t blinky1CB;
redThreadAttr_t const blinky1 = {
  {14,R_OBJECT_RED_THREAD,0},
  &blinky1CB
};

/*==========================================================
** Red Thread blinky2
==========================================================*/
extern redThreadCB_t blinky2CB;
redThreadAttr_t const blinky2 = {
  {15,R_OBJECT_RED_THREAD,0},
  &blinky2CB
};

/*==========================================================
** Red Thread blinky3
==========================================================*/
extern redThreadCB_t blinky3CB;
redThreadAttr_t const blinky3 = {
  {16,R_OBJECT_RED_THREAD,0},
  &blinky3CB
};

/*==========================================================
** Red Schedule redScheduleBlinky0
==========================================================*/
extern void redScheduleBlinky0_0(void);
redSchedAttr_t const redScheduleBlinky0 = {
  {17,R_OBJECT_RED_SCHEDULE,0},
  100,
  0,
  redScheduleBlinky0_0
};

/*==========================================================
** Red Schedule redSchedule2
==========================================================*/
extern void redSchedule2_0(void);
redSchedAttr_t const redSchedule2 = {
  {18,R_OBJECT_RED_SCHEDULE,0},
  200,
  0,
  redSchedule2_0
};

/*==========================================================
** Red Schedule redSchedule3
==========================================================*/
extern void redSchedule3_0(void);
redSchedAttr_t const redSchedule3 = {
  {19,R_OBJECT_RED_SCHEDULE,0},
  200,
  0,
  redSchedule3_0
};

/*==========================================================
** Red Schedule redScheduleStart
==========================================================*/
extern void redScheduleStart_0(void);
redSchedAttr_t const redScheduleStart = {
  {20,R_OBJECT_RED_SCHEDULE,0},
  10,
  0,
  redScheduleStart_0
};

/*==========================================================
** blueAttr
==========================================================*/
extern struct {
  bsStack_t header;
  uint_t      stack[(1024u + sizeof(uint_t) - 1u) / sizeof(uint_t)];
} blueStack;

blueAttr_t const blueAttr = {
  {5,R_OBJECT_BLUE,0},
  (1024u + sizeof(uint_t) - 1u) / sizeof(uint_t),
  (bsStack_t *)&blueStack,
  0u
};

/*==========================================================
** Blue Thread blueKernel
==========================================================*/
extern void blueKernelEntry(void);
extern blueThreadCB_t blueKernelCB;
blueThreadAttr_t const blueKernel = {
  {8,R_OBJECT_BLUE_THREAD | _R_THREAD_TYPE_NO_STACK,_R_BLOCKED},
  &blueKernelCB,
  15,
  (bsThread_t)&blueKernelEntry,
  0u,
  0u,
  0
};

/*==========================================================
** Blue Thread xhpHandlerRx
==========================================================*/
extern void xhpHandlerRxInternal(void);
extern blueThreadCB_t xhpHandlerRxCB;
extern struct {
  bsStack_t header;
  uint_t      stack[(256u + sizeof(uint_t) - 1u) / sizeof(uint_t)];
} xhpHandlerRxStack;
blueThreadAttr_t const xhpHandlerRx = {
  {6,R_OBJECT_BLUE_THREAD | _R_THREAD_TYPE_STACK,_R_BLOCKED},
  &xhpHandlerRxCB,
  1,
  (bsThread_t)&xhpHandlerRxInternal,
  0u,
  (256u + sizeof(uint_t) - 1u) / sizeof(uint_t),
  (bsStack_t *)&xhpHandlerRxStack
};

/*==========================================================
** Blue Thread xhpHandlerTx
==========================================================*/
extern void xhpHandlerTxInternal(void);
extern blueThreadCB_t xhpHandlerTxCB;
extern struct {
  bsStack_t header;
  uint_t      stack[(256u + sizeof(uint_t) - 1u) / sizeof(uint_t)];
} xhpHandlerTxStack;
blueThreadAttr_t const xhpHandlerTx = {
  {7,R_OBJECT_BLUE_THREAD | _R_THREAD_TYPE_STACK,_R_BLOCKED},
  &xhpHandlerTxCB,
  1,
  (bsThread_t)&xhpHandlerTxInternal,
  0u,
  (256u + sizeof(uint_t) - 1u) / sizeof(uint_t),
  (bsStack_t *)&xhpHandlerTxStack
};

/*==========================================================
** Blue Thread blueIdle
==========================================================*/
extern void rubusIdleMain(void);
extern blueThreadCB_t blueIdleCB;
blueThreadAttr_t const blueIdle = {
  {9,R_OBJECT_BLUE_THREAD | _R_THREAD_TYPE_NO_STACK,_R_BLOCKED},
  &blueIdleCB,
  0,
  (bsThread_t)&rubusIdleMain,
  0u,
  0u,
  0
};

/*==========================================================
** bsIdNameTable
==========================================================*/
bsIdNameElement_t const bsIdNameTable[21] ={
  /*  0 */ {"bsAttr",6},
  /*  1 */ {"bsLogAttr",9},
  /*  2 */ {"greenAttr",9},
  /*  3 */ {"comXhpRx",8},
  /*  4 */ {"comXhpTx",8},
  /*  5 */ {"blueAttr",8},
  /*  6 */ {"xhpHandlerRx",12},
  /*  7 */ {"xhpHandlerTx",12},
  /*  8 */ {"blueKernel",10},
  /*  9 */ {"blueIdle",8},
  /* 10 */ {"redAttr",7},
  /* 11 */ {"redStart",8},
  /* 12 */ {"blinkyResched",13},
  /* 13 */ {"blinky0",7},
  /* 14 */ {"blinky1",7},
  /* 15 */ {"blinky2",7},
  /* 16 */ {"blinky3",7},
  /* 17 */ {"redScheduleBlinky0",18},
  /* 18 */ {"redSchedule2",12},
  /* 19 */ {"redSchedule3",12},
  /* 20 */ {"redScheduleStart",16}
};

/*==========================================================
** bsAttr
==========================================================*/
extern char_t const *bsOSLabel;
extern bsLogIdArray_t bsLogIdArray[21];
char_t const * const bsLabelDate = "2012-09-06T14:20:44";
char_t const * const bsLabelCoder = "Generic:v3.9.1 (Build 77) 2011a";
char_t const * const bsLabelIdentifier = "6f9f9469-109f-447e-b98b-ec7ec0e712de";
bsObject_t const * const bsIdTable[21] ={
  /*  0 */ (bsObject_t const *)&bsAttr,
  /*  1 */ (bsObject_t const *)&bsLogAttr,
  /*  2 */ (bsObject_t const *)&greenAttr,
  /*  3 */ (bsObject_t const *)&comXhpRx,
  /*  4 */ (bsObject_t const *)&comXhpTx,
  /*  5 */ (bsObject_t const *)&blueAttr,
  /*  6 */ (bsObject_t const *)&xhpHandlerRx,
  /*  7 */ (bsObject_t const *)&xhpHandlerTx,
  /*  8 */ (bsObject_t const *)&blueKernel,
  /*  9 */ (bsObject_t const *)&blueIdle,
  /* 10 */ (bsObject_t const *)&redAttr,
  /* 11 */ (bsObject_t const *)&redStart,
  /* 12 */ (bsObject_t const *)&blinkyResched,
  /* 13 */ (bsObject_t const *)&blinky0,
  /* 14 */ (bsObject_t const *)&blinky1,
  /* 15 */ (bsObject_t const *)&blinky2,
  /* 16 */ (bsObject_t const *)&blinky3,
  /* 17 */ (bsObject_t const *)&redScheduleBlinky0,
  /* 18 */ (bsObject_t const *)&redSchedule2,
  /* 19 */ (bsObject_t const *)&redSchedule3,
  /* 20 */ (bsObject_t const *)&redScheduleStart
};

bsAttr_t const bsAttr = {
  {0,R_OBJECT_BASIC,0},
  1000L,
  1000000L,
  4000000,
  4000000,
  3u,
  0u,
  21,
  &bsLogIdArray[0],
  &bsIdTable[0],
  &bsIdNameTable[0],
  &bsOSLabel,
  &bsLabelCoder,
  &bsLabelDate,
  &bsLabelIdentifier
};

/*==========================================================
** bsLogAttr
==========================================================*/
extern bsLogElm_t R_LOC_FAR bsLogBuffer[1024];
bsLogAttr_t const bsLogAttr = {
  {1,R_OBJECT_BASIC_LOG,0},
  0u,
  1023,
  &bsLogBuffer[0]
};

