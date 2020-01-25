/**
  LCD Driver File

  @Author
    Jose Guerra Carmenate.

  @File Name
    lcd.c

  @Summary
    This is the driver implementation file for the LCD driver with 4bits
    interfaze using PIC MCUs 8bits.

  @Description
    Compiler          :  XC8 1.45
    MPLAB             :  MPLAB X 4.10
*/

/******************************************************************************
 ************************ Section: Included Files *****************************
 ******************************************************************************/

#include "lcd.h"
#include "lcd_config.h"

#include <xc.h>

#include "../hardware.h"

/******************************************************************************
 ************************ Section: LCD Module APIs ****************************
 ******************************************************************************/


/**
  @Summary
    Send a High-to-Low Pusle at Enable Pin

  @Description
    This macro send a High-to-Low Pusle at Enable Pin for pass data or command
 to LCD.
*/
#define lcd_strobe() do{ \
  EN = 1; 							 \
	__delay_us(10);        \
	EN = 0;                \
}while(0);


/**
  @Summary
    Generate a Signal for send a command to the LCD.

  @Description
    Drive RS pin to Low State and generate a clock pulse on EN pin
*/
#define lcd_SendCmdSignal() do{ \
	RS = 0;                       \
  lcd_strobe();                 \
} while(0)

/**
  @Summary
    Generate a Signal for send a data to the LCD.

  @Description
    Drive RS pin to High State and generate a clock pulse on EN pin
*/
#define lcd_SendDataSignal() do{  \
	RS = 1;                         \
  lcd_strobe();                   \
} while(0)

/**
  @Summary
    Wait while LCD controller is busy.

  @Description
    if RW pin is used this routine check the busy flag state.
    if RW is not used this routine make a delay of 1ms
    
*/
#ifdef LCD_USE_RW
inline void lcd_BusyCheck(){
    uint8_t busyFlag;
    //data bus as digital input
    D4_tris = D5_tris = D6_tris = D7_tris = 1;
    RS = 0;
    RW = 1; // read

    do{
    	// read the high nibble
      lcd_strobe(); 
      __delay_us(10);
      busyFlag = D7;
      //perform the read of the low nibble
      lcd_strobe();
      __delay_us(10);
    }while( busyFlag );
    
    //data bus as digital output
    D4_tris = D5_tris = D6_tris = D7_tris = 0;

}
#else
#define lcd_BusyCheck() do{ __delay_ms(1); }while(0)
#endif


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
  @Summary
    Send data to LCD 

  @Description

  @Preconditions
    'LCD_Initialize' must be called before.

  @Param
	- data: data to LCD.
		
  @Returns
    None

  @Comment
	None
*/
#define lcd_DataWrite(x) LCD_PrintChar(x)

/* See header file for especifications */
void LCD_Initialize( uint8_t lines, uint8_t row ){
  // data bus has output
  D4_tris = D5_tris = D6_tris = D7_tris = 0;
  
  //control bus has input
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
#ifdef LCD_USE_RW
  RW = 0;
#endif
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
