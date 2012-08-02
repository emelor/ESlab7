#ifndef  _BS_LOG_H_
#define  _BS_LOG_H_
/*
** File:     bs_log.h
**
** Contents: Rubus OS
**           Basic Services
**           Log Definitions.
**
** Version:  4.1
**
** Copyright 1996-2010 Arcticus Systems AB
**           All Rights Reserved
**
*/

#ifndef _BS_BASIC_H_
#include <basic/bs_basic.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*===============================================
  Log Events
===============================================*/
#define R_LOG_EVENT_1                   0x0001u
#define R_LOG_EVENT_2                   0x0002u
#define R_LOG_EVENT_3                   0x0003u
#define R_LOG_EVENT_4                   0x0004u
#define R_LOG_EVENT_5                   0x0005u
#define R_LOG_EVENT_6                   0x0006u
#define R_LOG_EVENT_7                   0x0007u
#define R_LOG_EVENT_8                   0x0008u

/*===============================================
  Event Log Definitions
===============================================*/
#define R_LOG_OBJECT_ON                1u
#define R_LOG_OBJECT_OFF               0u

/*===============================================
  Log Objects
===============================================*/
#define R_LOG_EVENT(object,event)      { bsLogPut(((bsObject_t const *)object)->index,event); }

/*===============================================
  Log Element Type
================================================*/
typedef struct bsLogElm_s {
          uint16_t                    index;
          uint16_t                    event;
          uint32_t                    time;
        } bsLogElm_t;

/*===============================================
  Log Control Block Type
===============================================*/
typedef struct bsLogCB_s {
          uint_t                      putx;
          uint_t                      getx;
          uint_t                      flags;
          uint_t                      logEntries;
          struct bsLogCB_s R_LOC_VAR *self;
        } bsLogCB_t;

/*===============================================
  Log Object Attribute Type
===============================================*/
typedef struct bsLogAttr_s {
          bsObject_t                  object;
          uint_t                      ceilingPrio;
          uint_t                      logEntries;
          bsLogElm_t R_LOC_LOG       *buffer;
        } bsLogAttr_t;

/*===============================================
  Externals
===============================================*/
extern bsLogAttr_t const              bsLogAttr;
extern bsLogCB_t R_LOC_VAR            bsLogCB;

/*===============================================
  Prototypes
===============================================*/
extern int_t  bsLogInit (void);
extern int_t  bsLogGet (bsLogElm_t *object);
extern void   bsLogPut (uint16_t id, uint16_t event);
extern void   bsLogSetAll (uint_t flags);
extern int_t  bsLogSet (int_t id, uint_t flags);
extern int_t  bsLogStart (uint_t flags);
extern int_t  bsLogStop (void);
extern int_t  bsLogStatus (uint_t *elements);

#ifdef __cplusplus
}
#endif
#endif
