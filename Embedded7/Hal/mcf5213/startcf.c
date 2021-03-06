/*
 *    CF_Startup.c - Default init/startup/termination routines for
 *                     Embedded Metrowerks C++
 *
 *    Copyright � 1993-1998 Metrowerks, Inc. All Rights Reserved.
 *    Copyright � 2005 Freescale semiConductor Inc. All Rights Reserved.
 *
 *
 *    THEORY OF OPERATION
 *
 *    This version of thestartup code is intended for linker relocated
 *    executables.  The startup code will assign the stack pointer to
 *    __SP_INIT, assign the address of the data relative base address
 *    to a5, initialize the .bss/.sbss sections to zero, call any
 *    static C++ initializers and then call main.  Upon returning from
 *    main it will call C++ destructors and call exit to terminate.
 */

#ifdef __cplusplus
#pragma cplusplus off
#endif

#pragma PID off
#pragma PIC off

#ifndef SUPPORT_ROM_TO_RAM
#define SUPPORT_ROM_TO_RAM			1
#endif

#include "hal_mcf5213.h"
#include "startcf.h"

	/* imported data */

extern unsigned long far _SP_INIT, __SP_END, _SDA_BASE;
extern unsigned long far _START_BSS, _END_BSS;
extern unsigned long far _START_SBSS, _END_SBSS;
extern unsigned long far __DATA_RAM, __DATA_ROM, __DATA_END;



	/* imported routines */

extern void main (void);
extern void mcf5213_init (void);

	/* exported routines */

extern asm void _startup(void);


/*
 *	Routine to copy a single section from ROM to RAM ...
 */
static __declspec(register_abi) void __copy_rom_section(char* dst, const char* src, unsigned long size)
{
	if (dst != src)
		 while (size--)
		    *dst++ = *src++;
}

/*
 *	Routine that copies all sections the user marked as ROM into
 *	their target RAM addresses ...
 *
 *	__S_romp is automatically generated by the linker if it
 *	is referenced by the program.  It is a table of RomInfo
 *	structures.  The final entry in the table has all-zero
 *	fields.
 */
static void __copy_rom_sections_to_ram(void)
{
	RomInfo		*info;

	/*
	 *	Go through the entire table, copying sections from ROM to RAM.
	 */
	for (info = _S_romp; info->Source != 0L || info->Target != 0L || info->Size != 0; ++info)
    __copy_rom_section( (char *)info->Target,(char *)info->Source, info->Size);
							
}

/*
 *    Routine to clear out blocks of memory should give good
 *    performance regardless of 68k or ColdFire part.
 */
static __declspec(register_abi) void clear_mem(char *dst, unsigned long n)
{
	unsigned long i;
	long *lptr;

	if (n >= 32)
	{
		/* align start address to a 4 byte boundary */
		i = (- (unsigned long) dst) & 3;

		if (i)
		{
			n -= i;
			do
				*dst++ = 0;
			while (--i);
		}

		/* use an unrolled loop to zero out 32byte blocks */
		i = n >> 5;
		if (i)
		{
			lptr = (long *)dst;
			dst += i * 32;
			do
			{
				*lptr++ = 0;
				*lptr++ = 0;
				*lptr++ = 0;
				*lptr++ = 0;
				*lptr++ = 0;
				*lptr++ = 0;
				*lptr++ = 0;
				*lptr++ = 0;
			}
			while (--i);
		}
		i = (n & 31) >> 2;

		/* handle any 4 byte blocks left */
		if (i)
		{
			lptr = (long *)dst;
			dst += i * 4;
			do
				*lptr++ = 0;
			while (--i);
		}
		n &= 3;
	}

	/* handle any byte blocks left */
	if (n)
		do
			*dst++ = 0;
		while (--n);
}

/***********************************************************
  _startup()
  Startup routine for embedded application ...
************************************************************/

asm void __declspec(register_abi) _startup(void)
{
	/* disable interrupts */
    move.w        #0x2700,sr
	
	/* Initialize IPSBAR */
	move.l	#(__IPSBAR + 1),d0
	move.l	d0,0x40000000
	
	/* Initialize FLASHBAR: locate internal Flash and validate it */
	move.l	#(__FLASH + 0x21),d0
    movec d0,FLASHBAR

	/* Initialize RAMBAR1: locate SRAM and validate it */
	move.l	#(__SRAM + 0x21),d0
	movec d0,RAMBAR1

	/* setup the stack pointer */
    lea           _SP_INIT,a7

	/* setup A6 dummy stackframe */
    movea.l       #0,a6
    link          a6,#0

	/* setup A5 */
    lea           _SDA_BASE,a5

// Fill Startup stack with pattern
	move.l	#_SP_INIT,d0
	sub.l	#__SP_END,d0
	move.l	#__SP_END,a0
	move.l	#0xAAAAAAAA,d1

L0:
	subq.l  #4,d0
	bcs     L1
	move.l	d1,(a0) 
	addq.l	#4,a0
	bra     L0
L1:
	/* Relocate Stack Pointer */ 
	move.l	#_SP_INIT,sp

    jsr           mcf5213_init

	/* zero initialize the .bss section */

    lea           _END_BSS, a0
    lea           _START_BSS, a1
    suba.l        a1, a0
    move.l        a0, d0

    beq           __skip_bss__

    lea           _START_BSS, a0

    /* call clear_mem with base pointer in a0 and size in d0 */
    jsr           clear_mem

__skip_bss__:

	/* zero initialize the .sbss section */

    lea           _END_SBSS, a0
    lea           _START_SBSS, a1
    suba.l        a1, a0
    move.l        a0, d0

    beq           __skip_sbss__

    lea           _START_SBSS, a0

    /* call clear_mem with base pointer in a0 and size in d0 */
    jsr           clear_mem

__skip_sbss__:

	/* copy all ROM sections to their RAM locations ... */
#if SUPPORT_ROM_TO_RAM

	/*
	 * _S_romp is a null terminated array of
	 * typedef struct RomInfo {
     *      unsigned long	Source;
     *      unsigned long	Target;
     *      unsigned long 	Size;
     *  } RomInfo;
     *
     * Watch out if you're rebasing using _PICPID_DELTA
     */

    lea           _S_romp, a0
    move.l        a0, d0
    beq           __skip_rom_copy__            
    jsr           __copy_rom_sections_to_ram

#else

	/*
   * There's a single block to copy from ROM to RAM, perform
   * the copy directly without using the __S_romp structure
   */

    lea           __DATA_RAM, a0
    lea           __DATA_ROM, a1
    
    cmpa          a0,a1
    beq           __skip_rom_copy__
              
    move.l        #__DATA_END, d0
    sub.l         a0, d0
                  
    jsr           __copy_rom_section

#endif
__skip_rom_copy__:
	

	jsr			  main

	/* should never reach here but just in case */
	illegal
	rts

}

