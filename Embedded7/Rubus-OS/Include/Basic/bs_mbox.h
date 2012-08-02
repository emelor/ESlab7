#ifndef  _BS_MBOX_H_
#define  _BS_MBOX_H_
/*
** File:     bs_mbox.h
**
** Contents: Rubus OS
**           Basic Services
**           Mailbox Services
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
  Mailbox Message Type
===============================================*/
#define R_MBOX_TYPE_UNSPECIFIED         0

	/*===============================================
  Mailbox Control Block Type
===============================================*/
typedef struct bsMailboxCB_s
        { bsLinkD_t                      link;
          uint_t                         flags;
          uint_t                         current;
          uint_t                         peek; 
          void                          *owner;
          struct bsMailboxCB_s R_LOC_CB *self;
        } R_LOC_CB bsMailboxCB_t;

/*===============================================
  Mailbox Attribute Type
===============================================*/
typedef struct bsMailboxAttr_s
        { bsObject_t              object;
          bsMailboxCB_t          *cb;
        } bsMailboxAttr_t;

/*===============================================
  Mailbox Buffer Header Type
===============================================*/
typedef struct 
        { bsLinkD_t   link;
          uint_t        type;
        } bsMailboxHdr_t;

/*===============================================
  Mailbox Id Type
===============================================*/
typedef bsMailboxAttr_t const *bsMailboxId_t;

/*===============================================
  Prototypes
===============================================*/
extern int_t  bsMailboxInit (bsMailboxId_t mailbox);
extern int_t  bsMailboxDestroy (bsMailboxId_t mailbox);
extern int_t  bsMailboxReceive (bsMailboxId_t mailbox, bsMailboxHdr_t **msgPtr, uint_t msgType);
extern int_t  bsMailboxSend (bsMailboxId_t mailbox, bsMailboxHdr_t *msgPtr);
extern int_t  bsMailboxFree (bsMailboxHdr_t **msgPtr);


#ifdef __cplusplus
}
#endif
#endif	

