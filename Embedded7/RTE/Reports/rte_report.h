#ifndef _RTE_REPORT_H_
#define _RTE_REPORT_H_
/*
** File:     rte_report.h
**
** Contents: Rubus RCM
**           Rubus RTE 
**           Report Services
**
** Version:  1.0
**
** Copyright 1996-2011 Arcticus Systems AB, All Rights Reserved.
** The format and content in the File is protected by copyright.
** The File is furnished under a licence and may only be used in
** accordance with the terms of this licence.
*/

#ifdef WIN32
#define _CRT_SECURE_NO_WARNINGS /* Use this definition to avoid warnings on variable argument length */
#endif

#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

/*=========================================================
  Externals
=========================================================*/
extern FILE *rteFile;

/*=========================================================
  Prototypes
=========================================================*/
extern void rteFileOpen (char *filename);
extern void rteFileClose (void);
extern void rteReportMonitorTime (void);
extern void rteReportMonitorConditional (void);
extern void rteReportPortAllInstances (void);
extern void rteReportPortInstanceIndex (unsigned int index);
extern void rteReportInstances (void);
extern void rteReportInterfaces (void);
extern void rteReportTasks (void);
extern void rteReportBehaviours (void);

#ifdef __cplusplus
}
#endif


#endif
