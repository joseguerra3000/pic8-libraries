/**
  @author Jose Guerra Carmenate

  @file lcd.h

  @brief This is the header file for LCD driver using PIC MCUs

    This header file provides APIs for driver for LCD. This API 
    can be used with any 8 bits PIC MCU using 6 GPIO pins. Pins are
    defined on lcd_config.h header.
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
 @brief LCD Commands
 
 Set of available commands for use with LCD display. LCD_CommandWrite 
 routine must be used for send commands to LCD.
 **/
typedef enum{
    LCD_CMD_CLEAR_DISPLAY                           = 0x01u,///< Clear Display command 
    LCD_CMD_RETURN_HOME                             = 0x02u,///< Return Home command
    LCD_CMD_FUNCTION_SET_8BITSMODE_2LINES_5x8DOTS	  = 0x38u,///< 8 bits mode with 2 lines command
    LCD_CMD_FUNCTION_SET_8BITSMODE_1LINE_5x8DOTS 	  = 0x30u,///< 8 bits mode with 1 line command
    LCD_CMD_FUNCTION_SET_4BITSMODE_2LINES_5X8DOTS	  = 0x28u,///< 4 bits mode with 2 lines command
    LCD_CMD_FUNCTION_SET_4BITSMODE_1LINE_5X8DOTS	  = 0x20u,///< 4 bits mode with 1 lines command
    LCD_CMD_FUNCTION_SET_4BITSMODE_1LINE_5X10DOTS   = 0x24u,///< 4 bits mode with 1 line and 5x10 dots chars command
    LCD_CMD_DISPLAY_ON_CURSOR_ON                    = 0x0Eu,///< Cursor On command
    LCD_CMD_DISPLAY_ON_CURSOR_BLINK                 = 0x0Fu,///< Cursor Blink command
    LCD_CMD_DISPLAY_ON_CURSOR_OFF                   = 0x0Cu,///< Cursor Off command
    LCD_CMD_DISPLAY_SHIFT_LEFT                      = 0x18u,///< Shift Left Display command
    LCD_CMD_DISPLAY_SHIFT_RIGHT                     = 0x1Cu,///< Shift Right Display command
    LCD_CMD_CURSOR_SHIFT_LEFT                       = 0x10, ///< Shift Left Cursor command
    LCD_CMD_CURSOR_SHIFT_RIGHT                      = 0x14, ///< Shift Right Cursor command
} LCD_CMD;

/******************************************************************************
 ************************** Section: LCD Module APIs **************************
 ******************************************************************************/

/**
  @brief
    Initializes the LCD for 4bit Mode

    This routine initializes the LCD, for this reason must be called 
    before any other LCD routine is called.
    This routine should only be called once during system initialization.

  @pre
    the lcd_config.h header file must be correctly configured. 
    
  @param[in] lines Number of lines on LCD (1 or 2)
  @param[in] row Number of rows on LCD 

  @return
    None

  <b>Example</b>
    @code
     LCD_Initialize( 2, 16 );
    @endcode
*/
void LCD_Initialize(uint8_t lines, uint8_t row);

/**
  @brief
    Send one command to LCD 
    
    
  @pre
    'LCD_Initialize' routine must be called before.

  @param[in] cmd: Command for send to LCD.
		"For available command refer to enum LCD_CMD or LCD datasheet"
	
  @return
    None

  <b>Example</b>
    @code
    LCD_CommandWrite( LCD_CMD_CLEAR_DISPLAY );
    @endcode
*/
void LCD_CommandWrite( LCD_CMD cmd );

/**
  @brief
    Print a character on LCD's cursor position

  @pre
    LCD_Initialize routine must be called before.

  @param[in] c Character to print.
		"Any printable character is valid"

  <b> Example </b>
    @code
     LCD_PrintChar( 'w' ); //Print a w on LCD.
    @endcode
*/
void LCD_PrintChar( char c );

/**
  @brief
    Print a string on LCD's current cursor position

  @pre
    LCD_Initialize routine must be called before.

  @param[in] string: String to print on LCD.
	
  <b>Example </b>
    @code
    LCD_PrintString( "Alfa" );
    @endcode
*/
void LCD_PrintString( char *string );

/**
  @brief
    Set the cursor position 

  @pre
    'LCD_Initialize' routine must be called before.

  @param[in] line Line to place the cursor.
	@param[in] row Row to place the cursor
	
  <b>Example </b>
    @code
     LCD_SetCursorPosition( 0, 0 );
    @endcode
*/
void LCD_SetCursorPosition( uint8_t line, uint8_t row ); 

/**
  @brief
    Clear the LCD Screen. 
    
    Send a Clear Display command to LCD. This command put 
    20H on all LCD RAM position.

  @pre
    'LCD_Initialize' routine must be called before.

  <b>Example </b>
    @code
     LCD_Clear();
    @endcode
*/
#define LCD_Clear() LCD_CommandWrite(LCD_CMD_CLEAR_DISPLAY)

/**
  @brief
    Move the cursor to first line first row position
  
    This macro sets DDRAM address 0 into the address counter, and returns the 
  display to its original status if it was shifted. 
    The DDRAM contents do not change.
    
  @pre
    'LCD_Initialize' routine must be called before.

  <b>Example </b>
    @code
     LCD_ReturnHome();
    @endcode
*/
#define LCD_ReturnHome() LCD_CommandWrite(LCD_CMD_RETURN_HOME)

/**
  @brief
    Shift Display to the left side

  @pre
    'LCD_Initialize' routine must be called before.

  <b>Example </b>
    @code
     LCD_DisplayShiftLeft();
    @endcode
*/
#define LCD_DisplayShiftLeft()  LCD_CommandWrite(LCD_CMD_DISPLAY_SHIFT_LEFT)

/**
  @brief
    Shift Display to the right side

  @pre
    'LCD_Initialize' routine must be called before.

  <b>Example </b>
    @code
     LCD_DisplayShiftRight();
    @endcode
*/
#define LCD_DisplayShiftRight()  LCD_CommandWrite(LCD_CMD_DISPLAY_SHIFT_RIGHT)

/**
  @brief
    Shift Cursor to the left side

  @pre
    'LCD_Initialize' routine must be called before.
  
  <b>Example </b>
    @code
     LCD_CursorShiftLeft();
    @endcode
*/
#define LCD_CursorShiftLeft()  LCD_CommandWrite(LCD_CMD_CURSOR_SHIFT_LEFT)

/**
  @brief
    Shift Cursor to the right side

  @pre
    'LCD_Initialize' routine must be called before.

  <b>Example </b>
    @code
     LCD_CursorShiftRight();
    @endcode
*/
#define LCD_CursorShiftRight()  LCD_CommandWrite(LCD_CMD_CURSOR_SHIFT_RIGHT)

#ifdef __cplusplus  // Provide C++ Compatibility
    }

#endif

#endif	//_LCD_H_ 
/**
 End of File
*/

