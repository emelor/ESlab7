/*
** File:     rte_report_instances.c
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

/************************************************
 rteReportInstances
*************************************************/
void rteReportInstances (void)

{ rteSwcInstanceAttr_t const  *swcInstance = 0u;
  rteSwcInterfaceAttr_t const *swcInterface;
  rteSwcBehaviour_t const     *behaviour;
  char                         buffer[132];
  char                        *ptr;
  char const                  *name;
  char const                  *mode;

  fprintf(rteFile,"Report all SWC Instances\n");
  while (rteGetObjectNext (R_OBJECT_CM_INSTANCE,(bsObject_t const **)&swcInstance) == R_OK) {
     name = rteObjectName(swcInstance->object.index);
     ptr  = &buffer[0];
     swcInterface = swcInstance->swcInterface;
     behaviour = swcInstance->behaviour;
     mode         = rteGetModeName(swcInstance->modeIndex);
     ptr = ptr + sprintf(ptr,"\t%s ",name);
     name = rteObjectName(swcInterface->object.index);
     ptr = ptr + sprintf(ptr,"Mode:%s Interface:%s RunTimeProfile:%s ",mode,name,behaviour->runTimeProfileName);
     name = rteObjectName(behaviour->object.index);
     ptr = ptr + sprintf(ptr,"Behaviour:%s\n",name);
     fprintf(rteFile,buffer);
  }

  fprintf(rteFile,"\n");
}
