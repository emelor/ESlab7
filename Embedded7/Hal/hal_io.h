#ifndef _HAL_IO_H_
#define _HAL_IO_H_
/*
** File:     hal_io.h
**
** Contents: Rubus OS
**           Tutorial
**           I/O Services
**
** Copyright 1996-2011 Arcticus Systems AB
**           All Rights Reserved
**
*/

/*===============================================
  Prototypes
===============================================*/
extern int_t  ioInit (void);
extern int_t  ioRead (uint_t *data);
extern int_t  ioWrite (uint8_t *data);
extern void ioLed1 (uint_t *state);
extern void ioLed2 (uint_t *state);


#endif
