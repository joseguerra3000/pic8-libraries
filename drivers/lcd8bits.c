/**
  LCD Driver File

  @Author
    Jose Guerra Carmenate.

  @File Name
    lcd8bits.c

  @Summary
    This is the driver implementation file for the LCD driver with 8bits 
    interfaze using PIC MCUs 8bits.

  @Description
    Compiler          :  XC8 1.45
    MPLAB             :  MPLAB X 4.10
*/

/******************************************************************************
 ************************ Section: Included Files *****************************
 ******************************************************************************/
#include "lcd.h"

#ifndef LCD_INTERFAZE_4BITS 

#include <xc.h>
#include <stdarg.h>
#include <stdio.h>
#include "../hardware.h"
#include "../utils.h"

/******************************************************************************
 ************************** Section: Constants ********************************
 ******************************************************************************/

volatile uint8_t *DataBus;
volatile uint8_t *DataBusDirection;
#define DataMask 0xFF;

volatile uint8_t *ControlBus;
volatile uint8_t *ControlBusDirection;
uint8_t RS,
        EN;

#ifdef LCD_USE_RW
uint8_t RW;
#endif

#define LCD_DataBus (*DataBus)
#define LCD_DataBusDirection (*DataBusDirection)

#define LCD_ControlBus (*ControlBus)
#define LCD_ControlBusDirection (*ControlBusDirection)

/******************************************************************************
 ************************ Section: LCD Module APIs ****************************
 ******************************************************************************/


/**
  @Summary
    Send a High-to-Low Pusle at Enable Pin

  @Description
    This routine send a High-to-Low Pusle at Enable Pin for pass data or command
 to LCD.
*/
static void lcd_strobe(){ 
    LCD_ControlBus |= 1<<EN;
	__delay_us(10);                          
    LCD_ControlBus &= ~(1<<EN);
}

/**
  @Summary
    Generate a Signal for send a command to the LCD.

  @Description
    Drive RS pin and RW( if used ) to Low State and generate a clock pulse on EN pin
*/
static void lcd_SendCmdSignal(){
#ifdef LCD_USE_RW
    LCD_ControlBus &= ~( 1u<<RS | 1u<<RW );
#else
    LCD_ControlBus &= ~(1u<<RS);    
#endif
    
	lcd_strobe();
}

/**
  @Summary
    Generate a Signal for send a data to the LCD.

  @Description
    Drive RS pin to High State, RW(if used) to Low State and generate a clock 
  pulse on EN pin
*/
static void lcd_SendDataSignal(){
	LCD_ControlBus |= 1u<<RS;
    
#ifdef LCD_USE_RW
    LCD_ControlBus &= ~(1u<<RW);
#endif
    lcd_strobe();
}

/**
  @Summary
    Wait while LCD controller is busy.

  @Description
    if RW pin is used this routine check the busy flag state.
    if RW is not used this routine make a delay of 1ms
    
*/
static bool lcd_BusyCheck(){
#ifdef LCD_USE_RW
    uint8_t busyFlag;
    LCD_DataBusDirection = DataMask; // Configure DataBus as digital inputs
    LCD_ControlBus &= ~(1u<<RS);
    LCD_ControlBus |= 1u<<RW;
    do{
        lcd_strobe();
        __delay_us(10);
        busyFlag = LCD_DataBus & 0x80; //get the last bit
    }while( busyFlag );
    LCD_DataBusDirection = 0x00; // Configure DataBus as digital output
#else
    __delay_ms(1);
#endif
}

/**
  @Summary
    Send data to LCD 

  @Description

  @Preconditions
    'LCD_Initialize8BitsMode' must be called before.

  @Param
	- data: data to LCD.
		
  @Returns
    None

  @Comment
	None
*/
static void lcd_DataWrite( char data ){
	lcd_BusyCheck();
    LCD_DataBus = data;
    lcd_SendDataSignal();

	
}

/**
  @Summary
    Get the TRISx register corresponding to a PORTx register 

  @Description
  	Check every posible PORTx option.

  @Param
	- port: Address direction of one PORTx SFR.
		"Ej: &PORTA"
	
  @Returns
    Address to one TRISx SFR.

  @Comment
	None
*/
volatile uint8_t* lcd_GetTrisAddress( volatile uint8_t *port ){
	#ifdef PORTA
	if( port == &PORTA )
		return &TRISA;
	#endif

	#ifdef PORTB
	if( port == &PORTB )
		return &TRISB;
	#endif

	#ifdef PORTC
	if( port == &PORTC )
		return &TRISC;
	#endif
	
	#ifdef PORTD
	if( port == &PORTD )
		return &TRISD;
	#endif
	#ifdef PORTE
	if( port == &PORTE )
		return &TRISE;
	#endif
}

/* See header file for especifications */
void LCD_Attach( volatile uint8_t * _dataBus, volatile uint8_t* _controlBus, uint8_t _RS, 
#ifdef LCD_USE_RW
        uint8_t _RW, 
#endif
        uint8_t _EN ){
	DataBus = _dataBus;
	DataBusDirection = lcd_GetTrisAddress( DataBus );
	ControlBus = _controlBus;
	ControlBusDirection = lcd_GetTrisAddress( ControlBus );
	RS = _RS;
    
#ifdef LCD_USE_RW
	RW = _RW;
#endif
    
	EN = _EN;
}

/* See header file for especifications */
void LCD_Initialize( uint8_t lines, uint8_t row ){
	
    LCD_DataBusDirection = 0x00;
#ifdef LCD_USE_RW
    LCD_ControlBusDirection &= ~((1u<<RS) | (1u<<RW) | (1u<<EN));
#else
    LCD_ControlBusDirection &= ~((1u<<RS) | (1u<<EN));
#endif
    
    __delay_ms(30);
    if( lines <= 1 )
        LCD_CommandWrite( LCD_CMD_FUNCTION_SET_8BITSMODE_1LINE_5x8DOTS );
    else
        LCD_CommandWrite( LCD_CMD_FUNCTION_SET_8BITSMODE_2LINES_5x8DOTS );
	
    __delay_us(50);
	
	LCD_CommandWrite( LCD_CMD_DISPLAY_ON_CURSOR_OFF );
    __delay_us(50);
    
	LCD_Clear();
    LCD_ReturnHome();	
    __delay_ms(2);
    
}

/* See header file for especifications */
void LCD_PrintChar( char a ){
	lcd_DataWrite( a );	
}

/* See header file for especifications */
void LCD_CommandWrite( LCD_CMD cmd ){
    lcd_BusyCheck();
    LCD_DataBus = (uint8_t)cmd;
    lcd_SendCmdSignal();
   
}

/* See header file for especifications */
void LCD_Clear( ){
    LCD_CommandWrite( LCD_CMD_CLEAR_DISPLAY );
    LCD_CommandWrite(LCD_CMD_RETURN_HOME);
}

/* See header file for especifications */
void LCD_PrintString(char* str){
    
    while( *str != '\0' )
        LCD_PrintChar( *str++ );
    
}

/* See header file for especifications */
void LCD_SetCursorPosition( uint8_t line, uint8_t row ){
    line--; row--;
    if( line < 2 && row < 40 )
        LCD_CommandWrite( (0x80 | (line*0x27)) + row );
}


#endif
/**
 End of File
*/
