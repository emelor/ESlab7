/**************************
	UNDER DEVELOPMENT
***************************/

//WE CANNOT USE cpu_pause IN THIS CODE! 
//IT USES PDTIN3 AND THAT CONFLICTS WITH ENCODER!!!

//****************************************************************************
// This file contains the implementation of the display-driver
// By: Fredrik Roos, Ulf Carlsson, Peter Lonnqvist				
// Copyright: 1999
// Modified by Tobias Lundberg 01-12-06 for use with MET-Labkort ver. 1	
// Modified by Martin Grimheden 2002-01-12, now for use instead with MET-Labkort ver. 2
// Modified by Jad El-khoury 2006-10-25, to be used with the Freescale 5213 processor.
//****************************************************************************

#include <stdio.h>
#include <stdarg.h>
#include "displayDriver.h"
#include "support_common.h"

//****************************************************************************
// @Function      void display_initialise(void)
//
//----------------------------------------------------------------------------
// @Description   This function initializes the display.
//
//****************************************************************************
void display_initialise(void)
{
	int delay;

	MCF_GPIO_PQSPAR = 0x0555;	//PIN CS3-> PQS[6]=GPIO, alla andra QSPI
	
	MCF_GPIO_DDRQS = 0x0040; 	//PQS[6] output
	
	MCF_QSPI_QMR = 0xA357; 		//8bit, QSPI_CLK 379 kHz (at 66 MHz bus clock)
	MCF_QSPI_QDLYR = 0x0000;	//delay ~150-170ms
	MCF_QSPI_QIR =0xD00F; 		//enable write collision, abort bus errors, clear any interrupts  
	MCF_QSPI_QAR = 0x0020;		//select the first command RAM entry, kanske denna ska va i while(1)???
	
	//MCF_QSPI_QWR |= MCF_QSPI_QWR_CSIV; //behövs nog inte
	
	MCF_QSPI_QDR = 0xAE00; //CS0 low
	MCF_QSPI_QDR = 0xAE00;
	MCF_QSPI_QDR = 0xAE00;
	MCF_QSPI_QDR = 0xAE00;
	MCF_QSPI_QDR = 0xAE00;
	MCF_QSPI_QDR = 0xAE00;
	MCF_QSPI_QDR = 0xAE00;
	MCF_QSPI_QDR = 0xAE00;
	MCF_QSPI_QDR = 0xAE00;
	
	//Reset display
	MCF_GPIO_PORTQS = 0x0040;
	cpu_pause2(1000);
	MCF_GPIO_PORTQS = 0x0000;
	cpu_pause2(500);
	MCF_GPIO_PORTQS = 0x0040;
	cpu_pause2(50000);
	
	MCF_QSPI_QAR = 0x0000;

	MCF_QSPI_QDR = 0x38; //Function set: 00111000
	MCF_QSPI_QDR = 0x39; //Function set: 00111001
	MCF_QSPI_QDR = 0x14; //Internal OSC frequency: 00010100
	MCF_QSPI_QDR = 0x55; //Power/ICON/Contrast control: 01011110
	MCF_QSPI_QDR = 0x6D; //Follower control: 01101010
	MCF_QSPI_QDR = 0x78; //Contrast set: 01111000
	MCF_QSPI_QDR = 0x0F; //Display ON/OFF control: 00001111
	MCF_QSPI_QDR = 0x01; //Clear display
	MCF_QSPI_QDR = 0x06; //Entry mode set
	
	delay = 50000;
	cpu_pause2(delay);

	//send first 5 bytes
	MCF_QSPI_QWR = MCF_QSPI_QWR_ENDQP(4) | MCF_QSPI_QWR_NEWQP(0x00); //Set up the write queue pointers, ENDQP = length-1
	MCF_QSPI_QDLYR |= MCF_QSPI_QDLYR_SPE; //Set the command to start the spi transfer
	while (!(MCF_QSPI_QIR & MCF_QSPI_QIR_SPIF)); //Wait until the operation has been completed
	MCF_QSPI_QIR |= 0x0001;		//Clear the SPIF finish flag

	//här måste vara delay >200ms
	delay = 250000;
	cpu_pause2(delay);

	//send next 3 bytes
	MCF_QSPI_QWR = MCF_QSPI_QWR_ENDQP(7) | MCF_QSPI_QWR_NEWQP(5); //Set up the write queue pointers, ENDQP = length-1
	MCF_QSPI_QDLYR |= MCF_QSPI_QDLYR_SPE; //Set the command to start the spi transfer
	while (!(MCF_QSPI_QIR & MCF_QSPI_QIR_SPIF)); //Wait until the operation has been completed
	MCF_QSPI_QIR |= 0x0001;		//Clear the SPIF finish flag

	//här måste vara delay >2ms
	delay = 2500;
	cpu_pause2(delay);

	//send last bytes
	MCF_QSPI_QWR = MCF_QSPI_QWR_ENDQP(8) | MCF_QSPI_QWR_NEWQP(8); //Set up the write queue pointers, ENDQP = length-1
	MCF_QSPI_QDLYR |= MCF_QSPI_QDLYR_SPE; //Set the command to start the spi transfer
	while (!(MCF_QSPI_QIR & MCF_QSPI_QIR_SPIF)); //Wait until the operation has been completed
	MCF_QSPI_QIR |= 0x0001;	//Clear the SPIF finish flag
}

//****************************************************************************
// @Function 	  void display_print_char(char data)
//
//----------------------------------------------------------------------------
// @Description   This function print a single char on display.
//		  (at current cursor position)
//		  (cursor position is automatically updated)
//	
//****************************************************************************
void display_print_char(char data)
{
	MCF_QSPI_QAR = 0x0020;	//select the first command RAM entry, kanske denna ska va i while(1)???
	MCF_QSPI_QDR = 0xAF00;	//CS0 high
	MCF_QSPI_QAR = 0x0000;
	MCF_QSPI_QDR = data;
	MCF_QSPI_QWR = MCF_QSPI_QWR_ENDQP(0) | MCF_QSPI_QWR_NEWQP(0x00); //Set up the write queue pointers, ENDQP = length-1
	MCF_QSPI_QDLYR |= MCF_QSPI_QDLYR_SPE; //Set the command to start the spi transfer
	while (!(MCF_QSPI_QIR & MCF_QSPI_QIR_SPIF)); //Wait until the operation has been completed
	MCF_QSPI_QIR |= 0x0001;		//Clear the SPIF finish flag
}

//****************************************************************************
// @Function 	  viod display_print_string(char[])
//
//----------------------------------------------------------------------------
// @Description   This function prints the strings on display.
//		  (prints from from current curser position)
//
//****************************************************************************
void display_print_string(char line[])
{
	int n;
	n=0;
	while(line[n]!='\0') 
		display_print_char(line[n++]);	// LINE OUT
}

//****************************************************************************
// @Function      void display_clear(void)
//
//----------------------------------------------------------------------------
// @Description   This function clears the display.
//
//****************************************************************************
void display_clear(void)
{
	MCF_QSPI_QAR = 0x0020;	//select the first command RAM entry, kanske denna ska va i while(1)???
	MCF_QSPI_QDR = 0xAE00;	//CS0 high
	MCF_QSPI_QAR = 0x0000;
	MCF_QSPI_QDR = 0x01;
	MCF_QSPI_QWR = MCF_QSPI_QWR_ENDQP(0) | MCF_QSPI_QWR_NEWQP(0x00); //Set up the write queue pointers, ENDQP = length-1
	MCF_QSPI_QDLYR |= MCF_QSPI_QDLYR_SPE; //Set the command to start the spi transfer
	while (!(MCF_QSPI_QIR & MCF_QSPI_QIR_SPIF)); //Wait until the operation has been completed
	MCF_QSPI_QIR |= 0x0001;		//Clear the SPIF finish flag
	
	//här måste vara delay >2ms
	cpu_pause2(2500);	
}

//****************************************************************************
// @Function 	  void display_move_cursor(int row,int col)
//
//----------------------------------------------------------------------------
// @Description   This function moves cursor to specified row and column.
//
//****************************************************************************
void display_move_cursor(int row,int col)
{
}

//****************************************************************************
// @Function      void display_scroll_left(void)
//
//----------------------------------------------------------------------------
// @Description   This function scrolls the display to the left.
//		  (this function must be called repeatadly to scroll)
//
//****************************************************************************
void display_scroll_left(void)
{
}


//****************************************************************************
// @Function      void display_scroll_right(void)
//
//----------------------------------------------------------------------------
// @Description   This function scrolls the display to the right.
//		  (this function must be called repeatadly to scroll)
//
//****************************************************************************
void display_scroll_right(void)
{
}


//****************************************************************************
// @Function      void display_cursor_on(void)
//
//----------------------------------------------------------------------------
// @Description   This function sets the cursor to be displayed and the 
// 		  character above to blink.
//
//****************************************************************************
void display_cursor_on(void)
{
}


//****************************************************************************
// @Function      void display_cursor_off(void)
//
//----------------------------------------------------------------------------
// @Description   This function sets the cursor not to be displayed.
//
//****************************************************************************
void display_cursor_off(void)
{
}


//****************************************************************************
// @Function      void dprintf(char *format, ... )
//
//----------------------------------------------------------------------------
// @Description   This function prints a float, int, char, unsigned int
//                with the same syntax as printf()
//
//****************************************************************************
void dprintf(char *format, ...)
{
 	char text[20];
 	va_list ap;
 	char *p, *sval; 
 	char cval;
 	int ival;
 	unsigned int uval;
 	double dval;
 	long int lival;
 	unsigned long int ulival;
 	
 	va_start(ap, format);
 	for (p = format; *p; p++)
 	{
    		if(*p != '%')
    		{
			display_print_char(*p);
			continue;
		}
    		switch (*++p)
    		{
    			case 'i':
      				ival = va_arg(ap, int);
      				sprintf(text, "%i", ival);
      				display_print_string(text);
      				break;
    			case 'f':
      				dval = va_arg(ap, double);
      				sprintf(text, "%.2f", dval);
      				display_print_string(text);
      				break;
    			case 's':
	      				sval = va_arg(ap, char *);
	      				sprintf(text, "%s", sval);
	      				display_print_string(text);
      				break;
//Have some problems printing with %c!!
//    			case 'c':
//      				cval = va_arg(ap, char);
//      				display_print_char(cval);
//      				break;
    			case 'u':
      				uval = va_arg(ap, unsigned int);
      				sprintf(text, "%u", uval);
      				display_print_string(text);
      				break;  
    			case 'l':
      				lival = va_arg(ap, long int);
      				sprintf(text, "%li", lival);
      				display_print_string(text);
      				break;
    			case 'h': //Not conventional format, but I don't know what to call it instead
      				ulival = va_arg(ap, unsigned long int);
      				sprintf(text, "%lu", ulival);
      				display_print_string(text);
      				break;
    			default:
				display_print_string("SYN ERROR");
				break;
     		}
	} 	
   	va_end(ap);	
}

void cpu_pause2(int usecs)
{
    /* Enable the DMA Timer 3 */
    MCF_DTIM3_DTRR = (usecs - 1);
    MCF_DTIM3_DTER = MCF_DTIM_DTER_REF;
    MCF_DTIM3_DTMR = 0
        | MCF_DTIM_DTMR_PS(SYSTEM_CLOCK_KHZ / 1000)
        | MCF_DTIM_DTMR_ORRI
        | MCF_DTIM_DTMR_FRR
        | MCF_DTIM_DTMR_CLK_DIV1
        | MCF_DTIM_DTMR_RST;

    while ((MCF_DTIM3_DTER & MCF_DTIM_DTER_REF) == 0) 
    {};
    
    /* Disable the timer */
    MCF_DTIM3_DTMR = 0;
}