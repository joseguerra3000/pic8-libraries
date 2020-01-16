/**
  LCD Driver API Header File for 8bit PIC MCUs

  @Author
    Jose Guerra Carmenate

  @File Name
    lcd.h

  @Summary
    This is the header file for LCD driver using PIC MCUs

  @Description
    This header file provides APIs for driver for LCD.
*/


#ifndef _LCD_H
#define _LCD_H

/******************************************************************************
 *********************** Section: Included Files ******************************
 ******************************************************************************/
#include <stdint.h>

#ifdef __cplusplus  // Provide C++ Compatibility
    extern "C" {
#endif

/******************************************************************************
 ********************* Section: Data Types Definitions ************************
 ******************************************************************************/
       
/**
 * LCD Commands
 **/
typedef enum{
    LCD_CMD_CLEAR_DISPLAY                           = 0x01u,
    LCD_CMD_RETURN_HOME                             = 0x02u,
    LCD_CMD_FUNCTION_SET_8BITSMODE_2LINES_5x8DOTS	  = 0x38u,
    LCD_CMD_FUNCTION_SET_8BITSMODE_1LINE_5x8DOTS 	  = 0x30u,
    LCD_CMD_FUNCTION_SET_4BITSMODE_2LINES_5X8DOTS	  = 0x28u,
    LCD_CMD_FUNCTION_SET_4BITSMODE_1LINE_5X8DOTS	  = 0x20u,
    LCD_CMD_FUNCTION_SET_4BITSMODE_1LINE_5X10DOTS   = 0x24u,	
    LCD_CMD_DISPLAY_ON_CURSOR_ON                    = 0x0Eu,
    LCD_CMD_DISPLAY_ON_CURSOR_BLINK                 = 0x0Fu,
    LCD_CMD_DISPLAY_ON_CURSOR_OFF                   = 0x0Cu,
    LCD_CMD_DISPLAY_SHIFT_LEFT                      = 0x18u,
    LCD_CMD_DISPLAY_SHIFT_RIGHT                     = 0x1Cu,
    LCD_CMD_CURSOR_SHIFT_LEFT                       = 0x10,
    LCD_CMD_CURSOR_SHIFT_RIGHT                      = 0x14,
   
} LCD_CMD;

/******************************************************************************
 ************************** Section: LCD Module APIs **************************
 ******************************************************************************/

/**
  @Summary
    Initializes the LCD for 4bit Mode

  @Description
    This routine initializes the LCD.
    This routine must be called before any other LCD routine is called.
    This routine should only be called once during system initialization.

  @Preconditions
    None
  @Param
    - lines: Number of lines on LCD
    
    - row: Number of rows on LCD 

  @Returns
    None

  @Example
    <code>
     LCD_Initialize( 2, 16 );
    </code>
*/
void LCD_Initialize(uint8_t lines, uint8_t row);

/**
  @Summary
    Send command to LCD 

  @Description

  @Preconditions
    'LCD_Initialize' must be called before.

  @Param
	- cmd: Command to LCD.
		"For available command refer to enum LCD_CMD or datasheet"
	
  @Returns
    None

  @Comment
	None

  @Example
    <code>
    LCD_CommandWrite( LCD_CMD_CLEAR_DISPLAY );
    </code>
*/
void LCD_CommandWrite( LCD_CMD cmd );

/**
  @Summary
    Print a character on LCD 

  @Description

  @Preconditions
    'LCD_Initialize' must be called before.

  @Param
	- c: Character to print.
		"Any printable character is valid"
	
  @Returns
    None

  @Comment
	None

  @Example
    <code>
     LCD_PrintChar( 'w' ); //Print a w on LCD.
    </code>
*/
void LCD_PrintChar( char c );

/**
  @Summary
    Print a string on LCD 

  @Description

  @Preconditions
    'LCD_Initialize' must be called before.

  @Param
	- string: String to print on LCD.
	
  @Returns
    None

  @Comment
	None

  @Example
    <code>
    LCD_PrintString( "Alfa" );
    </code>
*/
void LCD_PrintString( char *string );

/**
  @Summary
    Set the cursor position 

  @Description

  @Preconditions
    'LCD_Initialize' must be called before.

  @Param
	- line: Line to place the cursor.
	
	- row : Row to place the cursor
	
  @Returns
    None

  @Comment
    None

  @Example
    <code>
     LCD_SetCursorPosition( 0, 0 );
    </code>
*/
void LCD_SetCursorPosition( uint8_t line, uint8_t row ); 

/**
  @Summary
    Clear the LCD Screen 

  @Description

  @Preconditions
    'LCD_Initialize' must be called before.

  @Param
	  None
	
  @Returns
    None

  @Comment
	  None

  @Example
    <code>
     LCD_Clear();
    </code>
*/
#define LCD_Clear() LCD_CommandWrite(LCD_CMD_CLEAR_DISPLAY)

/**
  @Summary
    Move the cursor to first line first row position

  @Description
    This macro sets DDRAM address 0 into the address counter, and returns the 
  display to its original status if it was shifted. 
    The DDRAM contents do not change.
  @Preconditions
    'LCD_Initialize' must be called before.

  @Param
	  None
	
  @Returns
    None

  @Comment
	  None
  @Example
    <code>
     LCD_ReturnHome();
    </code>
*/
#define LCD_ReturnHome() LCD_CommandWrite(LCD_CMD_RETURN_HOME)

/**
  @Summary
    Shift Display to the left side

  @Description

  @Preconditions
    'LCD_Initialize' must be called before.

  @Param
	  None
	
  @Returns
    None

  @Comment
	  None
  @Example
    <code>
     LCD_DisplayShiftLeft();
    </code>
*/
#define LCD_DisplayShiftLeft()  LCD_CommandWrite(LCD_CMD_DISPLAY_SHIFT_LEFT)

/**
  @Summary
    Shift Display to the right side

  @Description

  @Preconditions
    'LCD_Initialize' must be called before.

  @Param
	None
	
  @Returns
    None

  @Comment
	None
  @Example
    <code>
     LCD_DisplayShiftRight();
    </code>
*/
#define LCD_DisplayShiftRight()  LCD_CommandWrite(LCD_CMD_DISPLAY_SHIFT_RIGHT)

/**
  @Summary
    Shift Cursor to the left side

  @Description

  @Preconditions
    'LCD_Initialize' must be called before.

  @Param
	None
	
  @Returns
    None

  @Comment
	  None
  
  @Example
    <code>
     LCD_CursorShiftLeft();
    </code>
*/
#define LCD_CursorShiftLeft()  LCD_CommandWrite(LCD_CMD_CURSOR_SHIFT_LEFT)

/**
  @Summary
    Shift Cursor to the right side

  @Description

  @Preconditions
    'LCD_Initialize' must be called before.

  @Param
	None
	
  @Returns
    None

  @Comment
	None
  @Example
    <code>
     LCD_CursorShiftRight();
    </code>
*/
#define LCD_CursorShiftRight()  LCD_CommandWrite(LCD_CMD_CURSOR_SHIFT_RIGHT)

#ifdef __cplusplus  // Provide C++ Compatibility
    }

#endif

#endif	//_LCD_H_ 
/**
 End of File
*/

