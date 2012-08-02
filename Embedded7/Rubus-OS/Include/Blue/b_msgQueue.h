#ifndef  _B_MSGQUEUE_H_
#define  _B_MSGQUEUE_H_
/*
** File:     b_msgqueue.h
**
** Contents: Rubus OS
**           Blue Kernel
**           Message Queue Definitions.
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

#ifndef _B_THREAD_H_
#include <blue/b_thread.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*===============================================
  Message Type, variable message size
===============================================*/
typedef struct blueMsgHdr_s
        { struct blueMsgHdr_s R_LOC_CB *link;
        } blueMsgHdr_t;

/*===============================================
  Message Type, variable message size
===============================================*/
typedef struct
        { blueLinkS_t  link;
          uint8_t      body[1];
        } R_LOC_CB blueMsgBuffer_t;

/*===============================================
  Message Queue Dynamic Type
===============================================*/
typedef struct blueMsgCB_s
        { blueCBHeader_t                  header;
          uint_t                          flags;
          uint_t                          size;
          uint_t                          current;
          uint_t                          peek;
          blueMsgBuffer_t                *firstMsg;
          blueMsgBuffer_t                *lastMsg;
          blueMsgBuffer_t                *freeMsg;
          struct blueMsgCB_s R_LOC_CB   *self;
        } R_LOC_CB blueMsgCB_t;

/*===============================================
  Message Queue Attribute Type
===============================================*/
typedef struct blueMsgAttr_s
        { bsObject_t       object;
          blueMsgCB_t     *cb;
          uint_t           entries;
          uint_t           size;
          uint_t           sizeAligned;
          uint_t R_LOC_CB *msgBlock;
        } blueMsgAttr_t;

/*===============================================
  Message Queue Id Type
===============================================*/
typedef blueMsgAttr_t const *blueMsgId_t;

/*===============================================
  Prototypes
===============================================*/
extern int_t  blueMsgInit (blueMsgId_t msg);
extern int_t  blueMsgDestroy (blueMsgId_t msg);
extern int_t  blueMsgTimedReceive (blueMsgId_t msg,uint8_t *msgPtr,uint_t msgLen,int32_t *timeout);
extern int_t  blueMsgSend (blueMsgId_t msg,uint8_t *msgPtr,uint_t msgLen);

#ifdef __cplusplus
}
#endif
#endif

