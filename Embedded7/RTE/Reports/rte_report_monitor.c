/*
** File:     rte_report_monitor.c
**
** Contents: Rubus RCM
**           Rubus RTE 
**           Report File Services
**
** Version:  1.0
**
** Copyright 1996-2011 Arcticus Systems AB, All Rights Reserved.
** The format and content in the File is protected by copyright.
** The File is furnished under a licence and may only be used in
** accordance with the terms of this licence.
*/

#ifndef _RTE_CONFIG_H_
#include <rte_config.h>
#endif

#ifndef _RTE_SERVICES_H_
#include <rte_services.h>
#endif

#ifndef _RTE_REPORT_H_
#include <rte_report.h>
#endif

/*===============================================
  Externals
===============================================*/
extern bsName_t bsObjectName(int_t id);

/*===============================================
  Defines
===============================================*/

/*==============================================
  Text Tables
===============================================*/

/************************************************
 rteReportMonitorTime
*************************************************/
void rteReportMonitorTime (void)

{ rteMonitorTimeAttr_t const  *object = 0u;
  char                         buffer[132];
  char                        *ptr;
  char const                  *name;

  fprintf(rteFile,"List all Time Monitors\n");
  while (rteGetObjectNext ((R_OBJECT_CM_MONITOR_TIME),(bsObject_t const **)&object) == R_OK) {
     if (object->object.type == R_OBJECT_CM_MONITOR_TIME) {
       ptr  = &buffer[0];
       name = bsObjectName(object->object.index);
       ptr = ptr + sprintf(ptr,"--%s ",name);

       ptr = ptr + sprintf(ptr,"Measured:%d\n",object->cb->temp);
       fprintf(rteFile,buffer);
     }
  }

  fprintf(rteFile,"\n");
}

/************************************************
 rteReportMonitorConditional
*************************************************/
void rteReportMonitorConditional (void)

{ rteMonitorCondAttr_t const  *object = 0u;
  char                         buffer[132];
  char                        *ptr;
  char const                  *name;

  fprintf(rteFile,"List all Conditionakl Monitors\n");
  while (rteGetObjectNext ((R_OBJECT_CM_MONITOR_CONDITIONAL),(bsObject_t const **)&object) == R_OK) {
     if (object->object.type == R_OBJECT_CM_MONITOR_CONDITIONAL) {
       ptr  = &buffer[0];
       name = bsObjectName(object->object.index);
       ptr = ptr + sprintf(ptr,"--%s ",name);

       ptr = ptr + sprintf(ptr,"Condition:%d Vcnt:%d Measured:%d\n",object->tvCondition,object->cb->vCnt,object->cb->diff);
       fprintf(rteFile,buffer);
     }
  }

  fprintf(rteFile,"\n");
}
