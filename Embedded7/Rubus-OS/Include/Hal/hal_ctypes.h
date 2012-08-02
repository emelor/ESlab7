/*
** File:     hal_ctypes.h
**
** Contents: Rubus OS
**           HAL 
**           ISO/MISRA C 2004 C-Types.
**
** Copyright 1996-2010 Arcticus Systems AB
**           All Rights Reserved
**
*/

#ifndef  _HAL_CTYPES_H_
#define  _HAL_CTYPES_H_


#ifdef __cplusplus
extern "C" {
#endif

/*===============================================
  ISO/MISRA C 2004 Types
===============================================*/

/*----------------------------------
 Exact data size types
-----------------------------------*/
typedef char                            char_t;

typedef signed char                     int8_t;
typedef unsigned char                   uint8_t;
typedef volatile signed char            vint8_t;
typedef volatile unsigned char          vuint8_t;

typedef signed short                    int16_t;
typedef unsigned short                  uint16_t;
typedef volatile signed short           vint16_t;
typedef volatile unsigned short         vuint16_t;

typedef signed int                      int32_t;
typedef unsigned int                    uint32_t;
typedef volatile signed int             vint32_t;
typedef volatile unsigned int           vuint32_t;

typedef signed long long int            int64_t;
typedef unsigned long long int          uint64_t;
typedef volatile signed long long int   vint64_t;
typedef volatile unsigned long long int vuint64_t;

typedef float                           float32_t;
typedef double                          float64_t;
typedef long double                     float128_t;

/*----------------------------------
 Pointer data size types
-----------------------------------*/
typedef int32_t                         intptr_t;
typedef uint32_t                        uintptr_t;

/*----------------------------------
 Environment related data size types
-----------------------------------*/
typedef int32_t                         int_t;
typedef uint32_t                        uint_t;


#ifdef __cplusplus
}
#endif

#endif		/* End of header */

