/**
  @author Jose Guerra Carmenate

  @file MCP4922.h

  @brief   MCP4922 DAC Driver API Header File for 8bit PIC MCUs

  This is the header file for MCP4922 DAC driver using PIC MCUs.
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
 * @brief MCP4922 Command
 **/
typedef union{
	uint16_t cmd;///< Used for evaluate the command as word of 16bits
    
    struct {
        uint8_t lowerByte;///< Low byte of command
        uint8_t upperByte;///< High byte of command
    };
    
} mcp4922_command_t;


/**
 * @brief MCP4922 Struct
 */
typedef struct{
    mcp4922_command_t command; ///< Struct for store the command to send.
		
    void (*SendCommand)( uint8_t byte ); ///< Routine used for send one byte using SPI interface

    bool (*IsBusy)( void ); ///< Routine used for check SPI buffer state

    volatile uint8_t *SS_port; ///< Port used for SS/CS pin

    uint8_t SS_bit; ///< Pin used for SS/CS of SS_port

} mcp4922_t;


/**
 * MCP4922 Select DAC options
 */
typedef enum{
    MCP_DAC_SELECT_A = 0x00,  ///< Select DAC A
    MCP_DAC_SELECT_B = 0x80   ///< Select DAC B
} MCP_DAC_SELECT;

/**
 * MCP4922 VREF BUFFER options
 */
typedef enum{
    MCP_VREF_UNBUFFERED = 0x0,///< Unbuffered
    MCP_VREF_BUFERED    = 0x40///< Buffered
}MCP_VREF_BUFF;

/**
 * MCP4922 GAIN options
 */
typedef enum{
    MCP_GAIN_x2 = 0x00, ///< Gain x2
    MCP_GAIN_x1 = 0x20  ///< Gain x1
} MCP_GAIN;

/**
 * MCP4922 Output Control options
 */
typedef enum{
    MCP_OUTPUT_CONTROL_BUFFER_DISABLED = 0x00, ///< Output buffer disabled
    MCP_OUTPUT_CONTROL_BUFFER_ENABLED  = 0x10  ///< Output buffer enabled
}MCP_OUTPUT_CONTROL;

/******************************************************************************
 ************************ Section: MCP4922 Module APIs ************************
 ******************************************************************************/

/**
  @brief Build a MCP4922 object 

    This routine take the pins used for Slave select( SS or /CS ), the 
  routines used for send data and check the state of SPI Bus; and return an
  mcp4922_t object.
    This routine must be called before any other MCP4922 routine is called.

  @pre
    - SPI Bus need be initialized before call this function
    - SS pin need be configurated as digital output before call this function

  @param[in] SSport Port used for SS. Ej: &PORTA, &PORTB, etc
 
  @param[in] SSbit Bit used for SS. Unsigned integer on range [0, 7]

  @param[in] SendByte The routine used to send one byte by SPI Bus

  @param[in] IsBusy The routine used to check the SPI bus state.
 
  @note Severals MCP4922 can have the same SendByte and ISBusy routine.

  <b>Example</b>
    @code
    struct mcp4922_t one, two;
    one = MCP4922_MCP4922( &PORTB, 2, SPI_WriteByte, SPI_IsBusy );
    two = MCP4922_MCP4922( &PORTC, 0, SPI_WriteByte, SPI_IsBusy );
    @endcode
*/
mcp4922_t MCP4922_MCP4922( volatile uint8_t *SSport, uint8_t SSbit, void (*SendByte)( uint8_t ), bool (*IsBusy)(void) );

/**
  @brief
   Set the mcp4922_t object passed as the 'active'.

   This routine set the mcp4922_t object passed as the 'active'.

  @param[in] dac pointer to MCP4922 object to be set as active
    
  @note The routines MCP4922_Initialize() and MCP4922_SendComand() take efect over
 MCP4922 active

  <b>Example</b>
    @code
    struct mcp4922_t one; //declare MCP4922 object
    one = MCP4922_MCP4922( &PORTB, 2, SPI_WriteByte, SPI_IsBusy ); // Set routines and SS pin
    MCP4922_SetActive( &one ); //Set as active
    @endcode
*/
inline void MCP4922_SetActive( mcp4922_t *dac );


/**
  @brief Set the configuration for the 'Active' MCP4922 
  
    This routine set the configuration of MCP4922.
    This routine must be called after MCP4922_SetActive routine 
    This routine can be called for change the configuration on any moment. 
    The change be updated on the next command send.

  @pre
    MCP4922_SetActive routine must be called first

  @param[in] vrefBuf Set Vref Buffer State.
     "See \ref MCP_VREF_BUFF enum on MCP4922.h file for available options"
     "Check Datasheet for more information"
  @param[in] gain Set the Gain Value
     "See \ref MCP_GAIN enum on MCP4922.h file for available options"
     "Check Datasheet for more information"

  @return
    - \b true: Operation performed sussesfuly,
    - \b false: Invalid Active MCP4922
 
  <b>Example</b>
    @code
    struct mcp4922_t one; //declare MCP4922 object
    one = MCP4922_MCP4922( &PORTB, 2, SPI_WriteByte, SPI_IsBusy ); // Set routines and SS pin
    MCP4922_SetActive( &one ); //Set as active
    MCP4922_SetConfiguration( MCP_VREF_BUFERED,MCP_GAIN_x1);
    @endcode
*/
bool MCP4922_SetConfiguration( MCP_VREF_BUFF vrefBuf, MCP_GAIN gain);

/**
  @brief
    Send the digital value to the 'Active' MCP4922
  
    This routine send one command to MCP4922 for set the output( VoutA, VoutB ).
    This routine must be called after MCP4922_SetActive routine 
    This routine can be called for change the configuration on any moment. 
    The change be updated on the next command send.

  @pre
    \ref MCP4922_SetActive routine must be called first

  @param[in] adc Set adc output to use.
     "See \ref MCP_DAC_SELECT enum on MCP4922.h file for available options"
     "Check Datasheet for more information"
  @param[in] data Set the data of selected output

  @return
    - true: Operation performed sussesfuly
    - false: Invalid 'Active' MCP4922
 
  <b>Example</b>
    @code
    struct mcp4922_t one; //declare MCP4922 object <br>
    one = MCP4922_MCP4922( &PORTB, 2, SPI_WriteByte, SPI_IsBusy ); // Set routines and SS pin <br>
    MCP4922_SetActive( &one ); //Set as active  <br>
    MCP4922_SetConfiguration( MCP_VREF_BUFERED,MCP_GAIN_x1); // Configure Mode <br>
    int i;                  // integer <br>
    for ( i = 0; i < 10; i++ ){  // loop <br>
      __delay_ms(100);          // delay of 100ms <br>
      MCP4922_WriteData( MCP_ADC_SELECT_A, i*100 ); // Write data <br>
    }
    @endcode
*/
bool MCP4922_WriteData( MCP_DAC_SELECT adc,  uint16_t data );


#ifdef __cplusplus  // Provide C++ Compatibility

    }

#endif

#endif	//MCP4944_H 
/**
 End of File
*/

