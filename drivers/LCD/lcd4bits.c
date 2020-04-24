/**
  @author
    Jose Guerra Carmenate.

  @file lcd4bits.c

  @brief
    This is the driver implementation file for the LCD API with 4bits
    interfaze using 8bits PIC MCUs.

  @note Compiler          :  XC8 2.00
  @note MPLAB             :  MPLAB X 5.10
*/

/******************************************************************************
 ************************ Section: Included Files *****************************
 ******************************************************************************/

#include "lcd.h"
#include "lcd_config.h"

#include <xc.h>

#include "device_config.h" // _XTAL_FREQ macro

/******************************************************************************
 ************************ Section: LCD Module APIs ****************************
 ******************************************************************************/


/**
  @brief
    Send a High-to-Low Pusle at Enable Pin

    This macro send a High-to-Low Pusle at Enable Pin for pass data or command
 to LCD.
*/
#define lcd_strobe() do{ \
  EN = 1; 							 \
	__delay_us(10);        \
	EN = 0;                \
}while(0);


/**
  @brief
    Generate a Signal for send a command to the LCD.

    Drive RS pin to Low State and generate a clock pulse on EN pin
*/
#define lcd_SendCmdSignal() do{ \
	RS = 0;                       \
  lcd_strobe();                 \
} while(0)

/**
  @brief
    Generate a Signal for send a data to the LCD.

    Drive RS pin to High State and generate a clock pulse on EN pin
*/
#define lcd_SendDataSignal() do{  \
	RS = 1;                         \
  lcd_strobe();                   \
} while(0)

/**
  @brief
    Wait while LCD controller is busy.

  This macro generate a delay of 1 ms.    
*/
#define lcd_BusyCheck() do{ __delay_ms(1); }while(0)

/**
  @brief
    Put the low nibble of data on LCD data bus. 


  @pre
    'LCD_Initialize' must be called before.

  @param[in] data data to put on LCD data bus.
		
  @return
    None

*/
static void lcd_PutNibble( uint8_t data ){
  D4 = data & 1;
  data >>=1;
  D5 = data & 1;
  data >>=1;
  D6 = data & 1;
  data >>=1;
  D7 = data & 1;
}

/**
  @brief
    Send data to LCD 

  @pre
    'LCD_Initialize' routine must be called before.

  @param x: data to send to LCD.
		
*/
#define lcd_DataWrite(x) LCD_PrintChar(x)


/* See header file for especifications */
void LCD_Initialize( uint8_t lines, uint8_t row ){
  // data bus has output
  D4_tris = D5_tris = D6_tris = D7_tris = 0;
  
  //control bus has output
  RS_tris = EN_tris = 0;
    
  __delay_ms(30u);
  // This routine is used to reset the LCD and configure on 4bits mode.
  lcd_PutNibble( 0x03u );
  lcd_SendCmdSignal();
  __delay_ms(100u);
  lcd_PutNibble( 0x03u );
  lcd_SendCmdSignal();
  __delay_us(200u);
  lcd_PutNibble( 0x03u );
  lcd_SendCmdSignal();
  __delay_us(200u);
  lcd_PutNibble( 0x02u );
  lcd_SendCmdSignal();
  __delay_us(200u);
  
  if( lines <= 1u )
    LCD_CommandWrite( LCD_CMD_FUNCTION_SET_4BITSMODE_1LINE_5X8DOTS );
  else
    LCD_CommandWrite( LCD_CMD_FUNCTION_SET_4BITSMODE_2LINES_5X8DOTS );

  __delay_us(50u);

  LCD_CommandWrite( LCD_CMD_DISPLAY_ON_CURSOR_OFF );
  __delay_us(50u);
  
  LCD_Clear();
  LCD_ReturnHome();
  __delay_ms(2u);    
}

/* See header file for especifications */
void LCD_PrintChar( char a ){
  lcd_BusyCheck();
	lcd_PutNibble( a>>4u );
  lcd_SendDataSignal();

	lcd_PutNibble( a );
  lcd_SendDataSignal();	
}

/* See header file for especifications */
void LCD_CommandWrite( LCD_CMD cmd ){
  lcd_BusyCheck();

  lcd_PutNibble( ((uint8_t)cmd)>>4u );
  lcd_SendCmdSignal();

  lcd_PutNibble( ((uint8_t)cmd) );
  lcd_SendCmdSignal(); 
}

/* See header file for especifications */
void LCD_PrintString(char* str){
    
  while( *str != '\0' )
    LCD_PrintChar( *str++ );
    
}

/* See header file for especifications */
void LCD_SetCursorPosition( uint8_t line, uint8_t row ){
  if( line < 2u && row < 40u )
    LCD_CommandWrite( (0x80u | (line*0x40u)) + row );
}
/**
 End of File
*/
