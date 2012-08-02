/**************************
	UNDER DEVELOPMENT
***************************/

#ifndef DISPLAYDRIVER_H
#define DISPLAYDRIVER_H

//****************************************************************************
// @Function      void display_initialise(void)
//
//----------------------------------------------------------------------------
// @Description   This function initializes the display.
//
//****************************************************************************
void display_initialise(void);

//****************************************************************************
// @Function 	  void display_print_char(char data)
//
//----------------------------------------------------------------------------
// @Description   This function print a single char on display.
//		  (at current cursor position)
//		  (cursor position is automatically updated)
//	
//****************************************************************************
void display_print_char(char data);

//****************************************************************************
// @Function 	  viod display_print_string(char[])
//
//----------------------------------------------------------------------------
// @Description   This function prints the strings on display.
//		  (prints from from current curser position)
//
//****************************************************************************
void display_print_string(char line[]);

//****************************************************************************
// @Function      void display_clear(void)
//
//----------------------------------------------------------------------------
// @Description   This function clears the display.
//
//****************************************************************************
void display_clear(void);

//****************************************************************************
// @Function 	  void display_move_cursor(int row,int col)
//
//----------------------------------------------------------------------------
// @Description   This function moves cursor to specified row and column.
//
//****************************************************************************
void display_move_cursor(int row,int col);

//****************************************************************************
// @Function      void display_scroll_left(void)
//
//----------------------------------------------------------------------------
// @Description   This function scrolls the display to the left.
//		  (this function must be called repeatadly to scroll)
//
//****************************************************************************
void display_scroll_left(void);

//****************************************************************************
// @Function      void display_scroll_right(void)
//
//----------------------------------------------------------------------------
// @Description   This function scrolls the display to the right.
//		  (this function must be called repeatadly to scroll)
//
//****************************************************************************
void display_scroll_right(void);

//****************************************************************************
// @Function      void display_cursor_on(void)
//
//----------------------------------------------------------------------------
// @Description   This function sets the cursor to be displayed and the 
// 		  character above to blink.
//
//****************************************************************************
void display_cursor_on(void);

//****************************************************************************
// @Function      void display_cursor_off(void)
//
//----------------------------------------------------------------------------
// @Description   This function sets the cursor not to be displayed.
//
//****************************************************************************
void display_cursor_off(void);

//****************************************************************************
// @Function      void dprintf(char *format, ... )
//
//----------------------------------------------------------------------------
// @Description   This function prints a float(%f), int (%i), string (%s), unsigned int(%u), long int (l) &  unsigned long int (h)
//                with the same syntax as printf()
//
//****************************************************************************
void dprintf(char *format, ...);

void cpu_pause2(int usecs);

#endif