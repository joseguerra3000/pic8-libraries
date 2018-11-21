/**
  MCP4922 DAC Driver API Header File for 8bit PIC MCUs

  @Author
    Jose Guerra Carmenate

  @File Name
    mcp4922.h

  @Summary
    This is the header file for mcp4922 DAC driver using PIC MCUs

  @Description
    This header file provides generic APIs for driver the MCP4922 DAC.
*/


#ifndef _MCP4922_H
#define _MCP4922_H

/******************************************************************************
 *********************** Section: Included Files ******************************
 ******************************************************************************/

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus  // Provide C++ Compatibility

    extern "C" {

#endif

/******************************************************************************
 ********************* Section: Configuration Options *************************
 ******************************************************************************/


/******************************************************************************
 ********************* Section: Data Types Definitions ************************
 ******************************************************************************/
       
/**
 * MCP4922 Command
 **/
typedef union{
	uint16_t cmd;
    
    struct {
        uint8_t lowerByte;
        uint8_t upperByte;
    };
    
} mcp4922_command_t;


/**
 * MCP4922 Class
 */
typedef struct{
    
    mcp4922_command_t command;
    /**
     * Routine used for send one byte using SPI interface
     */
    void (*SendCommand)( uint8_t byte );

    /**
     * Routine used for check SPI buffer state
     */
    bool (*IsBusy)( void );

    /**
     * Port used for SS/CS pin
     */
    volatile uint8_t *SS_port;

    /**
     * Pin used for SS/CS of SS_port
     */
    uint8_t SS_bit;
} MCP4922_t;


/**
 * MCP4922 Select DAC
 */
typedef enum{
    MCP_DAC_SELECT_A = 0x00,
    MCP_DAC_SELECT_B = 0x80
} MCP_DAC_SELECT;

/**
 * MCP4922 VREF BUFFER 
 */
typedef enum{
    MCP_VREF_UNBUFFERED = 0x0,
    MCP_VREF_BUFERED    = 0x40
}MCP_VREF_BUFF;

/**
 * MCP4922 GAIN 
 */
typedef enum{
    MCP_GAIN_x2 = 0x00,
    MCP_GAIN_x1 = 0x20 
} MCP_GAIN;

typedef enum{
    MCP_OUTPUT_CONTROL_BUFFER_DISABLED = 0x00,
    MCP_OUTPUT_CONTROL_BUFFER_ENABLED  = 0x10
            
}MCP_OUTPUT_CONTROL;

/******************************************************************************
 ************************ Section: MCP4922 Module APIs ************************
 ******************************************************************************/

/**
  @Summary
 Return an MCP4922 object 

  @Description
    This routine take the pins used for Slave select( SS, /CS ), the 
  routines used for send data and check the state of SPI Bus; and return an
  MCP4922 object.
    This routine must be called before any other MCP4922 routine is called.

  @Preconditions
    SPI Bus need be initialized before call this function
    SS pin need be configurated as digital output before call this function

  @Param
    - port: Port used for SS. Ej: &PORTA, &PORTB, etc
 
    - bit : Bit used for SS. Unsigned integer on range [0, 7]

    - SendByte: The routine used to send one byte by SPI Bus

    - IsBusy : The routine used to check the SPI bus state.
 
  @Returns
    None

  @Comment
 Severals MCP4922 can have the same SendByte and ISBusy routine.

  @Example
    <code>
 struct MCP4922_t one, two;
    one = MCP4922_MCP4922( &PORTB, 2, SPI_WriteByte, SPI_IsBusy );
    two = MCP4922_MCP4922( &PORTC, 0, SPI_WriteByte, SPI_IsBusy );
    </code>
*/
MCP4922_t MCP4922_MCP4922( volatile uint8_t *SSport, uint8_t SSbit, void (*SendByte)( uint8_t ), bool (*IsBusy)(void) );

/**
  @Summary
   Set the MCP4922_t object passed as the 'active'.

  @Description
   This routine set the MCP4922_t object passed as the 'active'.

  @Preconditions
    None

  @Param
    - dac: pointer to MCP4922 object to be set as active
    
  @Returns
    None

  @Comment
    The routines MCP4922_Initialize() and MCP4922_SendComand() take efect over
 MCP4922 active

  @Example
    <code>
    struct MCP4922_t one; //declare MCP4922 object
    one = MCP4922_MCP4922( &PORTB, 2, SPI_WriteByte, SPI_IsBusy ); // Set routines and SS pin
    MCP4922_SetActive( &one ); //Set as active
    </code>
*/
inline void MCP4922_SetActive( MCP4922_t *dac );


/**
  @Summary
    Set the configuration for the 'Active' MCP4922 

  @Description
    This routine set the configuration of MCP4922.
    This routine must be called after MCP4922_SetActive routine 
    This routine can be called for change the configuration on any moment. 
    The change be updated on the next command send.

  @Preconditions
    MCP4922_SetActive routine must be called first

  @Param
    - vrefBuf: Set Vref Buffer State.
     "See MCP_VREF_BUFF enum on MCP4922.h file for available options"
     "Check Datasheet for more information"
    - gain: Set the Gain Value
     "See MCP_GAIN enum on MCP4922.h file for available options"
     "Check Datasheet for more information"

  @Returns
    true - Operation performed sussesfuly
    false - Invalid Active MCP4922
  @Comment
 * None
 
  @Example
    <code>
    struct MCP4922_t one; //declare MCP4922 object
    one = MCP4922_MCP4922( &PORTB, 2, SPI_WriteByte, SPI_IsBusy ); // Set routines and SS pin
    MCP4922_SetActive( &one ); //Set as active
    MCP4922_SetConfiguration( MCP_VREF_BUFERED,MCP_GAIN_x1);
    </code>
*/
bool MCP4922_SetConfiguration( MCP_VREF_BUFF vrefBuf, MCP_GAIN gain);

/**
  @Summary
    Send the digital value to the 'Active' MCP4922

  @Description
    This routine send one command to MCP4922 for set the output( VoutA, VoutB ).
    This routine must be called after MCP4922_SetActive routine 
    This routine can be called for change the configuration on any moment. 
    The change be updated on the next command send.

  @Preconditions
    MCP4922_SetActive routine must be called first

  @Param
    - vrefBuf: Set Vref Buffer State.
     "See MCP_VREF_BUFF enum on MCP4922.h file for available options"
     "Check Datasheet for more information"
    - gain: Set the Gain Value
     "See MCP_GAIN enum on MCP4922.h file for available options"
     "Check Datasheet for more information"

  @Returns
    true - Operation performed sussesfuly
    false - Invalid 'Active' MCP4922
  @Comment
 * None
 
  @Example
    <code>
    struct MCP4922_t one; //declare MCP4922 object <br>
    one = MCP4922_MCP4922( &PORTB, 2, SPI_WriteByte, SPI_IsBusy ); // Set routines and SS pin <br>
    MCP4922_SetActive( &one ); //Set as active  <br>
    MCP4922_SetConfiguration( MCP_VREF_BUFERED,MCP_GAIN_x1); // Configure Mode <br>
    int i;                  // integer <br>
    for ( i = 0; i < 10; i++ ){  // loop <br>
      __delay_ms(100);          // delay of 100ms <br>
      MCP4922_WriteData( MCP_ADC_SELECT_A, i*100 ); // Write data <br>
    }
    </code>
*/
bool MCP4922_WriteData( MCP_DAC_SELECT adc,  uint16_t data );


#ifdef __cplusplus  // Provide C++ Compatibility

    }

#endif

#endif	//MCP4944_H 
/**
 End of File
*/

