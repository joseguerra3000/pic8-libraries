/**
  EEPROM Driver API Header File for PIC16F887

  @Author
    Jose Guerra Carmenate

  @File Name
    eeprom_16f887.h

  @Summary
    This is the header file for the EEPROM driver using PIC16F887 MCUs

  @Description
    This header file provides APIs for driver for EEPROM.
*/


#ifndef _EEPROM_16f887_H
#define _EEPROM_16f887_H

/**
  Section: Included Files
*/

#include <xc.h>
#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus  // Provide C++ Compatibility

    extern "C" {

#endif

        
/**
  Section: Data Types Definitions
*/

#define EEPROM_MAX_ADDRESS 255


/**
  Section: EEPROM Module APIs
*/

/**
  @Summary
    Write one byte to the internal EEPROM Memory

  @Description

  @Preconditions
    None

  @Param
    - address: Address to store the data.
          
    - data: Data to be stored.
    
  @Returns
    None

  @Comment
    

  @Example
    <code>

    EEPROM_WriteByte( 0x05, 12 );

    </code>
*/
void EEPROM_WriteByte(uint8_t address, uint8_t data);


/**
  @Summary
    Read one byte from the internal EEPROM Memory

  @Description

  @Preconditions
	None
  @Returns
    None

  @Param
    - address: Memory address to read

  @Example
    <code>
    uint8_t eeprom_val;
	eeprom_val = EEPROM_ReadByte(0x12); 
    </code>
*/
uint8_t EEPROM_ReadByte(uint8_t address);


/**
  @Summary
    Write a byte array to the internal EEPROM Memory

  @Description

  @Preconditions
    None

  @Param
    - address: Address to store the data.
          
    - data: Array to be stored.
    - len: Len of data
    
  @Returns
    None

  @Comment
    

  @Example
    <code>

    EEPROM_WriteArray( 0x05, str, 10 );

    </code>
*/
void EEPROM_WriteNBytes(uint8_t address, uint8_t *data, uint8_t len );
 


/**
  @Summary
    Read one segment of Bytes from the internal EEPROM Memory

  @Description
    Read one segment( range:[addres, addres+len) ) of Bytes from the internal EEPROM Memory 
  @Preconditions
	None
  @Returns
    None

  @Param
    - address: Memory address to start the read
    - data: array for data recover
    - len: amount of bytes to be recovered

  @Example
    <code>
    uint8_t eeprom_val;
	eeprom_val = EEPROM_ReadByte(0x12); 
    </code>
*/
void EEPROM_ReadNBytes(uint8_t address, uint8_t *data, uint8_t len );


#ifdef __cplusplus  // Provide C++ Compatibility

    }

#endif

#endif	//ADC_16f887_H 
/**
 End of File
*/

