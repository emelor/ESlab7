/*
** File:     rte_report_port.c
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

#ifndef _RRTE_INTERFACE_H_
#include <rRte_Interface.h>
#endif

#ifndef _RTE_REPORT_H_
#include <rte_report.h>
#endif

#ifndef _HAL_INTERNAL_H_
#include <hal_internal.h>
#endif

#ifndef _RTE_SERVICES_H_
#include <rte_services.h>
#endif

/*=========================================================
  Defines
=========================================================*/
#define RTE_INDENT                      4

/*=========================================================
  Text Tables
=========================================================*/
char const *portDataTypeText[6] = {
  "DataType=Undef",
  "DataType=Scalar",
  "DataType=Primitive",
  "DataType=Composite",
  "DataType=Enum",
  "DataType=Array"
};

char const *portTypeText[4] = {
  "Port Undef ",
  "Port IP: ",
  "Port OP: ",
  "Port SP: "
};

/*=========================================================
  rtePortConcat()

=========================================================*/
static char * rtePortConcat (char const *sp, char *dp)

{ int_t i = 0;

  while (sp[i]) {
    dp[i] = sp[i];
    i++;
  }

  dp[i] = 0;
  return(&dp[i]);
}

/*=========================================================
  rtePortConcatComplex()

=========================================================*/
static char * rtePortConcatComplex (char *dp, char const *ppre, char const *sp, char const *ppost)

{
  dp = rtePortConcat(ppre,dp);
  dp = rtePortConcat(sp,dp);
  dp = rtePortConcat(ppost,dp);
  return(dp);
}

/*=========================================================
  rtePortIndent()

=========================================================*/
static char * rtePortIndent (int_t indent, char *dp, char const *sp)

{ int_t i;

  for (i = 0; i < (indent * RTE_INDENT); i++) {
    dp[i] = ' ';
  }

  return(rtePortConcat(sp,&dp[i]));
}

/*=========================================================
  rtePortFormat()

=========================================================*/
char * rtePortFormat (rtePort_t const *port, char *str)

{ char   fs[32];
  uint_t i = 0;

  fs[i++] = ' ';
  fs[i++] = '=';
  fs[i++] = ' ';
  fs[i++] = '%';
  if (port->data.dataSigned) {
    fs[i++] = 'i';
  }
  else {
    fs[i++] = 'u';
  }

  fs[i++] = ' ';
  fs[i]   = 0;
  switch (port->data.dataSize) {
    case 1:
         str = str + sprintf(str,&fs[0],*(uint8_t *)port->accessAddr);
         break;

    case 2:
         str = str + sprintf(str,&fs[0],*(uint16_t *)port->accessAddr);
         break;

    case 4:
    default:
         str = str + sprintf(str,&fs[0],*(uint32_t *)port->accessAddr);
         break;
  }

  *str++ = '\n';
  *str   = 0;
  return(str);
}

/*=========================================================
  rtePortEvalScalar()

=========================================================*/
char * rtePortEvalScalar (rtePort_t const *port, int_t indent, char *str)

{
  str = rtePortIndent(indent,str,"");
  if (port->name) {
    str = rtePortConcat(port->name,str);
  }

  if (port->typeName) {
    str = rtePortConcatComplex (str, " (", port->typeName, ")");
  }

  return(rtePortFormat(port,str));
}

/*=========================================================
  rtePortEvalComplex()

=========================================================*/
char * rtePortEvalComplex (rtePort_t const *port, int_t indent, char *str, uint16_t dimension)

{ rtePort_t const   *pp;
  rtePort_t const   *pi;
  uint_t             i;
  int_t              idv;

  idv = indent;
  if ((port->data.dataType == R_PORT_ARRAY) || port->data.dataType == R_PORT_COMPOSITE) {
    str = rtePortIndent(indent,str,"{");
    str = str + sprintf(str,"   %s ",port->name);
    str = rtePortConcatComplex (str, " (", port->typeName, ") ");
    str = str + sprintf(str,"Dim:%d\n",dimension);
  }
  else {
    str = rtePortIndent(indent,str,"{\n");
  }

  indent++;
  for (i = 0; i < dimension; i++) {
    pp = &port[i];
    pi = pp->link;
    switch (pp->data.dataType) {
      case R_PORT_ARRAY:
      case R_PORT_COMPOSITE:
           str = rtePortEvalComplex(pi,indent,str,pp->data.dataSize);
           break;

      default:
           str = rtePortEvalScalar(pp,indent,str);
           break;
    }
  }

  return(rtePortIndent(idv,str,"}\n"));
}

/*=========================================================
  rtePortEval()

=========================================================*/
void rtePortEval (rteSwcPortAttr_t const *pAttr, rtePortTable_t const *port)

{ char        buffer[512];
  char       *str;
  char const *ptTxt, *pdTxt;
  int_t       indent;

  str  = &buffer[0];
  ptTxt = portTypeText[pAttr->portType & R_OBJECT_CM_SUB_CLASS];
  pdTxt = portDataTypeText[port->dataType];
  str = rtePortConcatComplex (str, "", ptTxt, " ");
  str = rtePortConcatComplex (str, "", pAttr->name, " ");
  str = str + sprintf(str,"Index=%d ",pAttr->portIndex);
  str = rtePortConcatComplex (str, "", pdTxt, " ");
  str = rtePortConcatComplex (str, "Type=", pAttr->typeName, " ");
  str = str + sprintf(str,"Dim:%d\n",port->dimension);
  fprintf(rteFile,&buffer[0]);
  str  = &buffer[0];
  indent = 1;
  switch (port->dataType) {
    case R_PORT_ARRAY:
    case R_PORT_COMPOSITE:
         str = rtePortEvalComplex(port->link,indent,str,port->dimension);
         break;

    default:
         str = rtePortEvalScalar(port->link,indent,str);
         break;
  }

  fprintf(rteFile,&buffer[0]);
  fprintf(rteFile,"\n");
}

/*=========================================================
  rtePortInstance()

=========================================================*/
void rtePortInstance (rteSwcInstanceAttr_t const  *swcInstance)

{ rteSwcInterfaceAttr_t const *swcInterface;
  rtePortTable_t const        *pInst;
  rteSwcPortAttr_t const      *pAttr;
  uint_t                       i;

  swcInterface = swcInstance->swcInterface;
  pInst = swcInstance->portTable;
  pAttr = swcInterface->portAttrTable;
  if (pAttr && pInst) {
    for (i = 0; i < swcInterface->noOfPorts;i++) {
      rtePortEval(pAttr++,pInst++);
    }
  }
}

/*=========================================================
  rteReportAllPorts()

=========================================================*/
void rteReportAllPorts (void)

{ rteSwcInstanceAttr_t const  *swcInstance = 0u;
  rteSwcInterfaceAttr_t const *swcInterface;
  rteSwcBehaviour_t const     *behaviour;
  char                         buffer[132];
  char                        *ptr;
  char const                  *name;
  char const                  *mode;

  fprintf(rteFile,"Report all Ports\n");
  while (rteGetObjectNext (R_OBJECT_CM_INSTANCE,(bsObject_t const **)&swcInstance) == R_OK) {
    name = rteObjectName(swcInstance->object.index);
    ptr  = &buffer[0];
    swcInterface = swcInstance->swcInterface;
    behaviour    = swcInstance->behaviour;
    mode         = rteGetModeName(swcInstance->modeIndex);
    ptr = ptr + sprintf(ptr,"%s ",name);
    name = rteObjectName(swcInterface->object.index);
    ptr = ptr + sprintf(ptr,"Mode:%s Interface:%s RunTimeProfile:%s ",mode,name,behaviour->runTimeProfileName);
    name = rteObjectName(behaviour->object.index);
    ptr = ptr + sprintf(ptr,"Behaviour:%s\n",name);
    fprintf(rteFile,buffer);
    rtePortInstance(swcInstance);
  }

  fprintf(rteFile,"\n");
}

/*=========================================================
  rteReportPortInstance()

=========================================================*/
void rteReportPortInstance (rteSwcInstanceAttr_t const  *swcInstance)

{ rteSwcInterfaceAttr_t const *swcInterface;
  rteSwcBehaviour_t const     *behaviour;
  char                         buffer[132];
  char                        *ptr;
  char const                  *name;
  char const                  *mode;

  ptr  = &buffer[0];
  name = rteObjectName(swcInstance->object.index);
  ptr = ptr + sprintf(ptr,"Report Ports of Instance:%s ",name);

  swcInterface = swcInstance->swcInterface;
  behaviour = swcInstance->behaviour;
  mode         = rteGetModeName(swcInstance->modeIndex);
  ptr = ptr + sprintf(ptr,"Mode:%s Interface:%s RunTimeProfile:%s ",mode,name,behaviour->runTimeProfileName);
  name = rteObjectName(behaviour->object.index);
  ptr = ptr + sprintf(ptr,"Behaviour:%s\n",name);
  fprintf(rteFile,buffer);
  rtePortInstance(swcInstance);
}

/*=========================================================
  rteReportPortInstanceIndex()

=========================================================*/
void rteReportPortInstanceIndex (unsigned int index)

{ rteSwcInstanceAttr_t const *swcInstance = 0;

  while (rteGetObjectNext (R_OBJECT_CM_INSTANCE,(bsObject_t const **)&swcInstance) == R_OK) {
    if (swcInstance->object.index == (int16_t)index) {
      rteReportPortInstance(swcInstance);
    }
  }
}

/*=========================================================
  rteReportPortAllInstances()

=========================================================*/
void rteReportPortAllInstances (void)

{ rteSwcInstanceAttr_t const *swcInstance = 0;

  fprintf(rteFile,"Report all Ports of all instances\n");
  while (rteGetObjectNext (R_OBJECT_CM_INSTANCE,(bsObject_t const **)&swcInstance) == R_OK) {
    rteReportPortInstance(swcInstance);
  }
}
