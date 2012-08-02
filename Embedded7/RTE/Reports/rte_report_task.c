/*
** File:     rte_report_tasks.c
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

extern bsName_t bsObjectName(int_t id);

/************************************************
 rteReportTasks
*************************************************/
void rteReportTasks (void)

{ rteTaskAttr_t const          *task = 0u;
  rteTaskEntry_t const         *entry;    
  rteSwcInterfaceAttr_t const  *swcInterface;
  rteSwcInstanceAttr_t const   *swcInstance;
  rteSwcBehaviour_t const      *behaviour;
  bsObject_t const             *thread;
  char                          buffer[132];
  char                         *ptr;
  char const                   *name;
  char const                   *mode;
  uint_t                        i;

  fprintf(rteFile,"Report all Tasks\n");
  while (rteGetObjectNext ((R_OBJECT_CM_TASK | R_OBJECT_CM_SUB_CLASS),(bsObject_t const **)&task) == R_OK) {
    name = rteObjectName(task->object.index);
    ptr  = &buffer[0];
    ptr = ptr + sprintf(ptr,"--%s ",name);
    thread = (bsObject_t const*)task->thread;
    name   = bsObjectName(thread->index);
    mode   = rteGetModeName(task->modeIndex);
    ptr = ptr + sprintf(ptr,"Mode:%s Entries:%d Thread:%s\n",mode,task->entries,name);
    fprintf(rteFile,buffer);
    for (i = 0; i < task->entries; i++) {
      entry = &task->entryTable[i];
      swcInstance  = entry->swcInstance;
      swcInterface = swcInstance->swcInterface;
      behaviour    = swcInstance->behaviour;
      name = rteObjectName(behaviour->object.index);
      ptr  = &buffer[0];
      ptr = ptr + sprintf(ptr,"\tBehaviour:%s\n",name);
      fprintf(rteFile,buffer);
    }
  }

  fprintf(rteFile,"\n");
}

/************************************************
 rteReportAll
*************************************************/
void rteReportAll (void)

{
  rteReportInstances();
  rteReportInterfaces();
  rteReportTasks();
}
