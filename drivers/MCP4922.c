/**
  MCP4922 Driver File

  @Author
    Jose Guerra Carmenate.

  @File Name
    MCP4922.c

  @Summary
    This is the driver implementation file for the MCP4922 driver using PIC MCUs 8bits.

  @Description
    Compiler          :  XC8 1.45
    MPLAB             :  MPLAB X 4.10
*/

/******************************************************************************
 ************************ Section: Included Files *****************************
 ******************************************************************************/

#include "MCP4922.h"

#include <xc.h>
#include <stddef.h>
#include "../hardware.h"
#include "../utils.h"
/******************************************************************************
 ************************** Section: Constants ********************************
 ******************************************************************************/

static MCP4922_t *ptr_adc = NULL; //Active MCP4922

/******************************************************************************
 ********************** Section: MCP4922 Module APIs **************************
 ******************************************************************************/


/* See header file for especifications */
MCP4922_t MCP4922_MCP4922(uint8_t* _port, uint8_t _bit, void(*sendByte)(uint8_t), bool(*isBusy)()){
    MCP4922_t adc;
    adc.IsBusy = isBusy;
    adc.SendCommand = sendByte;
    adc.SS_port = _port;
    adc.SS_bit = _bit;
    return adc;
}

/* See header file for especifications */
inline void MCP4922_SetActive(MCP4922_t* dac){
    ptr_adc = dac;
}


/* See header file for especifications */
bool MCP4922_SetConfiguration( MCP_VREF_BUFF vrefBuf, MCP_GAIN gain){
    if( ptr_adc == NULL )
        return false;
    BIT_SetBit( *(ptr_adc->SS_port), ptr_adc->SS_bit );
    ptr_adc->command.cmd = 0;
    ptr_adc->command.cmd |= (vrefBuf | gain);
    return true;
}

/* See header file for especifications */
bool MCP4922_WriteData( MCP_ADC_SELECT adc,  uint16_t data ){
    if( ptr_adc == NULL )
        return false;
    while( ptr_adc->IsBusy() );
    BIT_ClearBit( *(ptr_adc->SS_port), ptr_adc->SS_bit );
    ptr_adc->SendCommand( ptr_adc->command.upperByte );
    while( ptr_adc->IsBusy() );
    ptr_adc->SendCommand( ptr_adc->command.upperByte );

    return true;
}


/**
  @Summary
    Send a High-to-Low Pusle at Enable Pin

  @Description
    This routine send a High-to-Low Pusle at Enable Pin for pass data or command
 to LCD.
*/
static void lcd_strobe(){ 
    LCD_ControlBus |= 1u<<EN;
	__delay_us(10);                          
    LCD_ControlBus &= ~(1u<<EN);
}

/**
  @Summary
    Generate a Signal for send a command to the LCD.

  @Description
    Drive RS pin to Low State and generate a clock pulse on EN pin
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
    Drive RS pin to High State and generate a clock pulse on EN pin
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
#ifdef LCD_USE_RW
inline void lcd_BusyCheck(){
    uint8_t busyFlag;
    BIT_SetMask( LCD_DataBusDirection, DataMask ); // Configure DataBus as digital inputs
    LCD_ControlBus &= ~(1u<<RS);
    LCD_ControlBus |= 1u<<RW;
    do{
    	// read the high nibble
        lcd_strobe(); 
        __delay_us(10);
        busyFlag = BIT_GetBitStatus( LCD_DataBus,  DataPin[3]); //get the last bit
        //perform the read of the low nibble
        lcd_strobe();  
        __delay_us(10);
    }while( busyFlag );
    
    BIT_ClearMask( LCD_DataBusDirection, DataMask ); // Configure DataBus as digital outputs
}
#else
#define lcd_BusyCheck() do{ __delay_ms(1); }while(0)
#endif


static void lcd_PutNibble( uint8_t data ){
	uint8_t i = 0;
	while( i < 4u ){
		if( data & 1u )
			BIT_SetBit( LCD_DataBus, DataPin[i] );
		else
			BIT_ClearBit( LCD_DataBus, DataPin[i] );
		data >>= 1u;
		i++;
	}
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
	lcd_PutNibble( data>>4u );
    lcd_SendDataSignal();

	lcd_PutNibble( data );
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
void LCD_Attach( volatile uint8_t * _dataBus, uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7,  
                          volatile uint8_t* _controlBus, uint8_t _RS,
#ifdef LCD_USE_RW
        uint8_t _RW, 
#endif
        uint8_t _EN ){
	DataBus = _dataBus;
	DataBusDirection = lcd_GetTrisAddress( DataBus );
    DataPin[0u] = d4; DataPin[1u] = d5;
    DataPin[2u] = d6; DataPin[3u] = d7;
    DataMask = (1u<<d4) | (1u<<d5) | (1u<<d6) | (1u<<d7);
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
	
    BIT_ClearMask( LCD_DataBusDirection, DataMask );
    
#ifdef LCD_USE_RW
    LCD_ControlBusDirection &= ~((1u<<RS) | (1u<<RW) | (1u<<EN));
#else
    LCD_ControlBusDirection &= ~((1u<<RS) | (1u<<EN));
#endif
    
    
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
	lcd_DataWrite( a );	
}

/* See header file for especifications */
void LCD_CommandWrite( LCD_CMD cmd ){
    lcd_BusyCheck();
#ifdef LCD_USE_RW
    LCD_ControlBus &= ~( 1u<<RW );
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
    line--; row--;
    if( line < 2u && row < 40u )
        LCD_CommandWrite( (0x80u | (line*0x40u)) + row );
}


#endif
/**
 End of File
*/
