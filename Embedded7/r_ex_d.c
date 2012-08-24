/*
** File: C:\Documents and Settings\emeliehe\Desktop\Embedded7\r_ex_d.c
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
#include "r_ex_bs.h"
#include "r_ex_r.h"
#include "r_ex_g.h"
#include "r_ex_b.h"

/*==========================================================
** redAttr
==========================================================*/
struct {
  bsStack_t header;
  uint_t      stack[(1024 + sizeof(uint_t) - 1) / sizeof(uint_t)];
} redStack;
redFrameCB_t R_LOC_VAR redStackFrame[4];

/*==========================================================
** Red Thread redStart
==========================================================*/
redThreadCB_t redStartCB;

/*==========================================================
** Red Thread blinky0
==========================================================*/
redThreadCB_t blinky0CB;
int blinky0Args;

/*==========================================================
** Red Thread blinky1
==========================================================*/
redThreadCB_t blinky1CB;
int blinky1Args;

/*==========================================================
** Red Thread blinky2
==========================================================*/
redThreadCB_t blinky2CB;
int blinky2Args;

/*==========================================================
** Red Thread blinky3
==========================================================*/
redThreadCB_t blinky3CB;
int blinky3Args;

/*==========================================================
** blueAttr
==========================================================*/
struct {
  bsStack_t header;
  uint_t      stack[(1024u + sizeof(uint_t) - 1u) / sizeof(uint_t)];
} blueStack;

blueThreadCB_t * R_LOC_CB blueIntrTable[3];
blueThreadCB_t * R_LOC_CB * const blueIntrTableTop = &blueIntrTable[0];
blueThreadCB_t * R_LOC_CB * const blueIntrTableBottom = &blueIntrTable[2];

/*==========================================================
** Blue Thread blueKernel
==========================================================*/
blueThreadCB_t blueKernelCB;

/*==========================================================
** Blue Thread blueIdle
==========================================================*/
blueThreadCB_t blueIdleCB;

bsLogIdArray_t bsLogIdArray[15];

/*==========================================================
** bsAttr
==========================================================*/
/*==========================================================
** bsLogAttr
==========================================================*/
bsLogElm_t R_LOC_FAR bsLogBuffer[1024];

