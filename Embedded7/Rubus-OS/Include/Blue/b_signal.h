#ifndef  _B_SIGNAL_H_
#define  _B_SIGNAL_H_
/*
** File:     b_signal.h
**
** Contents: Rubus OS
**           Blue Kernel
**           Blue Signal Service definitions
**
** Version:  4.1
**
** Copyright 1996-2010 Arcticus Systems AB
**           All Rights Reserved
**
*/

#ifndef _B_THREAD_H_
#include <blue/b_thread.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*===============================================
  Blue Signal Flags
===============================================*/
#define R_SIGNAL_TIMEOUT    0x0001u /* Timeout signal */
#define R_SIGNAL_ACTIVATE   0x0002u /* Activate signal */
#define R_SIGNAL_RESOURCE   0x0004u /* Resource Unlock signal */
#define R_SIGNAL_RESERVED   0x000Fu /* Reserved Signal Mask, Internal Signals */

/*===============================================
  Prototypes
===============================================*/
extern int_t  blueActivate (blueThreadId_t thread);
extern int_t  blueSigEmptySet (blueThreadId_t thread, blueSigSet_t set);
extern int_t  blueSigPending (blueThreadId_t thread, blueSigSet_t *set);
extern int_t  blueSigSend (blueThreadId_t thread, blueSigSet_t set);
extern int_t  blueSigTimedWait (blueSigSet_t set, blueSigSet_t *rset, int32_t *timeout);
extern int_t  blueSleep (int32_t *timeout);

#ifdef __cplusplus
}
#endif
#endif

