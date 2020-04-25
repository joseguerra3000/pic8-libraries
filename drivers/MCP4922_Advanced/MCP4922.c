/**
  @author Jose Guerra Carmenate.

  @file MCP4922.c

  @brief   MCP4922 Driver File
  
  This is the driver implementation file for the MCP4922 driver using PIC MCUs 8bits.

  @note Compiler          :  XC8 2.00
  @note MPLAB             :  MPLAB X 5.10
*/

/******************************************************************************
 ************************ Section: Included Files *****************************
 ******************************************************************************/

#include "MCP4922.h"
#include <xc.h>
#include <stddef.h>
#include "../util/utils.h"
/******************************************************************************
 ************************** Section: Variables ********************************
 ******************************************************************************/

/**
 @brief Pointer to selected mcp4922_t struct
*/
static mcp4922_t *ptr_dac = NULL; //Active MCP4922

/******************************************************************************
 ********************** Section: MCP4922 Module APIs **************************
 ******************************************************************************/


/* See header file for especifications */
mcp4922_t MCP4922_MCP4922( volatile uint8_t* _port, uint8_t _bit, void (*sendByte) (uint8_t), bool(*isBusy)(void)){
    mcp4922_t dac;
    dac.IsBusy = isBusy;
    dac.SendCommand = sendByte;
    dac.SS_port = _port;
    dac.SS_bit = _bit;
    dac.command.cmd = 0;
    
    return dac;
}

/* See header file for especifications */
inline void MCP4922_SetActive(mcp4922_t* dac){
    ptr_dac = dac;
}


/* See header file for especifications */
bool MCP4922_SetConfiguration( MCP_VREF_BUFF vrefBuf, MCP_GAIN gain){
    if( ptr_dac == NULL )
        return false;
    BIT_SetBit( *(ptr_dac->SS_port), ptr_dac->SS_bit );
    ptr_dac->command.lowerByte = 0;
    ptr_dac->command.upperByte = ((uint8_t)vrefBuf | (uint8_t)gain);
    return true;
}

/* See header file for especifications */
bool MCP4922_WriteData( MCP_DAC_SELECT adc,  uint16_t data ){
    if( ptr_dac == NULL )
        return false;
    
    ptr_dac->command.upperByte &= 0x70;
    ptr_dac->command.upperByte |= (uint8_t)adc | (uint8_t)MCP_OUTPUT_CONTROL_BUFFER_ENABLED;
    ptr_dac->command.lowerByte = 0;
    ptr_dac->command.cmd |= (data & 0x0FFF);
    
    while( ptr_dac->IsBusy() );
    BIT_ClearBit( *(ptr_dac->SS_port), ptr_dac->SS_bit );
    ptr_dac->SendCommand( ptr_dac->command.upperByte );
    while( (*(ptr_dac->IsBusy))() );
    ptr_dac->SendCommand( ptr_dac->command.lowerByte );
    while( (*(ptr_dac->IsBusy))() );
    BIT_SetBit( *(ptr_dac->SS_port), ptr_dac->SS_bit );
    
    return true;
}
/**
 End of File
*/
