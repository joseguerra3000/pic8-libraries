/**
  EEPROM Driver File

  @Author
    Jose Guerra Carmenate.

  @File Name
    eeprom_16f887.c

  @Summary
    This is the driver implementation file for the EEPROM driver using PIC16F887 MCU.

  @Description
    Compiler          :  XC8 1.45
    MPLAB             :  MPLAB X 4.10
*/

#ifdef _16F887
/**
  Section: Included Files
*/

#include <xc.h>
#include <stdint.h>
#include "../eeprom.h"
/**
 Section: Constants
*/


/**
  Section: EEPROM Module APIs
*/

uint8_t EEPROM_ReadByte(uint8_t address){
	
    // wait until end read or write pending operations
    while( EECON1 & 0x03  );
    
    // Data Memory Address to read
    EEADR = address;
    
    // Point to data memory
    EECON1bits.EEPGD = 0;
    
    // Start read
    EECON1 |= _EECON1_RD_MASK;
    
    //wait the read process end
    while( EECON1 & _EECON1_RD_MASK );
    
    return EEDATA;
}

void EEPROM_WriteByte(uint8_t address, uint8_t data){
    // wait until end read or write pending operations
    while( EECON1 & 0x03 );
    
    // Data Memory Address to write
    EEADR = address;
    
    // Data Memory Data to write
    EEDAT = data;
    
    // Point to data memory
    EECON1bits.EEPGD = 0;
    
    // Enable Write
    EECON1bits.WREN = 1;
    
    //Disable INTs
    INTCONbits.GIE = 0;
    //Sequence
    EECON2 = 0x55;
    EECON2 = 0xAA;
    
    //Start to write
    EECON1bits.WR = 1;
    
    //Disable INTs
    INTCONbits.GIE = 1;
    
    // Wait until end write operation
    while( EECON1 & 0x03 );
    
    // Disable Write
    EECON1bits.WREN = 0;
}

void EEPROM_WriteNBytes(uint8_t address, uint8_t *data, uint8_t len ){
    while( len-- ){
        EEPROM_WriteByte( address, *data );
        data++;
        address++;
    }
}

void EEPROM_ReadNBytes(uint8_t address, uint8_t *data, uint8_t len ){
    while( len-- ){
        *data = EEPROM_ReadByte( address );
        data++;
    }
}


#endif
/**
 End of File
*/
