/**
  SPI Driver API Header File for PIC16F887

  @Author
    Jose Guerra Carmenate

  @File Name
    spi_16f887.h

  @Summary
    This is the header file for the SPI driver using PIC16F887 MCUs

  @Description
    This header file provides APIs for driver for SPI.
*/


#ifndef SPI_16f887_H
#define SPI_16f887_H

/**
  Section: Included Files
*/

#include <xc.h>
#include <stdint.h>
#include <stdbool.h>
#include "../../utils.h"
#ifdef __cplusplus  // Provide C++ Compatibility

    extern "C" {

#endif



/**
  Section: Macros
*/
#define SPI_SDI_TRIS TRISCbits.TRISC4
#define SPI_SDI_PORT PORTCbits.RC4

#define SPI_SDO_TRIS TRISCbits.TRISC5
#define SPI_SDO_PORT PORTCbits.RC5

#define SPI_SCK_TRIS TRISCbits.TRISC3
#define SPI_SCK_PORT PORTCbits.RC3

#define SPI_SS_TRIS TRISAbits.TRISA5
#define SPI_SS_PORT PORTAbits.RA5

        
/**
  Section: Data Types Definitions
*/

/**
 * SPI Master Clock Rate
 **/
typedef enum{
    SPI_CLOCK_RATE_FOSC_DIV_4  = 0b0000,
    SPI_CLOCK_RATE_FOSC_DIV_16 = 0b0001,
    SPI_CLOCK_RATE_FOSC_DIV_64 = 0b0010,
    SPI_CLOCK_RATE_TMR2_DIV_2  = 0b0011
} SPI_CLOCK_RATE;

/**
 * SPI CLOCK POLARITY
 **/
typedef enum{
    SPI_CLOCK_POLARITY_IDLE_LOW     = 0b00000,
    SPI_CLOCK_POLARITY_IDLE_HIGH    = _SSPCON_CKP_MASK
} SPI_CLOCK_POLARITY;

/**
 * SPI OUTPUT DATA PHASE
 **/
typedef enum{
    SPI_OUTPUT_DATA_PHASE_ON_ACTIVE_TO_IDLE_CLOCK = 0b00000000,
    SPI_OUTPUT_DATA_PHASE_ON_IDLE_TO_ACTIVE_CLOCK = _SSPSTAT_CKE_MASK
}SPI_OUTPUT_DATA_PHASE;


/**
 * SPI INPUT SAMPLING PHASE
 **/
typedef enum{
    SPI_INPUT_SAMPLING_PHASE_IN_MIDDLE  = 0b00000000,
    SPI_INPUT_SAMPLING_PHASE_AT_END     = _SSPSTAT_SMP_MASK,
} SPI_INPUT_SAMPLING_PHASE;


/**
  Section: SPI Module APIs
*/

/**
  @Summary
    Initializes the SPI

  @Description
    This routine initializes the MSSP on SPI Master mode.
    This routine must be called before any other SPI Master routine is called.
    This routine should only be called once during system initialization.

  @Preconditions
    None

  @Param bitRate - Select the bit rate used on CLK pin for SPI communication.
 See SPI_CLOCK_RATE enum for available options.
  
  @Param clkPolarity - Select the clock polarity used on CLK pin for SPI 
 communication. See SPI_CLOCK_POLARITY enum for available options.
  @Param clkEdge - Select the edge for data output. See SPI_OUTPUT_DATA_PHASE
   enum for available options
  
  @Returns
    None

  @Comment
    

  @Example
    <code>
   

    SPI_InitializeMaster( SPI_CLOCK_RATE_FOSC_DIV_4, 
                          SPI_CLOCK_POLARITY_IDLE_LOW, 
                          SPI_OUTPUT_DATA_PHASE_ON_IDLE_TO_ACTIVE_CLOCK,
                          SPI_INPUT_SAMPLING_PHASE_AT_END );

    </code>
*/
void SPI_InitializeMaster( SPI_CLOCK_RATE bitRate, SPI_CLOCK_POLARITY clkPolarity, SPI_OUTPUT_DATA_PHASE clkEdge, SPI_INPUT_SAMPLING_PHASE inSample){
    SSPCON = 0;                 // Power off the SSP module
    
    SPI_SDO_TRIS = OUTPUT;      // configure SDO pin as output
    SPI_SCK_TRIS = OUTPUT;      // configure SCK pin as output
    SPI_SDI_TRIS = INPUT;
    
    SSPCON |= bitRate;          // set the SSP module as SPI and the selected bit rate.
	SSPCON |= clkPolarity;      // set the CKP bit value
 
    SSPSTAT |= clkEdge;         // set the CKE bit value
    SSPSTAT |= inSample;        // set the SMP bit value
    
    SSPCON |= _SSPCON_SSPEN_MASK; // Power on the SSP module
   // SSPSTATbits.BF = 1;
}


/**
  @Summary
    Send one byte 

  @Description
    This routine is used to send one byte using SPI.
    This is a bloking routine. 
 This routine wait until BF = 1 for send the byte

  @Preconditions
    SPI_InitializeMaster() function should have been called before calling this function.

  @Returns
    None

  @Param
    byte - Byte to send.

  @Example
    <code>
    SPI_InitializeMaster( ... );
    .
    .
    .
    SPI_WriteByte( 0x45 );
    </code>
*/
inline void SPI_WriteByte( uint8_t byte ){
    while( !(SSPSTAT & _SSPSTAT_BF_MASK) );
    SSPBUF;                                  
    SSPBUF = (byte);                         
}

/**
  @Summary
    Returns the current SPI module activity status.

  @Description
    This routine is used to get SPI module activity status.
    
  @Preconditions
    SPI_InitializeMaster() function should have been called before calling this function.

  @Returns
    true - SPI module is currently busy with some transactions
    false - SPI module is currently idle

  @Param
    None

  @Example
    <code>
 bool status = SPI_IsBusy();
    </code>
*/
#define SPI_IsBusy() ((SSPSTAT & _SSPSTAT_BF_MASK)?0:1) 

/**
  @Summary
    This function returns the SPI buffer value

  @Description
    This routine is used to obtain the value stored on SPI buffer.
    This routine wait until BF = 1

  @Preconditions
    SPI_InitializeMaster() function should have been called before calling this function.

  @Returns
    The SPI buffer value

  @Param
    None

  @Example
    <code>
 uint8_t data_rx = SPI_ReadByte();
    </code>
 */
uint8_t SPI_ReadByte( ){
    while( !(SSPSTAT & _SSPSTAT_BF_MASK) );
    return SSPBUF;
}


 
#ifdef __cplusplus  // Provide C++ Compatibility

    }

#endif

#endif	//ADC_16f887_H 
/**
 End of File
*/

