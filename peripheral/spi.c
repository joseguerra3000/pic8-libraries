/**
  ADC Driver File

  @Author
    Jose Guerra Carmenate.

  @File Name
    spi.c

  @Summary
    This is the driver implementation file for the SPI driver using PIC Mid-Range MCU.

  @Description
    Compiler          :  XC8 2.00
    MPLAB             :  MPLAB X 5.10
*/

/**
  Section: Included Files
*/

#include <xc.h>
#include "spi.h"


/**
  Section: Macros
*/


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
void SPI_Initialize( SPI_MODE mode, SPI_CLOCK_POLARITY clkPolarity, SPI_OUTPUT_DATA clkEdge, SPI_INPUT_SAMPLING inSample){
    SSPCON = 0;                 // Power off the SSP module
    
    _SDO_TRIS = OUTPUT;         // SDO pin as output
    _SDI_TRIS = INPUT;          // SDI pin as input
    if( mode & 0x04 ){              // Is a Slave mode?
        _SCK_TRIS = INPUT;      // configure SCK pin as input
        _SS_TRIS = INPUT;       // configure SS pin as input
        SSPSTAT = clkEdge;
    }
    else{
        _SCK_TRIS = OUTPUT;      // configure SCK pin as output
        SSPSTAT = inSample | clkEdge;
    }
    
    SSPCON = mode | clkPolarity;
        
    SSPCONbits.SSPEN = 1; 
}

void SPI_SetTransmissionMode( SPI_TRANSMISSION_MODE txMode ){
    SSPCONbits.SSPEN = 0;
    SSPSTATbits.CKE = (_Bool)(txMode & _SSPSTAT_CKE_MASK);
    SSPCONbits.CKP = (_Bool)(txMode & _SSPCON_CKP_MASK);
    SSPCONbits.SSPEN = 1;
}


/* See header file for especifications */
inline uint8_t SPI_SendByte( uint8_t byte ){
    SSPBUF = byte;
    while( !SSPSTATbits.BF );
    return SSPBUF;
}


/**
 End of File
*/
