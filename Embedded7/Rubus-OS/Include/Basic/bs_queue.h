#ifndef  _BS_QUEUE_H_
#define  _BS_QUEUE_H_
/*
** File:     bs_queue.h
**
** Contents: Rubus OS
**           Basic Services
**           Queue Definitions.
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
  Queue Control Block Type
===============================================*/
typedef struct bsQueueCB_s {
          uint8_t R_LOC_CB              *put;
          uint8_t R_LOC_CB              *get;
          uint8_t R_LOC_CB              *read;
          uint_t                        flags;
          uint_t                        current;
          uint_t                        peek;
          struct bsQueueCB_s R_LOC_CB *self;
        } R_LOC_CB bsQueueCB_t;

/*===============================================
  Queue Object Attribute Type
===============================================*/
typedef struct bsQueueAttr_s {
          bsObject_t             object;
          bsQueueCB_t           *cb;
          uint_t                 entries;
          uint_t                 size;
          uint8_t R_LOC_CB       *top;
          uint8_t R_LOC_CB       *bottom;
        } bsQueueAttr_t;

/*===============================================
  Queue Id Type
===============================================*/
typedef bsQueueAttr_t const *bsQueueId_t;

/*===============================================
  Prototypes
===============================================*/
extern int_t bsQueueInit (bsQueueId_t queue, uint_t flags);
extern int_t bsQueueDestroy (bsQueueId_t queue);
extern int_t bsQueuePut (bsQueueId_t queue, uint8_t *object);
extern int_t bsQueueGet (bsQueueId_t queue, uint8_t *object);
extern int_t bsQueueRead (bsQueueId_t queue, uint8_t *object, uint_t flags);

#ifdef __cplusplus
}
#endif
#endif

