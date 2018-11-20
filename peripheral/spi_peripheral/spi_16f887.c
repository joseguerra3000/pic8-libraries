/**
  ADC Driver File

  @Author
    Jose Guerra Carmenate.

  @File Name
    adc_16f887.c

  @Summary
    This is the driver implementation file for the ADC driver using PIC16F887 MCU.

  @Description
    Compiler          :  XC8 1.45
    MPLAB             :  MPLAB X 4.10
*/

#ifdef _16F887
/**
  Section: Included Files
*/

#include <xc.h>
#include "../spi.h"
#include "../../hardware.h"
#include "../../utils.h"


/**
  Section: Macros
*/
#define _SPI_SDI_TRIS TRISCbits.TRISC4
#define _SPI_SDI_PORT PORTCbits.RC4

#define _SPI_SDO_TRIS TRISCbits.TRISC5
#define _SPI_SDO_PORT PORTCbits.RC5

#define _SPI_SCK_TRIS TRISCbits.TRISC3
#define _SPI_SCK_PORT PORTCbits.RC3

#define _SPI_SS_TRIS TRISAbits.TRISA5
#define _SPI_SS_PORT PORTAbits.RA5

#ifndef INPUT
#define INPUT 1
#endif

#ifndef OUTPUT
#define OUTPUT 0
#endif

/**
 Section: Constants
*/



/**
  Section: SPI Module APIs
*/

/* See header file for especifications */
void SPI_InitializeMaster( SPI_CLOCK_RATE bitRate, SPI_CLOCK_POLARITY clkPolarity, SPI_OUTPUT_DATA_PHASE clkEdge, SPI_INPUT_SAMPLING_PHASE inSample){
    SSPCON = 0;                 // Power off the SSP module
    
    _SPI_SDO_TRIS = OUTPUT;      // configure SDO pin as output
    _SPI_SCK_TRIS = OUTPUT;      // configure SCK pin as output
    _SPI_SDI_TRIS = INPUT;
    
    SSPCON |= bitRate;          // set the SSP module as SPI and the selected bit rate.
	SSPCON |= clkPolarity;      // set the CKP bit value
 
    SSPSTAT |= clkEdge;         // set the CKE bit value
    SSPSTAT |= inSample;        // set the SMP bit value
    
    SSPCON |= _SSPCON_SSPEN_MASK; // Power on the SSP module
   // SSPSTATbits.BF = 1;
}

/* See header file for especifications */
inline void SPI_WriteByte( uint8_t byte ){
    while( !(SSPSTAT & _SSPSTAT_BF_MASK) );
    SSPBUF;                                  
    SSPBUF = (byte);                         
}


/* See header file for especifications */
uint8_t SPI_ReadByte( ){
    while( !(SSPSTAT & _SSPSTAT_BF_MASK) );
    return SSPBUF;
}

#endif
/**
 End of File
*/
