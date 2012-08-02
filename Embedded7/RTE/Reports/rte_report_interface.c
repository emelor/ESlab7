/*
** File:     rte_report_interface.c
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

/************************************************
 rteTvToSie()
*************************************************/
char *rteTvToSie (uint32_t *tv)

{ char       *str;
  char        buffer[132];
  uint32_t    val;
  int_t       cnt = 0;

  val = *tv;
  while (val/1000 > 0) {
    val /= 1000;
    cnt++;
  }

  str  = &buffer[0];
  switch (cnt) {
    case 0:
         sprintf(str,"ps%d",val);
         break;

    case 1:
         sprintf(str,"ns%d",val);
         break;

    case 2:
         sprintf(str,"us%d",val);
         break;

    case 3:
         sprintf(str,"ms%d",val);
         break;

    case 4:
         sprintf(str," s%d",val);
         break;

    default:
         str = "---";
         break;
  }

  return(str);
}

/************************************************
 rteFormatTv()
*************************************************/
extern void rteJiffiesToTvExec (uint32_t jiffies, uint32_t *time);
void rteFormatTv (char *str, uint32_t jiffies)

{ uint32_t       tv;
  char          *sie;

  if (jiffies == (uint32_t)-1) {
    jiffies = 0;
  }

  rteJiffiesToTvExec(jiffies,&tv);
  sie = rteTvToSie(&tv);
  sprintf(str,"%s",sie);
}

/************************************************
 rteReportBehaviours()
*************************************************/
void rteReportBehaviours (void)

{ rteSwcBehaviour_t const    * behaviour = 0u;
  rteTimeCB_t                * cb;
  char                         buffer[132];
  char                         tvs[32];
  char                       * ptr;
  char const                 * name;

  fprintf(rteFile,"Report all SWC Behaviours\n");
  while (rteGetObjectNext (R_OBJECT_CM_BEHAVIOUR,(bsObject_t const **)&behaviour) == R_OK) {
    name = rteObjectName(behaviour->object.index);
    ptr  = &buffer[0];
    cb = behaviour->cb;
    ptr = ptr + sprintf(ptr,"%s ",name);
    rteFormatTv(&tvs[0],cb->bcet);
    ptr = ptr + sprintf(ptr,"BCET:%s ",tvs);
    rteFormatTv(&tvs[0],cb->acet);
    ptr = ptr + sprintf(ptr,"ACET:%s ",tvs);
    rteFormatTv(&tvs[0],cb->wcet);
    ptr = ptr + sprintf(ptr,"WCET:%s ",tvs);
    ptr = ptr + sprintf(ptr,"BCNT:%d WCNT:%d  ", cb->vCntBcet,cb->vCntWcet);
    rteFormatTv(&tvs[0],behaviour->timingSet.bcet);
    ptr = ptr + sprintf(ptr,"SBCET:%s ",tvs);
    rteFormatTv(&tvs[0],behaviour->timingSet.wcet);
    ptr = ptr + sprintf(ptr,"SWCET:%s\n",tvs);
    fprintf(rteFile,buffer);
  }

  fprintf(rteFile,"\n");
}

/************************************************
 rteReportInterfaces
*************************************************/
void rteReportInterfaces (void)

{ rteSwcInterfaceAttr_t const* swcInterface = 0u;
  char                         buffer[132];
  char                       * ptr;
  char const                 * name;

  fprintf(rteFile,"Report attribute of all Interfaces\n");
  while (rteGetObjectNext (R_OBJECT_CM_INTERFACE,(bsObject_t const **)&swcInterface) == R_OK) {
    name = rteObjectName(swcInterface->object.index);
    ptr  = &buffer[0];
    ptr = ptr + sprintf(ptr,"--%s No of Ports:%d\n",name,swcInterface->noOfPorts);
    fprintf(rteFile,buffer);
  }

  fprintf(rteFile,"\n");
}

