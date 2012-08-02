/*
** File:     rte_report_file.c
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

#ifndef _RTE_REPORT_H_
#include <rte_report.h>
#endif

/*=========================================================
  Externals
=========================================================*/
extern void halHalt(void);

/*=========================================================
  Variables
=========================================================*/
FILE *rteFile = NULL;

/*=========================================================
  rteFileOpen()

=========================================================*/
void rteFileOpen (char *filename)

{
  if ((rteFile = fopen (filename,"w+" )) == NULL) {
    halHalt();
  }

  fprintf(rteFile,"Beginning of File %s\n\n",filename);
}

/*=========================================================
  rteFileClose()

=========================================================*/
void rteFileClose (void)

{
  fprintf(rteFile,"End Of File\n");
  fclose(rteFile);
}
