#ifndef  _BS_POOL_H_
#define  _BS_POOL_H_
/*
** File:     bs_pool.h
**
** Contents: Rubus OS
**           Basic Services
**           Memory Pool Services
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
  Memory Pool Control Block Type
================================================*/
typedef struct bsPoolCB_s
        { bsLinkD_t                   link;
          uint_t                      flags;
          uint_t                      current; 
          uint_t                      peek; 
          struct bsPoolCB_s R_LOC_CB *self;
        } R_LOC_CB bsPoolCB_t;

/*===============================================
  Memory Pool Attribute Type
================================================*/
typedef struct bsPoolAttr_s
        { bsObject_t                  object;
          bsPoolCB_t                 *cb;
          uint_t                      entries;
          int_t                       size;
          uint_t                     *poolBlock;
	} bsPoolAttr_t;

/*===============================================
  Id Type
===============================================*/
typedef bsPoolAttr_t const *bsPoolId_t;

/*===============================================
  Memory Pool Buffer Header Type
===============================================*/
typedef struct 
        { bsLinkD_t     link;
          bsPoolId_t    pool;
        } bsPoolHdr_t;

/*===============================================
  Prototypes
===============================================*/
extern int_t bsPoolInit (bsPoolId_t pool,uint_t flags);
extern int_t bsPoolDestroy (bsPoolId_t pool);
extern int_t bsPoolAllocate (bsPoolId_t pool, uint8_t **buffer);
extern int_t bsPoolFree (bsPoolId_t pool, uint8_t **buffer);

#ifdef __cplusplus
}
#endif
#endif	

