#ifndef _RTE_LOG_H_
#define _RTE_LOG_H_
/*
** File:     rte_log.h
**
** Contents: Rubus RCM
**           Rubus RTE 
**           Log Services
**
** Version:  1.0
**
** Copyright 1996-2011 Arcticus Systems AB, All Rights Reserved.
** The format and content in the File is protected by copyright.
** The File is furnished under a licence and may only be used in
** accordance with the terms of this licence.
*/

/*==========================================================
** Include files
==========================================================*/
#ifndef _BS_LOG_H_
#include <basic/bs_log.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*==========================================================
** Log Events
==========================================================*/
#define RTE_LOG_EVENT_1                 R_LOG_EVENT_1
#define RTE_LOG_EVENT_2                 R_LOG_EVENT_2
#define RTE_LOG_EVENT_3                 R_LOG_EVENT_3
#define RTE_LOG_EVENT_4                 R_LOG_EVENT_4
#define RTE_LOG_EVENT_5                 R_LOG_EVENT_5
#define RTE_LOG_EVENT_6                 R_LOG_EVENT_6
#define RTE_LOG_EVENT_7                 R_LOG_EVENT_7
#define RTE_LOG_EVENT_8                 R_LOG_EVENT_8
#define RTE_LOG_EVENT_OBJECT            0x8000

/*==========================================================
** Event Log Definitions
==========================================================*/
#define RTE_LOG_OBJECT_ON               R_LOG_OBJECT_ON
#define RTE_LOG_OBJECT_OFF              R_LOG_OBJECT_OFF

/*==========================================================
** Log Objects
==========================================================*/
#define RTE_LOG_EVENT(object,event) { rteLogPut(((rteObject_t const *)object)->index,event); }

/*==========================================================
** Externals
==========================================================*/

/*==========================================================
** Prototypes
==========================================================*/
extern int_t  rteLogInit (void);
extern void   rteLogPut (uint16_t id, uint16_t event);
extern void   rteLogSetAll (uint_t flags);
extern int_t  rteLogSet (int_t id, uint_t flags);

extern void   bsLogPutElm (uint16_t id, uint16_t event);

#ifdef __cplusplus
}
#endif


#endif
