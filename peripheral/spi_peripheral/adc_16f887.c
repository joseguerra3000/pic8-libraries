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
#include "../adc.h"
#include "../../hardware.h"
#include "../../utils.h"
#include "../pin_manager.h"
/**
 Section: Constants
*/
/**
 * Map of: last analog channels to the TRISB bit 
 */
const uint8_t analog_channel_to_trisb_bit[] = { 
    2,  // AN8
    3,  // AN9
    1,  // AN10
    4,  // AN11
    0   // AN12
};

/**
  Section: ADC Module APIs
*/

void ADC_Initialize(CONVERSION_CLOCK convClock, VOLTAGE_REFERENCE voltRef){
    ADCON0 = 0 | convClock; 
    //right justified
    ADCON1 = 0b10000000 | voltRef;    
}

void ADC_SelectChannel(adc_channel_t channel){
    // select the A/D channel
    ADCON0bits.CHS = channel;
    
    //configure I/O pin as analog
    if( channel < 8 )
        ANSEL = 1u<<channel;
    else{
        ANSELH = 1u<<(channel-8);
    }
    // Turn on the ADC module
    ADCON0bits.ADON = 1;  
}

 uint16_t ADC_GetConversion(adc_channel_t channel){

    // select the A/D channel
    ADCON0bits.CHS = channel;
    
    if( channel < 4u ){
        BIT_SetBit( TRISA, channel );
    }
    else if( channel == 4 ){
        TRISAbits.TRISA5 = 1;
    }
    else if( channel < 8 ){
        BIT_SetBit( TRISE, channel-5);
    }
    else{
        BIT_SetBit( TRISB, analog_channel_to_trisb_bit[channel-8u] );
    }
    //configure I/O pin as analog
    if( channel < 8 )
        ANSEL = 1u<<channel;
    else{
        ANSELH = 1u<<(channel-8);
    }
    // Turn on the ADC module
    ADCON0bits.ADON = 1;  
    
    //ADC_SampleDelay();
    __delay_us(3);

    // Start the conversion
    ADCON0bits.GO_nDONE = 1;

    // Wait for the conversion to finish
    while (ADCON0bits.GO_nDONE);

    // Conversion finished, return the result
    return ADC_GetConversionResult();
    
}

#endif
/**
 End of File
*/
