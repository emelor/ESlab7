/*
** File: C:\Documents and Settings\emeliehe\Desktop\Embedded7\r_ex_c.c
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
** redStartInternal()
==========================================================*/
extern redThreadCB_t redStartCB;
void redStartInternal(int_t deadline)

{ R_TYPE_TIME_EXEC execTime;

  bsLogPut(7,R_LOG_EVENT_1);
  R_RED_SET_DEADLINE(&redStart,deadline)
  R_EXEC_TIME_START(execTime)
  R_RED_KERNEL_EXIT;
  redStartMain();
  R_RED_KERNEL_ENTER;
  R_EXEC_TIME_STOP(execTime,execTime,0u)
  bsLogPut(7,R_LOG_EVENT_2);
}

/*==========================================================
** blinky0Internal()
==========================================================*/
extern redThreadCB_t blinky0CB;
void blinky0Internal(int_t deadline)

{ R_TYPE_TIME_EXEC execTime;

  bsLogPut(8,R_LOG_EVENT_1);
  R_RED_SET_DEADLINE(&blinky0,deadline)
  R_EXEC_TIME_START(execTime)
  R_RED_KERNEL_EXIT;
  blinky0Main(&blinky0Args);
  R_RED_KERNEL_ENTER;
  R_EXEC_TIME_STOP(execTime,execTime,0u)
  bsLogPut(8,R_LOG_EVENT_2);
}

/*==========================================================
** Red Schedule redScheduleBlinky0 Releasetime 0
==========================================================*/
extern void redScheduleBlinky0_5(void);
void redScheduleBlinky0_0(void)

{
  bsLogPut(9,R_LOG_EVENT_1);
  R_RED_NEXT(&redScheduleBlinky0_5,5)
  blueActivate(&blueKernel);
  blinky0Internal(2);
}

/*==========================================================
** Red Schedule redScheduleBlinky0 Releasetime 5
==========================================================*/
extern void redScheduleBlinky0_10(void);
void redScheduleBlinky0_5(void)

{
  R_RED_NEXT(&redScheduleBlinky0_10,10)
  blueActivate(&blueKernel);
}

/*==========================================================
** Red Schedule redScheduleBlinky0 Releasetime 10
==========================================================*/
extern void redScheduleBlinky0_15(void);
void redScheduleBlinky0_10(void)

{
  R_RED_NEXT(&redScheduleBlinky0_15,15)
  blueActivate(&blueKernel);
}

/*==========================================================
** Red Schedule redScheduleBlinky0 Releasetime 15
==========================================================*/
extern void redScheduleBlinky0_20(void);
void redScheduleBlinky0_15(void)

{
  R_RED_NEXT(&redScheduleBlinky0_20,20)
  blueActivate(&blueKernel);
}

/*==========================================================
** Red Schedule redScheduleBlinky0 Releasetime 20
==========================================================*/
extern void redScheduleBlinky0_25(void);
void redScheduleBlinky0_20(void)

{
  R_RED_NEXT(&redScheduleBlinky0_25,25)
  blueActivate(&blueKernel);
}

/*==========================================================
** Red Schedule redScheduleBlinky0 Releasetime 25
==========================================================*/
extern void redScheduleBlinky0_30(void);
void redScheduleBlinky0_25(void)

{
  R_RED_NEXT(&redScheduleBlinky0_30,30)
  blueActivate(&blueKernel);
}

/*==========================================================
** Red Schedule redScheduleBlinky0 Releasetime 30
==========================================================*/
extern void redScheduleBlinky0_35(void);
void redScheduleBlinky0_30(void)

{
  R_RED_NEXT(&redScheduleBlinky0_35,35)
  blueActivate(&blueKernel);
}

/*==========================================================
** Red Schedule redScheduleBlinky0 Releasetime 35
==========================================================*/
extern void redScheduleBlinky0_40(void);
void redScheduleBlinky0_35(void)

{
  R_RED_NEXT(&redScheduleBlinky0_40,40)
  blueActivate(&blueKernel);
}

/*==========================================================
** Red Schedule redScheduleBlinky0 Releasetime 40
==========================================================*/
extern void redScheduleBlinky0_45(void);
void redScheduleBlinky0_40(void)

{
  R_RED_NEXT(&redScheduleBlinky0_45,45)
  blueActivate(&blueKernel);
}

/*==========================================================
** Red Schedule redScheduleBlinky0 Releasetime 45
==========================================================*/
extern void redScheduleBlinky0_50(void);
void redScheduleBlinky0_45(void)

{
  R_RED_NEXT(&redScheduleBlinky0_50,50)
  blueActivate(&blueKernel);
}

/*==========================================================
** Red Schedule redScheduleBlinky0 Releasetime 50
==========================================================*/
extern void redScheduleBlinky0_55(void);
void redScheduleBlinky0_50(void)

{
  R_RED_NEXT(&redScheduleBlinky0_55,55)
  blueActivate(&blueKernel);
}

/*==========================================================
** Red Schedule redScheduleBlinky0 Releasetime 55
==========================================================*/
extern void redScheduleBlinky0_60(void);
void redScheduleBlinky0_55(void)

{
  R_RED_NEXT(&redScheduleBlinky0_60,60)
  blueActivate(&blueKernel);
}

/*==========================================================
** Red Schedule redScheduleBlinky0 Releasetime 60
==========================================================*/
extern void redScheduleBlinky0_65(void);
void redScheduleBlinky0_60(void)

{
  R_RED_NEXT(&redScheduleBlinky0_65,65)
  blueActivate(&blueKernel);
}

/*==========================================================
** Red Schedule redScheduleBlinky0 Releasetime 65
==========================================================*/
extern void redScheduleBlinky0_70(void);
void redScheduleBlinky0_65(void)

{
  R_RED_NEXT(&redScheduleBlinky0_70,70)
  blueActivate(&blueKernel);
}

/*==========================================================
** Red Schedule redScheduleBlinky0 Releasetime 70
==========================================================*/
extern void redScheduleBlinky0_75(void);
void redScheduleBlinky0_70(void)

{
  R_RED_NEXT(&redScheduleBlinky0_75,75)
  blueActivate(&blueKernel);
}

/*==========================================================
** Red Schedule redScheduleBlinky0 Releasetime 75
==========================================================*/
extern void redScheduleBlinky0_80(void);
void redScheduleBlinky0_75(void)

{
  R_RED_NEXT(&redScheduleBlinky0_80,80)
  blueActivate(&blueKernel);
}

/*==========================================================
** Red Schedule redScheduleBlinky0 Releasetime 80
==========================================================*/
extern void redScheduleBlinky0_85(void);
void redScheduleBlinky0_80(void)

{
  R_RED_NEXT(&redScheduleBlinky0_85,85)
  blueActivate(&blueKernel);
}

/*==========================================================
** Red Schedule redScheduleBlinky0 Releasetime 85
==========================================================*/
extern void redScheduleBlinky0_90(void);
void redScheduleBlinky0_85(void)

{
  R_RED_NEXT(&redScheduleBlinky0_90,90)
  blueActivate(&blueKernel);
}

/*==========================================================
** Red Schedule redScheduleBlinky0 Releasetime 90
==========================================================*/
extern void redScheduleBlinky0_95(void);
void redScheduleBlinky0_90(void)

{
  R_RED_NEXT(&redScheduleBlinky0_95,95)
  blueActivate(&blueKernel);
}

/*==========================================================
** Red Schedule redScheduleBlinky0 Releasetime 95
==========================================================*/
extern void redScheduleBlinky0_0(void);
void redScheduleBlinky0_95(void)

{
  blueActivate(&blueKernel);
}

/*==========================================================
** Red Schedule redScheduleStart Releasetime 0
==========================================================*/
extern void redScheduleStart_5(void);
void redScheduleStart_0(void)

{
  bsLogPut(10,R_LOG_EVENT_1);
  R_RED_NEXT(&redScheduleStart_5,5)
  blueActivate(&blueKernel);
  redStartInternal(10);
}

/*==========================================================
** Red Schedule redScheduleStart Releasetime 5
==========================================================*/
extern void redScheduleStart_0(void);
void redScheduleStart_5(void)

{
  blueActivate(&blueKernel);
}

/*==========================================================
** Rubus OS Initialisation
==========================================================*/
int_t bsRubusInit(void)

{ int_t rcode;

  rcode = bsInit();
  if (rcode != R_OK) {
    return(rcode);
  }

  rcode = redInit(&redScheduleStart);
  if (rcode != R_OK) {
    return(rcode);
  }

  rcode = blueInit();
  if (rcode != R_OK) {
    return(rcode);
  }

  rcode = blueThreadInitAll();
  if (rcode != R_OK) {
    return(rcode);
  }

  return(R_OK);
}

