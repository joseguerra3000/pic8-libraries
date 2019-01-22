/* 
 * ADC Driver File for PIC12F683
 * 
 * @Author
 *      Jose Guerra Carmenate
 * 
 * @File 
 *      adc_12f683.h
 *
 * @Summary
 *      This is the driver implementation file for the ADC driver using PIC12F683 MCU.
 *      The ADC configuration is performed using the adc_12f683_config.h file
 * 
 * Created on 18 de enero de 2019, 1:21
 */

#include <xc.h>
#include <stdint.h>
#include "adc_12f683.h"

/* Implemented as macro */
/*
void ADC_Initialize(){
    ADCON0 = _ADC_RESOLUTION | _ADC_VOLTAGE_REF;
    ANSEL = _ADC_CONV_CLOCK;
    ADRESH = 0;
    ADRESL = 0;
}*/

/** See header file for more information **/
void ADC_SelectChannel( uint8_t channel ){
    ADCON0bits.CHS = channel;
    ADCON0bits.ADON = 1;
}


/* Implemented as macro */
/*
void ADC_StartConversion(){
    ADCON0bits.GO_nDONE = 1;
}*/


/* Implemented as macro */
/*
bool ADC_IsConversionDone(){
    return !(ADCON0bits.GO_nDONE);
}*/


/** See header file for more information **/
adc_result_t ADC_GetConversionResult( ){
#if (_ADC_RESOLUTION == _ADC_RESOLUTION_10BITS)
    return ((adc_result_t)((ADRESH << 8) + ADRESL));
#else
    return (ADRESH);
#endif
}


/** See header file for more information **/
adc_result_t ADC_GetConversion( uint8_t channel ){
    // Select Channel
    ADCON0bits.CHS = channel;
    // Turn on the ADC Module
    ADCON0bits.ADON = 1;
    // Wait Sample time
    __delay_us( ADC_ACQ_US_DELAY );
    
    // Start the conversion
    ADCON0bits.GO_nDONE = 1;
    
    // Wait for the conversion to finish
    //while (ADCON0bits.GO_nDONE);
    asm( "BTFSC ADCON0,0x01" );
    asm( "GOTO $-1" );
    
    // Conversion finished, return the result
#if (_ADC_RESOLUTION == _ADC_RESOLUTION_10BITS)
    return ((adc_result_t)((adc_result_t)(ADRESH << 8) + ADRESL));
#else
    return (ADRESH);
#endif
    
}
